#ifndef DIFFEREVOLVE
#define DIFFEREVOLVE

class Evolution
  {
  int              nm;           // number of members
  int              nv;           // number of variables
  int              genmax;       // maximum number of generations
  double           wtfact;       // weighting factor
  double           logmut;       // natural log of mutation probability
  double           mut;          // mutation probability
  double           conv;         // convergence factor
  bool             display;      // display intermediate results
  double*          current;
  double*          next;
  double*          value;

  int              find_best();
  double           uniform();
  void             create_next();
  void*            extra;

  public:
  void             setseed(unsigned int);
  void             setwtfact(double);
  void             toggledisplay();
  void             evolve(double*, double*, double*);
  virtual double   objective(double*, int, void*);
                   Evolution(int nv, int nm, void* extra = NULL);
                  ~Evolution();
  };

#endif

