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


#ifndef CASADI_QP_TO_NLP_HPP
#define CASADI_QP_TO_NLP_HPP

#include "casadi/core/function/conic_impl.hpp"
#include <casadi/solvers/conic/casadi_conic_nlpsol_export.h>


/** \defgroup plugin_Conic_nlpsol
 
   Solve QPs using an Nlpsol
   Use the 'nlpsol' option to specify the NLP solver to use.
*/

/** \pluginsection{Conic,nlpsol} */

/// \cond INTERNAL
namespace casadi {

  /** \brief \pluginbrief{Conic,nlpsol}

      @copydoc Conic_doc
      @copydoc plugin_Conic_nlpsol

      \author Joris Gillis
      \date 2011
  */
  class CASADI_CONIC_NLPSOL_EXPORT QpToNlp : public Conic {
  public:
    /** \brief  Create a new Solver */
    explicit QpToNlp(const std::string& name,
                     const std::map<std::string, Sparsity> &st);

    /** \brief  Create a new QP Solver */
    static Conic* creator(const std::string& name,
                          const std::map<std::string, Sparsity>& st) {
      return new QpToNlp(name, st);
    }

    /** \brief  Destructor */
    virtual ~QpToNlp();

    // Get name of the plugin
    virtual const char* plugin_name() const { return "nlpsol";}

    ///@{
    /** \brief Options */
    static Options options_;
    virtual const Options& get_options() const { return options_;}
    ///@}

    /** \brief  Initialize */
    virtual void init(const Dict& opts);

    virtual void eval(void* mem, const double** arg, double** res, int* iw, double* w) const;

    /// A documentation string
    static const std::string meta_doc;

    /// Solve with
    Function solver_;
  };

} // namespace casadi
/// \endcond
#endif // CASADI_QP_TO_NLP_HPP
