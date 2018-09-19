#include <stdio.h>
#include <stdlib.h>  // exit is here
#include <math.h>    // fabs is here


/* Homework 1 - Pawan Karki (09/07/2018) */
/* Solving exp(-x)-exp(-2x)=0.15 using the Bisection Algorithm */ 

// a function that finds the root using Bisection Algorirth for given function, lower and upper bounds 
// I am changing the function provided in the class to handle both increasing and decreasing functions
double findroot(double (*f)(double x), double l, double u, FILE *outfile = NULL, double tol = 0.000001)
  {
    // let the function be increasing by default 
    bool is_fuct_increasing = true; 
    double m = 0;

    //Check if the function is increasing
    if( (f(u) < 0.0) or (f(l) > 0.0))
    {
      fprintf(outfile , "Not an increasing function; f(u)=%lf, f(l)=%lf\n\n",f(u),f(l));
      is_fuct_increasing = false;
    }

  fprintf(outfile,"\t l\t\t\t m \t\t\t u\n");

  while(fabs(u - l) > tol)
  {
      m = (l + u)/2;
      // write the intermediate steps into the file 
      fprintf(outfile,"%10.4lf%10.4lf%10.4lf\n", l, m, u);

      if(is_fuct_increasing)
      {
        if(f(m) < 0.0)
          l = m;
        else
          u = m; 
      }
      else{
        if(f(m) < 0.0)
          u = m;
        else
          l = m; 

      }

    }
  return m;
  }
  
/* custom function returning exp(-x)-exp(-2x)-0.15 */
double getfuncvalue(double x){ return (exp(-x) - exp(-2*x)-0.15);}

/* The main function */
int main()
{
  double lowerbound = log(2);
  double upperbound = 10;
  FILE *outfile = fopen("outputfile.txt","w+");
  
  //save the results into a file
  fprintf(outfile, "%5s %12.4lf\n", "\n\nFor Given function, the root is: ", findroot(getfuncvalue, lowerbound, upperbound, outfile));

  // close the file
  fclose(outfile);

  return 0;  
}