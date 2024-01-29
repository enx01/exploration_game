#include "../../../headers/game_scenes/game/game_elements/item.h"
#include "../../../headers/game_scenes/game/game_elements/crosshair.h"
#include "../../../headers/game_scenes/game/game_elements/player.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <stdlib.h>

Item *create_Item(SDL_Renderer *rend, int flag, int x, int y)
{
  if (flag < 1000 || flag > 1005)
  {
    return NULL;
  }

  Item *res = malloc(sizeof(Item));
  char *path;

  switch (flag)
  {
    case APPLE :
      path = "res/img/items/apple.png";
      break;
    case SWORD :
      path = "res/img/items/sword.png";
      break;
    default :
      break;
  }

  
  SDL_Surface *temp_surface = IMG_Load(path);

  if (temp_surface == NULL)
  {
    fprintf(stderr, "Error : Couldn't load image. %s", IMG_GetError());
    return NULL;
  }

  res->texture = SDL_CreateTextureFromSurface(rend, temp_surface); 

  res->x = x;
  res->y = y;

  res->showing = TRUE;

  res->highlighted = FALSE;

  res->rect.x = x;
  res->rect.y = y;
  res->rect.w = temp_surface->w;
  res->rect.h = temp_surface->h;

  SDL_FreeSurface(temp_surface);

  return res;
}

void Item_update(Item *item, Player* player)
{
  if (player != NULL)
  {
    SDL_Point crosshair_pos = {player->crosshair->x, player->crosshair->y};
    if (Item_IsPointOnItem(item, crosshair_pos))
    {
      item->highlighted = TRUE;
    }
    else 
    {
      item->highlighted = FALSE;
    }
  }
  item->rect.x = item->x;
  item->rect.y = item->y;
}

void Item_render(Item *item, SDL_Renderer *rend)
{
  if (item->showing)
  {
    SDL_RenderCopy(rend, item->texture, NULL, &(item->rect));
    if (item->highlighted)
    {
      SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
      SDL_RenderDrawRect(rend, &(item->rect));
    }
  }
}

int Item_IsPointOnItem(Item *item, SDL_Point point)
{
  if (point.x >= (item->x-10) && 
      point.x < (item->x + item->rect.w + 10) && 
      point.y >= (item->y-10) &&
      point.y < (item->y + item->rect.h + 10))
  {
    return TRUE;
  }
  else 
  {
    return FALSE;
  }
}
