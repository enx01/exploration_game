#ifndef POP_UP_MENU_H
#include "../../../structs.h"

struct Pop_Up
{
  SDL_Rect rect;
  SDL_Texture *texture;

  Button **content;
  int choice_number;
};

Pop_Up *create_Pop_Up(SDL_Renderer *rend);
void Pop_Up_process_input(Pop_Up *pu);
void Pop_Up_update(Pop_Up *pu);
void Pop_Up_render(Pop_Up *pu, SDL_Renderer *rend);

void Pop_Up_destroy(Pop_Up *pu);
  
#endif // !POP_UP_MENU_H
