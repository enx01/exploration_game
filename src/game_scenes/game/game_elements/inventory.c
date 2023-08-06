#include "../../../headers/game_scenes/game/game_elements/inventory.h"

Inventory *create_Inventory(SDL_Renderer *rend)
{
  Inventory *res = malloc(sizeof(Inventory));

  return res;
}

void Inventory_destroy(Inventory *inventory)
{
  free(inventory);
}
