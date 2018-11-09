// This has source code version of Evolution

#include <stdio.h>
#include <stdlib.h>
#include <cmath>

#include "Evolution.h"

double Evolution::objective(double* x, int n, void* extra)
  {
  double obj = 100*pow(x[1]-x[0]*x[0],2) + pow(1.0-x[0],2);
  return obj;
  }

int main()
  {
  Evolution* ev = new Evolution(2, 20);
  ev->setwtfact(0.8);
  ev->setseed(9911);
  ev->toggledisplay();
  double lower[] = {-2, -2};
  double upper[] = {2, 2};
  double est[2];
  ev->evolve(lower, upper, est);
  for(int i=0; i<2; i++) printf("%10.4g", est[i]);
  printf("\n");
  return 0;
  }

