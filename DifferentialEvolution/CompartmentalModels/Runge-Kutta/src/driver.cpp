
#include <string.h>
#include <stdio.h>

#include <DEtable.h>
#include <DEsystem.h>

#include "Runge-Kutta.h"

// inputs for a linear system
// t is current time
// y is current value of variables
// data is pointer to structure of system parameters
// der is derivatives (here alpha + A y)
int Runge_Kutta::f(double t, const double* y, double* der, void* data)
  {
  DEsystem* A = (DEsystem*) data;
  int n = A->n;
  for(int i = 0; i<n; i++)
    {
    der[i] = A->infusion[i];
    for(int j=0; j<n; j++)
      der[i] += A->p[i][j]*y[j];
    }
  return 0;
  }
   
int main(int argc, char* argv[])
  {
  // open output files
  char plot[50];
  strcpy(plot, "plot.dat");
  FILE* output = fopen(plot, "w");
  
  char system[50];
  strcpy(system, "system.out");
  FILE* logfile = fopen(system, "w");

  // set dimentions and load system values
  const int      m   = 201;               // number of times
  const int      n   = 3;                 // size of system
  DEsystem*      A   = new DEsystem(n); 
  double     coef[]  = {-1, 0, 1,
                         1,-1, 0,
                         0, 1,-1};
  double x0[]        = {0, 0, 0};      
  double inf[]       = {10, 0, 0};             
  A->load(coef, x0, inf);
  A->print(logfile, "System values");
  
  // "solve" the equations
  double* t          = new double[m];
  for(int i=0; i<m; i++)
    t[i] = ((double) i/ (m-1))*2;
  Runge_Kutta* rk = new Runge_Kutta();  
  DEtable*      X = new DEtable(m, n);
  X->headings();
  X->set_x0(A->initial);
  rk->solve(t, X, A);
  X->print(output, t);
  
  // close files
  fclose(logfile);
  printf("System file is %s\n", system);
  fclose(output);
  printf("Plot file is %s\n", plot);
  return 0;
  }

