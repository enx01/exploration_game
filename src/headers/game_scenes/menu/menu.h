#ifndef MENU_H
#include "../../structs.h"

struct Menu
{
  Game_Scene *base;
  SDL_Rect rect;
  SDL_Texture *background;
  Label *mainTitle;
  Button *play, *settings, *quit;
};

Menu *create_Menu(int labels_count, int buttons_count, SDL_Renderer *rend);
void Menu_process_input(Menu *menu);
void Menu_update(Menu *menu);
void Menu_render(Menu *menu, SDL_Renderer *rend);

#endif // !MENU_H
