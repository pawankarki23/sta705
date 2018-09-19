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

double opposite(double a, double b, double angle)
  {
  return sqrt(a*a + b*b - 2*a*b*cos((M_PI/180)*angle));
  }

// some global variables
  Fl_Float_Input* len_a = 0;
  Fl_Float_Input* len_b = 0;
  Fl_Float_Input* theta = 0;
  Fl_Output*      len_c = 0;

void calc_CB(Fl_Widget*, void* v)
  {
  char*  ptr;
  double a = strtod(len_a->value(), &ptr);
  double b = strtod(len_b->value(), &ptr);
  if(a < 0.0 or b < 0.0)
    {
    fl_alert("A length must not be negative.");
    return;
    }
  double t = strtod(theta->value(), &ptr);
  char value[100];
  sprintf(value, "%.2lf", opposite(a, b, t));
  len_c->value(value);
  len_c->redraw();
  }

int main()
  {
  Fl_Double_Window* win = new Fl_Double_Window(w, h, "Law of Cosines Demonstration");
  win->begin();
  int x = bw;
  int y = sp;
  len_a = new Fl_Float_Input(x, y, bw, bh, "Length a");
  y += bh+sp;
  len_b = new Fl_Float_Input(x, y, bw, bh, "Length b");
  y += bh+sp;
  theta = new Fl_Float_Input(x, y, bw, bh, "Angle(degrees)");
  y += bh+sp;
  Fl_Button*      calc  = new Fl_Button(x, y, bw, bh, "Calculate");
  y += bh+sp;
  len_c = new Fl_Output(x, y, bw, bh, "Length c");
  y += bh+sp;
  win->end();
  len_a->value("0.0");
  len_b->value("0.0");
  theta->value("90.0");
  calc->callback(calc_CB);
  win->show();
  return Fl::run();
  }

