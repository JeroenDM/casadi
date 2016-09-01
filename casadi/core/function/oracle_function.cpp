/*
 *    This file is part of CasADi.
 *
 *    CasADi -- A symbolic framework for dynamic optimization.
 *    Copyright (C) 2010-2014 Joel Andersson, Joris Gillis, Moritz Diehl,
 *                            K.U. Leuven. All rights reserved.
 *    Copyright (C) 2011-2014 Greg Horn
 *
 *    CasADi is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License as published by the Free Software Foundation; either
 *    version 3 of the License, or (at your option) any later version.
 *
 *    CasADi is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with CasADi; if not, write to the Free Software
 *    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */


#include "oracle_function.hpp"
#include "external.hpp"

#include <iostream>
#include <iomanip>

using namespace std;

namespace casadi {

  OracleFunction::OracleFunction(const std::string& name, const Function& oracle)
  : FunctionInternal(name), oracle_(oracle) {
  }

  OracleFunction::~OracleFunction() {
  }

  Options OracleFunction::options_
  = {{&FunctionInternal::options_},
     {{"monitor",
       {OT_STRINGVECTOR,
        "Set of user problem functions to be monitored"}},
      {"common_options",
       {OT_DICT,
        "Options for auto-generated functions"}},
      {"specific_options",
       {OT_DICT,
        "Options for specific auto-generated functions,"
        " overwriting the defaults from common_options. Nested dictionary."}}
    }
  };

  void OracleFunction::init(const Dict& opts) {

    FunctionInternal::init(opts);

    // Read options
    for (auto&& op : opts) {
      if (op.first=="common_options") {
        common_options_ = op.second;
      } else if (op.first=="specific_options") {
        specific_options_ = op.second;
        for (auto&& i : specific_options_) {
          casadi_assert_message(i.second.is_dict(),
            "specific_option must be a nested dictionary."
            " Type mismatch for entry '" + i.first+ "': "
            " got type " + i.second.get_description() + ".");
        }
      }
    }
  }

  void OracleFunction::finalize(const Dict& opts) {
    // Default options
    vector<string> monitor;

    // Read options
    for (auto&& op : opts) {
      if (op.first=="monitor") {
        monitor = op.second;
      }
    }

    // Set corresponding monitors
    for (auto&& it : all_functions_) {
      it.second.monitored = false;
    }
    for (const string& fname : monitor) {
      auto it = all_functions_.find(fname);
      if (it==all_functions_.end()) {
        casadi_warning("Ignoring monitor '" + fname + "'."
                       " Available functions: " + join(get_function()) + ".");
      } else {
        casadi_assert_warning(!it->second.monitored, "Duplicate monitor " + fname);
        it->second.monitored = true;
      }
    }

    // Check specific options
    for (auto&& i : specific_options_) {
      if (all_functions_.find(i.first)==all_functions_.end())
        casadi_warning("Ignoring specific_options entry '" + i.first+"'."
                       " Available functions: " + join(get_function()) + ".");
    }

    // Recursive call
    FunctionInternal::finalize(opts);
  }

  Function OracleFunction::create_function(const std::string& fname,
                                   const std::vector<std::string>& s_in,
                                   const std::vector<std::string>& s_out,
                                   const Function::AuxOut& aux) {
    // Retrieve specific set of options if available
    Dict specific_options;
    auto it = specific_options_.find(fname);
    if (it!=specific_options_.end()) specific_options = it->second;

    // Combine specific and common options
    Dict opt = combine(specific_options, common_options_);

    // Generate the function
    Function ret = oracle_.factory(fname, s_in, s_out, aux, opt);
    set_function(ret, fname, true);
    return ret;
  }

  void OracleFunction::
  set_function(const Function& fcn, const std::string& fname, bool jit) {
    casadi_assert_message(!has_function(fname), "Duplicate function " + fname);
    RegFun& r = all_functions_[fname];
    r.f = fcn;
    r.jit = jit;
    alloc(fcn);
  }

  int OracleFunction::
  calc_function(OracleMemory* m, const std::string& fcn,
                const double* const* arg) const {

    // Respond to a possible Crl+C signals
    InterruptHandler::check();

    // Get function
    const Function& f = get_function(fcn);

    // Is the function monitored?
    bool monitored = this->monitored(fcn);

    // Get statistics structure
    FStats& fstats = m->fstats.at(fcn);

    // Number of inputs and outputs
    int n_in = f.n_in(), n_out = f.n_out();

    // Prepare stats, start timer
    fstats.tic();

    // Input buffers
    if (arg) {
      fill_n(m->arg, n_in, nullptr);
      for (int i=0; i<n_in; ++i) m->arg[i] = *arg++;
    }

    // Print inputs nonzeros
    if (monitored) {
      userOut() << fcn << " input nonzeros: " << endl;
      for (int i=0; i<n_in; ++i) {
        userOut() << " " << i << " (" << f.name_in(i) << "): ";
        if (m->arg[i]) {
          // Print nonzeros
          userOut() << "[";
          for (int k=0; k<f.nnz_in(i); ++k) {
            if (k!=0) userOut() << ", ";
            userOut() << m->arg[i][k];
          }
          userOut() << "]" << endl;
        } else {
          // All zero input
          userOut() << "0" << endl;
        }
      }
    }

    // Evaluate memory-less
    try {
      f(m->arg, m->res, m->iw, m->w, 0);
    } catch(exception& ex) {
      // Fatal error
      userOut<true, PL_WARN>()
        << name() << ":" << fcn << " failed:" << ex.what() << endl;
      return 1;
    }

    // Print output nonzeros
    if (monitored) {
      userOut() << fcn << " output nonzeros: " << endl;
      for (int i=0; i<n_out; ++i) {
        userOut() << " " << i << " (" << f.name_out(i) << "): ";
        if (m->res[i]) {
          // Print nonzeros
          userOut() << "[";
          for (int k=0; k<f.nnz_out(i); ++k) {
            if (k!=0) userOut() << ", ";
            userOut() << m->res[i][k];
          }
          userOut() << "]" << endl;
        } else {
          // Ignored output
          userOut() << " N/A" << endl;
        }
      }
    }

    // Make sure not NaN or Inf
    for (int i=0; i<n_out; ++i) {
      if (!m->res[i]) continue;
      if (!all_of(m->res[i], m->res[i]+f.nnz_out(i), [](double v) { return isfinite(v);})) {
        userOut<true, PL_WARN>()
          << name() << ":" << fcn << " failed: NaN or Inf detected for output "
          << f.name_out(i) << endl;
        return -1;
      }
    }

    // Update stats
    fstats.toc();

    // Success
    return 0;
  }

  std::string OracleFunction::
  generate_dependencies(const std::string& fname, const Dict& opts) {
    CodeGenerator gen(fname, opts);
    gen.add(oracle_);
    for (auto&& e : all_functions_) {
      if (e.second.jit) gen.add(e.second.f);
    }
    return gen.generate();
  }

  void OracleFunction::jit_dependencies(const std::string& fname) {
    if (verbose())
      log("OracleFunction::jit_dependencies", "compiling to "+ fname+"'.");
    // JIT dependent functions
    compiler_ = Importer(generate_dependencies(fname, Dict()),
                         compilerplugin_, jit_options_);

    // Replace the Oracle functions with generated functions
    for (auto&& e : all_functions_) {
      if (verbose())
        log("OracleFunction::jit_dependencies",
            "loading '" + e.second.f.name() + "' from '" + fname + "'.");
      if (e.second.jit) e.second.f = external(e.second.f.name(), compiler_);
    }
  }

  void OracleFunction::expand() {
    oracle_ = oracle_.expand();
  }

  // Convert a float to a string of an exact length.
  // First it tries fixed precision, then falls back to exponential notation.
  //
  // todo(jaeandersson,jgillis): needs either review or unit tests
  // because it throws exceptions if it fail.
  std::string formatFloat(double x, int totalWidth, int maxPrecision, int fallbackPrecision) {
    std::ostringstream out0;
    out0 << fixed << setw(totalWidth) << setprecision(maxPrecision) << x;
    std::string ret0 = out0.str();
    if (ret0.length() == totalWidth) {
      return ret0;
    } else if (ret0.length() > totalWidth) {
      std::ostringstream out1;
      out1 << setw(totalWidth) << setprecision(fallbackPrecision) << x;
      std::string ret1 = out1.str();
      if (ret1.length() != totalWidth)
        casadi_error(
          "ipopt timing formatting fallback is bugged, sorry about that."
          << "expected " << totalWidth <<  " digits, but got " << ret1.length()
          << ", string: \"" << ret1 << "\", number: " << x);
      return ret1;
    } else {
      casadi_error("ipopt timing formatting is bugged, sorry about that.");
    }
  }

  void print_stats_line(int maxNameLen, std::string label,
      double n_call, double t_proc, double t_wall) {
    // Skip when not called
    if (n_call == 0) return;

    std::stringstream s;

    s
      << setw(maxNameLen) << label << " "
      << formatFloat(t_proc, 9, 3, 3) << " [s]  "
      << formatFloat(t_wall, 9, 3, 3) << " [s]";
    if (n_call == -1) {
      // things like main loop don't have # evals
      s << endl;
    } else {
      s
        << " "
        << setw(5) << n_call;
      if (n_call < 2) {
        s << endl;
      } else {
        // only print averages if there is more than 1 eval
        s
          << " "
          << formatFloat(1000.0*t_proc/n_call, 10, 2, 3) << " [ms]  "
          << formatFloat(1000.0*t_wall/n_call, 10, 2, 3) << " [ms]"
          << endl;
      }
    }
    userOut() << s.str();
  }

  void OracleFunction::print_fstats(const OracleMemory* m) const {

    size_t maxNameLen=0;

    // Retrieve all nlp keys
    std::vector<std::string> keys;
    std::vector<std::string> keys_other;
    for (auto &&s : m->fstats) {
      maxNameLen = max(s.first.size(), maxNameLen);
      if (s.first.find("nlp")!=std::string::npos) {
        keys.push_back(s.first);
      } else if (s.first.find("mainloop")==std::string::npos) {
        keys_other.push_back(s.first);
      } else {
        continue;
      }
    }

    maxNameLen = max(std::string("all previous").size(), maxNameLen);
    maxNameLen = max(std::string("solver").size(), maxNameLen);

    // Print header
    std::stringstream s;
    std::string blankName(maxNameLen, ' ');
    s
      << blankName
      << "      proc           wall      num           mean             mean"
      << endl << blankName
      << "      time           time     evals       proc time        wall time";
    userOut() << s.str() << endl;

    // Sort the keys according to order
    std::vector<std::string> keys_order0;
    std::vector<std::string> keys_order1;
    std::vector<std::string> keys_order2;
    for (auto k : keys) {
      if (k.find("hess")!=std::string::npos) {
        keys_order2.push_back(k);
        continue;
      }
      if (k.find("grad")!=std::string::npos ||
          k.find("jac")!=std::string::npos) {
        keys_order1.push_back(k);
        continue;
      }
      keys_order0.push_back(k);
    }

    // Print all NLP stats
    for (auto keys : {&keys_order0, &keys_order1, &keys_order2}) {
        std::sort(keys->begin(), keys->end());
        for (auto k : *keys) {
          const FStats& fs = m->fstats.at(k);
          print_stats_line(maxNameLen, k, fs.n_call, fs.t_proc, fs.t_wall);
        }
    }

    // Sum the previously printed stats
    double t_wall_all_previous = 0;
    double t_proc_all_previous = 0;
    for (auto k : keys) {
      const FStats& fs = m->fstats.at(k);
      t_proc_all_previous += fs.t_proc;
      t_wall_all_previous += fs.t_wall;
    }
    print_stats_line(maxNameLen, "all previous", -1, t_proc_all_previous, t_wall_all_previous);

    // Sort and show the remainder of keys
    std::sort(keys_other.begin(), keys_other.end());
    for (std::string k : keys_other) {
      const FStats& fs = m->fstats.at(k);
      print_stats_line(maxNameLen, k, fs.n_call, fs.t_proc, fs.t_wall);
      t_proc_all_previous += fs.t_proc;
      t_wall_all_previous += fs.t_wall;
    }

    // Show the mainloop stats
    const FStats& fs_mainloop = m->fstats.at("mainloop");
    if (fs_mainloop.n_call>0) {
      print_stats_line(maxNameLen, "solver", -1,
        fs_mainloop.t_proc-t_proc_all_previous, fs_mainloop.t_wall-t_wall_all_previous);
      print_stats_line(maxNameLen, "mainloop", -1, fs_mainloop.t_proc, fs_mainloop.t_wall);
    }

  }

  Dict OracleFunction::get_stats(void *mem) const {
    auto m = static_cast<OracleMemory*>(mem);

    // Add timing statistics
    Dict stats;
    for (auto&& s : m->fstats) {
      stats["n_call_" +s.first] = s.second.n_call;
      stats["t_wall_" +s.first] = s.second.t_wall;
      stats["t_proc_" +s.first] = s.second.t_proc;
    }
    return stats;
  }

  void OracleFunction::init_memory(void* mem) const {
    auto m = static_cast<OracleMemory*>(mem);

    // Create statistics
    for (auto&& e : all_functions_) {
      m->fstats[e.first] = FStats();
    }
  }

  void OracleFunction::set_temp(void* mem, const double** arg, double** res,
                            int* iw, double* w) const {
    auto m = static_cast<OracleMemory*>(mem);
    m->arg = arg;
    m->res = res;
    m->iw = iw;
    m->w = w;
  }

  std::vector<std::string> OracleFunction::get_function() const {
    std::vector<std::string> ret;
    ret.reserve(all_functions_.size());
    for (auto&& e : all_functions_) {
      ret.push_back(e.first);
    }
    return ret;
  }

  const Function& OracleFunction::get_function(const std::string &name) const {
    auto it = all_functions_.find(name);
    casadi_assert_message(it!=all_functions_.end(),
      "No function \"" + name + "\" in " + this->name());
    return it->second.f;
  }

  bool OracleFunction::monitored(const std::string &name) const {
    auto it = all_functions_.find(name);
    casadi_assert_message(it!=all_functions_.end(),
      "No function \"" + name + "\" in " + this->name());
    return it->second.monitored;
  }

  bool OracleFunction::has_function(const std::string& fname) const {
    return all_functions_.find(fname) != all_functions_.end();
  }


} // namespace casadi
