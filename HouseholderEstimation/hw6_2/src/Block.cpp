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

#include "Table.h"
#include "Block.h"

void Block::memory()
  {
  p         = (double**) malloc(n*sizeof(double*));
  q         = (double*)  malloc(m*n*sizeof(double));
  maxabs    = (double*)  malloc(n*sizeof(double));
  beta      = (double*)  malloc(n*sizeof(double));
  diag      = (double*)  malloc(n*sizeof(double));
  for(int i=0; i<n; i++)
    p[i] = q + i*m;
  }
  
// indicator variables
// m = numner of observations
// n = number of levels
// level contains values 0 to n-1
Block::Block(int* level, int m, int n, const char* l)
  {
  if(l) strcpy(label, l); else label[0] = 0;
  this->m   = m;
  this->n   = n;
  memory();
  memset(q, 0, m*n*sizeof(double));
  for(int j=0; j<n; j++)
    maxabs[j] = 1;
  for(int i=0; i<m; i++)
    {
//    fprintf(stderr, "%8d\n", level[i]);
    p[level[i]][i] = 1;
    }
  return;
  }

// single column of ones
Block::Block(int m, const char* l)
  {
  if(l) strcpy(label, l); else label[0] = 0;
  this->m   = m;
  n         = 1;
  memory();
  maxabs[0] = 1;
  for(int i=0; i<m; i++) q[i] = 1;
  return;
  }
  
// single column numeric
Block::Block(double* x, int m, const char* l)
  {
  if(l) strcpy(label, l); else label[0] = 0;
  this->m    = m;
  n          = 1;
  memory();
  double max = 0;
  for(int i=0; i<m; i++) 
    if(fabs(x[i])>max) max = fabs(x[i]);
  maxabs[0] = max;
  memcpy(q, x, m*sizeof(double));
  return;
  }

// rectangular matrix from file
Block::Block(FILE* file, int m, int n, const char* l)
  {
  if(l) strcpy(label, l); else label[0] = 0;
  this->m = m;
  this->n = n;
  const int ll = 1025;
  char      line[ll];
  char*     ptr;
  memory();
  for(int i=0; i<m; i++)
    {
    ptr =fgets(line , ll-1 , file);
    if(!ptr)
      break;
    for(int j=0; j<n; j++)
      {
      p[j][i] = strtod(ptr, &ptr);
      if(not *ptr)
        break;
      }
    }
  }

int Block::adjoin(Block* adj)
  {
  if(m != adj->m)
    return 1;
  strcat(label, " | ");
  strcat(label, adj->label);
  int k = n + adj->n;
  q      = (double*)  realloc(q,    m*k*sizeof(double ));
  memcpy(q+m*n, adj->q, m*adj->n*sizeof(double));

  p      = (double**) realloc(p,      k*sizeof(double*));
  maxabs = (double*)  realloc(maxabs, k*sizeof(double));
  beta   = (double*)  realloc(beta,   k*sizeof(double));
  diag   = (double*)  realloc(diag,   k*sizeof(double));
  memcpy(maxabs+n, adj->maxabs, adj->n*sizeof(double));  
  memcpy(beta+n,   adj->beta,   adj->n*sizeof(double));  
  memcpy(diag+n,   adj->diag,   adj->n*sizeof(double));  
  n += adj->n;
  for(int j=0; j<n; j++)
    p[j] = q + j*m;
  return 0;
  }
  
Table* Block::get_block(Block* row)
  {
  int r = row->r1 - row->r0;
  Table* block = new Table(r, n);
  sprintf(block->label, "block(%s,%s)", row->label, label);
  if(row == this)
    {
    int k = 0;              // index of active row
    for(int i=0; i<n; i++)   
      {
      if(diag[i] == 0.0) continue;
      for(int j=0; j<i; j++) 
        block->p[k][j] = 0.0;
      block->p[k][i] = diag[i];
      for(int j=i+1; j<n; j++) 
        block->p[k][j] = p[j][k+r0];
      k++;
      }
    }
  else
    {
    for(int i=0; i<r; i++)
      for(int j=0; j<n; j++)
        {
        block->p[i][j] = p[j][row->r0+i];
        }
    }  
  return block;
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
  for(int i=offset; i < m; i++)
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
  for(int i = offset; i<m; i++)
    dot += *q++ * *r++;
  dot /= beta;
  q = w + offset;
  r = v + offset;
  for(int i = offset; i<m; i++)
    *r++ -= dot * *q++;
  return;
  }
  
int Block::calc_transform(int r0)
  {
  this->r0 = r0;
  r1       = r0;
  double norm;
  for(int j=0; j<n; j++)
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
      for(int k=j+1; k<n; k++)
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
  for(int i=0; i<n; i++)
    {
    if(beta[i] == 0.0) continue;
    for(int j=0; j<obj->n; j++)
      reflect(p[i], beta[i], obj->p[j], offset);
    offset++;
    }
  }

void Block::print(FILE* f, const char* title)
  {
  if(!f) return;
  fprintf(f, "\n");
  if(title)  fprintf(f, "%s\n", title);
  if(*label) fprintf(f, "%s\n", label);
  for(int i = 0; i<m; i++)
    {
    for(int j=0; j<n; j++)
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
  for(int i=0; i<n; i++)
    fprintf(f, "%12.4lf%12.4lf%12.4lf\n", diag[i], beta[i], maxabs[i]);
  fprintf(f, "%12s%12d%12s%12d\n", "r0 =", r0, "r1 =", r1);
  }

void  Block::calc_b(double* rhs, double* b)
  {
  memset(b, 0, n*sizeof(double));
  for(int i = r1, j = n; 0 < i; )
    {
    i--;
    j--;
    while(diag[j] == 0.0) j--;
    b[j] = rhs[i];
    for(int k = j+1; k < n; k++)
      b[j] -= p[k][i] * b[k];
    b[j] /= diag[j];
    }
  }
    


