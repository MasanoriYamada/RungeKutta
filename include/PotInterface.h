//
//  PotInterface.h
//  RugeKutta
//
//  Created by hoge on 2014/03/21.
//  Copyright (c) 2014年 yamada. All rights reserved.
//

#ifndef __RugeKutta__PotInterface__
#define __RugeKutta__PotInterface__

#include <string>

class PotInterface
{
public:
    //PotInterface(){};
    //~PotInterface(){};
    
    virtual int set(std::string ifile) = 0;
    virtual double pot(double x) = 0;
};


// contex class

class Potential
{

public:
    Potential(PotInterface* pot_obj);
    ~Potential();
    // x[1/MeV] pot[MeV]
    double pot(double x);
    void set(std::string ifile);
private:
    PotInterface* pot_obj_;
};


#endif /* defined(__RugeKutta__PotInterface__) */
