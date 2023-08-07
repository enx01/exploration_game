#include "../../../headers/game_scenes/game/game_elements/item.h"
#include <SDL2/SDL_image.h>
#include <stdlib.h>

Item *create_Item(SDL_Renderer *rend, int flag, int x, int y)
{
  if (flag < 1000 || flag > 1005)
  {
    return NULL;
  }

  Item *res = malloc(sizeof(Item));

  char path[] = "res/img/items/";
  char *name;
  char *temp;

  int nameSize;

  switch (flag) 
  {
    case APPLE :
      nameSize = 9;
      name = malloc(nameSize+1);
      temp = "apple.png";
      res->weight = 2;
      break;
    case SWORD :
      nameSize = 9;
      name = malloc(nameSize+1);
      temp = "sword.png";
      res->weight = 10;
      break;
  }

  strcpy(name,temp);

  strcat(path,name);

  SDL_Surface *temp_surface = IMG_Load(path);

  if (temp_surface == NULL)
  {
    fprintf(stderr, "Error : Couldn't load image. %s", IMG_GetError());
    return NULL;
  }
  res->texture = SDL_CreateTextureFromSurface(rend, temp_surface);

  res->x = x;
  res->y = y;

  res->is_on_ground = TRUE;

  res->rect.x = x;
  res->rect.y = y;
  res->rect.w = temp_surface->w;
  res->rect.h = temp_surface->h;

  SDL_FreeSurface(temp_surface);

  return res;
}
