
#ifndef BLOCKTRANSFORM
#define BLOCKTRANSFORM

#include <cstdio>

class Table;

// storage is column major order
class Block
  {
  char       label[100];
  double*    q;        // body stored column major order
  double*    maxabs;   // for checking linear dependencies
  double*    beta;     // normalizing factor for "w"
  void       memory();
  double     calc_norm(int, int, double tol=0.000001);
  void       reflect(double* w, double beta, double* v, int r1);
  public:
  Table*     get_block(Block* row);
  double*    diag;     // leading nonzero elememts in rows of E
  int        m;        // # number of elements in each vector
  int        n;        // # number of vectors
  double**   p;        // pointers to columns
  int        r0;       // cumulative rank of preceding blocks
  int        r1;       // cumulative rank in current block
  int        calc_transform(int r1);
  void       apply_transform(Block* obj);
  int        adjoin(Block* adj);
  void       calc_b(double*, double*);
  void       print(    FILE*, const char* title = 0);
  void       auxiliary(FILE*, const char* title = 0);
             // single column numeric
             Block(double* x, int m, const char* l=0);             
             // single column of 1s
             Block(int m, const char* l=0);                    
             // indicator variables
             Block(int* level, int m, int n, const char* l=0); 
             // from text file 
             Block(FILE* file, int m, int n, const char* l=0);

            ~Block();
  };
#endif


