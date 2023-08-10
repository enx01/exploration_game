#include "../../../headers/game_scenes/game/game_elements/crosshair.h"
#include "../../../headers/game_scenes/game/game_elements/player.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>
#include <stdio.h>


Crosshair *create_Crosshair(SDL_Renderer *rend, Player *p)
{
  Crosshair *res = malloc(sizeof(Crosshair));

  SDL_Surface *temp_surface = IMG_Load("res/img/crosshair.png");
  
  if (temp_surface == NULL)
  {
    fprintf(stderr, "Error : Couldn't load image. %s", IMG_GetError());
    return NULL;
  }
  
  res->texture = SDL_CreateTextureFromSurface(rend, temp_surface);

  res->posID = 0;

  res->x = 10;
  res->y = 10;

  res->rect.x = res->x;
  res->rect.y = res->y;
  res->rect.w = temp_surface->w;
  res->rect.h = temp_surface->h;

  res->speed = 0.005f;
  res->distance = 50;
  res->angle = 0.0f;
  res->rotation_dir = 0;

  res->p = p;

  SDL_FreeSurface(temp_surface);

  return res;
}

SDL_Point Crosshair_process_input(Crosshair *crosshair, SDL_Event event)
{
  SDL_Point res = { 0,0 };
  switch(event.type)
  {
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym)
      {
        case SDLK_RIGHT :
          crosshair->rotation_dir = 1; 
          break;
        case SDLK_LEFT :
          crosshair->rotation_dir = -1;
          break;
        case SDLK_SPACE :
          res.x = crosshair->x + (int)(crosshair->rect.w/2);
          res.y = crosshair->y + (int)(crosshair->rect.h/2);
          fprintf(stderr, "player interacted at x : %d y : %d.\n",res.x,res.y);
          return res;
      }
    break;
    case SDL_KEYUP:
      switch (event.key.keysym.sym) 
      {
        case SDLK_RIGHT :
          crosshair->rotation_dir = 0;
          break;
        case SDLK_LEFT :
          crosshair->rotation_dir = 0;
          break;
      }
    break;
   }
  return res;
}

SDL_Point Crosshair_GetCoordinates(Crosshair *crosshair)
{
  SDL_Point res = { 0,0 };
  res.x = crosshair->x + (int)(crosshair->rect.w/2);
  res.y = crosshair->y + (int)(crosshair->rect.h/2);
  return res;
}

void Crosshair_update(Crosshair *crosshair)
{   
  if (crosshair->rotation_dir != 0)
  {
    crosshair->angle += crosshair->rotation_dir * crosshair->speed;
  }
  
  crosshair->x = crosshair->p->x + (int)(cos(crosshair->angle) * crosshair->distance);
  crosshair->y = crosshair->p->y + (int)(sin(crosshair->angle) * crosshair->distance);
  
  crosshair->rect.x = crosshair->x;
  crosshair->rect.y = crosshair->y;
}

void Crosshair_render(Crosshair *crosshair, SDL_Renderer *rend)
{
  SDL_RenderCopy(rend, crosshair->texture, NULL, &(crosshair->rect));
}

void Crosshair_destroy(Crosshair *crosshair)
{
  SDL_DestroyTexture(crosshair->texture);
  free(crosshair);
}
