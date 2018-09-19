
#include <stdio.h>

int main()
{
  int m = 4;  // number of rows
  int n = 5;  // number of columns
  // from here down the literal constants are not referenced
  // create 2d array
  double** p = new double*[m];
  double*  q = new double[n*m];
  for(int i=0; i<m; i++)
    p[i] = q+i*n;        // pointer arithmetic
  // assign values
  for(int i =0; i<m; i++)
    for(int j=0; j<n; j++)
      {
      int x = i+1;
      int y = j+1;
      p[i][j] = x+y;
      }
  // print current value
  for(int i =0; i<m; i++)
    {
    for(int j=0; j<n; j++)
      fprintf(stdout, "%8.2lf", p[i][j]);
    fprintf(stdout, "\n");
    }
  delete []  p;  // [] is used when deleting arrays
  delete []  q;
  return 0;
}
