#include <cstdio>  

/* printf has a similar function to cout */

int main()
{
  double   a = 29.45;
  bool     b = 12;
  char     c = 'x';
  int      k = 45;
  int*     p = &k;        // & is read as "address of"
  double x[] = {1.2, 4.6, 6.9, 3.5, 2.1};
  
  printf("\nThe following are examples of common conversion specifiers\n");
  printf("%40s %14.4lf\n",  "Use lf (for long float) for double: ", a);
  printf("%40s %14.4g\n", " For a wide range of magnitude use g: ", a*10e10);
  printf("%40s %14i\n",    "For an integer character use i or d: ", k);
  printf("%40s %14c\n",                  "For a character use c: ", c);
  printf("%40s %14d\n", "For underlying integer code use i or d: ", c);
  printf("%40s %14p\n",                    "For a pointer use p: ", p);
  printf("%40s %14p\n",                    "For a pointer use p: ", x);
  return 0;
}
  

