#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <FL/fl_draw.H>
#include <FL/Fl.H>

// custom header files 
#include "Constants.h"
#include "Polygon.h"

Polygon::Polygon(int x, int y, int w, int h) :  Fl_Widget(x, y ,w ,h)
{
  box(FL_ENGRAVED_BOX);
  n  = 0;
  // change for homework 4
  // default color - wildcat blue
  polygon_color = 0x0033a000;
}

Polygon::~Polygon()
{
}
  
void Polygon::marks()
{
  for (int i = 0 ; i < n ; i++ )
    fl_rectf(x()+xv[i]-2, y()+yv[i]-2, 5, 5);
  redraw();
}  

void Polygon::fill()
{
  // change for homework 4 - change the color of the polygon
  fl_color(polygon_color);
  fl_begin_complex_polygon();
  for (int i = 0 ; i < n ; i++ )
    fl_vertex(x() + xv[i], y() + yv[i]);
  fl_end_complex_polygon();
  redraw();
}  

// this draw rountine will be called in redraw()
void Polygon::draw()
{
  // draw background
  fl_color(FL_WHITE);
  fl_rectf(x(), y(), w(), h());
  fl_color(FL_BLACK);
  fl_rect(x(), y(), w(), h());
  if(state and n > 2)
    fill();
  else
    marks();
}
  
int Polygon::handle(int event)
{
  int ret = Fl_Widget::handle(event);
  switch (event)
    {
    case FL_PUSH:
      ret = 1;
      break;
    case FL_DRAG:
      ret = 1;
      break;
    case FL_RELEASE:
      xv[n] = Fl::event_x() - x();
      yv[n] = Fl::event_y() - y();
      n++;
      ret = 1;
      redraw();
      break;
    default:
      ret = Fl_Widget::handle(event); 
    }
  return ret;  
  }

