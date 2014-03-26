//
//  math_func.h
//  RugeKutta
//
//  Created by hoge on 2014/03/25.
//  Copyright (c) 2014年 yamada. All rights reserved.
//

#ifndef __RugeKutta__math_func__
#define __RugeKutta__math_func__

#include <complex>

typedef std::complex<double> Complex;

namespace math_func {
    enum {Minus=0, Plus=1};
    void Hankel(Complex (*h)[2], int l, Complex z);
}

#endif /* defined(__RugeKutta__math_func__) */
