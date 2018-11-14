
#include <cstring>
#include <cstdio>
#include <math.h>

#include <DEtable.h>
#include <Runge-Kutta.h>


// excercise 11.1 
// t is time
// y is current value of variables
// output
// der is derivatives
int Runge_Kutta::f(double t, const double* y, double* der, void* data)
  {
  der[0] =   9*y[0] + 24*y[1] + 5*cos(t) - sin(t)/3;
  der[1] = -24*y[0] - 51*y[1] - 9*cos(t) + sin(t)/3;
  return 0;
  }
   
int main(int argc, char* argv[])
  {
  // open output file
  char name[50];
  strcpy(name, "plot.dat");
  FILE* output = fopen(name, "w");

  // set dimensions 
  const int      m   = 256;      
  const int      n   = 2;            // size of system
  
  // define times
  double max = 3*M_PI;
  double* t          = new double[m];
  for(int i=0; i<m; i++)
    t[i] = max*((double) i/ (m-1));
  printf("h is %.6lf\n", t[1]-t[0]);
  
  // define system    
  Runge_Kutta* rk = new Runge_Kutta();  
  DEtable*      X = new DEtable(m, n);
  double x0[n];
  x0[0] = 4.0/3;
  x0[1] = 2.0/3;
  X->set_x0(x0);
  // solve and save
  rk->solve(t, X); 
  X->headings();
  X->print(output, t);
  
  // evalute known functions and compare
  DEtable*  A  = new DEtable(m, n);
  for(int i =0; i<m; i++)
    {
    double s = t[i];
    A->p[i][0] = 2*exp(-3*s)-  exp(-39*s)+cos(s)/3;
    A->p[i][1] =  -exp(-3*s)+2*exp(-39*s)-cos(s)/3;
    }
  A->headings();
//  A->print(output, t);
  // as the solution was given - we can compare the solution we got with the one given see ex 11.1 
  double dif = X->compare(A);
  printf("maxium error = %.6g\n", dif);
  
  // clean up
  fclose(output);
  printf("Plot file is %s\n", name);
  return 0;
  }

