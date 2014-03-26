//
//  pot1g1y.h
//  RugeKutta
//
//  Created by hoge on 2014/03/21.
//  Copyright (c) 2014年 yamada. All rights reserved.
//

#ifndef __RugeKutta__pot1g1y__
#define __RugeKutta__pot1g1y__

#include <vector>
#include <string>
#include <math.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include "PotInterface.h"

class Pot1g1y : public PotInterface
{
public:
    Pot1g1y(){};
    ~Pot1g1y(){};
private:
    std::vector<double> p;
    
protected:
    int set(std::string ifile);
    double pot(double x);
    
};


#endif /* defined(__RugeKutta__pot1g1y__) */
