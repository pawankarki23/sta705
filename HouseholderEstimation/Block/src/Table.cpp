#include <string.h>
#include <math.h>

#include "Table.h"

Table::Table(int m, int n, const char* l)
  {
  if(l) strcpy(label, l); else label[0]=0;
  this->m = m;
  this->n = n;
  p = new double*[m];
  q = new double[m*n];
  for(int i=0; i<m; i++)
    p[i] = q + i*n;
  }

Table::~Table()
  {
  delete [] p;
  delete [] q;
  }
    
void Table::print(FILE* f, const char* title)
  {
  if(!f) return;
  fprintf(f, "\n");
  if(title)  fprintf(f, "%s\n", title);
  if(*label) fprintf(f, "%s\n", label);
  for(int i=0; i<m; i++)
    {
    for(int j=0; j<n; j++)
      fprintf(f, "%12.4lf", p[i][j]);
    fprintf(f, "\n");
    }
  return;
  } 

/*
The table must be echelon.
For a given vector c, a vector a such that a^t E = c^t is sought.
tol is a tolerance for checking zero values.
Return value is true if a is successfully computed, false if not.
The vector c is destroyed during computation.
*/
bool Table::calc_a(double* c, double* a, double tol)
  {
  int j  = 0;                            // j is column index
  for(int i=0; i< m; i++)                // i is row index
    {
    while( fabs(p[i][j]) <= tol) j++;    // find first non-zero element in row
    double mf = c[j]/p[i][j];            // calculate the multiplier
    a[i] = mf;
    for(int l=j; l< n; l++)
      c[l] -= mf*p[i][l];                // subtract multiple of row from c
    }
  bool check = true;
  for(int j=0; j< n; j++)                // check if solution exists
    if(fabs(c[j]) > tol)
      {
      check = false;
      break;
      }
  return check;
  }

// solve E b = rhs
// table must be echelon
void  Table::calc_b(double* rhs, double* b)
  {
  memset(b, 0, n*sizeof(double));
  for(int i = m; 0 < i; )
    {
    i--;
    int k = 0;
    while(p[i][k] == 0.0) k++;
    b[k] = rhs[i];
    for(int j = k+1; j < n; j++)
      b[k] -= p[i][j] * b[j];
    b[k] /= p[i][k];
    }
  }
  
void Table::mult(double* x, double* r)
  {
  for(int i=0; i<m; i++)
    {
    r[i] = 0.0;
    for(int j=0; j<n; j++)
      r[i] += p[i][j] * x[j];
    }
  }
    
    
  
