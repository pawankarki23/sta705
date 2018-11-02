#ifndef TABLE
#define TABLE

#include <cstdio>

class Table
  {
  private:
  int      split(int col, double pivot, int first, int last);
  int*     dp;
  public:
  int      m;// rows 
  int      n;// col
  double** p;// 2d array of numbers 
  double*  q;
  void     swap(int i, int j);
  int      print(FILE*, const char* title = 0);
  char*    to_text(const char* title = 0);
  void     zero();                          // set the whole matrix to 0.0
  void     load(double*);                   // load matrix by rows
  void     load(FILE*);                     // load from flat file
  void     load_col(int k, double*);        // load column k
  void     set_decimals(int*);              // set decimal places
  void     transpose();
  double   compare(const Table*);
  void     swap_rows(int i, int j);
  void     order(int col, int, int);
  void     pre_mult(const double* a, int k, double* c);
  void     resize(int, int);
  static int file_dim(FILE*, int &nrow, int &ncol);
  Table*   product(Table* B);               // product
  Table*   t_product(Table* B);             // transpose product
  Table*   product_t(Table* B);             // product transpose
  Table*   duplicate();
  Table*   merge(int col, Table* B);
          // constructors
           Table(int, int);
           Table(int); // for square matrix
           Table();    // to be resized later
           ~Table();
  };

#endif

