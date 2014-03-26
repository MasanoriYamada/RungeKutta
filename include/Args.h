//
//  Args.h
//  RugeKutta
//
//  Created by hoge on 2014/03/21.
//  Copyright (c) 2014年 yamada. All rights reserved.
//

#ifndef __RugeKutta__Args__
#define __RugeKutta__Args__
#include <string>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

class Args
{
public:
    double m;
    double E;
    std::string ifname;
    double R1;
    double dr;
    bool   is_jost;
    double R_jost;
    static const double HbarC = 197.3;
    

    
public:
    Args(){};
    ~Args(){};
    void set(int argc, char* argv[]);

private:
    void usage();
};


#endif /* defined(__RugeKutta__Args__) */
