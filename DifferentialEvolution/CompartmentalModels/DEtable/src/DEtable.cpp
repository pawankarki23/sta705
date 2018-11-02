#include <string.h>

#include "DEtable.h"

DEtable::DEtable(int m, int n)
  {
  label   = 0;
  this->m = m;
  this->n = n;
  p       = new double*[m];
  q       = new double[m*n];
  for(int i=0; i<m; i++)
    p[i] = q + i*n;
  }
  
DEtable::~DEtable()
  {
  delete [] p;
  delete [] q;
  if(label)
    {
    delete [] label;
    delete [] head;
    }
  }

void  DEtable::headings()
  {
  int k   = 20;
  head    = new char*[n];
  label   = new char[(n+1)*k];
  head[0] = label;
  strcpy(head[0], "Time");
  for(int i=0; i<n; i++)
    {
    head[i+1] = label + (i+1)*k;    
    sprintf(head[i+1], "State_%d", i+1);
    }
  }
 
void DEtable::print(FILE* f, double* t)
  {
  if(!f)
    return;
  if(label)
    {
    for(int j = 0; j<n+1; j++)
      fprintf(f, "%12s", head[j]);
    fprintf(f, "\n");
    }
  for(int i=0; i<m; i++)
    {
    if(t)
      fprintf(f, "%12.4lf", t[i]);
    for(int j = 0; j<n; j++)
      fprintf(f, "%12.4lf", p[i][j]);
    fprintf(f, "\n");
    }
  }

void DEtable::load(double* q)
  {
  memcpy(this->q, q, m*n*sizeof(double));
  }

