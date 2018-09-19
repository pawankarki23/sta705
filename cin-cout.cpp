#include <iostream>     // cin and cout are here
#include <cmath>        // cos and M_PI are here

using namespace std;

double opposite(double a, double b, double angle);

int main()
  {
  double a, b, angle;

  cout << "Enter length of side a: "; 
  cin  >> a;
  
  cout << "Enter length of side b: "; 
  cin  >> b;

  cout << "Enter angle (degrees) between sides a and b: "; 
  cin  >> angle;

  cout << "The length of side c is " << opposite(a, b, angle) << "." <<  endl;
  return 0;
  }

double opposite(double a, double b, double angle)
  {
  return sqrt(a*a + b*b - 2*a*b*cos((M_PI/180)*angle));
  }
  
