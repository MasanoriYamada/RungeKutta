//
//  PotInterface.cpp
//  RugeKutta
//
//  Created by hoge on 2014/03/21.
//  Copyright (c) 2014年 yamada. All rights reserved.
//


#include "PotInterface.h"
#include "stdlib.h"


Potential::Potential(PotInterface* pot_obj)
{
    this->pot_obj_ = pot_obj;
}
Potential::~Potential()
{
    free (pot_obj_ );
}

double Potential::pot(double x)
{
    return     this->pot_obj_->pot(x);
}
void Potential::set(std::string ifile)
{
    this->pot_obj_->set(ifile);
}
