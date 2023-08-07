#include "../../../headers/game_scenes/game/game_elements/health_bar.h"
#include "../../../headers/game_scenes/game/game_elements/player.h"
#include <SDL2/SDL_render.h>

Health_Bar *create_Health_Bar(SDL_Renderer *rend, Player *player)
{
  Health_Bar *res = malloc(sizeof(Health_Bar));
  res->player = player;
  res->width = 300;
  res->height = 20;
  return res;
}

void Health_Bar_update(Health_Bar *hb)
{
}

void Health_Bar_render(Health_Bar *hb, SDL_Renderer *rend)
{
  float hpPercent = (float)(hb->player->hp)/100;

  int currHealthWidth = (int)(hb->width * hpPercent);


  

  SDL_Rect healthBarRect = {
    40,
    570,
    currHealthWidth,
    hb->height
  };

  SDL_Rect backgroundBar = {
    40,
    570,
    hb->width,
    hb->height
  };

  hb->rect = healthBarRect;
  
  SDL_SetRenderDrawColor(rend, COLOR_BLACK[0], COLOR_BLACK[1], COLOR_BLACK[2], COLOR_BLACK[3]);

  SDL_RenderFillRect(rend, &backgroundBar);
  
  if (hpPercent <= .3)
  {
    SDL_SetRenderDrawColor(rend, COLOR_RED[0], COLOR_RED[1], COLOR_RED[2], COLOR_RED[3]);
  }
  else 
  {
    SDL_SetRenderDrawColor(rend, COLOR_GREEN[0], COLOR_GREEN[1], COLOR_GREEN[2], COLOR_GREEN[3]);
  }

  SDL_RenderFillRect(rend, &hb->rect);
}

void Health_Bar_destroy(Health_Bar *hb)
{
  hb->player = NULL;
  free(hb);
}
