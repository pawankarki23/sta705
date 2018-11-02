#ifndef GSLLINEAR
#define GSLLINEAR

#include <gsl/gsl_errno.h>
#include <gsl/gsl_odeiv2.h>

class Table;

struct DEmodel
{
  int      n;// size the dimension of A
  double*  infusion; // alpha
  double*  initial; // x(0)
  double** p;// matrix A
  double*  q;
  void     load(double*, double*, double*);
  // constructor
           DEmodel(int);
};

// function for alpha+A*x(t)
int function(double t, const double y[], double f[], void *data);
// Jacobian A matrix
int jacobian(double t, const double y[], double *dfdy, double dfdt[], void *data);

class GSLlinear
{
  double  hstart;
  double  epsabs;
  double  epsrel;
  public:
  void    set_hstart(double);
  void    set_epsabs(double);
  void    set_epsrel(double);
  int     solve(DEmodel* A, double* time, Table* Y);
          GSLlinear();
         ~GSLlinear();
};
#endif

