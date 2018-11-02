#include <stdio.h>
#include <cstdlib>
#include <cmath>
#include <cstring>

#include "Table.h"
#include "CompModel.h"
#include "GSLlinear.h"

int main(int argc, char** argv)
{
  // open output files two output functions 
  char system[50];
  strcpy(system, argv[0]);
  strcat(system, ".out");
  char data[50];
  strcpy(data, argv[0]);
  strcat(data, ".dat");
   
  FILE* logfile = fopen(system, "w");
  
  // number of rate constants
  int nr  = 3;  
  
  // Specify model, index compartments starting at 0
  int         from[]  = {0, 1, 2};
  int           to[]  = {1, 2, 0};

  // parameter values, rate constants followed by inputs
  double     param[]  = {1, 1, 1, 100}; 

  CompModel*  model = new CompModel(nr, from, to);
  // inputs
  model->bolus_site(0);
  //model->infusion_site(0);
  
  double*     theta = param;
  GSLlinear*  gsl = new GSLlinear();
  
  // Times 
  const int m = 21;
  double*   t = new double[m];
  // time from 0 to 21/8
  for(int i = 0; i<m; i++) t[i] = i/8.0;

  // Create place for results (we will put time in first column)
  Table*   X = new Table(m, model->n+1);
  X->zero();

  theta = model->system(theta);
  model->print(logfile, "System Information");

  gsl->solve(model->S, t, X);
  // put time vector into the first column
  X->load_col(0, t);
  FILE* dat = fopen(data, "w");
  X->print(dat);
  // close down
  fclose(dat);
  fclose(logfile);
  printf("%20s : %20s\n", "System info", system);
  printf("%20s : %20s\n", "Plot data",   data);
  return 0;
  }
  
