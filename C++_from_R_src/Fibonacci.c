
#include <R.h>
// typically n would not be a pointer
void Fibonacci(int* n, int* f)
  {
  if(*n < 2)
    *n = -1;
  else
    {
    f[0] = 0;
    f[1] = 1;
    for(int i = 2; i<*n; i++)
      f[i] = f[i-1]+f[i-2];
    }
  return;
  }

