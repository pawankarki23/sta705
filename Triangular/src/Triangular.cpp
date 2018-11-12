
#include <cmath>
#include <cstring>
#include <stdlib.h>
/*
Suppose a Matrix is symmetric. Storage is saved by using an upper
triangular matrix since the below diagonal elements can be deduced
from the upper triangular elements. The fucntions cholesky,
modified_cholesky, abbreviated_doolittle, and interchange assume
the matrix is symmetric.
*/

#include "Triangular.h"

Triangular::Triangular(int n)
  {
  mode       = -1;
  this->n    = n;
  p          = new double*[n];
  q          = new double[n*(n+1)/2];
  double* r  = q;
  for (int i=0; i<n; i++, r += n - i)
    p[i]   = r; // setting up the pointers so that it points to q
  // could also use:  p[i] = q + i*n -i*(i-1)/2 - i;
  }

Triangular::~Triangular()
  {
  delete []  q;
  delete []  p;
  }
  
void Triangular::check_mode(int required, const char* fun)
  {
  if(mode != required)
    {
    fprintf(stderr, "Improper mode for %s.\n", fun);
    exit(1);
    }
  }
  
void Triangular::zero(int mode)
  {
  this->mode = mode;
  memset(q, 0, n*(n+1)/2*sizeof(double));
  }

void Triangular::load(double* t, int mode)
  {
  this->mode = mode;
  memcpy(q, t, n*(n+1)/2*sizeof(double));
  }

/*
Suppose T is the Cholesky factor of S.
Calling update_T revises T to be the Cholesky factor of 
S + u * u^t.
*/
void Triangular::update_T(double* u)
  {
  check_mode(1, "Triangular::update_T");
  double a;
  double b;
  double c;
  for(int i=0; i<n; i++)
    {
    if(u[i] == 0.0) continue;
    if(fabs(p[i][i]) < fabs(u[i]))
      c = fabs(u[i])*   sqrt(1.0 + pow(p[i][i]/u[i],2));
    else
      c = fabs(p[i][i])*sqrt(1.0 + pow(u[i]/p[i][i],2));
    if(p[i][i] >= 0.0)
      {
      a       = p[i][i]/c;
      b       =    u[i]/c;
      p[i][i] = c;
      }
    else
      {
      a       = -p[i][i]/c;
      b       =    -u[i]/c;
      p[i][i] = -c;
      }
    for(int j=i+1; j<n; j++)
      {
      c       =  a*p[i][j] + b*u[j];
      u[j]    = -b*p[i][j] + a*u[j];
      p[i][j] = c;
      }
    }
  return;
  }

void Triangular::update_S(double* u)
  {
  check_mode(0, "Triangular::update_S");
  for(int i=0; i<n; i++)
    for(int j=i; j<n; j++)
      p[i][j] += u[i] * u[j];
  }
  
void Triangular::dampen(double* scale)
  {
  check_mode(1, "Triangular::dampen");
  if(scale == NULL)
    return;
  double* u = new double[n];
  for(int i=0; i<n; i++)
    {
    memset(u, 0, n*sizeof(double));
    u[i] = scale[i];
    update_T(u);
    }
  delete [] u;
  }

/*
Applies to a Triangular matrix.
The vector u is multiplied by T-transpose with the result
put in v. Routine is useful for calculating  the gradient
vector for the Gauss-Newton alogrithm.
*/
void Triangular::transpose_multiply(const double* u, double * v)
  {
  memset(v, 0, n*sizeof(double));
  for(int i=0; i<n; i++)
    for(int j=0; j<=i; j++)
      v[i] += p[j][i] * u[j];
  return;
  }

/*
Applies to a symmetric matrix. The i-th and j-th rows are
interchanged as are the i-th and j-th columns. The primary
use is to bring the largest pivot element to the top.
It is required that i < j.
*/
void Triangular::interchange(int i, int j)
  {
  if(i >= j) exit(1);
  double a;
  for(int l=0; l<i; l++)
    {
    a       = p[l][i];
    p[l][i] = p[l][j];
    p[l][j] = a;
    }
  for(int l=j+1; l<n; l++)
    {
    a       = p[i][l];
    p[i][l] = p[l][j];
    p[l][j] = a;
    }
  for(int l=0; l<(j-i); l++)
    {
    a         = p[i][i+l];
    p[i][i+l] = p[j-l][j];
    p[j-l][j] = a;
    }
  }


/*
Applies to a symmetric matrix. The matrix is replaced by its
upper triangular modified Cholesky factorization. The algorithm is based
on Gill, Murry, and Wright, page 111, but omitting the row and column
interchanges. Variable names are chosen to resemble notation in the
pseudo-code given there. The return code is 0 if no modification was
necessary and 1 otherwise.
*/
int Triangular::modified_cholesky()
  {
  check_mode(0, "Triangular::modified_cholesky");
  double  beta2;               /* square of bound on off-diagonal elements */
  double  gamma    = 0.0;      /* max abs diagonal element                 */
  double  xi       = 0.0;      /* max abs off-diagonal element             */
  double  nu       = (n>1)? sqrt(n*n - 1.0): 1.0;
  double  eM       = 1.0e-14;
  double  delta    = 1.0e-2;
  int     code     = 0;

  for(int i=0; i<n; i++)
    {
    if(fabs(p[i][i]) > gamma)
      gamma = fabs(p[i][i]);
    for(int j=i+1; j<n; j++)
      if(fabs(p[i][j]) > xi)
        xi = fabs(p[i][j]);
    }
//  fprintf(stderr, "%12s%12.4g%12s%12.4g\n", "gamma", gamma, "xi", xi);

  beta2 = gamma;
  if(beta2 < xi/nu) beta2 = xi/nu;
  if(beta2 < eM   ) beta2 = eM;
  for(int i=0; i<n; i++)
    {
    double theta = 0.0;
    for(int j=i+1; j<n; j++)
      if(fabs(p[i][j]) > theta)
        theta = fabs(p[i][j]);
    double d = delta;
    if(fabs(p[i][i]) > d)
      d = fabs(p[i][i]);
    if(theta*theta/beta2 > d)
      d = theta*theta/beta2;
    if(d > p[i][i])
      code = 1;
    d = sqrt(d);
    p[i][i] = d;
    for(int j=i+1; j<n; j++)
      p[i][j] /= d;
    for(int j=i+1; j<n; j++)
      for(int k=j; k<n; k++)
        p[j][k] -= p[i][j]*p[i][k];
    }
  mode = 1;
  return code;
  }

/*
Assumes a symmetric matrix S. Function attempts to replace S with its
Cholesky factorization. However, if a diagonal element of the attempted
Cholesky factorization is less than tol, S is deemed not positive definite.
If S is not positive definite, HUGE_VAL is returned. Otherwise, the
Cholesky factorization is succesful and the natural log determinint is
returned.
*/
double Triangular::cholesky(double tol)
  {
  check_mode(0, "Triangular::cholesky");
  double logdet = 0.0;
  for(int i=0; i<n; i++)
    {
    if(p[i][i] < tol)
      return HUGE_VAL;
    p[i][i] = sqrt(p[i][i]);
    logdet += log(p[i][i]);
    for(int j=i+1; j<n; j++)
      p[i][j] /= p[i][i];
    for(int j=i+1; j<n; j++)
      for(int k=j; k<n; k++)
        p[j][k] -= p[i][j]*p[i][k];
    }
  mode = 1;
  return 2*logdet;
  }

/*
Assumes matrix is triangular, say T.
T is replaced by (T-transpose) T.
*/
void Triangular::TtT()
  {
  check_mode(1, "Triangular::TtT");
  Triangular* S = new Triangular(n);
  S->zero(1);
  for(int i=0; i<n; i++)
    for(int j=i; j<n; j++)
      for(int l=0; l<= i; l++)
        S->p[i][j] += p[l][i]*p[l][j];
  memcpy(p[0], S->p[0], n*(n+1)/2*sizeof(double));
  delete S;
  mode = 0;
  return;
  }

/*
Assumes matrix is triangular, say T. Function gives the solution
to T x = rhs.
*/
void  Triangular::back_solve(const double* rhs, double* x)
  {
  check_mode(1, "Triangular::back_solve");
  int i = n;
  for(  ; i>0; )
    {
    i--;
    if(p[i][i] == 0.0)
      {
      fprintf(stderr, "Triangular matrix is singular.\n");
      exit(1);
      }
    double a = rhs[i];
    for(int j=i+1; j < n; j++)
      a -= p[i][j] * x[j];
    x[i] = a/p[i][i];
    }
  }

/*
Assumes matrix is triangular, say T. Function gives the solution
to (T-transpose) x = rhs. Returns squared norm of solution.
*/
double  Triangular::forward_solve(const double* rhs, double* x)
  {
  check_mode(1, "Triangular::forward_solve");
  double q = 0.0;
  for(int i=0; i<n; i++)
    {
    if(p[i][i] == 0.0)
      {
      fprintf(stderr, "Triangular matrix is singular.\n");
      exit(1);
      }
    double d = rhs[i];
    for(int j=0; j<i; j++)
      d -= p[j][i] * x[j];
    x[i] = d/p[i][i];
    q += x[i]*x[i];
    }
  return q;
  }

/*
Assumes a symmetric matrix S that is the variance matrix of a multivariate
normal distribution. x is the vector in the quadratic form in the likelihood
function. The return value is -2 times the log likelihood function apart
from a constant term not depending on S or x. If S is deemed not positive
definite, HUGE_VAL is returned.
*/
double Triangular::neg2loglihod(double *x)
  {
  check_mode(0, "Triangular::neg2loglihod");
  double logdet = cholesky();
  if(logdet == HUGE_VAL)
    return HUGE_VAL;
  double* u     = new double[n];
  double  quad  = forward_solve(x, u);
  delete [] u;
  return logdet + quad;
  }

/*
Assumes matrix is triangular, say T. Function gives the solution
to ((T-transpose) T) x = rhs.
*/
void  Triangular::solve(const double* rhs, double* x)
  {
  check_mode(1, "Triangular::solve");
  double* temp = new double[n];
  forward_solve(rhs, temp);
  back_solve(temp, x);
  delete [] temp;
  }

void Triangular::print(FILE* f, const char* title)
  {
  if(f == NULL) return;
  const char* label[] = {"symmetric", "triangular"};
  fprintf(f, "\n");
  fprintf(f, "%s --- %s\n", title, label[mode]);
  for(int i=0; i<n; i++)
    {
    int j;
    for(j=0; j<i; j++)
      fprintf(f, "%12s", "");
    for(  ; j<n; j++)
      fprintf(f, "%12.4lf", p[i][j]);
    fprintf(f, "\n");
    }
  return;
  }

