//
//  Args.cpp
//  RugeKutta
//
//  Created by hoge on 2014/03/21.
//  Copyright (c) 2014年 yamada. All rights reserved.
//

#include "Args.h"


void Args::set(int argc, char* argv[])
{
    argc--; argv++;
    
    if(argc==0) { usage(); exit(1); }
    
    while(argc > 0 && argv[0][0]=='-'){
        if(strcmp(argv[0],"-E")==0){
            E = atof(argv[1]);
            argc-=2; argv+=2;
            continue;
        }
        if(strcmp(argv[0],"-mass")==0){
            m = atof(argv[1]);
            argc-=2; argv+=2;
            continue;
        }
        if(strcmp(argv[0],"-ifname")==0){
            ifname = argv[1];
            argc-=2; argv+=2;
            continue;
        }
        if(strcmp(argv[0],"-solve")==0){
            //[fm]->[1/MeV]
            R1 = atof(argv[1])/HbarC;
            dr = atof(argv[2])/HbarC;
            argc-=3; argv+=3;
            continue;
        }
        if(strcmp(argv[0],"-Jost")==0){
            //[fm]->[1/MeV]
            is_jost = true;
            R_jost  = atof(argv[1])/HbarC;
            argc-=2; argv+=2;
            continue;
        }
        if(strcmp(argv[0],"-Func")==0){
            func_name = argv[1];
            argc-=2; argv+=2;
            continue;
        }
        
        usage();
        exit(1);
    }
}

void Args::usage()
{
    fprintf(stderr,
            "usage: RungeKutta [OPTIONS]\n"
            "OPTIONS:\n"
            "     -E    (energy[MeV])\n"
            "     -mass (mass[MeV])\n"
            "     -ifname (ifname[potential]: V [MeV] v.s. r [fm])\n"
            "     -solve (R1[fm]) (dr[fm])\n"
            "     -Jost  (R[fm])\n"
            );
    }
