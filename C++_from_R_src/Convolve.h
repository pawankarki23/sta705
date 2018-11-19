#ifndef CONVOLVE
#define CONVOLVE

// design is such that evaluate could be called
// multiple times for same na & nb
class Convolve
  {
  int      na;
  int      nb;
  public:
           Convolve(int na, int nb);
          ~Convolve();
  void     evaluate(const double* a, const double* b,
                                           double* ab);
  };
#endif

