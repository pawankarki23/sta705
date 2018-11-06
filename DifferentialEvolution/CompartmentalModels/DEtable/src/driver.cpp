
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
  DEtable*    X1  = new DEtable(m, n); 
  DEtable*    X2  = new DEtable(m, n); 
  double*     t   = new double[m];
  double*     x   = new double[n];
  double    max   = 4*M_PI;  
  for(int i=0; i<m; i++)
    {
    t[i] = ((double) i/ (m-1))*max;
    x[0] = cos(t[i]);
    x[1] = sin(t[i]);
    x[2] = t[i];
    memcpy(X1->p[i], x, n*sizeof(double));
    memcpy(X2->p[i], x, n*sizeof(double));
    }
  double x1[] = {4,5,6};
  double x2[] = {9,10,11};
  X1->set_x0(x1);
  X2->set_x0(x2);
  X1->headings();
  X2->headings();
  X1->print(output, t);
  X2->print(output, t);
  double dif = X1->compare(X2);
  fprintf(output, "max abs dif = %.6lf\n", dif);
  fclose(output);
  printf("Output file is %s\n", name);
  return 0;
  }

