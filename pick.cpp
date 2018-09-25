
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Group.H>
#include <FL/fl_show_colormap.H>
#include <FL/x.H>

#include <cstdlib>
#include <cstdio>

Fl_Color  c  = FL_GRAY;  // initial color

const int bh = 30;       // button height
const int bw = 100;      // button width
const int sp = 5;        // space between elements
const int h  = 500;      // window height
const int w  = 450;      // window width

  Fl_Box*    swatch  = 0;
  Fl_Group*  group   = 0;
  Fl_Button* pick    = 0;
  Fl_Output* code    = 0;
  Fl_Box*    spacer  = 0;

// a callback function --- is executed when button is clicked
void pick_cb(Fl_Widget*, void*)
{
  char value[100];
  c = fl_show_colormap(c);
  sprintf(value, " %d", c);
  code->value(value);
  swatch->color(c);
  swatch->redraw();
}

int main()
{
  Fl_Double_Window* win     = new Fl_Double_Window(w, h, "Color picker");
  win->begin();
  int x = sp;
  int y = sp;
  int z = y+h-bh-2*sp;
  swatch  = new Fl_Box  (x, y, w-2*sp, h-bh-3*sp);
  group   = new Fl_Group(x, z, w-2*sp, bh);
  group->begin();
    pick   = new Fl_Button(x, z, bw, bh, "Pick color"); x += 2*bw;
    code   = new Fl_Output(x, z, bw, bh, "Index");      x += bw;
    spacer = new Fl_Box(FL_NO_BOX, x, z, 1, bh, ""); // invisible window
  group->end();
  group->resizable(spacer);
  swatch->box(FL_DOWN_BOX);
  pick->color(c);
  pick->callback(pick_cb);
  win->resizable(swatch);
  win->end();
  win->show();
  return Fl::run();
}

