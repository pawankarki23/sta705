#ifndef DIFFERENTIAL_EVOLUTION
#define DIFFERENTIAL_EVOLUTION

class Evolution
  {
  int              nm;           // number of members
  int              nv;           // number of variables
  int              max_gen;      // maximum number of generations
  double           wt_factor;    // weighting factor
  double           mut;          // mutation probability
  double           conv;         // convergence factor
  bool             display;      // display intermediate results
  double*          current; // current population 
  double*          next; // next population 
  double*          value;

  int              find_best();
  double           uniform(); // create the values of uniform rv
  void             create_next(); // crete the value for next population
  void*            extra;

  public:
  void             set_seed(unsigned int);
  void             set_wt_factor(double);
  void             toggle_display();
  void             evolve(double*, double*, double*); // overall function 
  virtual double   objective(double*, int, void*);
                   Evolution(int nv, int nm, void* extra = NULL);
                  ~Evolution();
  };

#endif

