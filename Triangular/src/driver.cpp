
#include <cstring>
#include <cmath>

#include "Triangular.h"

int main(int argc, char **argv)
  {
  char name[100];
  strcpy(name, argv[0]);
  strcat(name, ".out");
  FILE* outfile = fopen(name,"w");

  double* number = new double[100];
  for(int i=0; i<100; i++) number[i] = i+1;
  Triangular* T = 0;
  
  T = new Triangular(5);
  T->load(number, 1);
  T->print(outfile, "Index check");
  delete T;
  fflush(outfile);
  
  double logdet;

  double t[] = { 2, -1, 2, 3,
                    -1, 0, 2,
                        3, 1,
                          -1};
  T = new Triangular(4);
  T->load(t, 1);
  T->print(outfile, "Matrix T");
  T->TtT();
  T->print(outfile, "T-transpose T");
  // log of determinent
  logdet = T->cholesky();
  if( logdet == HUGE_VAL)
    fprintf(outfile, "Matrix is not positive definite.\n");
  else
    {
    T->print(outfile, "Cholesky factorization");
    fprintf(outfile,  "log determinant = %12.6g\n", logdet);
    }

  // Evaluate negative two log likelihood
  double x[] = {1,1};
  double a[] = {4, -1, 3};
  Triangular* A = new Triangular(2);
  A->load(a, 0);
  double n2l = A->neg2loglihod(x);
  fprintf(outfile, "Negative two log likelihood = %.8g.\n", n2l);

  double d[] = { 5,   10,   16,   -7,
                      16,   19,    4,
                            28,    8,
                                 -19};
  T->load(d, 0);
  T->print(outfile, "Symmetric matrix");
  logdet = T->cholesky();
  if( logdet == HUGE_VAL)
    fprintf(outfile, "Matrix is not positive definite.\n");
  else
    {
    T->print(outfile, "Cholesky factorization");
    fprintf(outfile, "log determinant = %12.6g", logdet);
    }

  T->load(d, 0);
  if( T->modified_cholesky())
    T->print(outfile, "Modified Cholesky factorization");
  else
    T->print(outfile, "Cholesky factorization");
  T->TtT();
  T->print(outfile, "\"Nearby\" symmetric matrix");

  // illustrate solve
  double e[] = { 23,   16,   22,   23,
                       18,   21,   14,
                             30,   18,
                                   31};
  double rhs[] = {134, 76, 113, 164};
  double sol[4];
  T->load(e, 0);
  T->print(outfile, "Symmetric matrix");
  if( T->modified_cholesky())
    T->print(outfile, "Modified Cholesky factorization");
  else
    T->print(outfile, "Cholesky factorization");
  T->solve(rhs, sol); // sol should be 2,-3, 2, 4
  fprintf(outfile, "\nSolution\n%8.4g%8.4g%8.4g%8.4g\n", sol[0],sol[1],sol[2],sol[3]);

  delete T;
  
  double orth[] = {1,  1,  1,  1,
                   1,  1, -1, -1,
                   1, -1,  1, -1,
                   1, -1, -1,  1};
  T = new Triangular(4);
  T->zero(1);
  double* p = orth;
  for(int i=0; i<4; i++, p += 4)   
    T->update_T(p);
  T->print(outfile, "update_T test");
  double damp[] = {1,1,1,1};
  T->dampen(damp); 
  T->print(outfile, "dampen test");
  
  double agn[]  = {1,  1,  1,  1,
                   1,  1, -1, -1,
                   1, -1,  1, -1,
                   1, -1, -1,  1};
  T->zero(0);
  T->print(outfile, "zero");
  p = agn;
  for(int i=0; i<4; i++, p += 4)   
    T->update_S(p);
  T->print(outfile, "update_S test");
  delete T;
  
  // near positive semi-definite test
  double c1[] = {1, -2, 4, -9, 3};
  double c2[] = {-1, 4, 8, 2, 6};
  double u[3];
  T = new  Triangular(3);
  T->zero(0);
  for(int i=0; i<5; i++)
    {
    u[0] = c1[i];
    u[1] = c2[i];
    u[2] = 2*c1[i]+c2[i]+0.0001;
    T->update_S(u);
    }
  T->print(outfile, "Near positive semi-definite matrix");
  if(T->modified_cholesky())
    fprintf(outfile, "modified\n");
  T->print(outfile, "factored matrix");
  T->TtT();
  T->print(outfile, "reconstructed");
  fclose(outfile);
  printf("Output file: %s.\n", name);
  return 0;
  }
  
