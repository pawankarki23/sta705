
#ifndef TOWERS
#define TOWERS

#include <FL/Fl_Box.H>

class Disk
{
  public:
  Fl_Color     color;
  int          id;

  Disk(int id, Fl_Color  color);
};
  
class Peg : public Fl_Box 
{
  int          top;             // number of disks currently
  Disk**       disk;            // array of disks currently on peg
  public:
  void         draw(); 
  static int   n;               // maximum allowed disk
  void         push(Disk*);     // put disk on top of stack
  Disk*        pop();           // remove top disk
  
  Peg(int x, int y, int w, int h); 
  ~Peg();
  };

class Towers: public Fl_Box
  {
  void         background();
  void         draw(); 
  void         move_disk(Peg* from, Peg* to);
  public:
  Peg*         peg[3];
  void         move_stack(int k,  Peg* from, Peg* work, Peg* to);
  void         start();
  Towers(int x, int y, int w, int h); 
  ~Towers();
  };

#endif

