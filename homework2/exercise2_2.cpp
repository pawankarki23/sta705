/**********************************************************************************************************************
Exercise 2.2. Write a C++ program that does the following:

1. Reads an integer n from the command line.
2. Calculates sum=1/ (i*i). Accumulates the result in a variable declared as float up = 0.0.
3. Calculates the sum of the same terms in reverse order.Accumulates the result in a variable declared as float down = 0.0.
4. Prints n and prints up and down with 12 decimal places.

Run the program with argument 5000 and comment on the result.
**********************************************************************************************************************/

#include <iostream>     // cin and cout are here
#include <cstdlib>      // strtold is here
#include <iomanip>

using namespace std;

int main(int argc, char* argv[])
{
  
  if(argc < 2)
  {
      cout << "Please enter a number" <<  endl;
      return 1;
  }

  char* next;
  float up = 0.0;
  float down = 0.0;
  int i = 0;

  int n = strtold(argv[1], &next);

  for(i=1; i<=n ; i++){
    float x = i;
    up += 1/(x*x);
    down += 1/((n-x+1)*(n-x+1));
  }

  /* set the precision for upto 12 decimal places */
  cout << fixed;
  cout << setprecision(12);
  cout << "Input n: " << up <<  endl; 
  cout << "Result up: " << up <<  endl; 
  cout << "Result down: " << down <<  endl; 

  return 0;
}