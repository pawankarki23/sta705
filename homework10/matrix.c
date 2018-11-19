
#include <R.h>

void get_my_values(int *m, int *n, int *res)
{
  double a[] = {1 , 2 , 3 , 6 , 5 , 4};
  int mrow = 2;
  int ncol = 3;

  for(int i = 0; i<(mrow*ncol); i++)
  {
      res[i] = a[i];
  }
  
  return;
}

