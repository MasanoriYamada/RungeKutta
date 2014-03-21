//---------------------------------------------------------------------
/**
 * @file
 * @brief  Riccati Functions
 * @author Noriyoshi Ishii
 * @since  Thu Feb 27 20:19:41 JST 2014
 *
 * Copyright (C) 2014 by Noriyoshi Ishii
 *
 */
//---------------------------------------------------------------------

#ifndef IS_INCLUDED_RICCATI_H_140227
#define IS_INCLUDED_RICCATI_H_140227

#include <complex>

typedef std::complex<double> Complex;

namespace riccati {
  enum {Minus=0, Plus=1};

  extern void Hankel(Complex (*h)[2], int l, Complex z);
  extern void Jost  (double phi, double dphi,
		     int l,
		     Complex k, double R, 
		     Complex F[]);
}

#endif
