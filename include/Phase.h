//
//  Phase.h
//  RugeKutta
//
//  Created by hoge on 2014/04/01.
//  Copyright (c) 2014年 yamada. All rights reserved.
//

#ifndef __RugeKutta__Phase__
#define __RugeKutta__Phase__

#include <complex>
typedef std::complex<double> Complex;

class Phase
{
public:
    Phase(){};
    ~Phase(){};
Complex    getPhase(Complex S);
    
};


#endif /* defined(__RugeKutta__Phase__) */
