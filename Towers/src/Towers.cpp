
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>

#include "Towers.h"
#include "Constants.h"

extern bool     moveon;
extern Fl_Color brown;

Towers::Towers(int x, int y, int w, int h) :  Fl_Box(x, y ,w ,h)
  {
  box(FL_ENGRAVED_BOX);
  // create pegs
  int pw = w/3;
  for(int i = 0; i<3; i++)
    {
    peg[i] = new Peg(x, y, pw, h);
    x += pw;
    }

  // create and put all disks on peg 0 to start
  int n = Peg::n;
  for(int i=0; i < n; i++)
    {
    peg[0]->push(new Disk(i, i+1));
    }
  }
  
Towers::~Towers()
  {
  }
  
void Towers::background()
  {
  // draw background
  fl_color(FL_WHITE);
  fl_rectf(x(), y(), w(), h());
  Fl_Color brown = 0x8b5a2b00;
  fl_color(brown);
  fl_rectf(x(), y()+h()-bh, w(), bh);
  for(int i=0; i<3; i++)
    {
    int xs = w()/3.0*(i+0.5) - bh/2;
    int ys = y() + bh;
    fl_rectf(xs, ys, bh, h()-bh);
    }
  }  

void Towers::draw()
  {
  background();
  for(int i=0; i<3; i++)
    peg[i]->draw();
  fl_color(FL_BLACK);
  fl_rect(x(), y(), w(), h());
  }

void Towers::move_disk(Peg* from, Peg* to)
  {
  moveon = false;
  // infinite loop
  for (;;)
  {
    // wait for all the callback functions 
    Fl::wait();         // checks all callbacks
    // callback function will change the moveon variable value
    if(moveon) break;
  }
  Disk* d = from->pop();
  to->push(d);
  redraw();
  }

// k size of stack to be moved
void Towers::move_stack(int k,  Peg* from, Peg* work, Peg* to)
  {
  if(not k) return;
  move_stack(k-1, from, to, work);
  move_disk(from, to);
  move_stack(k-1, work, from, to);
  return;
  }

void Towers::start()
  {
  move_stack(Peg::n, peg[0], peg[1], peg[2]);
  }

