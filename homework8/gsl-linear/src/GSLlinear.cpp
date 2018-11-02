#include <string.h>

// This addaptation has evolved from example on GSL website.
// Have changed step function from gsl_odeiv2_step_rk8pd.

#include "Table.h"
#include "GSLlinear.h"

DEmodel::DEmodel(int n)
  {
  this->n = n;
  infusion = new double[n];
  initial  = new double[n];
  p        = new double*[n];
  q        = new double[n*n];
  for(int i=0; i<n; i++)
    p[i] = q + i*n;
  }
  
void  DEmodel::load(double* sys, double* initial, double* infusion)
  {
  memcpy(q, sys, n*n*sizeof(double));
  memcpy(this->initial, initial, n*sizeof(double));
  memcpy(this->infusion, infusion, n*sizeof(double));
  } 
  
//           time,     current x,        derivatives, system matrix      
int function(double t, const double s[], double f[],  void *data)
  {
  DEmodel* A = (DEmodel*) data;
  int     n = A->n;
  for(int i=0; i<n; i++)
    {
    f[i] = A->infusion[i];
    for(int j=0; j<n; j++)
      f[i] += A->p[i][j]*s[j];
    }
  return GSL_SUCCESS;
  }

//           time,     current x,        der wrt y,    der wrt t,     system matrix
int jacobian(double t, const double s[], double *dfdy, double dfdt[], void *data)
  {
    // time t is not being used
  DEmodel* A = (DEmodel*) data;
  int     n = A->n;
  for(int i=0; i<n; i++)
    {
    dfdt[i] = 0.0; // as t is not defined for this model
    for(int j=0; j<n; j++)
      dfdy[i*n+j] = A->p[i][j]; // define [i,j] element
    }
  return GSL_SUCCESS;
  }

GSLlinear::GSLlinear()
  {
  hstart  = 1e-6; 
  epsabs  = 1e-6;
  epsrel  = 0.0;
  }
  
GSLlinear::~GSLlinear()
  {
  }

void  GSLlinear::set_hstart(double value){hstart = value;}
void  GSLlinear::set_epsabs(double value){epsabs = value;}
void  GSLlinear::set_epsrel(double value){epsrel = value;}
  
//                       system,         time,  results
int GSLlinear::solve(DEmodel* A, double* time, Table* Y)
  {
  int n = A->n;
  gsl_odeiv2_system sys = {function, jacobian, (size_t) n, A};
  gsl_odeiv2_driver*  driver = gsl_odeiv2_driver_alloc_y_new (
       &sys, gsl_odeiv2_step_rk4imp, hstart, epsabs, epsrel);
       
  double* s = new double[n];  // storage for function value
  
  for(int i=0; i<n; i++) 
    s[i] = Y->p[0][i+1] = A->initial[i];
  double    t  = time[0];

  for (int i = 1; i < Y->m; i++)
    {
    int status  = gsl_odeiv2_driver_apply(driver, &t, time[i], s);
    if (status != GSL_SUCCESS) return status;
    for(int j=0; j<n; j++)
  	  Y->p[i][j+1] = s[j];      // store values for time[j]
    }
  gsl_odeiv2_driver_free(driver); 
  delete [] s;
  return GSL_SUCCESS;
  }


