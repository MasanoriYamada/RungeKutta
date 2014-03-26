//
//  divide.h
//  RugeKutta
//
//  Created by hoge on 2014/03/25.
//  Copyright (c) 2014年 yamada. All rights reserved.
//

#ifndef __RugeKutta__divide__
#define __RugeKutta__divide__

#include "math_func.h"
#include <complex>
typedef std::complex<double> Complex;

class divide 
{
public:
    divide(){};
    ~divide(){}
    enum {Minus=0, Plus=1};
    void Jost  (double phi, double dphi,
                       int l,
                       Complex k, double R,
                       Complex F[]);
    
};

#endif /* defined(__RugeKutta__divide__) */
