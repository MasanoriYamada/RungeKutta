//
//  math_func.cpp
//  RugeKutta
//
//  Created by hoge on 2014/03/25.
//  Copyright (c) 2014年 yamada. All rights reserved.
//

#include "math_func.h"
#include "stdlib.h"
#include <math.h>
#include <complex>

typedef std::complex<double> Complex;

static Complex I(0.0, 1.0);

inline Complex Exp(Complex z)
{
    double x = real(z);
    double y = imag(z);
    return exp(x)*Complex(cos(y), sin(y));
}

Complex  h0(Complex z,int sign);
Complex dh0(Complex z,int sign);

Complex  h1(Complex z,int sign);
Complex dh1(Complex z,int sign);

Complex  h2(Complex z,int sign);
Complex dh2(Complex z,int sign);

Complex  h3(Complex z,int sign);
Complex dh3(Complex z,int sign);

//---------------------------------------------------------------------
// math_func Hankel Functions
//---------------------------------------------------------------------

void math_func::Hankel(Complex (*h)[2], int l, Complex z)
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
                    "ERROR: math_func::Hankel with l > 3 is not implemented yet.\n");
            exit(1);
    }
}

using namespace math_func;

//---------------------------------------------------------------------
// math_func Hankel Functions of l=0
//---------------------------------------------------------------------

Complex h0(Complex z,int sign)
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

Complex dh0(Complex z,int sign)
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
// math_func Hankel Functions of l=1
//---------------------------------------------------------------------

Complex h1(Complex z,int sign)
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

Complex dh1(Complex z,int sign)
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
// math_func Hankel Functions of l=2
//---------------------------------------------------------------------

Complex h2(Complex z,int sign)
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

Complex dh2(Complex z,int sign)
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
// math_func Hankel Functions of l=3
//---------------------------------------------------------------------

Complex h3(Complex z,int sign)
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

Complex dh3(Complex z,int sign)
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



