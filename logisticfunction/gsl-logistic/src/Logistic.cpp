#include "Logistic.h"

int equation(double t, const double y[], double f[], void *param)
  {
  double* p     = (double *) param;
  double  theta = p[0];
  // dx/dt = theta(xt-a)(b-xt)
  f[0]          = theta*y[0]*(1.0-y[0]);
  return GSL_SUCCESS;
  }

int jacobian (double t, const double y[], double *dfdy, double dfdt[], void *param)
  {
  double* p     = (double *) param;
  double  theta = p[0];
  gsl_matrix_view dfdy_mat = gsl_matrix_view_array (dfdy, 1, 1);
  gsl_matrix*            m = &dfdy_mat.matrix; 
  gsl_matrix_set (m, 0, 0, theta*(-y[0]+1.0-y[0]));  // define [0,0] element
  dfdt[0] = 0.0;
  return GSL_SUCCESS;
  }

int solve(double* time, int n, double* param, double* solution)
  {
  gsl_odeiv2_system sys = {equation, jacobian, 1, param}; // 1 = dimension
  gsl_odeiv2_driver*  d = gsl_odeiv2_driver_alloc_y_new(
       &sys, gsl_odeiv2_step_rk8pd, 1e-6, 1e-6, 0.0);
       
  double t;                        // current time
  double y[1];                     // storage for function value
  double tmin  = time[0];
  y[0]         = param[1];         // initial value at tmin
  t = tmin;
  for (int i = 0; i < n; i++)
    {
    double  ti = time[i];
    int status = gsl_odeiv2_driver_apply (d, &t, ti, y);
    if (status != GSL_SUCCESS) return GSL_SUCCESS;
	  solution[i] = y[0];
    }
  gsl_odeiv2_driver_free (d);      // free the driver
  return GSL_SUCCESS;
  }

