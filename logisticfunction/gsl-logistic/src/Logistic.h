#ifndef LOGISTIC
#define LOGISTIC

#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>

int equation(double t, const double y[], double f[], void *param);
int jacobian(double t, const double y[], double *dfdy, double dfdt[], void *param);
int solve(double* time, int n, double* param, double* solution);

#endif

