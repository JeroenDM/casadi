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

#include "cplex_interface.hpp"
#include "casadi/core/std_vector_tools.hpp"
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <vector>

#include "ilcplex/cplex.h"

namespace casadi {

  using namespace std;

  extern "C"
  int CASADI_CONIC_CPLEX_EXPORT
  casadi_register_conic_cplex(Conic::Plugin* plugin) {
    plugin->creator = CplexInterface::creator;
    plugin->name = "cplex";
    plugin->doc = CplexInterface::meta_doc.c_str();
    plugin->version = 31;
    return 0;
  }

  extern "C"
  void CASADI_CONIC_CPLEX_EXPORT casadi_load_conic_cplex() {
    Conic::registerPlugin(casadi_register_conic_cplex);
  }

  CplexInterface::CplexInterface(const std::string& name,
                                 const std::map<std::string, Sparsity>& st)
    : Conic(name, st) {
  }

  Options CplexInterface::options_
  = {{&Conic::options_},
     {{"cplex",
       {OT_DICT,
        "Options to be passed to CPLEX"}},
      {"qp_method",
       {OT_INT,
        "Determines which CPLEX algorithm to use."}},
      {"dump_to_file",
       {OT_BOOL,
        "Dumps QP to file in CPLEX format."}},
      {"dump_filename",
       {OT_STRING,
        "The filename to dump to."}},
      {"tol",
       {OT_DOUBLE,
        "Tolerance of solver"}},
      {"dep_check",
       {OT_INT,
        "Detect redundant constraints."}},
      {"warm_start",
       {OT_BOOL,
        "Use warm start with simplex methods (affects only the simplex methods)."}}
     }
  };

  void CplexInterface::init(const Dict& opts) {
    // Call the init method of the base class
    Conic::init(opts);

    // Default options
    qp_method_ = 0;
    dump_to_file_ = false;
    dump_filename_ = "qp.dat";
    tol_ = 1e-6;
    dep_check_ = 0;
    warm_start_ = false;

    // Read options
    for (auto&& op : opts) {
      if (op.first=="cplex") {
        opts_ = op.second;
      } else if (op.first=="qp_method") {
        qp_method_ = op.second;
      } else if (op.first=="dump_to_file") {
        dump_to_file_ = op.second;
      } else if (op.first=="dump_filename") {
        dump_filename_ = op.second.to_string();
      } else if (op.first=="tol") {
        tol_ = op.second;
      } else if (op.first=="dep_check") {
        dep_check_ = op.second;
      } else if (op.first=="warm_start") {
        warm_start_ = op.second;
      }
    }

    // Are we solving a mixed-integer problem?
    mip_ = !discrete_.empty()
      && find(discrete_.begin(), discrete_.end(), true)!=discrete_.end();

    // Type of variable
    if (mip_) {
      ctype_.resize(nx_);
      for (int i=0; i<nx_; ++i) {
        ctype_[i] = discrete_[i] ? 'I' : 'C';
      }
    }

    // Allocate work vectors
    alloc_w(nx_, true); // g
    alloc_w(nx_, true); // lbx
    alloc_w(nx_, true); // ubx
    alloc_w(na_, true); // lba
    alloc_w(na_, true); // uba
    alloc_w(nnz_in(CONIC_H), true); // H
    alloc_w(nnz_in(CONIC_A), true); // A
    alloc_w(nx_, true); // x
    alloc_w(nx_, true); // lam_x
    alloc_w(na_, true); // lam_a
  }

  void CplexInterface::init_memory(void* mem) const {
    auto m = static_cast<CplexMemory*>(mem);

    // Start CPLEX
    int status;
    casadi_assert(m->env==0);
    m->env = CPXopenCPLEX(&status);
    if (m->env==0) {
      char errmsg[CPXMESSAGEBUFSIZE];
      CPXgeterrorstring(m->env, status, errmsg);
      casadi_error(string("Cannot initialize CPLEX environment: ") + errmsg);
    }

    // Set parameters to their default values
    if (CPXsetdefaults(m->env)) {
      casadi_error("CPXsetdefaults failed");
    }

    // Enable output by default
    if (CPXsetintparam(m->env, CPX_PARAM_SCRIND, CPX_ON)) {
      casadi_error("Failure setting CPX_PARAM_SCRIND");
    }

    // Optimality tolerance
    if (CPXsetdblparam(m->env, CPX_PARAM_EPOPT, tol_)) {
      casadi_error("Failure setting CPX_PARAM_EPOPT");
    }

    // Feasibility tolerance
    if (CPXsetdblparam(m->env, CPX_PARAM_EPRHS, tol_)) {
      casadi_error("Failure setting CPX_PARAM_EPRHS");
    }

    // We start with barrier if crossover was chosen.
    if (CPXsetintparam(m->env, CPX_PARAM_QPMETHOD, qp_method_ == 7 ? 4 : qp_method_)) {
      casadi_error("Failure setting CPX_PARAM_QPMETHOD");
    }

    // Setting dependency check option
    if (CPXsetintparam(m->env, CPX_PARAM_DEPIND, dep_check_)) {
      casadi_error("Failure setting CPX_PARAM_DEPIND");
    }

    // Setting crossover algorithm
    if (qp_method_ == 7) {
      if (CPXsetintparam(m->env, CPX_PARAM_BARCROSSALG, 1)) {
        casadi_error("Failure setting CPX_PARAM_BARCROSSALG");
      }
    }

    // Set parameters
    for (auto&& op : opts_) {
      // Get parameter index
      int whichparam;
      if (CPXgetparamnum(m->env, op.first.c_str(), &whichparam)) {
        casadi_error("No such CPLEX parameter: " + op.first);
      }

      // Get type of parameter
      int paramtype;
      if (CPXgetparamtype(m->env, whichparam, &paramtype)) {
        casadi_error("CPXgetparamtype failed");
      }

      // Pass to CPLEX
      switch (paramtype) {
      case CPX_PARAMTYPE_NONE:
        casadi_error("CPX_PARAMTYPE_NONE unsupported");
        break;
      case CPX_PARAMTYPE_INT:
        status = CPXsetintparam(m->env, whichparam, op.second);
        break;
      case CPX_PARAMTYPE_DOUBLE:
        status = CPXsetdblparam(m->env, whichparam, op.second);
        break;
      case CPX_PARAMTYPE_STRING:
        status = CPXsetstrparam(m->env, whichparam,
                                static_cast<string>(op.second).c_str());
        break;
      case CPX_PARAMTYPE_LONG:
        status = CPXsetlongparam(m->env, whichparam,
                                 static_cast<CPXLONG>(static_cast<int>(op.second)));
        break;
        default:
          casadi_error("Unknown CPLEX parameter type (" << paramtype << ") for " + op.first);
      }
      // Error handling
      if (status) {
        casadi_error("Failure setting option " + op.first);
      }
    }

    // Doing allocation of CPLEX data
    // Objective is to be minimized
    m->objsen = CPX_MIN;

    // Allocation of data
    // Type of constraint
    m->sense.resize(na_);
    // Right-hand side of constraints
    m->rhs.resize(na_);
    // Range value for lower AND  upper bounded constraints
    m->rngval.resize(na_);
    // Basis for primal variables
    m->cstat.resize(nx_);
    m->rstat.resize(na_);

    // Matrix A, count the number of elements per column
    const Sparsity& A_sp = sparsity_in(CONIC_A);
    m->matcnt.resize(A_sp.size2());
    transform(A_sp.colind()+1, A_sp.colind() + A_sp.size2()+1, A_sp.colind(), m->matcnt.begin(),
              minus<int>());

    // Matrix H, count the number of elements per column
    const Sparsity& H_sp = sparsity_in(CONIC_H);
    m->qmatcnt.resize(H_sp.size2());
    transform(H_sp.colind()+1, H_sp.colind() + H_sp.size2()+1, H_sp.colind(), m->qmatcnt.begin(),
              minus<int>());

    // Create problem object
    casadi_assert(m->lp==0);
    m->lp = CPXcreateprob(m->env, &status, "QP from CasADi");
    casadi_assert_message(m->lp!=0, "CPXcreateprob failed");
  }

  void CplexInterface::
  eval(void* mem, const double** arg, double** res, int* iw, double* w) const {
    auto m = static_cast<CplexMemory*>(mem);

    if (inputs_check_) {
      checkInputs(arg[CONIC_LBX], arg[CONIC_UBX], arg[CONIC_LBA], arg[CONIC_UBA]);
    }

    // Get inputs
    double* g=w; w += nx_;
    casadi_copy(arg[CONIC_G], nx_, g);
    double* lbx=w; w += nx_;
    casadi_copy(arg[CONIC_LBX], nx_, lbx);
    double* ubx=w; w += nx_;
    casadi_copy(arg[CONIC_UBX], nx_, ubx);
    double* lba=w; w += na_;
    casadi_copy(arg[CONIC_LBA], na_, lba);
    double* uba=w; w += na_;
    casadi_copy(arg[CONIC_UBA], na_, uba);
    double* H=w; w += nnz_in(CONIC_H);
    casadi_copy(arg[CONIC_H], nnz_in(CONIC_H), H);
    double* A=w; w += nnz_in(CONIC_A);
    casadi_copy(arg[CONIC_A], nnz_in(CONIC_A), A);
    double* x=w; w += nx_;
    casadi_copy(arg[CONIC_X0], nx_, x);
    double* lam_x=w; w += nx_;
    casadi_copy(arg[CONIC_LAM_X0], nx_, lam_x);

    // Temporaries
    double* lam_a=w; w += na_;

    // We change method in crossover
    if (m->is_warm && qp_method_ == 7) {
      (void)CPXsetintparam(m->env, CPX_PARAM_QPMETHOD, 1);
    }

    for (int i = 0; i < na_; ++i) {
      // CPX_INFBOUND

      // Equality
      if (uba[i] - lba[i] < 1e-20) {
        m->sense[i] = 'E';
        m->rhs[i] = lba[i];
        m->rngval[i] = 0.;
      } else if (lba[i] < -CPX_INFBOUND) {
        // Ineq - no lower bound
        m->sense[i] = 'L';
        m->rhs[i] = uba[i];
        m->rngval[i] = 0.;
      } else if (uba[i] > CPX_INFBOUND) {
        // Ineq - no upper bound
        m->sense[i] = 'G';
        m->rhs[i] = lba[i];
        m->rngval[i] = 0.;
      } else { // Inew both upper and lower bounds
        m->sense[i] = 'R';
        m->rhs[i] = lba[i];
        m->rngval[i] = uba[i] - lba[i];
      }
    }

    // Copying objective, constraints, and bounds.
    const Sparsity& A_sp = sparsity_in(CONIC_A);
    const int* matbeg = A_sp.colind();
    const int* matind = A_sp.row();
    const double* matval = A;
    const double* obj = g;
    const double* lb = lbx;
    const double* ub = ubx;
    if (CPXcopylp(m->env, m->lp, nx_, na_, m->objsen, obj, get_ptr(m->rhs), get_ptr(m->sense),
                  matbeg, get_ptr(m->matcnt), matind, matval, lb, ub, get_ptr(m->rngval))) {
      casadi_error("CPXcopylp failed");
    }

    // Preparing coefficient matrix Q
    const Sparsity& H_sp = sparsity_in(CONIC_H);
    const int* qmatbeg = H_sp.colind();
    const int* qmatind = H_sp.row();
    const double* qmatval = H;
    if (CPXcopyquad(m->env, m->lp, qmatbeg, get_ptr(m->qmatcnt), qmatind, qmatval)) {
    }

    if (dump_to_file_) {
      CPXwriteprob(m->env, m->lp, dump_filename_.c_str(), "LP");
      casadi_error("CPXwriteprob failed");
    }

    // Warm-starting if possible
    if (qp_method_ != 0 && qp_method_ != 4 && m->is_warm) {
      // TODO(Joel): Initialize slacks and dual variables of bound constraints
      if (CPXcopystart(m->env, m->lp, get_ptr(m->cstat), get_ptr(m->rstat), x, 0, 0, lam_x)) {
        casadi_error("CPXcopystart failed");
      }
    } else {
      if (CPXcopystart(m->env, m->lp, 0, 0, x, 0, 0, lam_x)) {
        casadi_error("CPXcopystart failed");
      }
    }

    // Solution
    double f;
    std::vector<double> slack(na_);
    int solstat;

    if (mip_) {
      // Pass type of variables
      if (CPXcopyctype(m->env, m->lp, &ctype_[0])) {
        casadi_error("CPXcopyctype failed");
      }

      // Optimize
      if (CPXmipopt(m->env, m->lp)) {
        casadi_error("CPXmipopt failed");
      }

      // Get objective value
      if (CPXgetobjval(m->env, m->lp, &f)) {
        casadi_error("CPXgetobjval failed");
      }

      // Get primal solution
      int cur_numcols = CPXgetnumcols(m->env, m->lp);
      if (CPXgetx(m->env, m->lp, x, 0, cur_numcols-1)) {
        casadi_error("CPXgetx failed");
      }

      // Get slacks
      int cur_numrows = CPXgetnumrows(m->env, m->lp);
      if (CPXgetslack(m->env, m->lp, get_ptr(slack), 0, cur_numrows-1)) {
        casadi_error("CPXgetslack failed");
      }

      // Not a number as dual variables (not calculated with MIQP algorithm)
      casadi_fill(lam_a, na_, nan);
      casadi_fill(lam_x, nx_, nan);

    } else {
      // Optimize
      if (CPXqpopt(m->env, m->lp)) {
        casadi_error("CPXqpopt failed");
      }

      // Retrieving solution
      if (CPXsolution(m->env, m->lp, &solstat, &f, x, lam_a, get_ptr(slack), lam_x)) {
        casadi_error("CPXsolution failed");
      }
    }

    // Retrieving the basis
    if (qp_method_ != 0 && qp_method_ != 4) {
      (void)CPXgetbase(m->env, m->lp, get_ptr(m->cstat), get_ptr(m->rstat));
    }

    // Flip the sign of the multipliers
    casadi_scal(na_, -1., lam_a);
    casadi_scal(nx_, -1., lam_x);

    int solnstat = CPXgetstat(m->env, m->lp);
    stringstream errormsg;
    // NOTE: Why not print directly to userOut() and userOut<true, PL_WARN>()?
    if (verbose()) {
      if (solnstat == CPX_STAT_OPTIMAL) {
        errormsg << "CPLEX: solution status: Optimal solution found.\n";
      } else if (solnstat == CPX_STAT_UNBOUNDED) {
        errormsg << "CPLEX: solution status: Model is unbounded\n";
      } else if (solnstat == CPX_STAT_INFEASIBLE) {
        errormsg << "CPLEX: solution status: Model is infeasible\n";
      } else if (solnstat == CPX_STAT_INForUNBD) {
        errormsg << "CPLEX: solution status: Model is infeasible or unbounded\n";
      } else if (solnstat == CPX_STAT_OPTIMAL_INFEAS) {
        errormsg << "CPLEX: solution status: Optimal solution "
            "is available but with infeasibilities\n";
      } else if (solnstat == CPX_STAT_NUM_BEST) {
        errormsg << "CPLEX: solution status: Solution available, but not "
            "proved optimal due to numeric difficulties.\n";
      } else if (solnstat == CPX_STAT_FIRSTORDER) {
        errormsg << "CPLEX: solution status: Solution satisfies first-order optimality "
            "conditions, but is not necessarily globally optimal.\n";
      } else {
        errormsg << "CPLEX: solution status: " <<  solnstat << "\n";
      }
      userOut() << errormsg.str();

      // Printing basis condition number
      //double cn;
      //status = CPXgetdblquality(m->env, m->lp, &cn, CPX_KAPPA);
      //userOut() << "CPLEX: Basis condition number: " << cn << endl;
    }
    if (solnstat != CPX_STAT_OPTIMAL) {
      //    throw CasadiException(errormsg.c_str());
    }

    // Next time we warm start
    if (warm_start_) {
      m->is_warm = true;
    }

    // Get the outputs
    if (res[CONIC_COST]) *res[CONIC_COST] = f;
    casadi_copy(lam_a, na_, res[CONIC_LAM_A]);
    casadi_copy(lam_x, nx_, res[CONIC_LAM_X]);
    casadi_copy(x, nx_, res[CONIC_X]);
  }

  CplexInterface::~CplexInterface() {
    clear_memory();
  }

  CplexMemory::CplexMemory() {
    // Setting warm-start flag
    this->is_warm = false;

    // Set pointer to zero to avoid deleting a nonexisting instance
    this->env = 0;
    this->lp = 0;
  }

  CplexMemory::~CplexMemory() {
    // Return flag
    int status;

    // Only free if Cplex problem if it has been allocated
    if (this->lp!=0) {
      status = CPXfreeprob(this->env, &this->lp);
      if (status!=0) {
        userOut<true, PL_WARN>() << "CPXfreeprob failed, error code " << status << ".\n";
      }
      this->lp = 0;
    }

    // Closing down license
    if (this->env!=0) {
      status = CPXcloseCPLEX(&this->env);
      if (status!=0) {
        userOut<true, PL_WARN>() << "CPXcloseCPLEX failed, error code " << status << ".\n";
      }
      this->env = 0;
    }
  }

} // end namespace casadi
