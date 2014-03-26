//
//  pot1g1yy.cpp
//  RugeKutta
//
//  Created by hoge on 2014/03/23.
//  Copyright (c) 2014年 yamada. All rights reserved.
//

#include "pot1g1yy.h"

int Pot1g1yy::set(std::string inFileName)
{
    std::fstream infile;
    int id = 0;
    int line_=1;
    infile.open(inFileName.c_str(),std::ios::in);
    if (!infile.is_open()) {
        std::cerr << "ERROR file can't open (no exist)::"<<inFileName<<std::endl;
        exit(1);
        return EXIT_FAILURE;
    }
    if (infile.fail()){
        std::cerr << "ERROR file size is 0 (can open)::"<<inFileName<<std::endl;
        exit(1);
        return EXIT_FAILURE;
    }
    std::string tmpdata;
    do{
        for (int tmpid =0;tmpid <line_;tmpid++){
            infile>>tmpdata;
        }
        double tmp =0.0;
        infile>>tmp;
        p.push_back( tmp );
        //for debug
        //std::cout<<tmp<<std::endl;
        //debug end

        int iChar = 0;
        while ((iChar = infile.get()) != '\n' && iChar != EOF) {}
        if (id>10000000) {
            std::cerr << "ERROR maybe imput file all number 0::"<<inFileName<<std::endl;
            exit(1);
        }
        id = id + 1;
    }
    while ( !infile.eof() ); // important for all 0 file
    id = id -1;
    static int tmp = 0;
    if (tmp==0) {
        //std::cout <<"#reading text type data size is_open;;"<<id<<" line;;"<<line_ + 1<<std::endl;
        tmp=tmp+1;
    }
    infile.close();
    return 0;
}

double Pot1g1yy::pot(double x)
{
    //[1/MeV]=>[fm]
    x*=197.3;
    if (x==0) {
        return p[0];
    }
    else {
        return p[0]*exp(-p[1]*x*x)+ p[2]*((1 - exp(-p[3]*x*x)))*((1 - exp(-p[3]*x*x))/x)*(exp(-p[4]*x))*(exp(-p[4]*x)/x);
    }
}
