#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Evolution.h"

// Structure definition that can hold the data
struct XYdata
{
  int     n;
  double* x;
  double* y;
  // constructor 
  XYdata(int, double*, double*);
};  

// definition of constructor
XYdata::XYdata(int n, double* x, double* y)
{
  this->n = n;
  this->x = new double[n];
  this->y = new double[n];
  memcpy(this->x, x, n*sizeof(double));
  memcpy(this->y, y, n*sizeof(double));
}

// the objective function that defines the function to be minimized 
double Evolution::objective(double* theta, int np, void* data)
{
  for(int i=0; i<np; i++)
    if(theta[i] <= 0.0)
      return HUGE_VAL;

  XYdata* dat = (XYdata*) data;  

  // we are minimizing the sum of sq of the residuals for the given data and model
  // ssr = sum of sq for residuals
  double ssr = 0.0;
  for(int i =0; i<dat->n; i++)
  {
      double n = dat->x[i];    
      double y = dat->y[i];
      // model is y = f(t,theta) = theta1 - theta1* exp(-theta2*x)
      // so residual sq is (datay-modely)^2
      // theta[0] is theta1 and theta[1] is theta2 here
      ssr += pow(y - (theta[0] - theta[0]*exp(-theta[1]*n)), 2);
  }

  return ssr;
}
  
int main()
{

  // Time (days) independent variable
  double days[] = {1,2,3,4,5,7};
  // BOD (mg/l) dependent variable 
  double bod[]    = {8.3,10.3,19,16,16.6,19.8};
  
  // create a data structure
  XYdata* data      = new XYdata(6, days, bod);
  
  // number of parameters (theta1 and theta2)
  int np = 2;

  // create the Evolution class
  Evolution* ev = new Evolution(np, 10*np, data); 
  ev->set_wt_factor(0.8);
  ev->set_seed(9911);
  ev->toggle_display();

  // define lower and upper bound for theta1 and theta2
  double lower[] = {9, 9};
  double upper[] = {18, 18};
  // create a pointer to hold the estimated parameter values
  double* est = new double[np];
  // run the differential evolution
  ev->evolve(lower, upper, est);

  // print the estimated values of the parameters 
  fprintf(stdout, "Final parameter values\n");
  for(int i=0; i<np; i++) 
    fprintf(stdout, "Estimation of theta[%d]: %12.6g\n", i+1, est[i]);

  return 0;
}