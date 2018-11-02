
#include <string.h>
#include <math.h>

#include "DEsystem.h"

int main(int argc, char* argv[])
{
  char name[50];
  strcpy(name, argv[0]);
  strcat(name, ".dat");
  FILE* output = fopen(name, "w");
  
  DEsystem*    S = new DEsystem(4);
  double    x0[] = {1,2,3,4};// bolus - initial condition
  double   inf[] = {5,6,7,8};// infusion
  double     a[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
  S->load(a, x0, inf);
  S->print(output, "Test data");
  delete S;
  fclose(output);
  printf("Output file is %s\n", name);
  return 0;
}

