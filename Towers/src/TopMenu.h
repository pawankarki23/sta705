#ifndef TOPMENU
#define TOPMENU

#include <FL/Fl_Menu_Bar.H>

class TopMenu : public Fl_Menu_Bar
{
public:
TopMenu(int x, int y, int w, int h, const char *label = 0);
};

#endif

