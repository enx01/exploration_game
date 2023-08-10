#include "../../../headers/game_scenes/game/game_elements/inv_item_slot.h"
#include "../../../headers/game_scenes/game/game_elements/item.h"
#include <SDL2/SDL_render.h>

Inv_Item_Slot *create_Inv_Item_Slot(SDL_Renderer *rend, int slot_nb)
{
  Inv_Item_Slot *res = malloc(sizeof(Inv_Item_Slot));
  
  switch (slot_nb) 
  {
    case 1 :
      res->rect.x = 40;
      res->rect.y = 40;
      res->interior_rect.x = 45;
      res->interior_rect.y = 45;
      break;
    default :
      fprintf(stderr, "invalid slot number. aborting creation.");
      return NULL;
      break;
  } 

  res->rect.w = 45;
  res->rect.h = 45;
  res->interior_rect.w = 35;
  res->interior_rect.h = 35;

  


  return res;
}

void Inv_Item_Slot_render(Inv_Item_Slot *iis, SDL_Renderer *rend)
{
  SDL_SetRenderDrawColor(rend, COLOR_DARK_GREY[0], COLOR_DARK_GREY[1], COLOR_DARK_GREY[2], COLOR_DARK_GREY[3]);
  SDL_RenderFillRect(rend, &(iis->rect));
  SDL_SetRenderDrawColor(rend, COLOR_CEMENT_GRAY[0], COLOR_CEMENT_GRAY[1], COLOR_CEMENT_GRAY[2], COLOR_CEMENT_GRAY[3]);
  SDL_RenderFillRect(rend, &(iis->interior_rect));
}
