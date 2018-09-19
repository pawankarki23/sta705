/*
Functions here apply Householder transformations as described 
in Golub and Van Loan, first edition, page 148. As defined there,
"beta" are nomalizing constants and "diag" are diagonal elements.
"maxabs" is my addition for a singularity test invariant to
units of meaurements.
For ease of access later, transformation may be applied to
blocks separately.
*/

#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>

#include "Blocks.h"

void Block::memory()
  {
  p         = (double**) malloc(m*sizeof(double*));
  q         = (double*)  malloc(m*n*sizeof(double));
  maxabs    = (double*)  malloc(m*sizeof(double));
  beta      = (double*)  malloc(m*sizeof(double));
  diag      = (double*)  malloc(m*sizeof(double));
  for(int i=0; i<m; i++)
    p[i] = q + i*n;
  }
  
// m = number of levels
// n = numner of observations
void Block::categories(int* level, int m, int n)
  {
  this->m   = m;
  this->n   = n;
  memory();
  memset(q, 0, m*n*sizeof(double));
  for(int i=0; i<m; i++)
    maxabs[i] = 1;
  for(int i=0; i<n; i++)
    p[level[i]][i] = 1;
  return;
  }

int Block::get_block(Block* term[], int row, int col)
  {
  if(col < row) return 1;
  int r0 = term[row]->r0;
  int r1 = term[row]->r1;
  if(r0 == r1)  return 2;
  n = r1 - r0;                  // # of rows
  m = term[col]->m;             // # of cols
  memory();
  if(row == col)
    {  
    int k = 0;              // index of active row
    for(int i=0; i<m; i++)   
      {
      if(term[col]->diag[i] == 0.0) continue;
      for(int j=0; j<i; j++) 
        p[j][k] = 0.0;
      p[i][k] = term[col]->diag[i];
      for(int j=i+1; j<m; j++) 
        p[j][k] = term[col]->p[j][k+r0];
      k++;
      }
    }
  else
    {
    for(int j=0; j<m; j++)
      for(int i=0; i<n; i++)
        {
        p[j][i] = term[col]->p[j][r0+i];
        }
    }
  return 0;
  }

void Block::ones(int n)
  {
  this->n   = n;
  m         = 1;
  memory();
  maxabs[0] = 1;
  for(int i=0; i<n; i++) q[i] = 1;
  return;
  }
  
void Block::numeric(double* x, int n)
  {
  this->n    = n;
  m          = 1;
  memory();
  double max = 0;
  for(int i=0; i<n; i++) 
    if(fabs(x[i])>max) max = fabs(x[i]);
  maxabs[0] = max;
  memcpy(q, x, n*sizeof(double));
  return;
  }

int Block::adjoin(Block* term[], int nt)
  {
  m = term[0]->m;
  n = term[0]->n;
  for(int j=1; j<nt; j++)
    {
    if(term[j]->n != n)
      return 1;
    m += term[j]->m;
    }
  memory();
  double* r = q;
  double* s = maxabs;
  for(int j=0; j<nt; j++)
    {
    int k = term[j]->m * term[j]->n;
    memcpy(r, term[j]->q, k*sizeof(double));
    r += k;
    int l = term[j]->m;
    memcpy(s, term[j]->maxabs, l*sizeof(double));
    s += l;
    }
  return 0;
  }
 
void Block::unpack()
  {
  if(!r1) return;
  int k = r0;                           // row index
  for(int i=0; i<m; i++)                // col index
    {
    if(diag[i] == 0.0) continue;
    for(int j=0; j<i; j++) p[j][k] = 0.0;
    p[i][k] = diag[i];
    k++;
    }
  for(int i=r1; i<n; i++)
    for(int j=0; j<m; j++)
      p[j][i] = 0.0;
  return;
  }
   
Block::Block()
  {
  m   = 0;
  n   = 0;
  r0  = 0;
  r1  = 0;
  }
  
Block::~Block()
  {
  if(m)
    {
    free(p);
    free(q);
    free(maxabs);
    free(diag);
    free(beta);
    m = 0;
    }
  }  
  
double Block::calc_norm(int col, int offset, double tol)
  {
  double*  q = p[col] + offset;
  double norm2 = 0.0;           // squared norm
  for(int i=offset; i < n; i++)
    norm2 += pow(*q++, 2);
  double norm = sqrt(norm2);
  if(norm <= tol*maxabs[col])
    return 0.0;
  if(p[col][offset] > 0.0)
    norm = -norm;
  return  norm;
  }
  
//  Applies an elementrary reflection w applied to v.
//  beta = normalization const for w 
//  r1   = offset
void Block::reflect(double* w, double beta, double* v, int offset)
  {
  double*  q = w + offset;
  double*  r = v + offset;
  double dot = 0.0;
  for(int i = offset; i<n; i++)
    dot += *q++ * *r++;
  dot /= beta;
  q = w + offset;
  r = v + offset;
  for(int i = offset; i<n; i++)
    *r++ -= dot * *q++;
  return;
  }
  
int Block::calc_transform(int r0)
  {
  this->r0 = r0;
  r1       = r0;
  double norm;
  for(int j=0; j<m; j++)
    {
    norm = calc_norm(j, r1);
    if(norm == 0.0)
      {
      beta[j] = 0.0;
      diag[j] = 0.0;
      }
    else
      {
      diag[j]   = norm;
      beta[j]   = norm*(norm - p[j][r1]);
      p[j][r1] -= norm;
      // apply to remaining columns
      for(int k=j+1; k<m; k++)
        reflect(p[j], beta[j], p[k], r1);
      r1++;
      }
    }
  // fprintf(stderr, "%12d\n", r1);
  return r1;
  }

// Apply stored transformations to columns in obj
void Block::apply_transform( Block* obj)
  {
  int offset = r0;
  for(int i=0; i<m; i++)
    {
    if(beta[i] == 0.0) continue;
    for(int j=0; j<obj->m; j++)
      reflect(p[i], beta[i], obj->p[j], offset);
    offset++;
    }
  }

/*
For a given vector c, a vector a such that a^t E = c^t is sought.
tol is a tolerance for checking zero values.
Return value is true if a is successfully computed, false if not.
c is over-written during computation.
*/
bool Block::calc_a(double* c, double* a, double tol)
  {
  int j  = 0;                        // j is column index
  for(int i=0; i < r1; i++, j++)     // i is row index
    {
    while( diag[j] == 0.0) j++;      // first non-zero element in row
    double mf = c[j]/diag[j];        // calculate the multiplier
    a[i] = mf;
    c[j] = 0.0;
    for(int l=j+1; l<m; l++)
      c[l] -= mf*p[l][i];            // subtract multiple of row from c
    }
  bool check = true;
  for(int j=0; j < m; j++)           // check if solution exists
    if(fabs(c[j]) > tol)
      {
      check = false;
      break;
      }
  return check;
  }

void Block::print(FILE* f, const char* title)
  {
  if(!f) return;
  fprintf(f, "\n");
  if(title) fprintf(f, "%s\n", title);
  for(int i = 0; i<n; i++)
    {
    for(int j=0; j<m; j++)
      fprintf(f, "%12.4lf", p[j][i]);
    fprintf(f, "\n");
    }
  }

// For viewing auxiliary variables
void Block::auxiliary(FILE* f, const char* title)
  {
  if(!f) return;
  fprintf(f, "\n");
  fprintf(f, "Auxiliary variables\n");
  if(title) fprintf(f, "%s\n", title);
  fprintf(f, "%12s%12s%12s\n", "diag", "beta", "maxabs");
  for(int i=0; i<m; i++)
    fprintf(f, "%12.4lf%12.4lf%12.4lf\n", diag[i], beta[i], maxabs[i]);
  fprintf(f, "%12s%12d%12s%12d\n", "r0 =", r0, "r1 =", r1);
  }
    
#ifdef X

/*
calulates least a squares solution
inputs:
the reduced X, Yx (the transformed Y), and col (the column of Yx used)
output:
solution vector b for X b = Yx[col]
*/
void Blocks::calc_b(Table* X, Table* Yx, int col, double* b)
  {
  int n = X->n;
  memset(b, 0, n*sizeof(double));
  for(int i = rank, j = n; 0 < i; )
    {
    i--;
    j--;
    while(diag[j] == 0.0) j--;
    b[j] = Yx->p[i][col];
    for(int k=j+1; k<n; k++)
      b[j] -= X->p[i][k] * b[k];
    b[j] /= diag[j];
    }
  }

#endif



