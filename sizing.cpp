
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Group.H>
#include <FL/x.H>

#include <cstdlib>
#include <cstdio>

const int w  = 150;   

int main() 
{
  const char* name[] = {"TL", "TM", "TR", "ML","MM","MR","BL","BM","BR"};
  const Fl_Color c[] = {1,2,3,4,5,6,141, 161, 187};
  Fl_Button* tile[9];
  Fl_Window* win = new  Fl_Window(3*w, 3*w, "Sizing");
  win->begin();
  Fl_Group*   gp = new  Fl_Group(0, 0, 3*w, 3*w);
  int k = 0;
  for(int i =0; i<3; i++)
    for(int j=0; j<3; j++, k++)
      {
      tile[k] = new Fl_Button(j*w, i*w, w, w, name[k]);
      tile[k]->box(FL_DOWN_BOX);
      tile[k]->color(c[k]);
      }
  gp->end();
  win->end();
  gp->resizable(tile[4]);
  win->resizable(gp);
  win->show();
  return Fl::run();
}

