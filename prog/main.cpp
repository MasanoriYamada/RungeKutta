//---------------------------------------------------------------------
/**
 * @file
 * @brief  Simple S-wave Schroedinger equation by Runge-Kutta
 * @author Noriyoshi Ishii
 * @since  Thu Feb 27 05:43:47 JST 2014
 *
 * Copyright (C) 2014 by Masanori Yamada
 *
 */
//---------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include <complex>

typedef std::complex<double> Complex;

#include "NR304/nr3.h"
#include "NR304/odeint.h"
#include "NR304/stepper.h"
#include "NR304/stepperdopr5.h"

#include "spline.h"
#include "Riccati.h"

#define HbarC 197.3

double m;
double E;
const char* ifname=NULL;
double R1;
double dr;

spline V; //< potential by spline

bool   is_jost = false;
double R_jost = 0.0;

//---------------------------------------------------------------------
/**
 * @brief load the potential
 *
 */
//---------------------------------------------------------------------

static spline load_V(const char* fname)
{
  FILE* fp;
  if((fp = fopen(fname, "r"))==0){
    fprintf(stderr, "cannot fopen '%s' for reading\n", fname);
    exit(1);
  }
  char   str[2048];
  double xtmp[1024*32];
  double ytmp[1024*32];
  int    length = 0;
  while(!feof(fp)){
    if(fgets(str, 2048, fp) != NULL){
      if(feof(fp))                     break;
      if(strncmp(str, "#END", 4) == 0) break;
      if(str[0] == '#')                continue;

      sscanf(str, "%lf %lf", &xtmp[length], &ytmp[length]);
      xtmp[length] /= HbarC;
      length++;
    }
    else{
      break;
    }
  }
  fclose(fp);

  return spline(xtmp, ytmp, length);
}

//---------------------------------------------------------------------
/**
 * description of usage
 */
//---------------------------------------------------------------------

void usage(const char* msg=NULL,...)
{
  fprintf(stderr,
	  "usage: swave [OPTIONS]\n"
	  "OPTIONS:\n"
	  "     -E    (energy[MeV])\n"
	  "     -mass (mass[MeV])\n"
	  "     -ifname (ifname[potential]: V [MeV] v.s. r [fm])\n"
	  "     -solve (R1[fm]) (dr[fm])\n"
	  "     -Jost  (R[fm])\n"
	  );
  if(NULL != msg){
    fprintf(stderr, "\n");

    va_list args;
    va_start(args, msg);

    vfprintf(stderr, msg, args);

    va_end(args);
  }
}

//---------------------------------------------------------------------
/**
 * command line options
 */
//---------------------------------------------------------------------

static void args(int argc, char* argv[])
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
      V = load_V(ifname);
      argc-=2; argv+=2;
      continue;
    }
    if(strcmp(argv[0],"-solve")==0){
      R1 = atof(argv[1])/HbarC;
      dr = atof(argv[2])/HbarC;
      argc-=3; argv+=3;
      continue;
    }
    if(strcmp(argv[0],"-Jost")==0){
      is_jost = true;
      R_jost  = atof(argv[1])/HbarC;
      argc-=2; argv+=2;
      continue;
    }
    
    usage("ERROR: invalid option '%s'\n", argv[0]);
    exit(1);
  }
}

//---------------------------------------------------------------------
/**
 * Derivative
 */
//---------------------------------------------------------------------

struct Derivs {
  void operator()(const Doub x, VecDoub_I& y, VecDoub_O& dydx){
    dydx[0] = y[1];
    dydx[1] = (m*V(x) - m*E)*y[0];
  }
};

//---------------------------------------------------------------------
/**
 * The main part
 */
//---------------------------------------------------------------------

int main(int argc,char* argv[])
{
  args(argc, argv);

  //---------------------------------------------------------------------
  // Runge-Kutta
  //---------------------------------------------------------------------
  Derivs derivs;
  VecDoub ystart(4);
  ystart[0] = 0.0;
  ystart[1] = 1.0;
  Output phi(1000);

  Odeint<StepperDopr5<Derivs> >
    ode(ystart, 0.0, R1, 1.0e-8, 1.0e-8, dr, 0.0, phi, derivs);
  ode.integrate();

  //---------------------------------------------------------------------
  // output
  //---------------------------------------------------------------------
  if(false == is_jost){
    for(int i = 0; i < phi.count; i++){
      double r = phi.xsave[i] * HbarC;
      printf("%1.16e  %1.16e %1.16e\n",
	     r,
	     phi.ysave[0][i]/r,
	     phi.ysave[1][i]);
    }
  }
  else{
    Complex k; // Complex momentum
    if(E >= 0.0){
      k = Complex(sqrt(m*E),0.0);
    }
    else{
      k = Complex(0.0, sqrt(-m*E));
    }

    double Phi, dPhi, R;
    for(int i = 0; i < phi.count; i++){
      if(phi.xsave[i] > R_jost) break;
      R    = phi.xsave[i];
      Phi  = phi.ysave[0][i];
      dPhi = phi.ysave[1][i];
    }
    
    Complex F[2];
    riccati::Jost(Phi, dPhi,
		  0,
		  k, R,
		  F);
    Complex S = F[riccati::Minus]/F[riccati::Plus];
    printf("# F(+k)  = %1.16e %1.16e\n",
	   real(F[riccati::Plus]),  imag(F[riccati::Plus]));
    printf("# F(-k)  = %1.16e %1.16e\n",
	   real(F[riccati::Minus]), imag(F[riccati::Minus]));
    printf("# S(k)   = %1.16e %1.16e\n", real(S), imag(S));
    printf("# 1/S(k) = %1.16e %1.16e\n", real(1.0/S), imag(1.0/S));

    for(int i = 0; i < phi.count; i++){
      double r = phi.xsave[i];
      Complex h[2][2];
      const Complex I(0.0, 1.0);

      riccati::Hankel(h, 0, k*r);

      printf("%1.16e  %1.16e %1.16e %1.16e %1.16e\n",
	     r * HbarC,
	     phi.ysave[0][i]/r,
	     phi.ysave[1][i],
	     +real((I/2.0)*F[riccati::Plus] *h[0][riccati::Minus])/r,
	     -real((I/2.0)*F[riccati::Minus]*h[0][riccati::Plus ])/r
	     );
    }

  }

  return 0;
}
