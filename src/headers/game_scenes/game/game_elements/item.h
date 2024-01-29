#ifndef ITEM_H
#include "../../../structs.h"

struct Item {
  SDL_Rect rect;
  SDL_Texture *texture;
  int x, y, weight, id, highlighted, showing;
};

Item *create_Item(SDL_Renderer *rend, int flag, int x, int y);
void Item_process_input(Item *item);
void Item_update(Item *item, Player *player);
void Item_render(Item *item, SDL_Renderer *rend);
int Item_IsPointOnItem(Item *item, SDL_Point point);
void Item_destroy(Item *item);

#endif // !ITEM_H
