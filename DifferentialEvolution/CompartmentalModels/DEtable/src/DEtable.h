
#ifndef DETABLE
#define DETABLE

#include <stdio.h>

class DEtable
{
  public:
  void     load(double*);
  void     print(FILE* f, double* t );
  void     headings();
  char**   head;     // pointers to labels
  char*    label;    // state labels
  int      c;        // characters per column
  int      m;        // number of rows
  int      n;        // number of columns
  double** p;        // row pointers
  double*  q;        // body in linear form
           DEtable(int m, int n);
          ~DEtable();
};
#endif

