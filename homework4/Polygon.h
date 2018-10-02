#ifndef POLYGON_
#define POLYGON_

#include <FL/Fl_Box.H>

class Polygon : public Fl_Widget 
{
  float   xv[100];
  float   yv[100];

  void    draw(); 
  int     handle(int event);
  void    marks();
  void    fill();
  
  public:
  // change for homework
  Fl_Color polygon_color;
  int     n;
  bool    state;
  // constructor 
  Polygon(int x, int y, int w, int h); 
  // default destructor
  ~Polygon();
};

#endif
