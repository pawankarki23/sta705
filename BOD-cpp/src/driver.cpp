
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <Triangular.h>
#include <LineSearch.h>

Triangular* T = 0;

class Data
{
  public:
  int     n;
  double* t;
  double* y;
  void    print();
          Data(int, double*, double*);
};
  
Data::Data(int n, double* t, double* y)
  {
  this->n = n;
  this->t = new double[n];
  this->y = new double[n];
  memcpy(this->t, t, n*sizeof(double));
  memcpy(this->y, y, n*sizeof(double));
  }  
  
void Data::print()
  {
  for(int i=0; i<n; i++)
    fprintf(stderr, "%12.4lf%12.4lf\n", t[i], y[i]);
  }  

// define virtual funcrions
double LineSearch::objective(double* theta, void* extra)
  {
  current(NULL, theta, "theta");
  for(int i=0; i<np; i++)
    if(theta[i] <= 0.0)
      return HUGE_VAL;
  Data*  data = (Data*) extra;
  double  ss  = 0.0;
  int n       = data->n;
  for(int i=0; i<n; i++)
    {
    double eta = theta[0]*(1.0-exp(-theta[1]*data->t[i]));
    ss += pow(data->y[i]-eta,2);
    }
  return ss;
  }

// inputs: theta, extra. output g
void LineSearch::gradient(double* theta, double* g, void* extra)
  {
  Data*  data = (Data*) extra;
  int       n = data->n;
  char   label[12];
  double u[np];
  memset(g, 0, np*sizeof(double));
  for(int i=0; i<n; i++)
    {
    sprintf(label, "jac[%2d]", i);
    double   t = data->t[i];
    double eta = theta[0]*(1.0-exp(-theta[1]*t));
    double   r = data->y[i] - eta;
    u[0]       = 1.0 - exp(-theta[1]*t);
    u[1]       = theta[0]*t*exp(-theta[1]*t);
    current(NULL, u, label);
    for(int j=0; j<np; j++)
      g[j] += -2*r*u[j];
    }
  current(NULL, g, "gradient");
  }
  
// inputs theta, g, and extra. output dir  
double LineSearch::direction(double* theta, double* g, double* dir, void* extra)
  {
  Data*       data = (Data*) extra;
  int         n    = data->n;
  double*     u    = new double[np];
  T->zero(0);                         // zero and set to symmetric
  for(int i=0; i<n; i++)
    {
    double   t = data->t[i];
    u[0]       = 1.0 - exp(-theta[1]*t);
    u[1]       = theta[0]*t*exp(-theta[1]*t);
    T->update_S(u);
    }
  // T->print(stderr, "JtJ");
  T->modified_cholesky();
  // T->print(stderr, "Factored JtJ");

  // find the direction vector
  double* temp = new double[np];
  double Q = T->forward_solve(g, temp);
  T->back_solve(temp, dir);         // dir is in argument list

  for(int i=0; i<np; i++)
    dir[i] = -dir[i];
  current(NULL, dir, "direction");
  delete [] u;
  delete [] temp;
  return sqrt(Q);
  }
    
void print(FILE* f, double* x, int n, double obj)
  {
  if(!f)
    return;
  for(int j=0; j<n; j++) fprintf(f, "%12.4lf", x[j]);
  fprintf(f, "%18s%.6g\n", "Objective = ", obj);
  }
  
void inference(FILE* f, double* theta, Triangular* T, double s2)
  {
  if(!f) return;
  
  char  label[12];
  int      np = T->get_n();
  double*   c = new double[np];
  double*   u = new double[np];
  fprintf(f, "\n%12s%12s%12s\n", "Parameter", "Estimate", "ese");
  for(int i=0; i<np; i++)
    {
    sprintf(label, "theta[%d]", i);
    memset(c, 0, np*sizeof(double));
    c[i] = 1.0;
    T->forward_solve(c, u);
    double v = 0.0;
    for(int j=0; j<np; j++) v += u[j]*u[j];
    fprintf(f, "%12s%12.6g%12.6g\n", label, theta[i], sqrt(v*s2));
    }
  delete [] c;
  delete [] u;
  }
    
int main(int argc, char* argv[])
  {
  char name[50];
  strcpy(name, "BOD.out");
  FILE* outfile = fopen(name, "w");

  char         label[25];
  double       tol;
  double       obj;
  const int     np = 2;                  // np = number of parameters
  double*     grad = new double[np];
  double*      dir = new double[np];
  T = new Triangular(np);
  double       t[] = {1,2,3,4,5,7};
  double       y[] = {8.3,10.3,19.0,16, 15.6,19.8};
  Data* data       = new Data(6, t, y);
  // data->print();
  
  double theta[] = {20, 0.24};  // initial values
  LineSearch ls(np);
  ls.set_maxit(3);
  for(int it =0; it<25; it++)
    {
    sprintf(label, "Iteration %d", it);
    ls.current(stderr, theta, label);
    ls.gradient (theta, grad, data);
    tol = ls.direction(theta, grad, dir, data);
    if(tol < 0.001)
      break;
    obj = ls.search(theta, dir, data);  // returns new theta
    }
  int df = data->n - np;  // residual degrees of freedom
  inference(outfile, theta, T, obj/df);
  fclose(outfile);
  return 0;
  }
  
