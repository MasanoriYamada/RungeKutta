//
//  divide.cpp
//  RugeKutta
//
//  Created by hoge on 2014/03/25.
//  Copyright (c) 2014年 yamada. All rights reserved.
//

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/triangular.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <complex>

#include "divide.h"
#include "math_func.h"

typedef boost::numeric::ublas::vector<Complex> cvector;
typedef boost::numeric::ublas::matrix<Complex> cmatrix;
typedef std::complex<double> Complex;
static Complex I(0.0, 1.0);


void divide::Jost  (double phi, double dphi,
            int l,
            Complex k, double R,
            Complex F[])
{
    // set value
    cvector vec(2);
    vec[0] = phi;
    vec[1] = dphi;
    Complex mat[2][2];
    
    math_func::Hankel(mat, l, k*R);
    
    cmatrix cmat(2,2);
    cmat(0,Minus)= (I/2.0) * mat[0][Minus];      cmat(0,Plus) = (I/2.0) * (-1.0) * mat[0][Plus];
    cmat(1,Minus)= (I/2.0) * k * mat[1][Minus];  cmat(1,Plus) = (I/2.0) * (-1.0) * k * mat[1][Plus];
    
    // solve
    boost::numeric::ublas::permutation_matrix<> pm(cmat.size1());
    lu_factorize(cmat,pm);
    lu_substitute(cmat,pm,vec);
    
    F[Plus]  = vec[0];
    F[Minus] = vec[1];
    
}

