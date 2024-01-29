#include "../../../headers/game_scenes/game/game_elements/inventory.h"
#include "../../../headers/game_scenes/game/game_elements/inv_item_slot.h"
#include "../../../headers/game_scenes/game/game_elements/item.h"

Inventory *create_Inventory(SDL_Renderer *rend)
{
  Inventory *res = malloc(sizeof(Inventory));

  res->is_open = FALSE;
  res->content_nb = 10;
  res->content = malloc(res->content_nb * sizeof(Inv_Item_Slot));

  res->rect.x = 35;
  res->rect.y = 35;
  res->rect.w = 255;
  res->rect.h = 105;

  int x_offset = 50;
  int y_offset = 50;
  int x = 40;
  int y = 40;

  for (int i = 0; i < res->content_nb; ++i)
  {
    res->content[i] = create_Inv_Item_Slot(rend, x, y);
    
    x += x_offset;

    if ((i+1) % 5 == 0)
    {
      fprintf(stderr, " i = %d", i);
      y += y_offset;
      x = 40;
    }

  }

  return res;
}

void Inventory_add_item(Inventory *inventory, Item *item)
{
  Inv_Item_Slot_change_content(inventory->content[inventory->item_count],item);
  ++inventory->item_count;
}

void Inventory_remove_item(Inventory *inventory, Item *item)
{
  int i = 0;
  while (inventory->content[i]->content != item)
  {
    ++i;
  }
  for (int j = i; j < inventory->content_nb-1; ++j)
  {
    Inv_Item_Slot_change_content(inventory->content[j],inventory->content[j+1]->content);
  }
}

void Inventory_render(Inventory *inventory, SDL_Renderer *rend)
{
  if (inventory->is_open)
  {
    SDL_SetRenderDrawColor(rend, COLOR_ASH_GREY[0], COLOR_ASH_GREY[1], COLOR_ASH_GREY[2], COLOR_ASH_GREY[3]);
    SDL_RenderFillRect(rend, &(inventory->rect));

    for (int i = 0; i < inventory->content_nb; ++i)
    { 
      Inv_Item_Slot_render(inventory->content[i], rend);
    }
  }
}

void Inventory_destroy(Inventory *inventory)
{
  free(inventory);
}
