#include <stdio.h>
#include <stdlib.h>
#include <cmath>

// using the Evolution.h in /usr/include installed using make install 
#include <Evolution.h>
#include "Logistic.h"

struct Data
{
  double* time;
  double* y; //response
  int     n;
};
  
double Evolution::objective(double* param, int np, void* data)
{
  double* time = ((Data*)data)->time;
  double* y    = ((Data*)data)->y;
  int     n    = ((Data*) data)->n;
  double* yhat = new double[n];
  int status   = solve(time, n, param, yhat);  // using gsl library
  if (status != GSL_SUCCESS) return HUGE_VAL;
  // sum of residual squared
  double rss = 0.0;
  for(int i=0; i<n; i++) 
    rss += pow(y[i]-yhat[i], 2);
  delete [] yhat;
  return rss;  
}
  
int main()
{
  Data* data = new Data;
  data->n    = 7;
  data->time = new double[data->n];  // times
  data->y    = new double[data->n];  // responses
  
  for(int i=0; i<data->n; i++)
  {
    data->time[i] = i+1;
    double s = exp(-8+2*data->time[i]); // from presentation on logistic function d = -8 and c=2
    data->y[i] = s/(1+s);               // fake data, allows exact fit
  }

  Evolution ev( 2, 20, data);
  ev.toggledisplay();
  ev.setwtfact(0.8);// weight factor
  ev.setseed(9911);
  // two parameters theta and x(1)
  double lower[] = {1.0, 0.05};
  double upper[] = {3.0, 0.2};

  double est[2];
  ev.evolve(lower, upper, est);
  printf("Parameter values\n");
  for(int i=0; i<2; i++) 
    printf("%10.4g", est[i]);
  printf("\n");
  printf("%12s%12s%12s\n", "Time", "y", "yhat");
  double* yhat = new double[data->n];
  solve(data->time, data->n, est, yhat);
  for(int i=0; i<data->n; i++)
    fprintf(stderr,"%12.6lf%12.6lf%12.6lf\n", 
    data->time[i],data->y[i], yhat[i]);
  return 0;
}
  
