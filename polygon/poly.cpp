
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Group.H>

#include "Constants.h"
#include "Polygon.h"

Polygon*         poly   = 0;
Fl_Box*          spacer = 0;
Fl_Check_Button* fill   = 0;
Fl_Group*        group  = 0;
Fl_Button*       clear  = 0;

void fill_cb(Fl_Widget* w, void*)
  {
  poly->state = ((Fl_Check_Button*) w)->value();
  poly->redraw();
  }

void clear_cb(Fl_Widget* w, void*)
  {
  poly->n = 0;
  poly->redraw();
  }

int main()
  {
  Fl_Double_Window*  win = new Fl_Double_Window(ww, wh, "Draw a Polygon");
  win->begin();
  poly  = new     Polygon(sp, sp,       ww-2*sp, wh-bh-3*sp);
  int x = sp;
  int z = wh - bh -sp;
  group   = new Fl_Group(x, z, ww-2*sp, bh);
  group->begin();
    fill   = new Fl_Check_Button(x, z, bw, bh, "Fill"); x += bw + sp;
    clear  = new Fl_Button(x, z, bw, bh, "Clear");      x += bw + sp;
    spacer = new Fl_Box(FL_NO_BOX, x, z, 1, bh, "");
  group->end();
  group->resizable(spacer);
  win->resizable(poly);
  win->end();
  fill->callback(fill_cb);
  clear->callback(clear_cb);
  win->show();
  return(Fl::run());
  }


