//---------------------------------------------------------------------
/**
 * @file
 * @brief  Riccati Functions
 * @author Noriyoshi Ishii
 * @since  Thu Feb 27 20:22:42 JST 2014
 *
 * Copyright (C) 2014 by Noriyoshi Ishii
 *
 */
//---------------------------------------------------------------------

#include <math.h>
#include <complex>
#include <stdlib.h>

typedef std::complex<double> Complex;

#include "Riccati.h"

static Complex I(0.0, 1.0);

inline Complex Exp(Complex z)
{
  double x = real(z);
  double y = imag(z);
  return exp(x)*Complex(cos(y), sin(y));
}

//---------------------------------------------------------------------
/**
 * Jost Function
 */
//---------------------------------------------------------------------

void riccati::Jost(double phi, double dphi,
		   int l,
		   Complex k, double R,
		   Complex F[])
{
  Complex mat[2][2];

  Hankel(mat, l, k*R);

  mat[0][Minus] = (I/2.0) *          mat[0][Minus];
  mat[0][Plus]  = (I/2.0) * (-1.0) * mat[0][Plus];
  mat[1][Minus] = (I/2.0) * k      * mat[1][Minus];
  mat[1][Plus]  = (I/2.0) * (-k)   * mat[1][Plus];

  Complex det = mat[0][0]*mat[1][1] - mat[0][1]*mat[1][0];

  F[Plus]  = (+mat[1][1] * phi - mat[0][1] * dphi)/det;
  F[Minus] = (-mat[1][0] * phi + mat[0][0] * dphi)/det;
}

static Complex  h0(Complex z,int sign);
static Complex dh0(Complex z,int sign);

static Complex  h1(Complex z,int sign);
static Complex dh1(Complex z,int sign);

static Complex  h2(Complex z,int sign);
static Complex dh2(Complex z,int sign);

static Complex  h3(Complex z,int sign);
static Complex dh3(Complex z,int sign);

//---------------------------------------------------------------------
/**
 * Riccati Hankel Functions
 */
//---------------------------------------------------------------------

void riccati::Hankel(Complex (*h)[2], int l, Complex z)
{
  switch(l){
  case 0:
    h[0][Plus]  =  h0(z,Plus);
    h[1][Plus]  = dh0(z,Plus);
        
    h[0][Minus] =  h0(z,Minus);
    h[1][Minus] = dh0(z,Minus);
    break;
  case 1:
    h[0][Plus]  =  h1(z,Plus);
    h[1][Plus]  = dh1(z,Plus);
        
    h[0][Minus] =  h1(z,Minus);
    h[1][Minus] = dh1(z,Minus);
    break;
  case 2:
    h[0][Plus]  =  h2(z,Plus);
    h[1][Plus]  = dh2(z,Plus);
        
    h[0][Minus] =  h2(z,Minus);
    h[1][Minus] = dh2(z,Minus);
    break;
  case 3:
    h[0][Plus]  =  h3(z,Plus);
    h[1][Plus]  = dh3(z,Plus);
        
    h[0][Minus] =  h3(z,Minus);
    h[1][Minus] = dh3(z,Minus);
    break;
  default:
    fprintf(stderr,
	    "ERROR: riccati::Hankel with l > 3 is not implemented yet.\n");
    exit(1);
  }
}

using namespace riccati;

//---------------------------------------------------------------------
// Riccati Hankel Functions of l=0
//---------------------------------------------------------------------

static Complex h0(Complex z,int sign)
{
  Complex ret;
  switch(sign){
  case Plus:  ret = Exp(+I*z); break;
  case Minus: ret = Exp(-I*z); break;
  default:
    fprintf(stderr, "ERROR(h0(Complex,int)): sign=%d\n", sign);
    exit(1);
  }
  return ret;
}

static Complex dh0(Complex z,int sign)
{
  Complex ret;
  switch(sign){
  case Plus:  ret = +I * Exp(+I*z); break;
  case Minus: ret = -I * Exp(-I*z); break;
  default:
    fprintf(stderr, "ERROR(dh0(Complex,int)): sign=%d\n", sign);
    exit(1);
  }
  return ret;
}

//---------------------------------------------------------------------
// Riccati Hankel Functions of l=1
//---------------------------------------------------------------------

static Complex h1(Complex z,int sign)
{
  Complex ret;
  switch(sign){
  case Plus:  ret = (-I + 1.0/z) * Exp(+I*z); break;
  case Minus: ret = (+I + 1.0/z) * Exp(-I*z); break;
  default:
    fprintf(stderr, "ERROR(h1(Complex,int)): sign=%d\n", sign);
    exit(1);
  }
  return ret;
}

static Complex dh1(Complex z,int sign)
{
  Complex zz = z*z;

  Complex ret;
  switch(sign){
  case Plus:  ret = (1.0 + I/z - 1.0/zz) * Exp(+I*z); break;
  case Minus: ret = (1.0 - I/z - 1.0/zz) * Exp(-I*z); break;
  default:
    fprintf(stderr, "ERROR(dh1(Complex,int)): sign=%d\n", sign);
    exit(1);
  }
  return ret;
}

//---------------------------------------------------------------------
// Riccati Hankel Functions of l=2
//---------------------------------------------------------------------

static Complex h2(Complex z,int sign)
{
  Complex zz = z*z;

  Complex ret;
  switch(sign){
  case Plus:  ret = (-1.0 - 3.0*I/z + 3.0/zz) * Exp(+I*z); break;
  case Minus: ret = (-1.0 + 3.0*I/z + 3.0/zz) * Exp(-I*z); break;
  default:
    fprintf(stderr, "ERROR(h1(Complex,int)): sign=%d\n", sign);
    exit(1);
  }
  return ret;
}

static Complex dh2(Complex z,int sign)
{
  Complex zz  = z*z;
  Complex zzz = zz*z;

  Complex ret;
  switch(sign){
  case Plus:  ret = (-I + 3.0/z + 6.0*I/zz - 6.0/zzz) * Exp(+I*z); break;
  case Minus: ret = (-I + 3.0/z - 6.0*I/zz - 6.0/zzz) * Exp(-I*z); break;
  default:
    fprintf(stderr, "ERROR(dh1(Complex,int)): sign=%d\n", sign);
    exit(1);
  }
  return ret;
}

//---------------------------------------------------------------------
// Riccati Hankel Functions of l=3
//---------------------------------------------------------------------

static Complex h3(Complex z,int sign)
{
  Complex zz  = z*z;
  Complex zzz = zz*z;

  Complex ret;
  switch(sign){
  case Plus:  ret = (+I - 6.0/z - 15.0*I/zz + 15.0/zzz) * Exp(+I*z); break;
  case Minus: ret = (-I - 6.0/z + 15.0*I/zz + 15.0/zzz) * Exp(-I*z); break;
  default:
    fprintf(stderr, "ERROR(h3(Complex,int)): sign=%d\n", sign);
    exit(1);
  }
  return ret;
}

static Complex dh3(Complex z,int sign)
{
  Complex zz   = z*z;
  Complex zzz  = zz*z;
  Complex zzzz = zz*zz;

  Complex ret;
  switch(sign){
  case Plus:  ret = (-1.0 - 6.0*I/z + 21.0/zz + 45.0*I/zzz - 45.0/zzzz) * Exp(+I*z); break;
  case Minus: ret = (-1.0 + 6.0*I/z + 21.0/zz - 45.0*I/zzz - 45.0/zzzz) * Exp(-I*z); break;
  default:
    fprintf(stderr, "ERROR(dh3(Complex,int)): sign=%d\n", sign);
    exit(1);
  }
  return ret;
}


