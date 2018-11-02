#include <string.h>

#include <DEtable.h>
#include <DEsystem.h>

#include "Runge-Kutta.h"

Runge_Kutta::Runge_Kutta()
  {
  }

// "time" is a vector of times.
// "X" is the place were values are placed
// "data" contains system parameters
int Runge_Kutta::solve(const double* time, DEtable* X, void* data)
  {
  DEsystem*   A = (DEsystem*) data;
  int         s = 4;                       // number of stages 
  int         m = X->m;                    // number of time points
  int         n = X->n;                    // sizeof system
  DEtable*    D = new DEtable(s, n);
  DEtable*    Y = new DEtable(s, n);
  double      t, h;
  int         err = 0;
  memcpy(X->p[0], A->initial, n*sizeof(double));
  for(int i = 1; i<m; i++)
    {
    t = time[i];
    h = t - time[i-1];
    for(int j = 0; j<n; j++) 
      Y->p[0][j] = X->p[i-1][j];
    err = f(t, Y->p[0], D->p[0], data); if(err) break;
    for(int j = 0; j<n; j++) 
      Y->p[1][j] = X->p[i-1][j]+(h/2)*D->p[0][j];
    err = f(t, Y->p[1], D->p[1], data); if(err) break;
    for(int j = 0; j<n; j++) 
      Y->p[2][j] = X->p[i-1][j]+(h/2)*D->p[1][j];
    err = f(t, Y->p[2], D->p[2], data); if(err) break;
    for(int j = 0; j<n; j++) 
      Y->p[3][j] = X->p[i-1][j]+    h*D->p[2][j];
    err = f(t, Y->p[3], D->p[3], data); if(err) break;
    for(int j = 0; j<n; j++) X->p[i][j] = X->p[i-1][j] + 
      (h/6) * (D->p[0][j] + 2*D->p[1][j] + 2*D->p[2][j] + D->p[3][j]);
    }  
  delete D;
  delete Y;
  return err;
  }

