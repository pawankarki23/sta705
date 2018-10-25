
#include <cstdio>
#include <cstring>

#include <FL/Fl.H>
#include <FL/fl_draw.H>

#include "Towers.h"
#include "Constants.h"

Disk::Disk(int id, Fl_Color  color)
  {
  this->id    = id;
  this->color = color;
  }

Peg::Peg (int x, int y, int w, int h):Fl_Box(x, y ,w ,h) 
  {
  disk    = new Disk*[n];
  top     = 0;
  }
  
Peg::~Peg()
  {
  }
     
void Peg::push(Disk* d)
  {
  disk[top++] = d;
  return;
  }

Disk* Peg::pop()
  {
  return disk[--top];
  }

void Peg::draw() 
  {
  int         dh = (h()-3*bh)/n;       // disk height
  // draw disks
  for(int i=0; i<top; i++)
    {
    int width = w()-disk[i]->id*w()/(2*(n-1))-8;
    int ys = y()+h()-bh-i*dh-dh;
    fl_color(disk[i]->color);
    fl_rectf(x() + w()/2-width/2, ys, width, dh);
    fl_rect (x() + w()/2-width/2, ys, width, dh, FL_BLACK);
    }  
  }
      
  

