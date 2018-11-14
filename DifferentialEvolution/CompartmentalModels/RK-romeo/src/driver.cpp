
#include <cstring>
#include <cstdio>
#include <math.h>

#include <DEtable.h>

// uses the Runge-Kutta library that we installed in /usr/lib using make install
#include <Runge-Kutta.h>

// inputs for a linear system
// t is time
// y is current value of variables
// data is pointer to constants (here A, matrix of linear system)
// output
// der is derivatives (here A y)
int Runge_Kutta::f(double t, const double* y, double* der, void* data)
  {
  DEtable* A = (DEtable*) data;
  int m = A->m;
  for(int i = 0; i<m; i++)
    {
    der[i] = 0;
    for(int j=0; j<m; j++)
      der[i] += A->p[i][j]*y[j];
    }
  return 0;
  }
   
int main(int argc, char* argv[])
  {
  // output file
  char name[50];
  strcpy(name, "plot.dat");
  FILE* output = fopen(name, "w");
  
  // system values
  const int      m   = 201;                 // number of times
  const int      n   = 2;                   // size of system
  DEtable*       A   = new DEtable(n, n);   // matrix of linear system
  double     coef[]  = { 0, -9,
                         4,  0};
  double x0[]        = {10,  0};                    
  A->load(coef);
  double* t          = new double[m];
  for(int i=0; i<m; i++)
    t[i] = ((double) i/ (m-1))* M_PI;

  // solve system and save  
  Runge_Kutta* rk = new Runge_Kutta();  
  DEtable*      X = new DEtable(m, n);
  X->set_x0(x0);
  rk->solve(t, X, A);
  X->print(output, t);
  fclose(output);
  
  // close up
  delete A;
  delete X;
  printf("Output file is %s\n", name);
  return 0;
  }

