#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>

#include "TopMenu.h"
#include "Towers.h"
#include "Constants.h"

int Peg::n  = 5;

void next_cb(Fl_Widget *, void *);

int main() 
  {
  Fl_Double_Window*  win = new Fl_Double_Window(ww, wh, "Towers of Hanoi");
  win->begin();
  TopMenu* move  = new TopMenu(sp, sp,      ww-2*sp, bh        );
  Towers*  tower = new Towers (sp, bh+2*sp, ww-2*sp, wh-bh-3*sp);
  move->callback(next_cb);
  win->resizable(tower);
  win->end();
  win->show();
  tower->start();
  return Fl::run();
  }

  
