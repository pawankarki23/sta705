#include <cstdio>
#include <cstdlib>
#include <R.h>
#include "Convolve.h"

static Convolve* conv;
extern "C"
  {

void setup(int* na, int* nb)  // arguments are pointers
  {
  conv = new Convolve(*na, *nb);
  }

void evaluate(double* a, double* b, double* ab)
  {
  conv->evaluate(a, b, ab);
  }

void closeout()
  {
  delete conv; // calls destructor
  }

  } // end extern "C"
