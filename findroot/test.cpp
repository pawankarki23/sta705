
#include <stdio.h>
#include "findroot.h"

double quad(double x){ return x*x - 4;}

double line(double x){ return -5 + x;}

int main()
  {
  double l = 0;
  double u = 10;
  FILE *outfile = fopen("outputfile.txt","w");
  fprintf(stdout, "%5s %12.4lf\n", "quad", findroot(quad, l, u));
  fprintf(stdout, "%5s %12.4lf\n", "line", findroot(line, l, u));

  //save the results into a FILE

  fprintf(outfile, "%5s %12.4lf\n", "quad", findroot(quad, l, u));
  fprintf(outfile, "%5s %12.4lf\n", "line", findroot(line, l, u));

  fclose(outfile);
  return 0;  
  }
    
