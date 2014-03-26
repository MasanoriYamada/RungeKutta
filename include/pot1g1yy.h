//
//  pot1g1yy.h
//  RugeKutta
//
//  Created by hoge on 2014/03/23.
//  Copyright (c) 2014年 yamada. All rights reserved.
//

#ifndef __RugeKutta__pot1g1yy__
#define __RugeKutta__pot1g1yy__

#include <iostream>

#include <vector>
#include <string>
#include <math.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include "PotInterface.h"

class Pot1g1yy : public PotInterface
{
public:
    Pot1g1yy(){};
    ~Pot1g1yy(){};
private:
    std::vector<double> p;
    
protected:
    int set(std::string ifile);
    double pot(double x);
    
};



#endif /* defined(__RugeKutta__pot1g1yy__) */
