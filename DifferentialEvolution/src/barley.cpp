#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Evolution.h"

struct XYdata
  {
  int     n;
  double* x;
  double* y;
          XYdata(int, double*, double*);
  };  

XYdata::XYdata(int n, double* x, double* y)
  {
  this->n = n;
  this->x = new double[n];
  this->y = new double[n];
  memcpy(this->x, x, n*sizeof(double));
  memcpy(this->y, y, n*sizeof(double));
  }

double Evolution::objective(double* theta, int np, void* data)
  {
  for(int i=0; i<np; i++)
    if(theta[i] <= 0.0)
      return HUGE_VAL;
  XYdata* dat = (XYdata*) data;    
  double ssr = 0.0;
  for(int i =0; i<dat->n; i++)
    {
    double n = dat->x[i];    
    double y = dat->y[i];
    ssr += pow(y - (theta[0] - theta[1]*exp(-theta[2]*n)), 2);
    }
  return ssr;
  }
  
int main()
  {
  // nitrogen (10kg/ha)
  double nitrogen[] = {0,0,0,0,3,3,3,3,6,6,6,6,9,9,9,9};
  // yield (kg/ha)
  double yield[]    = {23,22,19,21,31,35,31,34,37,40,38,38,40,42,40,40};
  XYdata* data      = new XYdata(16, nitrogen, yield);
  
  int np = 3;
  Evolution* ev = new Evolution(np, 10*np, data); // NOTE
  ev->set_wt_factor(0.8);
  ev->set_seed(9911);
  ev->toggle_display();
  double lower[] = {40, 25, 0.1};
  double upper[] = {45, 35, 1.0};
  double* est = new double[np];
  ev->evolve(lower, upper, est);
  fprintf(stdout, "Final parameter values\n");
  for(int i=0; i<np; i++) 
    fprintf(stdout, "%12.6g\n", est[i]);
  return 0;
  }

