/*
 *    This file is part of CasADi.
 *
 *    CasADi -- A minimalistic computer algebra system with automatic differentiation 
 *    and framework for dynamic optimization.
 *    Copyright (C) 2010 by Joel Andersson, Moritz Diehl et al., K.U.Leuven. All rights reserved.
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

#include "idas_integrator.hpp"
#include "idas_internal.hpp"

using namespace std;
namespace CasADi{
namespace Sundials{

IdasIntegrator::IdasIntegrator(){ 
}

IdasIntegrator::IdasIntegrator(const FX& f, const FX& q){
  assignNode(new IdasInternal(f,q));
}

IdasInternal* IdasIntegrator::operator->(){
  return (IdasInternal*)(FX::operator->());
}

const IdasInternal* IdasIntegrator::operator->() const{
  return (const IdasInternal*)(FX::operator->());
}

void IdasIntegrator::setLinearSolver(const FX& jacx, const FX& linsol){
  (*this)->jacx_ = jacx;
  (*this)->linsol_ = linsol;
}


} // namespace Sundials
} // namespace CasADi


