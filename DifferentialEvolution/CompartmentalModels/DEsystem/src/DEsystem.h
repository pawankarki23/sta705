#ifndef DESYSTEM
#define DESYSTEM

#include <stdio.h>

class DEsystem
{
  public:
  int      n;
  double*  infusion;
  double*  initial;
  double** p; // the matrix
  double*  q;
  void     load(double*, double*, double*);
  void     print(FILE* f,  const char* title = 0);
           DEsystem(int);
          ~DEsystem();
};

#endif

