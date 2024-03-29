//
//  Phase.cpp
//  RugeKutta
//
//  Created by hoge on 2014/04/01.
//  Copyright (c) 2014年 yamada. All rights reserved.
//

#include "Phase.h"
#include <math.h>

static Complex I(0.0, 1.0);

Complex Phase::getPhase(Complex S)
{
    Complex phase = log(S) / (2.0 * I);
    Complex degree = phase * 180.0 / M_PI;
    if(degree.real() < 0.0)
      {
	degree = degree + 180.0;
      }
    return degree;
}

Complex Phase::getKcotPhase(Complex k,Complex S)
{
  Complex rad = log(S) / (2.0 * I);
  return k / tan(rad);
}
