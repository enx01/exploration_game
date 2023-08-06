#ifndef INV_ITEM_SLOT_H
#include "../../../structs.h"

struct Inv_Item_Slot
{
  SDL_Rect rect;
  SDL_Texture *texture;
  Item *content;
  int slot_nb;
};

Inv_Item_Slot *create_Inv_Item_Slot(SDL_Renderer *rend, int slot_nb);
void Inv_Item_Slot_process_input(Inv_Item_Slot *iis);
void Inv_Item_Slot_update(Inv_Item_Slot *iis);
void Inv_Item_Slot_render(Inv_Item_Slot *iis, SDL_Renderer *rend);

void Inv_Item_Slot_destroy(Inv_Item_Slot *iis);

#endif // !INV_ITEM_SLOT_H
