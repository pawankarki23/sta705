#include <string.h>

#include "DEsystem.h"

DEsystem::DEsystem(int n)
  {
  this->n = n;
  infusion = new double[n];
  initial  = new double[n];
  p        = new double*[n];
  q        = new double[n*n];
  for(int i=0; i<n; i++)
    p[i] = q + i*n;
  }
  
DEsystem::~DEsystem()
  {
  delete [] infusion;
  delete [] initial;
  delete [] p;
  delete [] q;
  }
  
void  DEsystem::load(double* sys, double* initial, double* infusion)
  {
  memcpy(q, sys, n*n*sizeof(double));
  memcpy(this->initial, initial, n*sizeof(double));
  memcpy(this->infusion, infusion, n*sizeof(double));
  } 

void DEsystem::print(FILE* f,  const char* title)
  {
  if(!f)
    return;
  if(title)
    fprintf(f, "\n%s\n", title);
  fprintf(f, "\nSystem matrix\n");
  for(int i=0; i<n; i++)
    {
    for(int j=0; j<n; j++)
      fprintf(f, "%12.6lf", p[i][j]);
    fprintf(f, "\n");
    }  
  fprintf(f, "\n%12s%12s\n", "Bolus", "Infusion");
  for(int i=0; i<n; i++)
    fprintf(f, "%12.6lf%12.6lf\n", initial[i], infusion[i]);
  }

