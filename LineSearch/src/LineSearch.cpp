#include <stdlib.h>
#include <cstring>
#include <cmath>

#include "LineSearch.h"

LineSearch::LineSearch(int np)
  {
  this->np         = np;
  outfile         = 0;
  maxit           = 5;
  rho             = 0.05;           /* 0   < rho < 0.5  */
  sigma           = 0.95;           /* rho < sigma      */
  tau             = 0.1;            /* tau < sigma      */
  }

LineSearch::~LineSearch()
  {
  }

void  LineSearch::set_maxit(int k)
  {
  maxit = k;
  }
  
void  LineSearch::set_outfile(FILE* f)
  {
  outfile = f;
  }

// print a vector with optional label
void  LineSearch::current(FILE* f, double* v, const char* label)
  {
  if(!f) 
    return;
  if(label)
    fprintf(f, "%24s", label);
  for(int i=0; i<np; i++)
    fprintf(f, "%12.4lf", v[i]);
  fprintf(f, "\n");
  }

/*
name:  dot_product
usage: returns dot product of two np-vectors, x and y
*/
double LineSearch::dot_product(double *x, double *y)
{
double d = 0.0;
for(int i=0; i<np; i++)
 d += *x++ * *y++;
return d;
}

/*
name:  extrapolation
input: dd = directional derivative?
  da = alpha1 - alpha0 ?
  d0 = derivative of f at alpha0 ?
return value:
  extrapolation value (step size alpha?)
*/
double LineSearch::extrapolation(double da, double dd, double d0)
{
double a;
if( dd <= 0.0 )
  return 9.0*da;  //somewhat arbitrary
a = -(d0*da)/dd;
return (a>tau*da) ? a : tau*da;
}

/***
name: interpolation
inputs:
  da = alpha1 - alpha0
  df = obj1     - obj0
  d0 = derivative of f at alpha0
return value:
  interpolation value
***/
double LineSearch::interpolation(double da, double df, double d0)
{
double a;
a = (0.5 * da)/(1.0 - df/(da*d0));
return (a > tau*da) ? a : tau*da;
}


/* line search -- Fletcher page 26 */
double LineSearch::search(double* x0, double* dir, void* surface)
  { 
  double  a0     = 0.0;                 //initial lower bracket for alpha
  double  a      = 1.0;                 //initial value for alpha
  double  a1     = 2.0;                 //initial upper bracket for alpha
  double  obj1   = 0.0;
  double* x1   = new double[np];
  double*  g   = new double[np];
  gradient(x0, g, surface);
  double  d0   = dot_product(g, dir);
  double  obj0 = objective(x0, surface);
//  if(outfile)
//    fprintf(outfile,"%5s%8s%8s%8s\n", "it", "alpha0", "alpha", "alpha1");
  for(int it = 0; it < maxit; it++)
    {
//    if(outfile)
//      fprintf(outfile, "%5d%8.4lf%8.4lf%8.4lf\n", it, a0, a, a1);
    for(int i=0; i<np; i++)
      x1[i] = x0[i] + a*dir[i];
    obj1 = objective(x1, surface);
    if(obj1 == HUGE_VAL)
      {
      a1 = a/2.0;
      a = (a0 + a1)/2.0;
      continue;
      }
    if( (obj0-obj1) < -rho*a*d0)   /* Fletcher 2.4.2 page 20 */
      {
      //fprintf(stderr, "Interpolation\n");
      a1 = a;
      a  = a0 + interpolation(a1 - a0, obj1 - obj0, d0);
      continue;
      }
    double g1[10];
    gradient(x1, g1, surface);
    double d1 = dot_product(g1, dir);
    // fprintf(stderr, "Directional derivative at x1: %.4lf\n", d1);
    if(d1 < -sigma * d0)        /* Fletcher 2.4.7 page 22 */
      {
      //fprintf(stderr, "Extrapolation\n");
      a0 = a;
      a  = a0 + extrapolation(a1 - a0, d1 - d0, d0);
      if( (a - a0) > 0.5*(a1-a0))
        a = a0 + 0.5*(a1-a0);
      obj0 = obj1;
      d0 = d1;
      continue;
      }
    break;  
    } /* end of loop */
  memcpy(x0, x1, np*sizeof(double)); // x0 stores best vector
  delete [] x1;
  return obj1;
  }



