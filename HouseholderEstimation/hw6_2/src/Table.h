#ifndef TABLECLASS
#define TABLECLASS

#include <stdio.h>

// Layout is row major
class Table
  {
  public:
  char     label[80];
  int      m;         // number of rows
  int      n;         // number of columns
  double** p;         // pointers to rows
  double*  q;         // body
  void     calc_b(double* rhs, double* b);
  bool     calc_a(double*   c, double* a, double tol=0.000001);
  void     mult  (double*   x, double* r);
  void     print(FILE*, const char* title = 0);
           Table(int, int, const char* l = 0);
          ~Table();
  };
  
#endif
  
