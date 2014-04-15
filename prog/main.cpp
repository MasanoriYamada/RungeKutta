//
//  main.cpp
//  RugeKutta
//
//  Created by hoge on 2014/03/21.
//  Copyright (c) 2014 yamada. All rights reserved.
//

#include <iostream>

#include "Args.h"
#include "divide.h"
#include "Phase.h"
#include "pot1g1y.h"
#include "pot1g1yy.h"

#include "NR304/nr3.h"
#include "NR304/odeint.h"
#include "NR304/stepper.h"
#include "NR304/stepperdopr5.h"

int l = 0;
Args args;
static Potential*  potential;

//---------------------------------------------------------------------
//   Derivative
//---------------------------------------------------------------------

struct Derivs {
    void operator()(const Doub x, VecDoub_I& y, VecDoub_O& dydx){
        dydx[0] = y[1];
        dydx[1] = (args.m*potential->pot(x) - args.m*args.E)*y[0];
    }
};


//---------------------------------------------------//
//    main
//---------------------------------------------------//

int main(int argc, char* argv[])
{
    args.set(argc, argv);

//---------------------------------------------------//
//    generate potential part
//---------------------------------------------------//
    if("1g1yy" == args.func_name)
    {
        potential = new Potential(new Pot1g1yy());
    }
    else if("1g1y" == args.func_name)
    {
        potential = new Potential(new Pot1g1y());
    }
    else
    {
        std::cout<<"func type is strange = "<<args.func_name<<std::endl;
    }
    potential->set(args.ifname);
//---------------------------------------------------//
//    solve schrodinger eq
//---------------------------------------------------//
    
    {    
      Derivs derivs;
      VecDoub ystart(4);
      ystart[0] = 0.0;
      ystart[1] = 1.0;
      Output phi(1000);
      
      Odeint<StepperDopr5<Derivs> >
	ode(ystart, 0.0, args.R1, 1.0e-8, 1.0e-8, args.dr, 0.0, phi, derivs);
      ode.integrate(); 
      

//---------------------------------------------------------------------
// solve jost function
//---------------------------------------------------------------------   
    double Phi = 0.0;
    double dPhi = 0.0;
    double R = 0.0;

    Complex k;
    // k>0  k is real , k<0 k is imaginary
    if(args.E >= 0.0){
        k = Complex(sqrt(args.m*args.E),0.0);
    }
    else{
        k = Complex(0.0, sqrt(-args.m*args.E));
    }
    
//for search
//    for (double rE = -1.0 ; rE <0.0 ; rE = rE + 0.01)
//    {
//        for (double iE = -4.5 ; iE <-3.0 ; iE = iE + 0.01)
//        {
//            k = Complex(sqrt(-args.m*rE), sqrt(-args.m*iE));
    
    for(int i = 0; i < phi.count; i++){
        if(phi.xsave[i] > args.R_jost) break;
        R    = phi.xsave[i];
        Phi  = phi.ysave[0][i];
        dPhi = phi.ysave[1][i];
    }
    
//---------------------------------------------------------------------
// calc S-matrix
//---------------------------------------------------------------------
    
    Complex F[2];
    divide div;
    div.Jost(Phi, dPhi, 0, k, R, F);

    Complex S = F[divide::Minus]/F[divide::Plus];
    Phase phase;
//---------------------------------------------------------------------
// out put
//---------------------------------------------------------------------
    
    printf("%1.16e %1.16e %1.16e %1.16e %1.16e\n", args.E, real(1.0/S), imag(1.0/S),
           phase.getPhase(S).real(), phase.getPhase(S).imag());

//printf("%1.16e %1.16e %1.16e %1.16e \n", rE, iE , S.real(), S.imag());
//        }
//    }

    /*
    printf("%1.16e %1.16e %1.16e\n", args.E, real(1.0/S), imag(1.0/S));
    
    printf("# F(+k)  = %1.16e %1.16e\n",
           real(F[divide::Plus]),  imag(F[divide::Plus]));
    printf("# F(-k)  = %1.16e %1.16e\n",
           real(F[divide::Minus]), imag(F[divide::Minus]));
    printf("# S(k)   = %1.16e %1.16e\n", real(S), imag(S));
    printf("# 1/S(k) = %1.16e %1.16e\n", real(1.0/S), imag(1.0/S));
    printf("#r[fm]                  (1/r)phi(x)            d/dr(phi(x))           hankel(+)               hankel(-)\n");
 
    for(int i = 0; i < phi.count; i++){
        double r = phi.xsave[i];
        Complex h[2][2];
        const Complex I(0.0, 1.0);

        math_func::Hankel(h, l, k*r);
        printf("%1.16e  %1.16e %1.16e %1.16e %1.16e\n",
               r * args.HbarC,
               phi.ysave[0][i]/r,
               phi.ysave[1][i],
               +real((I/2.0)*F[divide::Plus] *h[0][divide::Minus])/r,
               -real((I/2.0)*F[divide::Minus]*h[0][divide::Plus ])/r
               );
    
	       }
std::cout<< "# ALL finished"<< std::endl;
    */
    }
return 0;
}

    
