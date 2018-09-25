/**********************************************************************************************************************
Exercise 2.1. Consider the quadratic polynomial q(x) = x^2 − 111.11x + 1.2121.

1. Find the roots of q using the two forms of the quadratic formula. After every operation (+, −, ×, /, sqrt) truncate
the result to five significant decimal digits.

2. For a quadratic polynomial ax^2 + bx + c, show that the roots x1 and x2 satisfy x1x2 = c/a. Use this latter
relationship to evaluate the root having smaller absolute value.

3. Write a C++ program that reads constants a, b, c from the command line, applies the appropriate formula to
calculate the roots, and outputs the roots.
**********************************************************************************************************************/
#include <iostream>     // cin and cout are here
#include <cmath>        // cos and M_PI are here
#include <cstdlib>      // strtold is here

using namespace std;
  
int main(int argc, char* argv[])
{
  char* next;
  double a = 0;
  double b = 0;
  double c = 0;
  double x1 = 0;
  double x2 = 0;
  
  if(argc < 4)
  {
    cout << "User input should be coeff of quadratic eqaution (a, b & c)" <<  endl;
    return 1;
  }
  else if((b*b-4*a*c) < 0)
  {
    cout << "No real roots for the given quadratic equation" <<  endl;
    return 1;
  }

  a = strtold(argv[1], &next);
  b = strtold(argv[2], &next);
  c = strtold(argv[3], &next);

  if(b < 0)
  {
    x1 = (-b + sqrt(b*b-4*a*c))/(2*a);
    x2 = c/(a*x1);
  }
  else
  {
    x1 = (-b - sqrt(b*b-4*a*c))/(2*a);
    x2 = c/(a*x1);
  }

  cout << "Roots for given quadratic equation are as follows:" <<  endl;
  cout << "x1:  "<< x1 << endl;
  cout << "x2:  "<< x2 << endl;

  return 0;
  }