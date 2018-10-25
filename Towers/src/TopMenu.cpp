#include <cstdio>
#include <cstdlib>

#include "TopMenu.h"

bool  moveon = false;

void quit_cb(Fl_Widget*, void*)
  {
  exit(0);
  }

void next_cb(Fl_Widget *, void *)
  {
  moveon = true;
  }

void manual_cb(Fl_Widget* , void* d)
  {
  fprintf(stderr, "manual_cb\n");
  }

void about_cb(Fl_Widget* , void* d)
  {
  fprintf(stderr, "about_cb\n");
  }

Fl_Menu_Item  menutable[] =
    {
    {  "File",               0,          0,         0, FL_SUBMENU},
      {"Quit",	             0,    quit_cb,         0, FL_MENU_DIVIDER},
      {0},
    {"Next",                 0,    next_cb},
    {"Help",                 0,          0,         0, FL_SUBMENU},
      {"Manual",             0,  manual_cb},
      {"About",              0,   about_cb},
      {0},
    {0}
    };

TopMenu::TopMenu(int x, int y, int w, int h, const char *label):
                      Fl_Menu_Bar(x,y,w,h,label)
  {
  box(FL_DOWN_BOX);
  copy(menutable, this);
  }

