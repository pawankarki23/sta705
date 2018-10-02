/************************************************************************************************************************
Exercise 4.1. The program pick.cpp demonstrated how to pick a color and change the background color of a widget.
This exercise is to take elements of pick.cpp and merge them into the current program to change color of the polygon.
Hand in your program listing. Mail to me a screen shot of an aquamarine hexagon. It need not be a regular hexagon.
**************************************************************************************************************************/

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Group.H>
#include <FL/fl_show_colormap.H>

// custom header files
#include "Constants.h"
#include "Polygon.h"

// global variable initializations
Polygon *poly   = 0;
Fl_Box *spacer = 0;
Fl_Check_Button *fill   = 0;
Fl_Group *group = 0;
Fl_Button *clear = 0;
Fl_Button *choose_color  = 0;
Fl_Color c = FL_GRAY;  // initial color

// callback to fill polygon
void fill_cb(Fl_Widget* w, void*)
{
  poly->state = ((Fl_Check_Button*) w)->value();
  poly->redraw();
}

// callback to clear the polygon
void clear_cb(Fl_Widget* w, void*)
{
  poly->n = 0;
  poly->redraw();
}

// a callback to change the color of polygon when a color is chosen
void choose_colr_cb(Fl_Widget*, void*)
{
  c = fl_show_colormap(c);
  poly->polygon_color = c;
  poly->redraw();
}

// main function
int main()
{
  Fl_Double_Window*  win = new Fl_Double_Window(ww, wh, "Draw a Polygon");
  win->begin();
  poly  = new Polygon(sp, sp, ww-2*sp, wh-bh-3*sp);
  int x = sp;
  int z = wh - bh -sp;
  
  group   = new Fl_Group(x, z, ww-2*sp, bh);
  group->begin();
    fill   = new Fl_Check_Button(x, z, bw, bh, "Fill"); 
    x += bw + sp;
    clear  = new Fl_Button(x, z, bw, bh, "Clear");      
    x += bw + sp;
    choose_color  = new Fl_Button(x, z, bw, bh, "Choose color");
    x += bw + sp;
    spacer = new Fl_Box(FL_NO_BOX, x, z, 1, bh, "");
  group->end();
  group->resizable(spacer);
  
  win->resizable(poly);
  win->end();
  // assign callbacks
  fill->callback(fill_cb);
  clear->callback(clear_cb);
  choose_color->color(c);
  choose_color->callback(choose_colr_cb);

  win->show();
  return(Fl::run());
}


