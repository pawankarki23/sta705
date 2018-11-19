#include <cstring>  // memset is here
#include "Convolve.h"

Convolve::Convolve(int na, int nb)
  {
  this->na = na; this->nb = nb;
  }
Convolve::~Convolve(){}

void Convolve::evaluate(const double* a, const double* b,
                                             double* ab)
  {
  memset(ab, 0, (na + nb - 1)*sizeof(double));
  for(int i = 0; i < na; i++)
    for(int j = 0; j < nb; j++)
      ab[i + j] += a[i] * b[j];
  }
