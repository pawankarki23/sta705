
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "DEtable.h"

int main(int argc, char* argv[])
  {
  char name[50];
  strcpy(name, argv[0]);
  strcat(name, ".dat");
  FILE* output = fopen(name, "w");
  const int   m   = 25;               // number of times
  const int   n   = 3;                 
  DEtable*    A   = new DEtable(m, n); 
  double*     t   = new double[m];
  double*     x   = new double[n];
  double    max   = 4*M_PI;  
  for(int i=0; i<m; i++)
    {
    t[i] = ((double) i/ (m-1))*max;
    x[0] = cos(t[i]);
    x[1] = sin(t[i]);
    // x[2] is not defined
    memcpy(A->p[i], x, n*sizeof(double));
    }
  A->headings();
  A->print(output, t);
  fclose(output);
  printf("Output file is %s\n", name);
  return 0;
  }

