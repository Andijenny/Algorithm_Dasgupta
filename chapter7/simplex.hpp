/*
 * https://people.richland.edu/james/ictcm/2006/simplex.html
 * run example:
 * maximize obj f = 
 *      15 * x1 + 17 * x2 + 20 * x3 with conditions:
 *                     x2 -      x3 <= 2
 *       3 * x1  + 3 * x2 +  5 * x3 <= 15
 *       3 * x1 +  2 * x2 +      x3 <= 8
 *
 * first write as it dual form:
 *                     x2 -      x3 + s1 = 2
 *       3 * x1  + 3 * x2 +  5 * x3 + s2 = 15
 *       3 * x1 +  2 * x2 +      x3 + s3 = 8,
 * with                 s1, s2, s3  >= 0
 *
 *
 * A:
 *   x1 x2  x3 s1 s2 s3 rhs
 *  [[0, 1, -1, 1, 0, 0  2],
 *   [3, 3,  5, 0, 1, 0  15],
 *   [3, 2,  1, 0, 0, 1  8],
 * [-15, -17, -20, 0, 0, 0  0]]
 *
 * */

#pragma once

#include <vector>
#include <Dense>
#include <numeric>
#include <cmath>
#include <iostream>

class simplex {
public:
    simplex(const std::vector<std::vector<double>>& A, const std::vector<double>& C, const std::vector<double>& F)
    : nrows_(A.size())
    , ncols_(A.empty()?0:A[0].size())
    {
        if(ncols_ != 0) {
            A_.resize(nrows_+1, ncols_+nrows_+1);


            //A
            for(size_t i = 0;i < nrows_; ++i)
                A_.block(i, 0, 1, ncols_) = Eigen::Map<const Eigen::MatrixXd>(A[i].data(), 1, ncols_);

            //F
            A_.block(nrows_, 0, 1, ncols_) = (-1)*Eigen::Map<const Eigen::MatrixXd>(F.data(), 1, ncols_);

            //S
            A_.block(0, ncols_, nrows_, nrows_) = Eigen::MatrixXd::Identity(nrows_, nrows_);
            A_.block(nrows_, ncols_, 1, nrows_) = Eigen::MatrixXd::Zero(1, nrows_);

            // C
            A_.block(0, ncols_+nrows_, nrows_, 1) = Eigen::Map<const Eigen::MatrixXd>(C.data(), nrows_, 1);
            A_(nrows_, ncols_+nrows_) = 0;
        }
    }

    double solve(std::vector<double>& para)
    {
        if(A_.rows() == 0) return std::numeric_limits<double>::min();

        while(true) {
            size_t col;
            if(!pivotColumn(col)) break;
            if(!pivotRow(col)) break;
        }


        para.resize(ncols_, 0);
        for(size_t i = 0; i < ncols_; ++i) {
            double x;
            if(basicColumn(i, x))
                para[i] = x;
        }
        return A_(nrows_, ncols_+nrows_);
    }

    const auto& getFinalA() const {return A_;}
private:

    //find the most negative value in the last row.
    //note that we have written the objective function
    // F = ax1 +  bx2 .. as [-a, -b, ...],
    // so the most negative value is actually the larget 
    // coefficient in F
    bool pivotColumn(size_t& pos) const
    {
        pos = 0;
        double min = A_(nrows_, 0);
        for(size_t i = 1; i < (size_t)A_.cols(); ++i) {
            if(A_(nrows_, i) < 0 && A_(nrows_, i) < min) {
                min = A_(nrows_, i);
                pos = i;
            }
        }
        if(min >= 0) return false;
        return true;
    }

    // pivotColumn give us the directon where we move to,
    // pivotRow tells us how large we should move,
    // to avoid move outside the feasible region, choose the smallest step,
    // then eliminite the whole column except the pivotRow being 1
    bool pivotRow(size_t col)
    {
        size_t rowPos = A_.rows();
        double min = std::numeric_limits<double>::max();
        for(size_t i = 0; i < (size_t)A_.rows(); ++i) {
            if(A_(i, col) > 0) {
                const double ratio = A_(i, ncols_+nrows_)/A_(i, col);
                if(ratio < min) {
                    min = ratio;
                    rowPos = i;
                }
            }
        }
        if(rowPos == A_.rows()) return false;

        for(size_t i = 0; i < (size_t)A_.rows(); ++i) {
            if(i == rowPos) {
                A_.row(rowPos) /= A_(rowPos, col);
            }
            else {//eliminite A_(i, col)
                A_.row(i) -= A_.row(rowPos)*A_(i, col)/A_(rowPos, col);

            }
        }
        return true;
    }

    //basic column : has only one one and all others zero.
    bool basicColumn(size_t col, double& x) const
    {
        size_t count = 0;
        size_t rowPos;
        for(size_t j = 0; j < A_.rows(); ++j) {
            if(std::abs(A_(j, col)) > 0) {
                count++;
                rowPos = j;
            }

            if(count > 1) return false;
        }

        if(count == 1 && std::abs(A_(rowPos, col) - 1) < 1.0e-8) {
            x = A_(rowPos, A_.cols()-1); // the solution of that variable 
            return true;
        }

        return false;

    }

    size_t              nrows_;
    size_t              ncols_;
    Eigen::MatrixXd     A_;
};
