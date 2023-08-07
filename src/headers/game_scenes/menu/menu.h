#ifndef MENU_H
#include "../../structs.h"

struct Menu
{
  SDL_Rect rect;
  SDL_Texture *texture;
  Label *mainTitle;
  Button *play, *settings, *quit;
  Button **button_list;
  int button_count;
};

Menu *create_Menu(SDL_Renderer *rend);
int Menu_process_input(Menu *menu);
void Menu_update(Menu *menu);
void Menu_render(Menu *menu, SDL_Renderer *rend);
void Menu_run(Menu *menu, SDL_Renderer *rend);
int play_button_action();
int settings_button_action();
int quit_button_action();
void Menu_destroy(Menu *menu);

#endif // !MENU_H
