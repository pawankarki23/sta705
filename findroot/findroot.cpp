#include <stdio.h>
#include <stdlib.h>  // exit is here
#include <math.h>    // fabs is here

double findroot(double (*f)(double x), double l, double u, 
                                      double tol = 0.000001)
  {
  // tol is the tolerance value
  // Insure an increasing function at the root. 
  if( (f(u) < 0.0) or (f(l) > 0.0))
    {
    fprintf(stderr, "Illegal input.\n");
    exit(1);
    }
  double m;
  while( fabs(u - l) > tol)
    {
    m = (l + u)/2;
    if(f(m) < 0.0)
      l = m;
    else
      u = m; 
    fprintf(stderr,"%10.4lf%10.4lf%10.4lf\n", l, m, u);
    }
  return m;
  }
