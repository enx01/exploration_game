#ifndef ITEM_H
#include "../../../structs.h"

struct Item
{
  SDL_Rect rect;
  SDL_Texture *texture;
  int is_on_ground,x,y,weight,id;

};

Item *create_Item(SDL_Renderer *rend, int flag, int x, int y);
void Item_process_input(Item *item);
void Item_update(Item *item);
void Item_render(Item *item, SDL_Renderer *rend);

void Item_destroy(Item *item);

#endif // !ITEM_H
