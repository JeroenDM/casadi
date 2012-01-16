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

#include "worhp_internal.hpp"
#include "casadi/stl_vector_tools.hpp"
#include "casadi/matrix/matrix_tools.hpp"
#include "casadi/mx/mx_tools.hpp"
#include "casadi/matrix/sparsity_tools.hpp"
#include "casadi/fx/mx_function.hpp"
#include <ctime>

using namespace std;

namespace CasADi{

WorhpInternal::WorhpInternal(const FX& F, const FX& G, const FX& H, const FX& J, const FX& GF) : NLPSolverInternal(F,G,H,J), GF_(GF){
  casadi_warning("WorhpSolver is not mature yet");

  int status;
  InitParams(&status, &worhp_p);
  
  std::stringstream ss;
  ss << "Armijo recovery strategies. Vector of size " << NAres;
  
  std::vector<int> ares(NAres);
  std::copy(worhp_p.Ares,worhp_p.Ares+NAres,ares.begin());
  addOption("Ares",OT_INTEGERVECTOR,ares,ss.str());
    
  /**
  *  Autogenerated from C_worhp_aux.h with params.pl
  *
  */
  
  addOption("AcceptTolFeas",OT_REAL,worhp_p.AcceptTolFeas,"Tolerance for acceptable feasibility");
  addOption("AcceptTolOpti",OT_REAL,worhp_p.AcceptTolOpti,"Tolerance for acceptable optimality");
  addOption("ArmijoBeta",OT_REAL,worhp_p.ArmijoBeta,"Trial stepsize decrease factor for Armijo rule");
  addOption("ArmijoMaxAlpha",OT_REAL,worhp_p.ArmijoMaxAlpha,"Initial alpha for Armijo rule");
  addOption("ArmijoMinAlpha",OT_REAL,worhp_p.ArmijoMinAlpha,"Lower bound on alpha for Armijo rule");
  addOption("ArmijoMinAlphaRec",OT_REAL,worhp_p.ArmijoMinAlphaRec,"Lower bound on alpha for Armijo rule during recovery");
  addOption("ArmijoSigma",OT_REAL,worhp_p.ArmijoSigma,"Scale factor for linearised descent check in Armijo rule");
  addOption("BettsFactor",OT_REAL,worhp_p.BettsFactor,"Update factor for Betts' Hessian regularisation");
  addOption("BettsPoint",OT_REAL,worhp_p.BettsPoint,"Smallest eigenvalue of the regularised Hessian");
  addOption("BoundTolFac",OT_REAL,worhp_p.BoundTolFac,"Factor in determining active constraints by KKT");
  addOption("CorStepBettsSum",OT_REAL,worhp_p.CorStepBettsSum,"(experimental)");
  addOption("CorStepConvio",OT_REAL,worhp_p.CorStepConvio,"(experimental)");
  addOption("CorStepConStop",OT_REAL,worhp_p.CorStepConStop,"(experimental)");
  addOption("CorStepPFactor",OT_REAL,worhp_p.CorStepPFactor,"(experimental)");
  addOption("CorStepPMax",OT_REAL,worhp_p.CorStepPMax,"(experimental)");
  addOption("CheckFJ",OT_REAL,worhp_p.CheckFJ,"Upper bound used by Fritz-John heuristic");
  addOption("CurvBCond",OT_REAL,worhp_p.CurvBCond,"Block BFGS curvature condition bound");
  addOption("CurvBFac",OT_REAL,worhp_p.CurvBFac,"Block BFGS curvature condition regularisation factor");
  addOption("CurvCond",OT_REAL,worhp_p.CurvCond,"BFGS Curvature condition bound");
  addOption("CurvFac",OT_REAL,worhp_p.CurvFac,"BFGS curvature condition regularisation factor");
  addOption("CutLength",OT_REAL,worhp_p.CutLength,"Scaling factor for Cut recovery strategy");
  addOption("FeasibleInitTol",OT_REAL,worhp_p.FeasibleInitTol,"Feasibility tolerance for no-objective feasible mode");
  addOption("FidifEps",OT_REAL,worhp_p.FidifEps,"Finite difference perturbation");
  addOption("FocusOnFeasFactor",OT_REAL,worhp_p.FocusOnFeasFactor,"Factor in Focus-on-Feasibility mode");
  addOption("Infty",OT_REAL,worhp_p.Infty,"Upper bound for numbers to be regarded as finite");
  addOption("InftyUnbounded",OT_REAL,worhp_p.InftyUnbounded,"Tolerance for unboundedness detection heuristic");
  addOption("LMestQPipComTol",OT_REAL,worhp_p.LMestQPipComTol,"IP complementarity tolerance in initial multiplier estimate");
  addOption("LMestQPipResTol",OT_REAL,worhp_p.LMestQPipResTol,"IP residual tolerance in initial multiplier estimate");
  addOption("LowPassAlphaF",OT_REAL,worhp_p.LowPassAlphaF,"Lowpass-filter update factor for objective values");
  addOption("LowPassAlphaG",OT_REAL,worhp_p.LowPassAlphaG,"Lowpass-filter update factor for constraint values");
  addOption("LowPassAlphaMerit",OT_REAL,worhp_p.LowPassAlphaMerit,"Lowpass-filter update factor for merit function values");
  addOption("Ma57PivotThresh",OT_REAL,worhp_p.Ma57PivotThresh,"Pivoting tolerance for MA57 = CNTL(1)");
  addOption("MeritGradTol",OT_REAL,worhp_p.MeritGradTol,"Threshold of meritfunction gradient for increasing Hessian regularisation");
  addOption("PenUpdEpsKFac",OT_REAL,worhp_p.PenUpdEpsKFac,"Penalty update parameter factor for MeritFunction = 4");
  addOption("PenUpdEpsBar",OT_REAL,worhp_p.PenUpdEpsBar,"Penalty update parameter factor for MeritFunction = 3");
  addOption("PenUpdMaxDeltaK",OT_REAL,worhp_p.PenUpdMaxDeltaK,"Max penalty for MeritFunction = 4");
  addOption("PenUpdMaxFac",OT_REAL,worhp_p.PenUpdMaxFac,"Max factor for increasing penalty for MeritFunction = 4");
  addOption("PenUpdRBar",OT_REAL,worhp_p.PenUpdRBar,"Penalty update parameter for MeritFunction = 3");
  addOption("PrecisionF",OT_REAL,worhp_p.PrecisionF,"(currently unused) Relative precision of objective");
  addOption("PrecisionG",OT_REAL,worhp_p.PrecisionG,"(currently unused) Relative precision of constraints");
  addOption("QPscaleParam",OT_REAL,worhp_p.QPscaleParam,"(currently unused)");
  addOption("RelaxMaxDelta",OT_REAL,worhp_p.RelaxMaxDelta,"Upper bound for accepting the constraint relaxation variable");
  addOption("RelaxMaxPen",OT_REAL,worhp_p.RelaxMaxPen,"Upper bound on the constraint relaxation penalty");
  addOption("RelaxRho",OT_REAL,worhp_p.RelaxRho,"Update factor for the constraint relaxation penalty");
  addOption("RelaxStart",OT_REAL,worhp_p.RelaxStart,"Initial value of the constraint relaxation penalty");
  addOption("ScaleFacObj",OT_REAL,worhp_p.ScaleFacObj,"Value to scale large objective functions to");
  addOption("ScaleFacQP",OT_REAL,worhp_p.ScaleFacQP,"Upper bound on resulting matrix norm for QP scaling");
  addOption("StartBettsTau",OT_REAL,worhp_p.StartBettsTau,"Initial value for Betts' update dampening term");
  addOption("Timeout",OT_REAL,worhp_p.Timeout,"Timeout in seconds");
  addOption("TolComp",OT_REAL,worhp_p.TolComp,"Complementarity tolerance");
  addOption("TolFeas",OT_REAL,worhp_p.TolFeas,"Feasibility tolerance");
  addOption("TolOpti",OT_REAL,worhp_p.TolOpti,"Optimality tolerance");
  addOption("TolWeakActive",OT_REAL,worhp_p.TolWeakActive,"(experimental)");
  addOption("TooBigCV",OT_REAL,worhp_p.TooBigCV,"Upper bound on constraint violation for too-big heuristic");
  addOption("TooBigKKT",OT_REAL,worhp_p.TooBigKKT,"Upper bound on KKT values for too-big heuristic");
  addOption("eps",OT_REAL,worhp_p.eps,"Machine epsilon");
  addOption("IncreaseIWS",OT_REAL,worhp_p.IncreaseIWS,"Increase factor for estimated integer workspace requirement");
  addOption("IncreaseRWS",OT_REAL,worhp_p.IncreaseRWS,"Increase factor for estimated real workspace requirement");
  addOption("FilterGammaCV",OT_REAL,worhp_p.FilterGammaCV,"Constraint violation decrease factor in Filter acceptance check");
  addOption("FilterGammaF",OT_REAL,worhp_p.FilterGammaF,"Objective decrease factor in Filter acceptance check");
  addOption("GammaAlpha",OT_REAL,worhp_p.GammaAlpha,"Safety factor for alphamin calculation by Filter");
  addOption("IncBettsTau",OT_REAL,worhp_p.IncBettsTau,"Increase factor for Betts' update dampening term");
  addOption("IncBettsTauMore",OT_REAL,worhp_p.IncBettsTauMore,"Larger increase factor for Betts' update dampening term");
  addOption("MinBettsTau",OT_REAL,worhp_p.MinBettsTau,"Lower bound for Betts' update dampening term");
  addOption("ReduceBettsTau",OT_REAL,worhp_p.ReduceBettsTau,"Decrease factor for Betts' update dampening term");
  addOption("SwitchingDelta",OT_REAL,worhp_p.SwitchingDelta,"Filter switching condition parameter");
  addOption("SwitchingSF",OT_REAL,worhp_p.SwitchingSF,"Filter switching condition parameter");
  addOption("SwitchingSCV",OT_REAL,worhp_p.SwitchingSCV,"Filter switching condition parameter");
  addOption("BFGSmethod",OT_INTEGER,worhp_p.BFGSmethod,"Choose BFGS method (dense, block, sparse)");
  addOption("BFGSrestart",OT_INTEGER,worhp_p.BFGSrestart,"Restart BFGS update after this many iterations");
  addOption("BFGSmaxblockSize",OT_INTEGER,worhp_p.BFGSmaxblockSize,"Maximum BFGS block size (depends on BFGS method)");
  addOption("BFGSminblockSize",OT_INTEGER,worhp_p.BFGSminblockSize,"Minimum BFGS block size (depends on BFGS method)");
  addOption("CorStepMaxIter",OT_INTEGER,worhp_p.CorStepMaxIter,"(experimental)");
  addOption("CorStepMethod",OT_INTEGER,worhp_p.CorStepMethod,"(experimental)");
  addOption("CorStepMode",OT_INTEGER,worhp_p.CorStepMode,"(experimental)");
  addOption("GroupMethod",OT_INTEGER,worhp_p.GroupMethod,"Select method to determine graph colouring groups");
  addOption("LogLevel",OT_INTEGER,worhp_p.LogLevel,"Enable XML logfiles and writing interval");
  addOption("LogResult",OT_INTEGER,worhp_p.LogResult,"Enable XML result logging and detail level");
  addOption("MaxCalls",OT_INTEGER,worhp_p.MaxCalls,"Upper bound to Reverse Communication calls");
  addOption("MaxForce",OT_INTEGER,worhp_p.MaxForce,"Maximum number of Force recovery strategy steps");
  addOption("MaxGPart",OT_INTEGER,worhp_p.MaxGPart,"(experimental)");
  addOption("MaxIter",OT_INTEGER,worhp_p.MaxIter,"Upper bound on major iterations");
  addOption("MeritFunction",OT_INTEGER,worhp_p.MeritFunction,"Select merit function and penalty update [0, 3..5]");
  addOption("NLPmethod",OT_INTEGER,worhp_p.NLPmethod,"Select (1) Meritfunction or (3) Filter globalisation");
  addOption("NLPprint",OT_INTEGER,worhp_p.NLPprint,"NLP print level [-1..4]");
  addOption("PairMethod",OT_INTEGER,worhp_p.PairMethod,"Select method to determine graph colouring pairgroups");
  addOption("PenUpdEpsKSequence",OT_INTEGER,worhp_p.PenUpdEpsKSequence,"Penalty update parameter");
  addOption("UserHMstructure",OT_INTEGER,worhp_p.UserHMstructure,"Enable automatic Hessian structure generation or checking");
  addOption("MaxLScounter",OT_INTEGER,worhp_p.MaxLScounter,"Control activation of Filter acceleration heuristics");
  addOption("RegStrategy",OT_INTEGER,worhp_p.RegStrategy,"Select Hessian regularisation strategy in Filter");
  addOption("AutoQPRecovery",OT_BOOLEAN,worhp_p.AutoQPRecovery,"Enable automatic QP recovery");
  addOption("CheckStructureDF",OT_BOOLEAN,worhp_p.CheckStructureDF,"Enable structural checking of DF");
  addOption("CheckStructureDG",OT_BOOLEAN,worhp_p.CheckStructureDG,"Enable structural checking of DG");
  addOption("CheckStructureHM",OT_BOOLEAN,worhp_p.CheckStructureHM,"Enable structural checking of HM");
  addOption("CorStepRecoveryDX",OT_BOOLEAN,worhp_p.CorStepRecoveryDX,"Enable structural checking of HM");
  addOption("FGtogether",OT_BOOLEAN,worhp_p.FGtogether,"F and G cannot be evaluated separately");
  addOption("FJandND",OT_BOOLEAN,worhp_p.FJandND,"Enable Fritz-John and non-differentiable check heuristics");
  addOption("FeasibleDual",OT_BOOLEAN,worhp_p.FeasibleDual,"Activate dual feasibility mode");
  addOption("FeasibleInit",OT_BOOLEAN,worhp_p.FeasibleInit,"Activate initial feasibility mode");
  addOption("FeasibleOnly",OT_BOOLEAN,worhp_p.FeasibleOnly,"Activate feasible-only mode");
  addOption("FidifHM",OT_BOOLEAN,worhp_p.FidifHM,"Approximate Hessian by finite differences (otherwise BFGS)");
  addOption("FirstDifCentral",OT_BOOLEAN,worhp_p.FirstDifCentral,"Use central finite difference quotient for first derivatives");
  addOption("FocusOnFeas",OT_BOOLEAN,worhp_p.FocusOnFeas,"Enable Focus-on-Feasibility mode");
  addOption("InitialLMest",OT_BOOLEAN,worhp_p.InitialLMest,"Enable initial Lagrange multiplier estimate");
  addOption("KeepAcceptableSol",OT_BOOLEAN,worhp_p.KeepAcceptableSol,"Save acceptable solutions as fallback");
  addOption("LinMult",OT_BOOLEAN,worhp_p.LinMult,"Control Lagrange multiplier update");
  addOption("LowPassFilter",OT_BOOLEAN,worhp_p.LowPassFilter,"Enable lowpass-filter termination criterion");
  addOption("MatrixCC",OT_BOOLEAN,worhp_p.MatrixCC,"Not to be included into a parameter file!");
  addOption("MoreRelax",OT_BOOLEAN,worhp_p.MoreRelax,"Introduce one relaxation variable for every constraint");
  addOption("QuadraticProblem",OT_BOOLEAN,worhp_p.QuadraticProblem,"Not to be included into a parameter file!");
  addOption("RestUntilFeas",OT_BOOLEAN,worhp_p.RestUntilFeas,"Do restoration until a feasible solution is found");
  addOption("ScaleConIter",OT_BOOLEAN,worhp_p.ScaleConIter,"Scale constraints in every iteration");
  addOption("ScaledFD",OT_BOOLEAN,worhp_p.ScaledFD,"Use a scaled perturbation for finite differences");
  addOption("ScaledKKT",OT_BOOLEAN,worhp_p.ScaledKKT,"Scale KKT conditions");
  addOption("ScaledObj",OT_BOOLEAN,worhp_p.ScaledObj,"Scale the objective function");
  addOption("ScaledQP",OT_BOOLEAN,worhp_p.ScaledQP,"Scale some matrices handed to the QP");
  addOption("TakeQPSol",OT_BOOLEAN,worhp_p.TakeQPSol,"Evaluate QP search direction regardless of convergence");
  addOption("TooBig",OT_BOOLEAN,worhp_p.TooBig,"Enable too-big termination heuristics");
  addOption("UserDF",OT_BOOLEAN,worhp_p.UserDF,"Objective gradient values supplied by caller");
  addOption("UserDG",OT_BOOLEAN,worhp_p.UserDG,"Jacobian values supplied by caller");
  addOption("UserHM",OT_BOOLEAN,worhp_p.UserHM,"Hessian values supplied by caller");
  addOption("WeakActiveSet",OT_BOOLEAN,worhp_p.WeakActiveSet,"(experimental)");
  addOption("AlphaMinConst",OT_BOOLEAN,worhp_p.AlphaMinConst,"Use a constant lower bound on Armijo stepsize in Filter");
  addOption("IgnoreFilterCrit",OT_BOOLEAN,worhp_p.IgnoreFilterCrit,"Activate accelerating heuristics for Filter");
  addOption("FilterBisecAlpha",OT_BOOLEAN,worhp_p.FilterBisecAlpha,"Filter heuristic to save Armijo iterations");
  addOption("FilterIntersecAlpha",OT_BOOLEAN,worhp_p.FilterIntersecAlpha,"Filter heuristic to save Armijo iterations");
  addOption("MaxNorm",OT_BOOLEAN,worhp_p.MaxNorm,"Select max-norm instead of 1-norm in Filter");
  addOption("ReinitFilter",OT_BOOLEAN,worhp_p.ReinitFilter,"Enables Filter-reinitialisation accelerating heuristic");
  addOption("DebugMarker06",OT_INTEGER,worhp_p.DebugMarker06,"Debug marker, only needed for ASTOS integration");
  addOption("initialised",OT_BOOLEAN,worhp_p.initialised,"Automatically added initialisation flag. ");
  
  
}


WorhpInternal::~WorhpInternal(){

}

void WorhpInternal::init(){

  NLPSolverInternal::init();
  
  worhp_o.initialised = false;
  worhp_w.initialised = false;
  worhp_p.initialised = false;
  worhp_c.initialised = false;
  
  worhp_o.n = n_;  // Number of variables
  worhp_o.m = m_;  // Number of constraints
  
  if (GF_.isNull()) GF_ = F_.jacobian();
  
  // Gradient of the objective function, remove?
  if(!GF_.isNull()) GF_.init();
  if(!GF_.isNull()) {
    casadi_assert_message(GF_.getNumInputs()>=1, "Wrong number of input arguments to GF");
    casadi_assert_message(GF_.getNumOutputs()>=1, "Wrong number of output arguments to GF");
    casadi_assert_message(GF_.input().numel()==n_,"Inconsistent dimensions");
    casadi_assert_message((GF_.output().size1()==n_ && GF_.output().size2()==1) || (GF_.output().size1()==1 && GF_.output().size2()==n_),"Inconsistent dimensions");
  }
  
  
  // Worhp uses the CS format internally, hence it is the preferred sparse matrix format.
  
  worhp_w.DF.nnz = GF_.output().size(); // Gradient of f
  worhp_w.DG.nnz = J_.output().size();  // Jacobian of G
  
  
  if (hasSetOption("generate_hessian") && getOption("generate_hessian")) {
    std::vector< MX > input = H_.symbolicInput();
    MX H = H_.call(input)[0];
    H = vertcat(vec(H(lowerSparsity(H.sparsity(),false))),vec(H(sp_diag(n_))));
    
    H_tril_ = MXFunction(input,H);
    H_tril_.init();
    
    worhp_w.HM.nnz = H_tril_.output().size();
  }
  

  if (hasSetOption("Ares")) {
    std::vector<int> ares = getOption("Ares");
    std::copy(ares.begin(),ares.begin()+NAres,worhp_p.Ares);
  }
  

  /**
  *  Autogenerated from C_worhp_aux.h with params.pl
  *
  */
  
  if (hasSetOption("AcceptTolFeas")) worhp_p.AcceptTolFeas = getOption("AcceptTolFeas");
  if (hasSetOption("AcceptTolOpti")) worhp_p.AcceptTolOpti = getOption("AcceptTolOpti");
  if (hasSetOption("ArmijoBeta")) worhp_p.ArmijoBeta = getOption("ArmijoBeta");
  if (hasSetOption("ArmijoMaxAlpha")) worhp_p.ArmijoMaxAlpha = getOption("ArmijoMaxAlpha");
  if (hasSetOption("ArmijoMinAlpha")) worhp_p.ArmijoMinAlpha = getOption("ArmijoMinAlpha");
  if (hasSetOption("ArmijoMinAlphaRec")) worhp_p.ArmijoMinAlphaRec = getOption("ArmijoMinAlphaRec");
  if (hasSetOption("ArmijoSigma")) worhp_p.ArmijoSigma = getOption("ArmijoSigma");
  if (hasSetOption("BettsFactor")) worhp_p.BettsFactor = getOption("BettsFactor");
  if (hasSetOption("BettsPoint")) worhp_p.BettsPoint = getOption("BettsPoint");
  if (hasSetOption("BoundTolFac")) worhp_p.BoundTolFac = getOption("BoundTolFac");
  if (hasSetOption("CorStepBettsSum")) worhp_p.CorStepBettsSum = getOption("CorStepBettsSum");
  if (hasSetOption("CorStepConvio")) worhp_p.CorStepConvio = getOption("CorStepConvio");
  if (hasSetOption("CorStepConStop")) worhp_p.CorStepConStop = getOption("CorStepConStop");
  if (hasSetOption("CorStepPFactor")) worhp_p.CorStepPFactor = getOption("CorStepPFactor");
  if (hasSetOption("CorStepPMax")) worhp_p.CorStepPMax = getOption("CorStepPMax");
  if (hasSetOption("CheckFJ")) worhp_p.CheckFJ = getOption("CheckFJ");
  if (hasSetOption("CurvBCond")) worhp_p.CurvBCond = getOption("CurvBCond");
  if (hasSetOption("CurvBFac")) worhp_p.CurvBFac = getOption("CurvBFac");
  if (hasSetOption("CurvCond")) worhp_p.CurvCond = getOption("CurvCond");
  if (hasSetOption("CurvFac")) worhp_p.CurvFac = getOption("CurvFac");
  if (hasSetOption("CutLength")) worhp_p.CutLength = getOption("CutLength");
  if (hasSetOption("FeasibleInitTol")) worhp_p.FeasibleInitTol = getOption("FeasibleInitTol");
  if (hasSetOption("FidifEps")) worhp_p.FidifEps = getOption("FidifEps");
  if (hasSetOption("FocusOnFeasFactor")) worhp_p.FocusOnFeasFactor = getOption("FocusOnFeasFactor");
  if (hasSetOption("Infty")) worhp_p.Infty = getOption("Infty");
  if (hasSetOption("InftyUnbounded")) worhp_p.InftyUnbounded = getOption("InftyUnbounded");
  if (hasSetOption("LMestQPipComTol")) worhp_p.LMestQPipComTol = getOption("LMestQPipComTol");
  if (hasSetOption("LMestQPipResTol")) worhp_p.LMestQPipResTol = getOption("LMestQPipResTol");
  if (hasSetOption("LowPassAlphaF")) worhp_p.LowPassAlphaF = getOption("LowPassAlphaF");
  if (hasSetOption("LowPassAlphaG")) worhp_p.LowPassAlphaG = getOption("LowPassAlphaG");
  if (hasSetOption("LowPassAlphaMerit")) worhp_p.LowPassAlphaMerit = getOption("LowPassAlphaMerit");
  if (hasSetOption("Ma57PivotThresh")) worhp_p.Ma57PivotThresh = getOption("Ma57PivotThresh");
  if (hasSetOption("MeritGradTol")) worhp_p.MeritGradTol = getOption("MeritGradTol");
  if (hasSetOption("PenUpdEpsKFac")) worhp_p.PenUpdEpsKFac = getOption("PenUpdEpsKFac");
  if (hasSetOption("PenUpdEpsBar")) worhp_p.PenUpdEpsBar = getOption("PenUpdEpsBar");
  if (hasSetOption("PenUpdMaxDeltaK")) worhp_p.PenUpdMaxDeltaK = getOption("PenUpdMaxDeltaK");
  if (hasSetOption("PenUpdMaxFac")) worhp_p.PenUpdMaxFac = getOption("PenUpdMaxFac");
  if (hasSetOption("PenUpdRBar")) worhp_p.PenUpdRBar = getOption("PenUpdRBar");
  if (hasSetOption("PrecisionF")) worhp_p.PrecisionF = getOption("PrecisionF");
  if (hasSetOption("PrecisionG")) worhp_p.PrecisionG = getOption("PrecisionG");
  if (hasSetOption("QPscaleParam")) worhp_p.QPscaleParam = getOption("QPscaleParam");
  if (hasSetOption("RelaxMaxDelta")) worhp_p.RelaxMaxDelta = getOption("RelaxMaxDelta");
  if (hasSetOption("RelaxMaxPen")) worhp_p.RelaxMaxPen = getOption("RelaxMaxPen");
  if (hasSetOption("RelaxRho")) worhp_p.RelaxRho = getOption("RelaxRho");
  if (hasSetOption("RelaxStart")) worhp_p.RelaxStart = getOption("RelaxStart");
  if (hasSetOption("ScaleFacObj")) worhp_p.ScaleFacObj = getOption("ScaleFacObj");
  if (hasSetOption("ScaleFacQP")) worhp_p.ScaleFacQP = getOption("ScaleFacQP");
  if (hasSetOption("StartBettsTau")) worhp_p.StartBettsTau = getOption("StartBettsTau");
  if (hasSetOption("Timeout")) worhp_p.Timeout = getOption("Timeout");
  if (hasSetOption("TolComp")) worhp_p.TolComp = getOption("TolComp");
  if (hasSetOption("TolFeas")) worhp_p.TolFeas = getOption("TolFeas");
  if (hasSetOption("TolOpti")) worhp_p.TolOpti = getOption("TolOpti");
  if (hasSetOption("TolWeakActive")) worhp_p.TolWeakActive = getOption("TolWeakActive");
  if (hasSetOption("TooBigCV")) worhp_p.TooBigCV = getOption("TooBigCV");
  if (hasSetOption("TooBigKKT")) worhp_p.TooBigKKT = getOption("TooBigKKT");
  if (hasSetOption("eps")) worhp_p.eps = getOption("eps");
  if (hasSetOption("IncreaseIWS")) worhp_p.IncreaseIWS = getOption("IncreaseIWS");
  if (hasSetOption("IncreaseRWS")) worhp_p.IncreaseRWS = getOption("IncreaseRWS");
  if (hasSetOption("FilterGammaCV")) worhp_p.FilterGammaCV = getOption("FilterGammaCV");
  if (hasSetOption("FilterGammaF")) worhp_p.FilterGammaF = getOption("FilterGammaF");
  if (hasSetOption("GammaAlpha")) worhp_p.GammaAlpha = getOption("GammaAlpha");
  if (hasSetOption("IncBettsTau")) worhp_p.IncBettsTau = getOption("IncBettsTau");
  if (hasSetOption("IncBettsTauMore")) worhp_p.IncBettsTauMore = getOption("IncBettsTauMore");
  if (hasSetOption("MinBettsTau")) worhp_p.MinBettsTau = getOption("MinBettsTau");
  if (hasSetOption("ReduceBettsTau")) worhp_p.ReduceBettsTau = getOption("ReduceBettsTau");
  if (hasSetOption("SwitchingDelta")) worhp_p.SwitchingDelta = getOption("SwitchingDelta");
  if (hasSetOption("SwitchingSF")) worhp_p.SwitchingSF = getOption("SwitchingSF");
  if (hasSetOption("SwitchingSCV")) worhp_p.SwitchingSCV = getOption("SwitchingSCV");
  if (hasSetOption("BFGSmethod")) worhp_p.BFGSmethod = getOption("BFGSmethod");
  if (hasSetOption("BFGSrestart")) worhp_p.BFGSrestart = getOption("BFGSrestart");
  if (hasSetOption("BFGSmaxblockSize")) worhp_p.BFGSmaxblockSize = getOption("BFGSmaxblockSize");
  if (hasSetOption("BFGSminblockSize")) worhp_p.BFGSminblockSize = getOption("BFGSminblockSize");
  if (hasSetOption("CorStepMaxIter")) worhp_p.CorStepMaxIter = getOption("CorStepMaxIter");
  if (hasSetOption("CorStepMethod")) worhp_p.CorStepMethod = getOption("CorStepMethod");
  if (hasSetOption("CorStepMode")) worhp_p.CorStepMode = getOption("CorStepMode");
  if (hasSetOption("GroupMethod")) worhp_p.GroupMethod = getOption("GroupMethod");
  if (hasSetOption("LogLevel")) worhp_p.LogLevel = getOption("LogLevel");
  if (hasSetOption("LogResult")) worhp_p.LogResult = getOption("LogResult");
  if (hasSetOption("MaxCalls")) worhp_p.MaxCalls = getOption("MaxCalls");
  if (hasSetOption("MaxForce")) worhp_p.MaxForce = getOption("MaxForce");
  if (hasSetOption("MaxGPart")) worhp_p.MaxGPart = getOption("MaxGPart");
  if (hasSetOption("MaxIter")) worhp_p.MaxIter = getOption("MaxIter");
  if (hasSetOption("MeritFunction")) worhp_p.MeritFunction = getOption("MeritFunction");
  if (hasSetOption("NLPmethod")) worhp_p.NLPmethod = getOption("NLPmethod");
  if (hasSetOption("NLPprint")) worhp_p.NLPprint = getOption("NLPprint");
  if (hasSetOption("PairMethod")) worhp_p.PairMethod = getOption("PairMethod");
  if (hasSetOption("PenUpdEpsKSequence")) worhp_p.PenUpdEpsKSequence = getOption("PenUpdEpsKSequence");
  if (hasSetOption("UserHMstructure")) worhp_p.UserHMstructure = getOption("UserHMstructure");
  if (hasSetOption("MaxLScounter")) worhp_p.MaxLScounter = getOption("MaxLScounter");
  if (hasSetOption("RegStrategy")) worhp_p.RegStrategy = getOption("RegStrategy");
  if (hasSetOption("AutoQPRecovery")) worhp_p.AutoQPRecovery = getOption("AutoQPRecovery");
  if (hasSetOption("CheckStructureDF")) worhp_p.CheckStructureDF = getOption("CheckStructureDF");
  if (hasSetOption("CheckStructureDG")) worhp_p.CheckStructureDG = getOption("CheckStructureDG");
  if (hasSetOption("CheckStructureHM")) worhp_p.CheckStructureHM = getOption("CheckStructureHM");
  if (hasSetOption("CorStepRecoveryDX")) worhp_p.CorStepRecoveryDX = getOption("CorStepRecoveryDX");
  if (hasSetOption("FGtogether")) worhp_p.FGtogether = getOption("FGtogether");
  if (hasSetOption("FJandND")) worhp_p.FJandND = getOption("FJandND");
  if (hasSetOption("FeasibleDual")) worhp_p.FeasibleDual = getOption("FeasibleDual");
  if (hasSetOption("FeasibleInit")) worhp_p.FeasibleInit = getOption("FeasibleInit");
  if (hasSetOption("FeasibleOnly")) worhp_p.FeasibleOnly = getOption("FeasibleOnly");
  if (hasSetOption("FidifHM")) worhp_p.FidifHM = getOption("FidifHM");
  if (hasSetOption("FirstDifCentral")) worhp_p.FirstDifCentral = getOption("FirstDifCentral");
  if (hasSetOption("FocusOnFeas")) worhp_p.FocusOnFeas = getOption("FocusOnFeas");
  if (hasSetOption("InitialLMest")) worhp_p.InitialLMest = getOption("InitialLMest");
  if (hasSetOption("KeepAcceptableSol")) worhp_p.KeepAcceptableSol = getOption("KeepAcceptableSol");
  if (hasSetOption("LinMult")) worhp_p.LinMult = getOption("LinMult");
  if (hasSetOption("LowPassFilter")) worhp_p.LowPassFilter = getOption("LowPassFilter");
  if (hasSetOption("MatrixCC")) worhp_p.MatrixCC = getOption("MatrixCC");
  if (hasSetOption("MoreRelax")) worhp_p.MoreRelax = getOption("MoreRelax");
  if (hasSetOption("QuadraticProblem")) worhp_p.QuadraticProblem = getOption("QuadraticProblem");
  if (hasSetOption("RestUntilFeas")) worhp_p.RestUntilFeas = getOption("RestUntilFeas");
  if (hasSetOption("ScaleConIter")) worhp_p.ScaleConIter = getOption("ScaleConIter");
  if (hasSetOption("ScaledFD")) worhp_p.ScaledFD = getOption("ScaledFD");
  if (hasSetOption("ScaledKKT")) worhp_p.ScaledKKT = getOption("ScaledKKT");
  if (hasSetOption("ScaledObj")) worhp_p.ScaledObj = getOption("ScaledObj");
  if (hasSetOption("ScaledQP")) worhp_p.ScaledQP = getOption("ScaledQP");
  if (hasSetOption("TakeQPSol")) worhp_p.TakeQPSol = getOption("TakeQPSol");
  if (hasSetOption("TooBig")) worhp_p.TooBig = getOption("TooBig");
  if (hasSetOption("UserDF")) worhp_p.UserDF = getOption("UserDF");
  if (hasSetOption("UserDG")) worhp_p.UserDG = getOption("UserDG");
  if (hasSetOption("UserHM")) worhp_p.UserHM = getOption("UserHM");
  if (hasSetOption("WeakActiveSet")) worhp_p.WeakActiveSet = getOption("WeakActiveSet");
  if (hasSetOption("AlphaMinConst")) worhp_p.AlphaMinConst = getOption("AlphaMinConst");
  if (hasSetOption("IgnoreFilterCrit")) worhp_p.IgnoreFilterCrit = getOption("IgnoreFilterCrit");
  if (hasSetOption("FilterBisecAlpha")) worhp_p.FilterBisecAlpha = getOption("FilterBisecAlpha");
  if (hasSetOption("FilterIntersecAlpha")) worhp_p.FilterIntersecAlpha = getOption("FilterIntersecAlpha");
  if (hasSetOption("MaxNorm")) worhp_p.MaxNorm = getOption("MaxNorm");
  if (hasSetOption("ReinitFilter")) worhp_p.ReinitFilter = getOption("ReinitFilter");
  if (hasSetOption("DebugMarker06")) worhp_p.DebugMarker06 = getOption("DebugMarker06");
  if (hasSetOption("initialised")) worhp_p.initialised = getOption("initialised");


         
  /* Data structure initialisation. */
  WorhpInit(&worhp_o, &worhp_w, &worhp_p, &worhp_c);
  if (worhp_c.status != FirstCall) {
    casadi_error("Main: Initialisation failed.");
  }
  
  if (worhp_w.DF.NeedStructure) {
    vector<int> row,col;
    GF_.output().sparsity().getSparsity(col,row); // transpose
    for (int i=0;i<row.size();++i) worhp_w.DF.row[i] = row[i] + 1; // Index-1 based
  }
  
  if (worhp_w.DG.NeedStructure) {

    
    vector<int> row,col;
    trans(J_.output()).sparsity().getSparsity(col,row);
    std::vector< MX > J = J_.symbolicInput();
      
    casadi_assert(col.size()==worhp_w.DG.nnz);
    casadi_assert(row.size()==worhp_w.DG.nnz);
    
    for (int i=0;i<col.size();++i) worhp_w.DG.col[i] = col[i] + 1;
    for (int i=0;i<row.size();++i) worhp_w.DG.row[i] = row[i] + 1;
    

  }
  
    

  if (hasSetOption("generate_hessian") && getOption("generate_hessian")) {
    log("generate_hessian sparsity");
    int nz=0;
    if (worhp_w.HM.NeedStructure) {
      vector<int> row,col;
      lowerSparsity(H_.output().sparsity(),false).getSparsity(row,col);

      for (int i=0;i<col.size();++i) worhp_w.HM.col[i] = col[i] + 1;
      for (int i=0;i<row.size();++i) worhp_w.HM.row[i] = row[i] + 1;
      
      vector<int> rowd,cold;
      H_.output()(sp_diag(n_)).sparsity().getSparsity(rowd,cold);
      
      casadi_assert(worhp_w.HM.nnz<=worhp_w.HM.dim_row);
      casadi_assert(worhp_w.HM.nnz<=worhp_w.HM.dim_col);
      
      casadi_assert(cold.size()+col.size()==worhp_w.HM.nnz);
      casadi_assert(rowd.size()+row.size()==worhp_w.HM.nnz);
      
      for (int i=0;i<cold.size();++i) worhp_w.HM.col[i+col.size()] = cold[i] + 1;
      for (int i=0;i<rowd.size();++i) worhp_w.HM.row[i+row.size()] = rowd[i] + 1;

    }
  }
  
}

void WorhpInternal::evaluate(int nfdir, int nadir){
  casadi_assert(nfdir==0 && nadir==0);

  // Set the static parameter
  if (!F_.isNull()) {
    if (F_.getNumInputs()==2) F_.setInput(input(NLP_P),1);
  }
  if (!G_.isNull()) {
    if (G_.getNumInputs()==2) G_.setInput(input(NLP_P),1);
  }
  if (!H_tril_.isNull()) {
    if (H_tril_.getNumInputs()==4) H_tril_.setInput(input(NLP_P),1);
  }
  if (!J_.isNull()) {
    if (J_.getNumInputs()==2) J_.setInput(input(NLP_P),1);
  }
  if (!GF_.isNull()) {
    if (GF_.getNumInputs()==2) GF_.setInput(input(NLP_P),1);
  }
  
  input(NLP_X_INIT).getArray(worhp_o.X,n_);
  output(NLP_LAMBDA_X).getArray(worhp_o.Lambda,n_);
  input(NLP_LAMBDA_INIT).getArray(worhp_o.Mu,m_);
   
  input(NLP_LBX).getArray(worhp_o.XL,n_);
  input(NLP_UBX).getArray(worhp_o.XU,n_);
  input(NLP_LBG).getArray(worhp_o.GL,m_);
  input(NLP_UBG).getArray(worhp_o.GU,m_);

  
  // Reverse Communication loop
  while(worhp_c.status < TerminateSuccess &&  worhp_c.status > TerminateError) {

    if (GetUserAction(&worhp_c, callWorhp)) {
      Worhp(&worhp_o, &worhp_w, &worhp_p, &worhp_c);
    }

    if (GetUserAction(&worhp_c, iterOutput)) {
      if (!callback_.isNull()) {
        // Copy outputs
        copy(worhp_o.X,worhp_o.X+n_,callback_.input(NLP_X_OPT).begin());
        callback_.input(NLP_COST)[0] = worhp_o.F;
        copy(worhp_o.G,worhp_o.G+n_,callback_.input(NLP_G).begin());
        copy(worhp_o.Lambda,worhp_o.Lambda+n_,callback_.input(NLP_LAMBDA_X).begin());
        copy(worhp_o.Mu,worhp_o.Mu+n_,callback_.input(NLP_LAMBDA_G).begin());
        
        callback_.evaluate();
      }
    
      IterationOutput(&worhp_o, &worhp_w, &worhp_p, &worhp_c);
      DoneUserAction(&worhp_c, iterOutput);
    }

    if (GetUserAction(&worhp_c, evalF)) {
      eval_f(worhp_o.X, worhp_o.F);
      DoneUserAction(&worhp_c, evalF);
    }

    if (GetUserAction(&worhp_c, evalG)) {
      eval_g(worhp_o.X, worhp_o.G);
      DoneUserAction(&worhp_c, evalG);
    }

    if (GetUserAction(&worhp_c, evalDF)) {
      eval_grad_f(worhp_o.X, worhp_w.ScaleObj, worhp_w.DF.val);
      DoneUserAction(&worhp_c, evalDF);
    }

    if (GetUserAction(&worhp_c, evalDG)) {
      eval_jac_g(worhp_o.X,worhp_w.DG.val);
      DoneUserAction(&worhp_c, evalDG);
    }

    if (GetUserAction(&worhp_c, evalHM)) {
      eval_h(worhp_o.X, worhp_w.ScaleObj, worhp_o.Mu, worhp_w.HM.val);
      DoneUserAction(&worhp_c, evalHM);
    }
    
    if (GetUserAction(&worhp_c, fidif)) {
      WorhpFidif(&worhp_o, &worhp_w, &worhp_p, &worhp_c);
    }

  }
  
  // Copy outputs
  copy(worhp_o.X,worhp_o.X+n_,output(NLP_X_OPT).begin());
  output(NLP_COST)[0] = worhp_o.F;
  copy(worhp_o.G,worhp_o.G+n_,output(NLP_G).begin());
  copy(worhp_o.Lambda,worhp_o.Lambda+n_,output(NLP_LAMBDA_X).begin());
  copy(worhp_o.Mu,worhp_o.Mu+n_,output(NLP_LAMBDA_G).begin());
  
  StatusMsg(&worhp_o, &worhp_w, &worhp_p, &worhp_c);
  WorhpFree(&worhp_o, &worhp_w, &worhp_p, &worhp_c);
 
}

bool WorhpInternal::eval_h(const double* x, double obj_factor, const double* lambda, double* values){
  try{
    log("eval_h started");
    double time1 = clock();
    // Number of inputs to the hessian
    int n_hess_in = H_tril_.getNumInputs();
    
    // Pass input
    H_tril_.setInput(x);
    if(n_hess_in>1){
      H_tril_.setInput(lambda, n_hess_in==4? 2 : 1);
      H_tril_.setInput(obj_factor, n_hess_in==4? 3 : 2);
    }

    // Evaluate
    H_tril_.evaluate();

    // Scale objective
    if(n_hess_in==1 && obj_factor!=1.0){
      for(vector<double>::iterator it=H_tril_.output().begin(); it!=H_tril_.output().end(); ++it){
        *it *= obj_factor;
      }
    }

    // Get results
    H_tril_.output().get(values);
      
    double time2 = clock();
    t_eval_h_ += double(time2-time1)/CLOCKS_PER_SEC;
    log("eval_h ok");
    return true;
  } catch (exception& ex){
    cerr << "eval_h failed: " << ex.what() << endl;
    return false;
  }
}

bool WorhpInternal::eval_jac_g(const double* x,double* values){
  try{
    log("eval_jac_g started");
    
    // Quich finish if no constraints
    if(m_==0){
      log("eval_jac_g quick return (m==0)");
      return true;
    }
    
    double time1 = clock();

    // Pass the argument to the function
    J_.setInput(x);
    
     // Evaluate the function
    J_.evaluate();

    // Get the output
    trans(J_.output()).get(values);
    
    if(monitored("eval_jac_g")){
      cout << "x = " << J_.input().data() << endl;
      cout << "J = " << endl;
      J_.output().printSparse();
    }
    
    double time2 = clock();
    t_eval_jac_g_ += double(time2-time1)/CLOCKS_PER_SEC;
    
    log("eval_jac_g ok");
    return true;
  } catch (exception& ex){
    cerr << "eval_jac_g failed: " << ex.what() << endl;
    return false;
  }
}

bool WorhpInternal::eval_f(const double* x, double& obj_value)
{
  try {
    log("eval_f started");
    
    // Log time
    double time1 = clock();

    // Pass the argument to the function
    F_.setInput(x);
      
    // Evaluate the function
    F_.evaluate();

    // Get the result
    F_.getOutput(obj_value);

    // Printing
    if(monitored("eval_f")){
      cout << "x = " << F_.input() << endl;
      cout << "obj_value = " << obj_value << endl;
    }

    double time2 = clock();
    t_eval_f_ += double(time2-time1)/CLOCKS_PER_SEC;

    log("eval_f ok");
    return true;
  } catch (exception& ex){
    cerr << "eval_f failed: " << ex.what() << endl;
    return false;
  }
}

bool WorhpInternal::eval_g(const double* x, double* g)
{
  try {
    log("eval_g started");
    double time1 = clock();

    // Pass the argument to the function
    G_.setInput(x);

    // Evaluate the function and tape
    G_.evaluate();

    // Ge the result
    G_.getOutput(g);

    // Printing
    if(monitored("eval_g")){
      cout << "x = " << G_.input() << endl;
      cout << "g = " << G_.output() << endl;
    }

      
    double time2 = clock();
    t_eval_g_ += double(time2-time1)/CLOCKS_PER_SEC;
    
    log("eval_g ok");
    return true;
  } catch (exception& ex){
    cerr << "eval_g failed: " << ex.what() << endl;
    return false;
  }
}

bool WorhpInternal::eval_grad_f(const double* x,double scale , double* grad_f )
{
  try {
    log("eval_grad_f started");
    double time1 = clock();
    
    // If no gradient function has been provided, use AD adjoint
    if(GF_.isNull()){
    
      // Pass the argument to the function
      F_.setInput(x);
      
      // Give a seed to the function
      F_.setAdjSeed(scale);

      // Evaluate, adjoint mode
      F_.evaluate(0,1);

      // Get the result
      F_.getAdjSens(grad_f);

      // Printing
      if(monitored("eval_grad_f")){
        cout << "grad_f = " << F_.adjSens() << endl;
      }
      
    } else {
      
      // Pass the argument to the function
      GF_.setInput(x);
      
      // Evaluate, adjoint mode
      GF_.evaluate();

      GF_.output()*=scale;
      // Get the result
      GF_.getOutput(grad_f);
      
      // Printing
      if(monitored("eval_grad_f")){
        cout << "grad_f = " << GF_.output() << endl;
      }
    }
    
    double time2 = clock();
    t_eval_grad_f_ += double(time2-time1)/CLOCKS_PER_SEC;

    // Check the result for regularity
    for(int i=0; i<n_; ++i){
        if(isnan(grad_f[i]) || isinf(grad_f[i])){
          log("eval_grad_f: result not regular");
          return false;
      }
    }

    log("eval_grad_f ok");
    return true;
  } catch (exception& ex){
    cerr << "eval_jac_f failed: " << ex.what() << endl;
    return false;
  }
}


} // namespace CasADi
