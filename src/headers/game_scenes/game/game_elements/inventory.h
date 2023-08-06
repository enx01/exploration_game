#ifndef INVENTORY_H
#include "../../../structs.h"

struct Inventory
{
  SDL_Rect rect;
  SDL_Texture *texture;

  Inv_Item_Slot *content;
  int item_count;

  int is_open;
};

Inventory *create_Inventory(SDL_Renderer *rend);

void Inventory_add_item(Inventory *inventory, Item *item);
void Inventory_remove_item(Inventory *inventory, Item *item);

void Inventory_process_input(Inventory *inventory);
void Inventory_update(Inventory *inventory);
void Inventory_render(Inventory *inventory, SDL_Renderer *rend);

void Inventory_destroy(Inventory *inventory);

#endif // !INVENTORY_H
