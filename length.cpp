#include <iostream>     // cin and cout are here
#include <cmath>        // cos and M_PI are here
#include <cstdlib>      // strtold is here

using namespace std;

double opposite(double a, double b, double angle)
  {
  return sqrt(a*a + b*b - 2*a*b*cos((M_PI/180)*angle));
  }
  
int main(int argc, char* argv[])
  {
  char* next;
  
  if(argc < 4)
    {
    cout << "Inputs should be length a, length b, angle between." <<  endl;
    return 1;
    }
  double a     = strtold(argv[1], &next);
  double b     = strtold(argv[2], &next);
  double angle = strtold(argv[3], &next);

  cout << "Length of side a: " << a <<  endl; 
  cout << "Length of side b: " << b <<  endl; 
  cout << "Angle between sides a and b: " << angle  <<  endl; 
  cout << "Length of side c: " << opposite(a, b, angle) <<  endl;
  return 0;
  }

