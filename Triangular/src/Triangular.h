#ifndef TRIANGULAR
#define TRIANGULAR

#include <cstdio>

class Triangular
{
  int      n;
  int      mode;                           // 0 = if symmetric, 1 = if triangular
  double*  q; // storage of the matrix 
  void     check_mode(int required, const char* fun);//check the mode 
  
  public:
  int get_n();
  double** p; // points to q and returns specific element of q  
  void     print(FILE*, const char* = "");
  void     zero(int mode);                 // set every element to 0.0
  void     load(double*, int mode);        // mode: 0 = sym, 1 = tri
  void     update_T(double*);              // update as if there is another row
  void     update_S(double*);              // update as if there is another row
  void     dampen(double* scale);
  double   forward_solve(const double*, double* x);
  double   neg2loglihod(double *x);        // -2 log likelihood
  void     back_solve(const double*, double* x);
  void     solve(const double*, double* x);
  void     TtT(); // transpose of T*T
  void     interchange(int i, int j);
  double   cholesky(double tol = 0.000001);
  int      modified_cholesky();
  void     transpose_multiply(const double*, double*);
           Triangular(int);
           ~Triangular();
};

#endif

