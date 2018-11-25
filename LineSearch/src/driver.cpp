
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <Triangular.h>

#include "LineSearch.h"

// define virtual funcrions
double LineSearch::objective(double* x, void* surface)
  {
    // rosenbrock function
  return 100*pow(x[1]-x[0]*x[0],2) + pow(1.0-x[0],2);
  current(stderr, x, "x");
  }
  
void LineSearch::gradient(double* x, double* g, void* surface)
  {
  g[0] = -400*(x[1]-x[0]*x[0])*x[0] -2*(1.0-x[0]);     /* dx0 */
  g[1] =  200*(x[1]-x[0]*x[0]);                        /* dx1 */
  current(stderr, g, "gradient");
  }
  
double LineSearch::direction(double* x, double* g, double* dir, void* surface)
  {
  Triangular* T = (Triangular*) surface;
  double h[3];
  h[0] = -400*x[1] + 1200*x[0]*x[0] + 2;               /* dx0 dx0 */
  h[1] = -400*x[0];                                    /* dx0 dx1 */
  h[2] =  200;                                         /* dx1 dx1 */    
  T->load(h, 0);        
  int code = T->modified_cholesky();
  if(code and outfile)
    fprintf(outfile, "Hessian was modified.\n");

  // find the direction vector
  double* temp = new double[np];
  double Q = T->forward_solve(g, temp);
  T->back_solve(temp, dir);
  delete [] temp;

  for(int i=0; i<np; i++)
    dir[i] = -dir[i];
  current(stderr, dir, "direction");
  return sqrt(Q);
  }
    
void print(FILE* f, double* x, int n, double obj)
  {
  if(!f)
    return;
  for(int j=0; j<n; j++) fprintf(f, "%12.4lf", x[j]);
  fprintf(f, "%18s%.6g\n", "Objective = ", obj);
  }
    
int main(int argc, char* argv[])
  {
  char name[50];
  strcpy(name, argv[0]);
  strcat(name, ".txt");
  FILE* outfile = fopen(name, "w");

  double       tol;
  const int      n = 2;
  double*        x = new double[n];
  double*     grad = new double[n];
  double*      dir = new double[n];
  Triangular*    T = new Triangular(n);
  
  double temp[] = {-1, 1};
  LineSearch ls(n);
  ls.set_outfile(stderr);
  ls.set_maxit(3);
  memcpy(x, temp, n*sizeof(double));
  for(int it =0; it<25; it++)
    {
    ls.gradient (x, grad);
    tol = ls.direction(x, grad, dir, T);
    if(tol < 0.000001)
      break;
    double obj = ls.search(x, dir);  // returns new x
    print(outfile, x, n, obj);
    }
  T->print(outfile, "Final factored Hessian");  
  fclose(outfile);
  delete [] x;
  delete [] grad;
  delete [] dir;
  delete    T;
  return 0;
  }
  
