#ifndef SETTINGS_H
#include "../../structs.h"

struct Settings
{
  SDL_Rect rect;
  SDL_Texture *texture;
  Label *mainTitle;
  Button *nill, *sound, *ret;
  Button **button_list;
  int button_count;
};

Settings *create_Settings(SDL_Renderer *rend);
int Settings_process_input(Settings *settings);
void Settings_update(Settings *settings);
void Settings_render(Settings *settings, SDL_Renderer *rend);
void Settings_run(Settings *settings, SDL_Renderer *rend);
int void_button_action();
int sound_button_action();
int return_button_action();

#endif // !SETTINGS_H
