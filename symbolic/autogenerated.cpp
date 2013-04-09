/*
 *    This file is part of CasADi.
 *
 *    CasADi -- A symbolic framework for dynamic optimization.
 *    Copyright (C) 2010 by Joel Andersson, Moritz Diehl, K.U.Leuven. All rights reserved.
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

/** All edits to this file will be lost - autogenerated by misc/autogencode.py */
#include "autogenerated.hpp"
#include <string>
namespace CasADi{

std::string describeInput(InputOutputScheme scheme, int i) {
  std::stringstream ss;
  ss << "Input argument #" << i;
  if (scheme!=SCHEME_unknown) {
    ss << " (" << getSchemeEntryEnumName(scheme,i) <<  " aka '" << getSchemeEntryName(scheme,i) << "')";
  }
  return ss.str();
}

std::string describeOutput(InputOutputScheme scheme, int i) {
  std::stringstream ss;
  ss << "Output argument #" << i;
  if (scheme!=SCHEME_unknown) {
    ss << " (" << getSchemeEntryEnumName(scheme,i) <<  " aka '" << getSchemeEntryName(scheme,i) << "')";
  }
  return ss.str();
}
std::string getSchemeName(InputOutputScheme scheme) {
  switch (scheme) {
    case SCHEME_ACADO_Input: return "ACADO_Input";
    case SCHEME_ACADO_Output: return "ACADO_Output";
    case SCHEME_ACADO_FCN_Input: return "ACADO_FCN_Input";
    case SCHEME_ControlledDAEInput: return "ControlledDAEInput";
    case SCHEME_ControlSimulatorInput: return "ControlSimulatorInput";
    case SCHEME_DAEInput: return "DAEInput";
    case SCHEME_DAEOutput: return "DAEOutput";
    case SCHEME_RDAEInput: return "RDAEInput";
    case SCHEME_RDAEOutput: return "RDAEOutput";
    case SCHEME_IntegratorInput: return "IntegratorInput";
    case SCHEME_IntegratorOutput: return "IntegratorOutput";
    case SCHEME_NLPInput: return "NLPInput";
    case SCHEME_NLPOutput: return "NLPOutput";
    case SCHEME_MayerInput: return "MayerInput";
    case SCHEME_OCPInput: return "OCPInput";
    case SCHEME_OCPOutput: return "OCPOutput";
    case SCHEME_QPInput: return "QPInput";
    case SCHEME_QPOutput: return "QPOutput";
    case SCHEME_SDPInput: return "SDPInput";
    case SCHEME_SDPOutput: return "SDPOutput";
    case SCHEME_unknown: return "unknown";
}
}
std::string getSchemeEntryNames(InputOutputScheme scheme) {
  switch (scheme) {
    case SCHEME_ACADO_Input: return "x_guess, u_guess, p_guess, lbx, ubx, lbx0, ubx0, lbxf, ubxf, lbu, ubu, lbp, ubp, lbc, ubc, lbr, ubr";
    case SCHEME_ACADO_Output: return "x_opt, u_opt, p_opt, cost";
    case SCHEME_ACADO_FCN_Input: return "t, xd, xa, u, p, xdot";
    case SCHEME_ControlledDAEInput: return "t, x, z, p, u, u_interp, x_major, t0, tf";
    case SCHEME_ControlSimulatorInput: return "x0, p, u";
    case SCHEME_DAEInput: return "x, z, p, t";
    case SCHEME_DAEOutput: return "ode, alg, quad";
    case SCHEME_RDAEInput: return "rx, rz, rp, x, z, p, t";
    case SCHEME_RDAEOutput: return "ode, alg, quad";
    case SCHEME_IntegratorInput: return "x0, p, rx0, rp";
    case SCHEME_IntegratorOutput: return "xf, qf, rxf, rqf";
    case SCHEME_NLPInput: return "x0, lbx, ubx, lbg, ubg, lam_g0, p";
    case SCHEME_NLPOutput: return "x, f, lam_g, lam_x, lam_p, g";
    case SCHEME_MayerInput: return "x, p";
    case SCHEME_OCPInput: return "lbx, ubx, x_init, lbu, ubu, u_init, lbp, ubp, p_init, lbh, ubh, lbg, ubg";
    case SCHEME_OCPOutput: return "x_opt, u_opt, p_opt, cost";
    case SCHEME_QPInput: return "h, g, a, lba, uba, lbx, ubx, x_init, lambda_init";
    case SCHEME_QPOutput: return "primal, cost, lambda_a, lambda_x";
    case SCHEME_SDPInput: return "a, b, c";
    case SCHEME_SDPOutput: return "primal, p, dual, primal_cost, dual_cost";
    case SCHEME_unknown: return "not available";
}
}
std::string getSchemeEntryName(InputOutputScheme scheme, int i) {
  switch (scheme) {
    case SCHEME_ACADO_Input: 
      if(i==0) return "x_guess";
      if(i==1) return "u_guess";
      if(i==2) return "p_guess";
      if(i==3) return "lbx";
      if(i==4) return "ubx";
      if(i==5) return "lbx0";
      if(i==6) return "ubx0";
      if(i==7) return "lbxf";
      if(i==8) return "ubxf";
      if(i==9) return "lbu";
      if(i==10) return "ubu";
      if(i==11) return "lbp";
      if(i==12) return "ubp";
      if(i==13) return "lbc";
      if(i==14) return "ubc";
      if(i==15) return "lbr";
      if(i==16) return "ubr";
      casadi_error("getSchemeEntryName: supplied number is out of range. ACADO_Input has only 17 entries: ('ACADO_Input', 'x_guess, u_guess, p_guess, lbx, ubx, lbx0, ubx0, lbxf, ubxf, lbu, ubu, lbp, ubp, lbc, ubc, lbr, ubr')");
      break;
    case SCHEME_ACADO_Output: 
      if(i==0) return "x_opt";
      if(i==1) return "u_opt";
      if(i==2) return "p_opt";
      if(i==3) return "cost";
      casadi_error("getSchemeEntryName: supplied number is out of range. ACADO_Output has only 4 entries: ('ACADO_Output', 'x_opt, u_opt, p_opt, cost')");
      break;
    case SCHEME_ACADO_FCN_Input: 
      if(i==0) return "t";
      if(i==1) return "xd";
      if(i==2) return "xa";
      if(i==3) return "u";
      if(i==4) return "p";
      if(i==5) return "xdot";
      casadi_error("getSchemeEntryName: supplied number is out of range. ACADO_FCN_Input has only 6 entries: ('ACADO_FCN_Input', 't, xd, xa, u, p, xdot')");
      break;
    case SCHEME_ControlledDAEInput: 
      if(i==0) return "t";
      if(i==1) return "x";
      if(i==2) return "z";
      if(i==3) return "p";
      if(i==4) return "u";
      if(i==5) return "u_interp";
      if(i==6) return "x_major";
      if(i==7) return "t0";
      if(i==8) return "tf";
      casadi_error("getSchemeEntryName: supplied number is out of range. ControlledDAEInput has only 9 entries: ('ControlledDAEInput', 't, x, z, p, u, u_interp, x_major, t0, tf')");
      break;
    case SCHEME_ControlSimulatorInput: 
      if(i==0) return "x0";
      if(i==1) return "p";
      if(i==2) return "u";
      casadi_error("getSchemeEntryName: supplied number is out of range. ControlSimulatorInput has only 3 entries: ('ControlSimulatorInput', 'x0, p, u')");
      break;
    case SCHEME_DAEInput: 
      if(i==0) return "x";
      if(i==1) return "z";
      if(i==2) return "p";
      if(i==3) return "t";
      casadi_error("getSchemeEntryName: supplied number is out of range. DAEInput has only 4 entries: ('DAEInput', 'x, z, p, t')");
      break;
    case SCHEME_DAEOutput: 
      if(i==0) return "ode";
      if(i==1) return "alg";
      if(i==2) return "quad";
      casadi_error("getSchemeEntryName: supplied number is out of range. DAEOutput has only 3 entries: ('DAEOutput', 'ode, alg, quad')");
      break;
    case SCHEME_RDAEInput: 
      if(i==0) return "rx";
      if(i==1) return "rz";
      if(i==2) return "rp";
      if(i==3) return "x";
      if(i==4) return "z";
      if(i==5) return "p";
      if(i==6) return "t";
      casadi_error("getSchemeEntryName: supplied number is out of range. RDAEInput has only 7 entries: ('RDAEInput', 'rx, rz, rp, x, z, p, t')");
      break;
    case SCHEME_RDAEOutput: 
      if(i==0) return "ode";
      if(i==1) return "alg";
      if(i==2) return "quad";
      casadi_error("getSchemeEntryName: supplied number is out of range. RDAEOutput has only 3 entries: ('RDAEOutput', 'ode, alg, quad')");
      break;
    case SCHEME_IntegratorInput: 
      if(i==0) return "x0";
      if(i==1) return "p";
      if(i==2) return "rx0";
      if(i==3) return "rp";
      casadi_error("getSchemeEntryName: supplied number is out of range. IntegratorInput has only 4 entries: ('IntegratorInput', 'x0, p, rx0, rp')");
      break;
    case SCHEME_IntegratorOutput: 
      if(i==0) return "xf";
      if(i==1) return "qf";
      if(i==2) return "rxf";
      if(i==3) return "rqf";
      casadi_error("getSchemeEntryName: supplied number is out of range. IntegratorOutput has only 4 entries: ('IntegratorOutput', 'xf, qf, rxf, rqf')");
      break;
    case SCHEME_NLPInput: 
      if(i==0) return "x0";
      if(i==1) return "lbx";
      if(i==2) return "ubx";
      if(i==3) return "lbg";
      if(i==4) return "ubg";
      if(i==5) return "lam_g0";
      if(i==6) return "p";
      casadi_error("getSchemeEntryName: supplied number is out of range. NLPInput has only 7 entries: ('NLPInput', 'x0, lbx, ubx, lbg, ubg, lam_g0, p')");
      break;
    case SCHEME_NLPOutput: 
      if(i==0) return "x";
      if(i==1) return "f";
      if(i==2) return "lam_g";
      if(i==3) return "lam_x";
      if(i==4) return "lam_p";
      if(i==5) return "g";
      casadi_error("getSchemeEntryName: supplied number is out of range. NLPOutput has only 6 entries: ('NLPOutput', 'x, f, lam_g, lam_x, lam_p, g')");
      break;
    case SCHEME_MayerInput: 
      if(i==0) return "x";
      if(i==1) return "p";
      casadi_error("getSchemeEntryName: supplied number is out of range. MayerInput has only 2 entries: ('MayerInput', 'x, p')");
      break;
    case SCHEME_OCPInput: 
      if(i==0) return "lbx";
      if(i==1) return "ubx";
      if(i==2) return "x_init";
      if(i==3) return "lbu";
      if(i==4) return "ubu";
      if(i==5) return "u_init";
      if(i==6) return "lbp";
      if(i==7) return "ubp";
      if(i==8) return "p_init";
      if(i==9) return "lbh";
      if(i==10) return "ubh";
      if(i==11) return "lbg";
      if(i==12) return "ubg";
      casadi_error("getSchemeEntryName: supplied number is out of range. OCPInput has only 13 entries: ('OCPInput', 'lbx, ubx, x_init, lbu, ubu, u_init, lbp, ubp, p_init, lbh, ubh, lbg, ubg')");
      break;
    case SCHEME_OCPOutput: 
      if(i==0) return "x_opt";
      if(i==1) return "u_opt";
      if(i==2) return "p_opt";
      if(i==3) return "cost";
      casadi_error("getSchemeEntryName: supplied number is out of range. OCPOutput has only 4 entries: ('OCPOutput', 'x_opt, u_opt, p_opt, cost')");
      break;
    case SCHEME_QPInput: 
      if(i==0) return "h";
      if(i==1) return "g";
      if(i==2) return "a";
      if(i==3) return "lba";
      if(i==4) return "uba";
      if(i==5) return "lbx";
      if(i==6) return "ubx";
      if(i==7) return "x_init";
      if(i==8) return "lambda_init";
      casadi_error("getSchemeEntryName: supplied number is out of range. QPInput has only 9 entries: ('QPInput', 'h, g, a, lba, uba, lbx, ubx, x_init, lambda_init')");
      break;
    case SCHEME_QPOutput: 
      if(i==0) return "primal";
      if(i==1) return "cost";
      if(i==2) return "lambda_a";
      if(i==3) return "lambda_x";
      casadi_error("getSchemeEntryName: supplied number is out of range. QPOutput has only 4 entries: ('QPOutput', 'primal, cost, lambda_a, lambda_x')");
      break;
    case SCHEME_SDPInput: 
      if(i==0) return "a";
      if(i==1) return "b";
      if(i==2) return "c";
      casadi_error("getSchemeEntryName: supplied number is out of range. SDPInput has only 3 entries: ('SDPInput', 'a, b, c')");
      break;
    case SCHEME_SDPOutput: 
      if(i==0) return "primal";
      if(i==1) return "p";
      if(i==2) return "dual";
      if(i==3) return "primal_cost";
      if(i==4) return "dual_cost";
      casadi_error("getSchemeEntryName: supplied number is out of range. SDPOutput has only 5 entries: ('SDPOutput', 'primal, p, dual, primal_cost, dual_cost')");
      break;
}
}
std::string getSchemeEntryDoc(InputOutputScheme scheme, int i) {
  switch (scheme) {
    case SCHEME_ACADO_Input: 
      if(i==0) return "Initial guess for x (default: 0)";
      if(i==1) return "Initial guess for u (default: 0)";
      if(i==2) return "Initial guess for p (default: 0)";
      if(i==3) return "Lower bound on x (default:  -infinity)";
      if(i==4) return "Upper bound on x (default:  infinity)";
      if(i==5) return "Lower bound on x0 (default:  -infinity)";
      if(i==6) return "Upper bound on x0 (default:  infinity)";
      if(i==7) return "Lower bound on xf (default:  -infinity)";
      if(i==8) return "Upper bound on xf (default:  infinity)";
      if(i==9) return "Lower bound on u (default:  -infinity)";
      if(i==10) return "Upper bound on u (default:  infinity)";
      if(i==11) return "Lower bound on p (default:  -infinity)";
      if(i==12) return "Upper bound on p (default:  infinity)";
      if(i==13) return "Lower bound on the path constraint function (default:  -infinity)";
      if(i==14) return "Upper bound on the path constraint function (default:  infinity)";
      if(i==15) return "Lower bound on the initial constraint function (default:  0)";
      if(i==16) return "Upper bound on the initial constraint function (default:  0)";
      casadi_error("getSchemeEntryDoc: supplied number is out of range. ACADO_Input has only 17 entries: ('ACADO_Input', 'x_guess, u_guess, p_guess, lbx, ubx, lbx0, ubx0, lbxf, ubxf, lbu, ubu, lbp, ubp, lbc, ubc, lbr, ubr')");
      break;
    case SCHEME_ACADO_Output: 
      if(i==0) return "Optimal states";
      if(i==1) return "Optimal control inputs";
      if(i==2) return "Optimal parameters";
      if(i==3) return "Optimal cost";
      casadi_error("getSchemeEntryDoc: supplied number is out of range. ACADO_Output has only 4 entries: ('ACADO_Output', 'x_opt, u_opt, p_opt, cost')");
      break;
    case SCHEME_ACADO_FCN_Input: 
      if(i==0) return "Time";
      if(i==1) return "Differential state";
      if(i==2) return "Algebraic state";
      if(i==3) return "Control input";
      if(i==4) return "Parameter";
      if(i==5) return "Differential state derivative";
      casadi_error("getSchemeEntryDoc: supplied number is out of range. ACADO_FCN_Input has only 6 entries: ('ACADO_FCN_Input', 't, xd, xa, u, p, xdot')");
      break;
    case SCHEME_ControlledDAEInput: 
      if(i==0) return "Global physical time. (1-by-1)";
      if(i==1) return "State vector (dimension nx-by-1). Should have same amount of non-zeros as DAEOutput:DAE_RES";
      if(i==2) return "Algebraic state vector (dimension np-by-1).";
      if(i==3) return "Parameter vector (dimension np-by-1).";
      if(i==4) return "Control vector (dimension nu-by-1).";
      if(i==5) return "Control vector, linearly interpolated (dimension nu-by-1).";
      if(i==6) return "State vector (dimension nx-by-1) at the last major time-step";
      if(i==7) return "Time at start of control interval (1-by-1)";
      if(i==8) return "Time at end of control interval (1-by-1)";
      casadi_error("getSchemeEntryDoc: supplied number is out of range. ControlledDAEInput has only 9 entries: ('ControlledDAEInput', 't, x, z, p, u, u_interp, x_major, t0, tf')");
      break;
    case SCHEME_ControlSimulatorInput: 
      if(i==0) return "Differential or algebraic state at t0  (dimension nx-by-1)";
      if(i==1) return "Parameters that are fixed over the entire horizon  (dimension np-by-1)";
      if(i==2) return "Parameters that change over the integration intervals (dimension (ns-1)-by-nu)";
      casadi_error("getSchemeEntryDoc: supplied number is out of range. ControlSimulatorInput has only 3 entries: ('ControlSimulatorInput', 'x0, p, u')");
      break;
    case SCHEME_DAEInput: 
      if(i==0) return "Differential state";
      if(i==1) return "Algebraic state";
      if(i==2) return "Parameter";
      if(i==3) return "Explicit time dependence";
      casadi_error("getSchemeEntryDoc: supplied number is out of range. DAEInput has only 4 entries: ('DAEInput', 'x, z, p, t')");
      break;
    case SCHEME_DAEOutput: 
      if(i==0) return "Right hand side of the implicit ODE";
      if(i==1) return "Right hand side of algebraic equations";
      if(i==2) return "Right hand side of quadratures equations";
      casadi_error("getSchemeEntryDoc: supplied number is out of range. DAEOutput has only 3 entries: ('DAEOutput', 'ode, alg, quad')");
      break;
    case SCHEME_RDAEInput: 
      if(i==0) return "Backward differential state";
      if(i==1) return "Backward algebraic state";
      if(i==2) return "Backward  parameter vector";
      if(i==3) return "Forward differential state";
      if(i==4) return "Forward algebraic state";
      if(i==5) return "Parameter vector";
      if(i==6) return "Explicit time dependence";
      casadi_error("getSchemeEntryDoc: supplied number is out of range. RDAEInput has only 7 entries: ('RDAEInput', 'rx, rz, rp, x, z, p, t')");
      break;
    case SCHEME_RDAEOutput: 
      if(i==0) return "Right hand side of ODE.";
      if(i==1) return "Right hand side of algebraic equations.";
      if(i==2) return "Right hand side of quadratures.";
      casadi_error("getSchemeEntryDoc: supplied number is out of range. RDAEOutput has only 3 entries: ('RDAEOutput', 'ode, alg, quad')");
      break;
    case SCHEME_IntegratorInput: 
      if(i==0) return "Differential state at the initial time";
      if(i==1) return "Parameters";
      if(i==2) return "Backward differential state at the final time";
      if(i==3) return "Backward parameter vector";
      casadi_error("getSchemeEntryDoc: supplied number is out of range. IntegratorInput has only 4 entries: ('IntegratorInput', 'x0, p, rx0, rp')");
      break;
    case SCHEME_IntegratorOutput: 
      if(i==0) return "Differential state at the final time";
      if(i==1) return "Quadrature state at the final time";
      if(i==2) return "Backward differential state at the initial time";
      if(i==3) return "Backward quadrature state at the initial time";
      casadi_error("getSchemeEntryDoc: supplied number is out of range. IntegratorOutput has only 4 entries: ('IntegratorOutput', 'xf, qf, rxf, rqf')");
      break;
    case SCHEME_NLPInput: 
      if(i==0) return "Decision variables initial guess (nx x 1) ";
      if(i==1) return "Decision variables lower bound (nx x 1), default -inf";
      if(i==2) return "Decision variables upper bound (nx x 1), default +inf";
      if(i==3) return "Constraints lower bound (ng x 1), default -inf";
      if(i==4) return "Constraints upper bound (ng x 1), default +inf";
      if(i==5) return "Lagrange multipliers associated with G, initial guess (ng x 1)";
      if(i==6) return "Parameters on which the objective and constraints might depend (np x 1)";
      casadi_error("getSchemeEntryDoc: supplied number is out of range. NLPInput has only 7 entries: ('NLPInput', 'x0, lbx, ubx, lbg, ubg, lam_g0, p')");
      break;
    case SCHEME_NLPOutput: 
      if(i==0) return "Decision variables for optimal solution (nx x 1)";
      if(i==1) return "Objective/cost function for optimal solution (1 x 1)";
      if(i==2) return "Lagrange multipliers associated with G at the solution (ng x 1)";
      if(i==3) return "Lagrange multipliers associated with bounds on X at the solution (nx x 1)";
      if(i==4) return "Lagrange multipliers associated with the parameters (np x 1)";
      if(i==5) return "The constraints evaluated at the optimal solution (ng x 1)";
      casadi_error("getSchemeEntryDoc: supplied number is out of range. NLPOutput has only 6 entries: ('NLPOutput', 'x, f, lam_g, lam_x, lam_p, g')");
      break;
    case SCHEME_MayerInput: 
      if(i==0) return "States at the end of integration (nx x 1)";
      if(i==1) return "Problem parameters (np x 1)";
      casadi_error("getSchemeEntryDoc: supplied number is out of range. MayerInput has only 2 entries: ('MayerInput', 'x, p')");
      break;
    case SCHEME_OCPInput: 
      if(i==0) return "States lower bounds (nx x (ns+1))";
      if(i==1) return "States upper bounds (nx x (ns+1))";
      if(i==2) return "States initial guess (nx x (ns+1))";
      if(i==3) return "Controls lower bounds (nu x ns)";
      if(i==4) return "Controls upper bounds (nu x ns)";
      if(i==5) return "Controls initial guess (nu x ns)";
      if(i==6) return "Parameters lower bounds (np x 1)";
      if(i==7) return "Parameters upper bounds (np x 1)";
      if(i==8) return "Parameters initial guess (np x 1)";
      if(i==9) return "Point constraint lower bound (nh x (ns+1))";
      if(i==10) return "Point constraint upper bound (nh x (ns+1))";
      if(i==11) return "Lower bound for the coupling constraints";
      if(i==12) return "Upper bound for the coupling constraints";
      casadi_error("getSchemeEntryDoc: supplied number is out of range. OCPInput has only 13 entries: ('OCPInput', 'lbx, ubx, x_init, lbu, ubu, u_init, lbp, ubp, p_init, lbh, ubh, lbg, ubg')");
      break;
    case SCHEME_OCPOutput: 
      if(i==0) return "Optimal state trajectory";
      if(i==1) return "Optimal control trajectory";
      if(i==2) return "Optimal parameters";
      if(i==3) return "Objective/cost function for optimal solution (1 x 1)";
      casadi_error("getSchemeEntryDoc: supplied number is out of range. OCPOutput has only 4 entries: ('OCPOutput', 'x_opt, u_opt, p_opt, cost')");
      break;
    case SCHEME_QPInput: 
      if(i==0) return "The square matrix H: sparse, (nx x nx). Only the lower triangular part is actually used. The matrix is assumed to be symmetrical.";
      if(i==1) return "The vector G: dense,  (nx x 1)";
      if(i==2) return "The matrix A: sparse, (nc x nx) - product with x must be dense.";
      if(i==3) return "dense, (nc x 1)";
      if(i==4) return "dense, (nc x 1)";
      if(i==5) return "dense, (nx x 1)";
      if(i==6) return "dense, (nx x 1)";
      if(i==7) return "dense, (nx x 1)";
      if(i==8) return "dense";
      casadi_error("getSchemeEntryDoc: supplied number is out of range. QPInput has only 9 entries: ('QPInput', 'h, g, a, lba, uba, lbx, ubx, x_init, lambda_init')");
      break;
    case SCHEME_QPOutput: 
      if(i==0) return "The primal solution";
      if(i==1) return "The optimal cost";
      if(i==2) return "The dual solution corresponding to linear bounds";
      if(i==3) return "The dual solution corresponding to simple bounds";
      casadi_error("getSchemeEntryDoc: supplied number is out of range. QPOutput has only 4 entries: ('QPOutput', 'primal, cost, lambda_a, lambda_x')");
      break;
    case SCHEME_SDPInput: 
      if(i==0) return "The vertical stack of all matrices A_i: ( nm x n)";
      if(i==1) return "The vector b: ( m x 1)";
      if(i==2) return "The matrix C: ( n x n)";
      casadi_error("getSchemeEntryDoc: supplied number is out of range. SDPInput has only 3 entries: ('SDPInput', 'a, b, c')");
      break;
    case SCHEME_SDPOutput: 
      if(i==0) return "The primal solution (m x 1) - may be used as initial guess";
      if(i==1) return "The solution P (n x n) - may be used as initial guess";
      if(i==2) return "The dual solution (n x n) - may be used as initial guess";
      if(i==3) return "The primal optimal cost (1 x 1)";
      if(i==4) return "The dual optimal cost (1 x 1)";
      casadi_error("getSchemeEntryDoc: supplied number is out of range. SDPOutput has only 5 entries: ('SDPOutput', 'primal, p, dual, primal_cost, dual_cost')");
      break;
    case SCHEME_unknown: return "none";
}
}
std::string getSchemeEntryEnumName(InputOutputScheme scheme, int i) {
  switch (scheme) {
    case SCHEME_ACADO_Input: 
      if(i==0) return "ACADO_X_GUESS";
      if(i==1) return "ACADO_U_GUESS";
      if(i==2) return "ACADO_P_GUESS";
      if(i==3) return "ACADO_LBX";
      if(i==4) return "ACADO_UBX";
      if(i==5) return "ACADO_LBX0";
      if(i==6) return "ACADO_UBX0";
      if(i==7) return "ACADO_LBXF";
      if(i==8) return "ACADO_UBXF";
      if(i==9) return "ACADO_LBU";
      if(i==10) return "ACADO_UBU";
      if(i==11) return "ACADO_LBP";
      if(i==12) return "ACADO_UBP";
      if(i==13) return "ACADO_LBC";
      if(i==14) return "ACADO_UBC";
      if(i==15) return "ACADO_LBR";
      if(i==16) return "ACADO_UBR";
      casadi_error("getSchemeEntryEnumName: supplied number is out of range. ACADO_Input has only 17 entries: ('ACADO_Input', 'x_guess, u_guess, p_guess, lbx, ubx, lbx0, ubx0, lbxf, ubxf, lbu, ubu, lbp, ubp, lbc, ubc, lbr, ubr')");
      break;
    case SCHEME_ACADO_Output: 
      if(i==0) return "ACADO_X_OPT";
      if(i==1) return "ACADO_U_OPT";
      if(i==2) return "ACADO_P_OPT";
      if(i==3) return "ACADO_COST";
      casadi_error("getSchemeEntryEnumName: supplied number is out of range. ACADO_Output has only 4 entries: ('ACADO_Output', 'x_opt, u_opt, p_opt, cost')");
      break;
    case SCHEME_ACADO_FCN_Input: 
      if(i==0) return "ACADO_FCN_T";
      if(i==1) return "ACADO_FCN_XD";
      if(i==2) return "ACADO_FCN_XA";
      if(i==3) return "ACADO_FCN_U";
      if(i==4) return "ACADO_FCN_P";
      if(i==5) return "ACADO_FCN_XDOT";
      casadi_error("getSchemeEntryEnumName: supplied number is out of range. ACADO_FCN_Input has only 6 entries: ('ACADO_FCN_Input', 't, xd, xa, u, p, xdot')");
      break;
    case SCHEME_ControlledDAEInput: 
      if(i==0) return "CONTROL_DAE_T";
      if(i==1) return "CONTROL_DAE_X";
      if(i==2) return "CONTROL_DAE_Z";
      if(i==3) return "CONTROL_DAE_P";
      if(i==4) return "CONTROL_DAE_U";
      if(i==5) return "CONTROL_DAE_U_INTERP";
      if(i==6) return "CONTROL_DAE_X_MAJOR";
      if(i==7) return "CONTROL_DAE_T0";
      if(i==8) return "CONTROL_DAE_TF";
      casadi_error("getSchemeEntryEnumName: supplied number is out of range. ControlledDAEInput has only 9 entries: ('ControlledDAEInput', 't, x, z, p, u, u_interp, x_major, t0, tf')");
      break;
    case SCHEME_ControlSimulatorInput: 
      if(i==0) return "CONTROLSIMULATOR_X0";
      if(i==1) return "CONTROLSIMULATOR_P";
      if(i==2) return "CONTROLSIMULATOR_U";
      casadi_error("getSchemeEntryEnumName: supplied number is out of range. ControlSimulatorInput has only 3 entries: ('ControlSimulatorInput', 'x0, p, u')");
      break;
    case SCHEME_DAEInput: 
      if(i==0) return "DAE_X";
      if(i==1) return "DAE_Z";
      if(i==2) return "DAE_P";
      if(i==3) return "DAE_T";
      casadi_error("getSchemeEntryEnumName: supplied number is out of range. DAEInput has only 4 entries: ('DAEInput', 'x, z, p, t')");
      break;
    case SCHEME_DAEOutput: 
      if(i==0) return "DAE_ODE";
      if(i==1) return "DAE_ALG";
      if(i==2) return "DAE_QUAD";
      casadi_error("getSchemeEntryEnumName: supplied number is out of range. DAEOutput has only 3 entries: ('DAEOutput', 'ode, alg, quad')");
      break;
    case SCHEME_RDAEInput: 
      if(i==0) return "RDAE_RX";
      if(i==1) return "RDAE_RZ";
      if(i==2) return "RDAE_RP";
      if(i==3) return "RDAE_X";
      if(i==4) return "RDAE_Z";
      if(i==5) return "RDAE_P";
      if(i==6) return "RDAE_T";
      casadi_error("getSchemeEntryEnumName: supplied number is out of range. RDAEInput has only 7 entries: ('RDAEInput', 'rx, rz, rp, x, z, p, t')");
      break;
    case SCHEME_RDAEOutput: 
      if(i==0) return "RDAE_ODE";
      if(i==1) return "RDAE_ALG";
      if(i==2) return "RDAE_QUAD";
      casadi_error("getSchemeEntryEnumName: supplied number is out of range. RDAEOutput has only 3 entries: ('RDAEOutput', 'ode, alg, quad')");
      break;
    case SCHEME_IntegratorInput: 
      if(i==0) return "INTEGRATOR_X0";
      if(i==1) return "INTEGRATOR_P";
      if(i==2) return "INTEGRATOR_RX0";
      if(i==3) return "INTEGRATOR_RP";
      casadi_error("getSchemeEntryEnumName: supplied number is out of range. IntegratorInput has only 4 entries: ('IntegratorInput', 'x0, p, rx0, rp')");
      break;
    case SCHEME_IntegratorOutput: 
      if(i==0) return "INTEGRATOR_XF";
      if(i==1) return "INTEGRATOR_QF";
      if(i==2) return "INTEGRATOR_RXF";
      if(i==3) return "INTEGRATOR_RQF";
      casadi_error("getSchemeEntryEnumName: supplied number is out of range. IntegratorOutput has only 4 entries: ('IntegratorOutput', 'xf, qf, rxf, rqf')");
      break;
    case SCHEME_NLPInput: 
      if(i==0) return "NLP_SOLVER_X0";
      if(i==1) return "NLP_SOLVER_LBX";
      if(i==2) return "NLP_SOLVER_UBX";
      if(i==3) return "NLP_SOLVER_LBG";
      if(i==4) return "NLP_SOLVER_UBG";
      if(i==5) return "NLP_SOLVER_LAM_G0";
      if(i==6) return "NLP_SOLVER_P";
      casadi_error("getSchemeEntryEnumName: supplied number is out of range. NLPInput has only 7 entries: ('NLPInput', 'x0, lbx, ubx, lbg, ubg, lam_g0, p')");
      break;
    case SCHEME_NLPOutput: 
      if(i==0) return "NLP_SOLVER_X";
      if(i==1) return "NLP_SOLVER_F";
      if(i==2) return "NLP_SOLVER_LAM_G";
      if(i==3) return "NLP_SOLVER_LAM_X";
      if(i==4) return "NLP_SOLVER_LAM_P";
      if(i==5) return "NLP_SOLVER_G";
      casadi_error("getSchemeEntryEnumName: supplied number is out of range. NLPOutput has only 6 entries: ('NLPOutput', 'x, f, lam_g, lam_x, lam_p, g')");
      break;
    case SCHEME_MayerInput: 
      if(i==0) return "MAYER_X";
      if(i==1) return "MAYER_P";
      casadi_error("getSchemeEntryEnumName: supplied number is out of range. MayerInput has only 2 entries: ('MayerInput', 'x, p')");
      break;
    case SCHEME_OCPInput: 
      if(i==0) return "OCP_LBX";
      if(i==1) return "OCP_UBX";
      if(i==2) return "OCP_X_INIT";
      if(i==3) return "OCP_LBU";
      if(i==4) return "OCP_UBU";
      if(i==5) return "OCP_U_INIT";
      if(i==6) return "OCP_LBP";
      if(i==7) return "OCP_UBP";
      if(i==8) return "OCP_P_INIT";
      if(i==9) return "OCP_LBH";
      if(i==10) return "OCP_UBH";
      if(i==11) return "OCP_LBG";
      if(i==12) return "OCP_UBG";
      casadi_error("getSchemeEntryEnumName: supplied number is out of range. OCPInput has only 13 entries: ('OCPInput', 'lbx, ubx, x_init, lbu, ubu, u_init, lbp, ubp, p_init, lbh, ubh, lbg, ubg')");
      break;
    case SCHEME_OCPOutput: 
      if(i==0) return "OCP_X_OPT";
      if(i==1) return "OCP_U_OPT";
      if(i==2) return "OCP_P_OPT";
      if(i==3) return "OCP_COST";
      casadi_error("getSchemeEntryEnumName: supplied number is out of range. OCPOutput has only 4 entries: ('OCPOutput', 'x_opt, u_opt, p_opt, cost')");
      break;
    case SCHEME_QPInput: 
      if(i==0) return "QP_H";
      if(i==1) return "QP_G";
      if(i==2) return "QP_A";
      if(i==3) return "QP_LBA";
      if(i==4) return "QP_UBA";
      if(i==5) return "QP_LBX";
      if(i==6) return "QP_UBX";
      if(i==7) return "QP_X_INIT";
      if(i==8) return "QP_LAMBDA_INIT";
      casadi_error("getSchemeEntryEnumName: supplied number is out of range. QPInput has only 9 entries: ('QPInput', 'h, g, a, lba, uba, lbx, ubx, x_init, lambda_init')");
      break;
    case SCHEME_QPOutput: 
      if(i==0) return "QP_PRIMAL";
      if(i==1) return "QP_COST";
      if(i==2) return "QP_LAMBDA_A";
      if(i==3) return "QP_LAMBDA_X";
      casadi_error("getSchemeEntryEnumName: supplied number is out of range. QPOutput has only 4 entries: ('QPOutput', 'primal, cost, lambda_a, lambda_x')");
      break;
    case SCHEME_SDPInput: 
      if(i==0) return "SDP_A";
      if(i==1) return "SDP_B";
      if(i==2) return "SDP_C";
      casadi_error("getSchemeEntryEnumName: supplied number is out of range. SDPInput has only 3 entries: ('SDPInput', 'a, b, c')");
      break;
    case SCHEME_SDPOutput: 
      if(i==0) return "SDP_PRIMAL";
      if(i==1) return "SDP_PRIMAL_P";
      if(i==2) return "SDP_DUAL";
      if(i==3) return "SDP_PRIMAL_COST";
      if(i==4) return "SDP_DUAL_COST";
      casadi_error("getSchemeEntryEnumName: supplied number is out of range. SDPOutput has only 5 entries: ('SDPOutput', 'primal, p, dual, primal_cost, dual_cost')");
      break;
    case SCHEME_unknown: return "none";
}
}
int getSchemeEntryEnum(InputOutputScheme scheme, const std::string &name) {
  switch (scheme) {
    case SCHEME_ACADO_Input: 
      if(name=="x_guess") return 0;
      if(name=="u_guess") return 1;
      if(name=="p_guess") return 2;
      if(name=="lbx") return 3;
      if(name=="ubx") return 4;
      if(name=="lbx0") return 5;
      if(name=="ubx0") return 6;
      if(name=="lbxf") return 7;
      if(name=="ubxf") return 8;
      if(name=="lbu") return 9;
      if(name=="ubu") return 10;
      if(name=="lbp") return 11;
      if(name=="ubp") return 12;
      if(name=="lbc") return 13;
      if(name=="ubc") return 14;
      if(name=="lbr") return 15;
      if(name=="ubr") return 16;
      break;
    case SCHEME_ACADO_Output: 
      if(name=="x_opt") return 0;
      if(name=="u_opt") return 1;
      if(name=="p_opt") return 2;
      if(name=="cost") return 3;
      break;
    case SCHEME_ACADO_FCN_Input: 
      if(name=="t") return 0;
      if(name=="xd") return 1;
      if(name=="xa") return 2;
      if(name=="u") return 3;
      if(name=="p") return 4;
      if(name=="xdot") return 5;
      break;
    case SCHEME_ControlledDAEInput: 
      if(name=="t") return 0;
      if(name=="x") return 1;
      if(name=="z") return 2;
      if(name=="p") return 3;
      if(name=="u") return 4;
      if(name=="u_interp") return 5;
      if(name=="x_major") return 6;
      if(name=="t0") return 7;
      if(name=="tf") return 8;
      break;
    case SCHEME_ControlSimulatorInput: 
      if(name=="x0") return 0;
      if(name=="p") return 1;
      if(name=="u") return 2;
      break;
    case SCHEME_DAEInput: 
      if(name=="x") return 0;
      if(name=="z") return 1;
      if(name=="p") return 2;
      if(name=="t") return 3;
      break;
    case SCHEME_DAEOutput: 
      if(name=="ode") return 0;
      if(name=="alg") return 1;
      if(name=="quad") return 2;
      break;
    case SCHEME_RDAEInput: 
      if(name=="rx") return 0;
      if(name=="rz") return 1;
      if(name=="rp") return 2;
      if(name=="x") return 3;
      if(name=="z") return 4;
      if(name=="p") return 5;
      if(name=="t") return 6;
      break;
    case SCHEME_RDAEOutput: 
      if(name=="ode") return 0;
      if(name=="alg") return 1;
      if(name=="quad") return 2;
      break;
    case SCHEME_IntegratorInput: 
      if(name=="x0") return 0;
      if(name=="p") return 1;
      if(name=="rx0") return 2;
      if(name=="rp") return 3;
      break;
    case SCHEME_IntegratorOutput: 
      if(name=="xf") return 0;
      if(name=="qf") return 1;
      if(name=="rxf") return 2;
      if(name=="rqf") return 3;
      break;
    case SCHEME_NLPInput: 
      if(name=="x0") return 0;
      if(name=="lbx") return 1;
      if(name=="ubx") return 2;
      if(name=="lbg") return 3;
      if(name=="ubg") return 4;
      if(name=="lam_g0") return 5;
      if(name=="p") return 6;
      break;
    case SCHEME_NLPOutput: 
      if(name=="x") return 0;
      if(name=="f") return 1;
      if(name=="lam_g") return 2;
      if(name=="lam_x") return 3;
      if(name=="lam_p") return 4;
      if(name=="g") return 5;
      break;
    case SCHEME_MayerInput: 
      if(name=="x") return 0;
      if(name=="p") return 1;
      break;
    case SCHEME_OCPInput: 
      if(name=="lbx") return 0;
      if(name=="ubx") return 1;
      if(name=="x_init") return 2;
      if(name=="lbu") return 3;
      if(name=="ubu") return 4;
      if(name=="u_init") return 5;
      if(name=="lbp") return 6;
      if(name=="ubp") return 7;
      if(name=="p_init") return 8;
      if(name=="lbh") return 9;
      if(name=="ubh") return 10;
      if(name=="lbg") return 11;
      if(name=="ubg") return 12;
      break;
    case SCHEME_OCPOutput: 
      if(name=="x_opt") return 0;
      if(name=="u_opt") return 1;
      if(name=="p_opt") return 2;
      if(name=="cost") return 3;
      break;
    case SCHEME_QPInput: 
      if(name=="h") return 0;
      if(name=="g") return 1;
      if(name=="a") return 2;
      if(name=="lba") return 3;
      if(name=="uba") return 4;
      if(name=="lbx") return 5;
      if(name=="ubx") return 6;
      if(name=="x_init") return 7;
      if(name=="lambda_init") return 8;
      break;
    case SCHEME_QPOutput: 
      if(name=="primal") return 0;
      if(name=="cost") return 1;
      if(name=="lambda_a") return 2;
      if(name=="lambda_x") return 3;
      break;
    case SCHEME_SDPInput: 
      if(name=="a") return 0;
      if(name=="b") return 1;
      if(name=="c") return 2;
      break;
    case SCHEME_SDPOutput: 
      if(name=="primal") return 0;
      if(name=="p") return 1;
      if(name=="dual") return 2;
      if(name=="primal_cost") return 3;
      if(name=="dual_cost") return 4;
      break;
}
return -1;}
}

