/**********************************************************************************************************************
Exercise 3.1

Write a FLTK program that elicits the length, width, and height of a box and then displays the volume of
the box. Hand in a listing of your program and a screen shot of the result after running the program.
**********************************************************************************************************************/
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Float_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>
#include <FL/fl_ask.H>         // fl_alert is here
#include <math.h>              // M_PI, sqrt, and cos are here
#include <cstdlib>
#include <cstdio>

// some constants to make changes in layout easier 
const int bh =   30;           // button height
const int bw =  120;           // button width
const int sp =    5;           // a little space
const int h  =  5*(bh+sp)+sp;  // window height
const int w  =  2*(bw+sp)+bw;  // window width

// some global variables
Fl_Float_Input *length = 0;
Fl_Float_Input *width = 0;
Fl_Float_Input *height = 0;
Fl_Output *volume = 0;

void calc_CB(Fl_Widget*, void* v)
{
  char * ptr = NULL;
  double l = strtod(length->value(), &ptr);
  double b = strtod(width->value(), &ptr);
  double h = strtod(height->value(), &ptr);

  if(l < 0.0 or b < 0.0 or h < 0.0)
  {
    fl_alert("Length or width or height can not be negative.");
    return;
  }

  char value[100];
  sprintf(value, "%.2lf", (l*b*h));
  
  volume->value(value);
  volume->redraw();
}

int main()
{
  Fl_Double_Window *win = new Fl_Double_Window(w, h, "Calculate volume of a box");
  win->begin();
  int x = bw;
  int y = sp;
  length = new Fl_Float_Input(x, y, bw, bh, "Length l");
  y += bh+sp;
  width = new Fl_Float_Input(x, y, bw, bh, "width b");
  y += bh+sp;
  height = new Fl_Float_Input(x, y, bw, bh, "height h");
  y += bh+sp;
  Fl_Button* calc  = new Fl_Button(x, y, bw, bh, "Calculate Volume");
  y += bh+sp;
  volume = new Fl_Output(x, y, bw, bh, "Volume");
  y += bh+sp;
  win->end();
  
  length->value("0.0");
  width->value("0.0");
  height->value("0.0");
  
  calc->callback(calc_CB);
  win->show();
  
  return Fl::run();
}


