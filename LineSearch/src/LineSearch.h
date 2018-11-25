#ifndef LINESEARCH
#define LINESEARCH

#include <cstdio>

class LineSearch
  {
  private:
  double         rho;           // line search parameter, Fletcher page 20 
  double         sigma;         // line search parameter, Fletcher page 22 
  double         tau;           // line search parameter, Fletcher page 27 
  double         obj;           // value of objective function             
  double         dot_product  (double*  x, double *y);
  double         interpolation(double  da, double df, double d0);
  double         extrapolation(double  da, double dd, double d0);
  FILE*          outfile;
  int            maxit;
  public:
  virtual double objective(double* x,                           void* surface=0);
  virtual void   gradient (double* x,  double* g,               void* surface=0);
  virtual double direction(double* x,  double* g,  double* dir, void* surface=0);
  double         search   (double* x0, double* dir,             void* surface=0);
  int            np;                     // number of parameters
  void           current(FILE*, double*, const char* label=0);
  void           set_outfile(FILE* f);
  void           set_maxit(int maxit);
                 LineSearch(int n);
                ~LineSearch();
  };

#endif
