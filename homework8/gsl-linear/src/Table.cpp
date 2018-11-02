
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <cctype>

#include "Table.h"

Table::Table(int m, int n)
  {
  this->m       = m;
  this->n       = n;
  p             = new double*[m];
  q             = new double[m*n];
  dp            = new int[n];
  for(int i=0; i<m; i++)
    p[i] = q + i*n;
  for(int i=0; i<n; i++)
    dp[i] = 4;
  }

Table::Table(int m)
  {
  this->m       = m;
  this->n       = m;
  p             = new double*[m];
  q             = new double[m*n];
  dp            = new int[n];
  for(int i=0; i<m; i++)
    p[i] = q + i*n;
  for(int i=0; i<n; i++)
    dp[i] = 4;
  }

Table::Table()
  {
  m = 0;
  n = 0;
  }

void Table::resize(int m, int n)
  {
  if(this->m)
    {
    delete []  q;
    delete []  p;
    delete []  dp;
    }
  this->m       = m;
  this->n       = n;
  p             = new double*[m];
  q             = new double[m*n];
  dp            = new int[n];
  for(int i=0; i<m; i++)
    p[i] = q + i*n;
  for(int i=0; i<n; i++)
    dp[i] = 4;
  }

Table::~Table()
  {
  if(m)
    {
    delete []  q;
    delete []  p;
    delete []  dp;
    }
  }

void Table::transpose()
  {
  if(m != n)
    {
    fprintf(stderr, "Transpose non-square matrix presently not allowed");
    exit(1);
    }
  for(int i=0; i<(n-1); i++)
    for(int j=i+1; j<n; j++)
      {
      double a = p[i][j];
      p[i][j]  = p[j][i];
      p[j][i]  = a;
      }
  }

void Table::zero()
  {
  memset(q, 0, m*n*sizeof(double));
  }

/* Swaps pointers to rows */
void Table::swap(int i, int j)
  {
  if(i == j) return;
  double* q;
  q    = p[i];
  p[i] = p[j];
  p[j] = q;
  }

#ifdef X
int Table::split(int col, double pivot, int first, int last)
  {
  while(1 < num)
    {
    while( pivot  < p[last][col]	and first<last)	last--;
		swap(first, last);

		while( p[first][col] <= pivot	and first<last) first++;
		swap(last, first);
	  }
	return first;  // while loop exits when first and last are equal
  }

// col   = index of column to specify order
// first = index of first row
// num   = number of rows in block
void Table::order(int col, int first, int last)
  {
  if(num <= 1)
    return;
  double pivot = p[first][col];	 // pivot is first element
  int        i = first;          // increasing index
  int        j = first+num;      // decreasing index

  while(i < j)
    {
    for( ; p[i][col] <= pivot     and (i <= j); i++);
    for( ; pivot      < p[j][col] and (i <= j); j--);
	k = split(col, pivot, first, last);
    if((k-first) < (last-k))
      {
      order(col, first,  k-1);        // sort lower group
      order(col,   k+1, last);	      // sort higher group
      }
    else
      {
      order(col,   k+1, last);	      // sort higher group
      order(col, first,  k-1);        // sort lower group
      }
	}
  }
#endif

void Table::load(double* a)
  {
  memcpy(q, a, m*n*sizeof(double));
  }

void Table::load_col(int j, double* a)
  {
  for(int i=0; i<m; i++)
    p[i][j] = *a++;
  }

void Table::load(FILE* file)
  {
  const int ll = 1025;
  char      line[ll];
  char*     ptr;
  zero();
  for(int i=0; i<m; i++)
    {
    ptr =fgets(line , ll-1 , file);
    if(!ptr)
      break;
    for(int j=0; j<n; j++)
      {
      p[i][j] = strtod(ptr, &ptr);
      if(not *ptr)
        break;
      }
    }
  }
  
int Table::file_dim(FILE* file, int &nrow, int &ncol)
  {
  const int ll = 1025;
  char      line[ll];
  char*     ptr;
  nrow = 0;
  ncol = 0;
  while(true)
    {
    ptr =fgets(line , ll-1 , file);
    if(!ptr)
      break;
    int k = 0;
    while(*ptr and (*ptr != '\n'))
      {
      k++;
      //fprintf(stderr, "%12.4g", strtod(ptr, &ptr));
      strtod(ptr, &ptr);
      if(not isspace(*ptr))
        return 1;
      while(isspace(*ptr)) ptr++;
      }
    if(nrow)
      {
      if(k != ncol) break;
      }
    else
      ncol = k;
    nrow++;
    //fprintf(stderr, "%5d%5d\n", nrow, ncol);
    }
  rewind(file);
  return 0;
  }

void Table::set_decimals(int* dp)              // set decimal places
  {
  memcpy(this->dp, dp, n*sizeof(int));
  }

int Table::print(FILE* f, const char* title)
  {
  if(f == NULL)
    return 1;
  if(title)
    {
    fprintf(f, "\n");
    fprintf(f, "%s\n", title);
    }
  for(int i=0; i<m; i++)
    {
    for(int j=0; j<n; j++)
      fprintf(f, "%12.*lf", dp[j],  p[i][j]);
    fprintf(f, "\n");
    }
  return 0;
  }

char* Table::to_text(const char* title)
  {
  int      k = strlen(title) + 12*m*(n+1)*sizeof(char);
  char* text = new char[k];
  char*    s = text;
  if(title)
    {
    s += sprintf(s, "\n");
    s += sprintf(s, "%s\n", title);
    }
  for(int i=0; i<m; i++)
    {
    for(int j=0; j<n; j++)
      s += sprintf(s, "%12.*lf", dp[j],  p[i][j]);
    s += sprintf(s, "\n");
    }
  return text;
  }

double Table::compare(const Table* A)
  {
  if((A->m != m) or (A->n != n))
    return HUGE_VAL;
  double  d = 0.0;
  for(int i = 0; i<m; i++)
    for(int j = 0; j<n; j++)
      if(fabs(p[i][j] - A->p[i][j]) > d)
        d = fabs(p[i][j] - A->p[i][j]);
  return d;
  }

void  Table::swap_rows(int i, int j)
  {
  if( i != j)
    {
    double* q = p[i];
    p[i] = p[j];
    p[j] = q;
    }
  return;
  }

Table* Table::merge(int col, Table* B)
  {
  if(n != B->n)
    return NULL;
  Table* C = new Table(m + B->m, n);
  int     i = 0;
  int    ib = 0;
  double* q = C->q;
  while( i < m and ib < B->m)
    {
    if(p[i][col] < B->p[ib][col])
      memcpy(q, p[i++], n*sizeof(double));
    else
      memcpy(q, B->p[ib++], n*sizeof(double));
    q += n;
    }
  while(i < m)
    {
    memcpy(q, p[i++], n*sizeof(double));
    q += n;
    }
  while(ib < B->m)
    {
    memcpy(q, B->p[ib++], n*sizeof(double));
    q += n;
    }
  return C;
  }

void Table::pre_mult(const double* a, int k, double* c)
  {
  memset(c, 0, n*sizeof(double));
  for(int j=0; j<n; j++)
    for(int i=0; i<k; i++)
        c[j] += a[i] * p[i][j];
  }

Table* Table::product(Table* B)
  {
  if( n != B->m )
    return NULL;
  Table* C = new Table(m, B->n);
  C->zero();
  for(int i = 0; i<m; i++)
    for(int j = 0; j < B->n; j++)
      for(int k=0; k<n; k++)
        C->p[i][j] += p[i][k] * B->p[k][j];
  return C;
  }

// transpose product
Table* Table::t_product(Table* B)
  {
  if( m != B->m )
    return NULL;
  Table* C = new Table(n, B->n);
  C->zero();
  for(int i = 0; i<n; i++)
    for(int j = 0; j < B->n; j++)
      for(int k=0; k<m; k++)
        C->p[i][j] += p[k][i] * B->p[k][j];
  return C;
  }

// product transpose
Table* Table::product_t(Table* B)
  {
  if( n != B->n)
    return NULL;
  Table* C = new Table(m, B->m);
  C->zero();
  for(int i = 0; i<m; i++)
    for(int j = 0; j < B->m; j++)
      for(int k=0; k<n; k++)
        C->p[i][j] += p[i][k] * B->p[j][k];
  return C;
  }

Table* Table::duplicate()
  {
  Table* C = new Table(m, n);
  for(int i = 0; i<m; i++)
    memcpy(C->p[i], p[i], n*sizeof(double));
  return C;
  }

#ifdef X
void Table::order(int col, int first, int last)
  {
  double pivot = p[first][col];	 // pivot is first element
  int k;
  if(last > first)	// if equal, done
    {
	k = split(col, pivot, first, last);
    if((k-first) < (last-k))
      {
      order(col, first,  k-1);        // sort lower group
      order(col,   k+1, last);	      // sort higher group
      }
    else
      {
      order(col,   k+1, last);	      // sort higher group
      order(col, first,  k-1);        // sort lower group
      }
	}
  }
#endif


