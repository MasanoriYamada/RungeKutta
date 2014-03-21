//---------------------------------------------------------------------
/**
 * @file
 * @bried  spline
 * @author Noriyoshi Ishii
 */
//---------------------------------------------------------------------

#ifndef IS_INCLUDED_SPLINE_H
#define IS_INCLUDED_SPLINE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "NR304/nr3.h"
#include "NR304/interp_1d.h"

struct spline {
  VecDoub x;
  VecDoub y;

  Spline_interp* ptr;

  ~spline();
  spline();
  spline(double xtmp[],double ytmp[],int length);
  spline(const spline& rhs);

  spline& operator=(const spline& rhs);

  double operator()(double x) {
    if(ptr == 0){
      return 0;
    }
    else{
      return (*ptr).interp(x);
    }
  }

  //---------------------------------------------------------------------
  // arithmetic
  //---------------------------------------------------------------------
  spline& operator+=(const spline& other);
  spline& operator-=(const spline& other);
  spline& operator*=(double x);
  spline& operator/=(double x) { return operator*=(1.0/x); }
  spline& unary_minus();
};

//---------------------------------------------------------------------
// arithmetic
//---------------------------------------------------------------------

inline spline operator+(spline lhs, const spline& rhs) { return lhs += rhs; }
inline spline operator-(spline lhs, const spline& rhs) { return lhs -= rhs; }

inline spline operator*(spline spl, double x) { return spl*=x; }
inline spline operator*(double x, spline spl) { return spl*=x; }
inline spline operator/(spline spl, double x) { return spl/=x; }

inline spline operator-(spline spl) { return spl.unary_minus(); }
inline spline operator+(spline spl) { return spl; }

#endif
