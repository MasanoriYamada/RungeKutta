//---------------------------------------------------------------------
/**
 * @file
 * @brief  spline
 * @author Noriyoshi Ishii
 * @since  Mon Feb 24 19:28:22 JST 2014
 *
 * Copyright (C) 2014 by Noriyoshi Ishii
 *
 */
//---------------------------------------------------------------------

#include "spline.h"

//---------------------------------------------------------------------
/**
 * The destructor
 */
//---------------------------------------------------------------------

spline::~spline()
{
  if(ptr != 0) delete ptr;
}

//---------------------------------------------------------------------
/**
 * The default constructor
 */
//---------------------------------------------------------------------

spline::spline()
  : x(), y(), ptr(0)
{}

//---------------------------------------------------------------------
/**
 * Main constructor
 */
//---------------------------------------------------------------------

spline::spline(double xtmp[], double ytmp[], int length)
  : x(length,xtmp), y(length,ytmp), ptr(new Spline_interp(x,y))
{}

//---------------------------------------------------------------------
/**
 * Copy constructor
 */
//---------------------------------------------------------------------

spline::spline(const spline& rhs)
  : x(rhs.x), y(rhs.y), ptr(new Spline_interp(x,y))
{}

//---------------------------------------------------------------------
/**
 * The assignment operator
 */
//---------------------------------------------------------------------

spline& spline::operator=(const spline& rhs)
{
  if(ptr != 0) delete ptr;

  x = rhs.x;
  y = rhs.y;

  ptr = new Spline_interp(x,y);

  return *this;
}


//---------------------------------------------------------------------
/**
 * operator+=
 */
//---------------------------------------------------------------------

spline& spline::operator+=(const spline& other)
{
  if(x.size() != other.x.size()){
    fprintf(stderr,
	    "ERROR: inconsistent size in spline::operator+=(const spline&)\n");
    exit(1);
  }
  for(int i = 0; i < x.size(); i++){
    if(x[i] != other.x[i]){
      fprintf(stderr,
	      "ERROR: inconsistent x[] in spline::operator+=(const spline&)\n");
      exit(1);
    }
  }

  for(int i = 0; i < x.size(); i++){
    y[i] += other.y[i];
  }

  if(NULL != ptr) delete ptr;

  ptr = new Spline_interp(x,y);

  return *this;
}

//---------------------------------------------------------------------
/**
 * operator-=
 */
//---------------------------------------------------------------------

spline& spline::operator-=(const spline& other)
{
  if(x.size() != other.x.size()){
    fprintf(stderr,
	    "ERROR: inconsistent size in spline::operator+=(const spline&)\n");
    exit(1);
  }
  for(int i = 0; i < x.size(); i++){
    if(x[i] != other.x[i]){
      fprintf(stderr,
	      "ERROR: inconsistent x[] in spline::operator+=(const spline&)\n");
      exit(1);
    }
  }

  for(int i = 0; i < x.size(); i++){
    y[i] -= other.y[i];
  }

  if(NULL != ptr) delete ptr;

  ptr = new Spline_interp(x,y);

  return *this;
}

//---------------------------------------------------------------------
/**
 * operator*=
 */
//---------------------------------------------------------------------

spline& spline::operator*=(double z)
{
  for(int i = 0; i < x.size(); i++){
    y[i] *= z;
  }
  
  if(NULL != ptr) delete ptr;

  ptr = new Spline_interp(x,y);

  return *this;
}

//---------------------------------------------------------------------
/**
 * unary minus
 */
//---------------------------------------------------------------------

spline& spline::unary_minus()
{
  for(int i = 0; i < x.size(); i++){
    y[i] = -y[i];
  }

  if(NULL != ptr) delete ptr;

  ptr = new Spline_interp(x,y);

  return *this;
}
