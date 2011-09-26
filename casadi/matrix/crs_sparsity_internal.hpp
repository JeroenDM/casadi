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

#ifndef CRS_SPARSITY_INTERNAL_HPP
#define CRS_SPARSITY_INTERNAL_HPP

#include "crs_sparsity.hpp"

namespace CasADi{

class CRSSparsityInternal : public SharedObjectNode{
  public:
    /// Construct a sparsity pattern from vectors
    CRSSparsityInternal(int nrow, int ncol, std::vector<int> col, std::vector<int> rowind) : nrow_(nrow), ncol_(ncol), col_(col), rowind_(rowind) { sanityCheck(false); }
    
    /// Check if the dimensions and rowind,col vectors are compatible
    void sanityCheck(bool complete=false) const;

    /// Calculate the elimination tree
    std::vector<int> eliminationTree(bool ata) const;
    
    /// Find strongly connected components
    int depthFirstSearch(int j, int top, std::vector<int>& xi, std::vector<int>& pstack, const std::vector<int>& pinv, std::vector<bool>& marked) const;

    /// Find the strongly connected components of a square matrix
    void stronglyConnectedComponents() const;

    /// Transpose the matrix and get the reordering of the non-zero entries, i.e. the non-zeros of the original matrix for each non-zero of the new matrix
    CRSSparsity transpose(std::vector<int>& mapping) const;

    /// Breadth-first search for coarse decomposition
    void breadthFirstSearch(int n, int *wi, int *wj, int *queue, const int *imatch, const int *jmatch, int mark);
    
    /// Collect matched rows and columns into p and q
    static void matched(int n, const int *wj, const int *imatch, int *p, int *q, int *cc, int *rr, int set, int mark);
    
    /// Collect unmatched rows into the permutation vector p
    static void unmatched(int m, const int *wi, int *p, int *rr, int set);
    
    /// return 1 if row i is in R2
    static int rprune (int i, int j, double aij, void *other);

    /// Compute the Dulmage-Mendelsohn decomposition
    void dulmageMendelsohn(int seed) const;
    
    /// Compute the maximum transversal (maximum matching)
    void maxTransversal(std::vector<int>& imatch, std::vector<int>& jmatch, int seed) const;
    
    /// Find an augmenting path
    void augmentingPath(int k, int *jmatch, int *cheap, int *w, int *js, int *is, int *ps) const;
    
    /// Get the row for each nonzero
    std::vector<int> getRow() const;

    /// Number of structural non-zeros
    int size() const;

    /// Clone
    virtual CRSSparsityInternal* clone() const{ return new CRSSparsityInternal(*this); }

    /// Print representation
    virtual void repr(std::ostream &stream) const;

    /// Print description
    virtual void print(std::ostream &stream) const;

    /// Number of rows
    int nrow_;
    
    /// Number of columns
    int ncol_;
    
    /// vector of length nnz containing the columns for all the indices of the non-zero elements
    std::vector<int> col_;
    
    /// vector of length n+1 containing the index of the last non-zero element up till each row 
    std::vector<int> rowind_;
    
};

} // namespace CasADi

#endif // CRS_SPARSITY_INTERNAL_HPP
