#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

#include "Evolution.h"

void Evolution::setseed(unsigned int seed)
  {
  srand(seed);
  return;
  }
  
void Evolution::setwtfact(double wtfact)
  {
  this->wtfact = wtfact;
  return;
  }

void Evolution::toggledisplay()
  {
  display = not display;
  }  
  
double Evolution::uniform()
  {
  return rand()/(double) RAND_MAX;
  }

Evolution::Evolution(int nv, int nm, void* extra)  
  {
  this->extra      = extra;                  // passed to objective
  this->nv         = nv;                     // number of variables
  this->nm         = nm;                     // number of members
  genmax           = 50;                     // maximum generations allowed    
  wtfact           = 0.85;                   // weighting factor               
  mut              = 1.0/100;                // mutation probability           
  conv             = 0.000001;               // convergence factor        
  current          = new double[nv*nm];      // memory for current popultation
  next             = new double[nv*nm];      // values of objective function
  value            = new double[nm];
  display          = false;
  }

Evolution::~Evolution()
  {
  delete [] current;
  delete [] next;
  delete [] value;
  }
  
void Evolution::evolve(double* lower, double* upper, double* phi )
  {
  if(display)
    fprintf(stderr, "%10s%10s%15s\n", "Iteration", "Member", "Value");
  /* create generation 0 */
  double* x    = current;
  for(int j=0; j<nm; j++)          // loop over members
    for(int i=0; i<nv; i++)        // loop over parameter values
      *x++ = lower[i] + uniform()*(upper[i] - lower[i]);

  double* swap  = current;
  int      gen  = 0;
  int     best  = find_best();
  bool    done  = false;
  while ( (gen < genmax) and !done ) 
    {
    if(display)
      fprintf(stderr, "%10d%10d%15.4g\n", gen, best, value[best]);
//  imut = floor( log(uniform()+0.0001)/lnmut );
    create_next();
    swap         = current;
    current      = next;
    next         = swap;
    best         = find_best();
    gen++;
    }
//  free(history);
  for(int i=0; i<nv; i++)
    phi[i] = *(current + best*nv+i);
  return;
  }

int Evolution::find_best()
  {
  int    best   = 0;
  double lowest = HUGE_VAL;
  for(int j=0; j<nm; j++)
    {
    value[j] = objective(current + j*nv, nv, extra);
    if(value[j] < lowest)
      {
      lowest = value[j];
      best   = j;
      }
    }
  return best;
  }
  
/* create next generation */
void Evolution::create_next()
  {
  int     r1;
  int     r2;
  double* b;
  double* trial;
  double* xj;
  double* x1;
  double* x2;
  double  trial_value;
  
  int best = find_best();
  for (int j = 0; j < nm; j++)
    {
 	  do
      r1 = (int)(uniform()* nm );
    while(r1==j);

 	  do
      r2 = (int)(uniform()* nm );
 	  while((r2==j) || (r2==r1));

    b     = current + best*nv;
    xj    = current + j*nv;
    x1    = current + r1*nv;
    x2    = current + r2*nv;
    trial = next    +  j*nv;
    for(int i=0; i<nv; i++)
      if(uniform() <= mut)
        trial[i] = xj[i] + wtfact*(b[i] - xj[i]) - wtfact*(x1[i] - x2[i]);
      else
        trial[i] = xj[i] + wtfact*(b[i] - xj[i]) + wtfact*(x1[i] - x2[i]);
    trial_value = objective(trial, nv, extra);
    if(trial_value < value[j] )
      value[j] = trial_value;
    else
      memcpy(next + j*nv, current + j*nv, nv*sizeof(double));
    }
  }
  
