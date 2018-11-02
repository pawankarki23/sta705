#include <cstring>
#include <cstdlib>
#include <cmath>

#include "GSLlinear.h"
#include "CompModel.h"

// constructor
CompModel::CompModel(int nr, int* from, int* to)
  {
  if(nr < 1)
    {
    fprintf(stderr, "The number of rate constants must be positive.\n");
    exit(1);
    }
  this->nr      = nr;
  this->from    = new int[nr];
  this->to      = new int[nr];
  n             = 0;
  for(int i=0; i<nr; i++)
    {
    if(from[i] > n) n = from[i];
    if(to[i]   > n) n = to[i];
    this->from[i]     = from[i];
    this->to[i]       = to[i];
    }
  n++;
  S        = new DEmodel(n);
  np       = nr;
  inf      = -1;
  bol      = -1;
  param    =  0;
  }
  
CompModel::~CompModel()
  {
  delete [] from;
  delete [] to;
  }  
  
// Fills system matrix with parameter values  
// On entry     --- theta points to a vector of rate constants,
//                  followed by amount of bolus if present,
//                  followed by the infusion constant if present.
// Return value --- pointer just beyond entry vector. 
double* CompModel::system(double* theta)
  {
  param = theta;
  memset(S->q, 0, n*n*sizeof(double));
  for(int i=0; i < nr; i++, theta++) 
    {
    S->p[from[i]][from[i]] -= *theta;
    S->p[  to[i]][from[i]] += *theta;
    }
  if(bol>= 0)
    {
    memset(S->initial, 0, sizeof(double));
    S->initial[bol] = *theta++;
    }
  if(inf >= 0)
    {
    memset(S->infusion, 0, sizeof(double));
    S->infusion[inf]= *theta++;
    }
  return theta;
  }

void CompModel::bolus_site(int bol)
  {
  if((bol<0) or (bol>=n))
    {
    fprintf(stderr, "Illegal bolus compartment.\n");
    exit(1);
    }
  this->bol = bol;
  np = nr + (bol >= 0) + (inf >= 0);
  }
    
void CompModel::infusion_site(int inf)
  {
  if((inf<0) or (inf>=n))
    {
    fprintf(stderr, "Illegal infusion compartment.\n");
    exit(1);
    }
  this->inf = inf;
  np = nr + (bol >= 0) + (inf >= 0);
  }
    
void CompModel::print(FILE* f,  const char* title)
  {
  if(!f)
    return;
  if( param)
    {
    fprintf(f, "\n%s\n", title);
    fprintf(f, "Rate constants:\n");
    fprintf(f, "%12s%12s%12s\n", "From", "To", "Value");
    for(int i=0; i<nr; i++) 
      fprintf(f, "%12d%12d%12.6g\n", from[i],  to[i], param[i]);
    fprintf(f, "\nSystem matrix\n");
    for(int i=0; i<n; i++)
      {
      for(int j=0; j<n; j++)
        fprintf(f, "%12.6lf", S->p[i][j]);
      fprintf(f, "\n");
      }  
    fprintf(f, "\n%12s%12s\n", "Bolus", "Infusion");
    for(int i=0; i<n; i++)
      {
      fprintf(f, "%12.6lf%12.6lf\n", S->initial[i], S->infusion[i]);
      }
    }  
  }

