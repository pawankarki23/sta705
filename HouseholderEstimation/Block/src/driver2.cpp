
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Table.h"
#include "Block.h"
int main(int argc, char **argv)
{
  char name[100];
  strcpy(name, argv[0]);
  strcat(name, ".out");
  FILE*  out = fopen(name,"w");
  
  double  x[]     = {1.2,2.9,3.8,4.1,5.7,6.3,7.0,8.5,9.2};
  int     treat[] = {0,0,0,1,1,1,2,2,2};
  int     block[] = {0,1,2,0,1,2,0,1,2};
  double  y[]     = {1,2,3,4,5,6,7,8,9};

  Block* X = new Block(9, "intercept");
  X->adjoin(new Block(treat, 9, 3, "treatment"));
  X->adjoin(new Block(block, 9, 3, "block"));
  X->print(out, "X matrix");

  X->calc_transform(0);
  Table* E = X->get_block(X);
  E->print(out, "Echelon matrix");
 
  Block* Y = new Block(y, 9, "Y"); 
  X->apply_transform(Y);

  Y->print(out, "Transformed Y");
  
  double* Yx = Y->p[0];
  double* Yp = Yx + E->m;
  
  double b[100];
  E->calc_b(Yx, b);
  for(int i=0; i<E->n; i++)
    fprintf(out, "b[%d] = %12.6lf\n", i, b[i]);

  double r[100];
  E->mult(b, r);  
  for(int i=0; i<E->n; i++)
    fprintf(out, "r[%d] = %12.6lf\n", i, r[i]);
    
  double a[100];

  double c[] = {0,1,0,-1, 0, 0, 0};
  bool estimable = E->calc_a(c, a);
  if(estimable)
  {
    double v = 0.0;
    double e = 0.0;
    for(int i=0; i < E->m; i++)
    {
      fprintf(out, "%12.6lf%12.6lf\n", a[i], Yx[i]);
      v += a[i]*a[i];
      e += a[i]*Yx[i];
    }
    fprintf(out, "v = %.4lf, e = %.4lf\n", v, e);
  }
  else
    fprintf(out, "Not estimable\n");

  fclose( out);
  printf("Output file: %s\n", name);
  return 0;
  }