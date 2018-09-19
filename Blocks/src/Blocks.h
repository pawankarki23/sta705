
#ifndef BLOCKTRANSFORM
#define BLOCKTRANSFORM

#include <cstdio>

class Block
  {
  double**   p;
  double*    q;
  double*    maxabs;   // for checking linear dependencies
  double*    diag;     // leading nonzero elememts in rows of E
  double*    beta;     // normalizing factor for "w"
  int        m;        // # number of vectors
  int        n;        // # number of elements in each vector
  void       memory();
  double     calc_norm(int, int, double tol=0.000001);
  void       reflect(double* w, double beta, double* v, int r1);
  public:
  int        r0;       // cumulative rank of preceding blocks
  int        r1;       // cumulative rank in current block
  int        calc_transform(int r1);
  void       apply_transform(Block* obj);
  void       numeric(double* x, int n);
  void       ones (int n);
  void       categories(int* level, int m, int n);
  int        adjoin(Block* term[], int nt);
  int        get_block(Block* term[], int i, int j);
  bool       calc_a(double*, double*, double tol=0.000001);
  void       unpack();
  void       print(    FILE*, const char* title = 0);
  void       auxiliary(FILE*, const char* title = 0);
             Block();
            ~Block();
  };

#endif


