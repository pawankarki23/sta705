#ifndef COMPMODEL
#define COMPMODEL

#include <stdio.h>

class DEmodel;

class CompModel
  {
  double*       param;                 // points beginning of parameters
  public:
  int           n;                     // number of compartments
  int*          from;                  // vector of source compartments
  int*          to;                    // vector of destination compartments
  int           inf;                   // id of infusion compartment 0 1 2 or 3 etc
  int           bol;                   // id of bolus compartment
  int           nr;                    // number of rate constants
  int           np;                    // number of parameters (number of rate constants + nums of inf + num of bols
  double*       system(double* theta); // loads parameters into system
  DEmodel*      S; // DE model
  void          bolus_site(int);
  void          infusion_site(int);
  void          print(FILE*, const char*);
                //constructor
                CompModel(int nr, int* from, int* to);
                ~CompModel();
  };
  
#endif
