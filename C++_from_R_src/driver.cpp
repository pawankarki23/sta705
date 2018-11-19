#include <cstdio>
#include "Convolve.cpp"

int main(int argc, char *argv[])
  {
  const int n = 6;
  double a[n];
  double b[n];

  for(int i = 0; i<n; i++)
    {
    a[i] = 1.0/n;
    b[i] = 1.0/n;
    }

  Convolve* con;
  double* ab = new double[n+n-1];
  con = new Convolve(n, n);
  con->evaluate(a, b, ab);

  fprintf(stdout, "Distribution of sum\n");
  fprintf(stdout, "%10s%10s\n", "value", "prob");
  for(int i = 0; i<(n+n-1); i++)
    fprintf(stdout, "%10i%10.4lf\n", i+2, ab[i]);
  return 0;
  }
