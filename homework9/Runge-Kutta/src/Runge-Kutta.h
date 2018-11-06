
#ifndef RUNGE_KUTTA
#define RUNGE_KUTTA

class DEtable;

class Runge_Kutta
  {
  public:
  int         solve(const double* t, DEtable* X, void* extra = 0);
  virtual int f(double t, const double* y, double* der_y, void* extra = 0);
              Runge_Kutta();
  };
  
#endif
  
