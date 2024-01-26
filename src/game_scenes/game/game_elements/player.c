#include "../../../headers/game_scenes/game/game_elements/player.h"
#include "../../../headers/game_scenes/game/game_elements/health_bar.h"
#include "../../../headers/game_scenes/game/game_elements/inventory.h"
#include "../../../headers/game_scenes/game/game_elements/crosshair.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <stdio.h>

Player *create_Player(SDL_Renderer *rend, int x, int y)
{
  Player *res = malloc(sizeof(Player));

  SDL_Surface *temp_surface = IMG_Load("res/img/player.png");
  if (temp_surface == NULL)
  {
    fprintf(stderr, "Error : Couldn't load image. %s", IMG_GetError());
    return NULL;
  }
  res->texture = SDL_CreateTextureFromSurface(rend, temp_surface);
  


  res->rect.x = x;
  res->rect.y = y;
  res->rect.w = temp_surface->w;
  res->rect.h = temp_surface->h;

  SDL_FreeSurface(temp_surface);

  res->x = x;
  res->y = y;
  res->hp = 28;
  res->speed = 100;



  Health_Bar *hb = create_Health_Bar(rend, res);
  Inventory *inv = create_Inventory(rend);
  Crosshair *cross = create_Crosshair(rend, res);

  res->health_bar = hb;
  res->inventory = inv;
  res->crosshair = cross;

  res->up = FALSE;
  res->down = FALSE;
  res->left = FALSE;
  res->right = FALSE;
  res->sprint = FALSE;

  return res;
}

SDL_Point Player_process_input(Player *player, SDL_Event event)
{

  switch (event.type) 
  {
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
        case SDLK_w :
        case SDLK_z :
          player->up = TRUE;
          break;
        case SDLK_s :
          player->down = TRUE;
          break;
        case SDLK_d:
          player->right = TRUE;
          break;
        case SDLK_a:
        case SDLK_q :
          player->left = TRUE;
          break;
        case SDLK_LSHIFT:
          player->sprint = TRUE;
          break;
        case SDLK_i:
          if (player->inventory->is_open)
          {
            player->inventory->is_open = 0;
          }
          else 
          {
            player->inventory->is_open = 1;
          }
    }
      break;
    case SDL_KEYUP:
      switch (event.key.keysym.sym) {
        case SDLK_w:
        case SDLK_z:
          player->up = FALSE;
          break;
        case SDLK_s:
          player->down = FALSE;
          break;
        case SDLK_d:
          player->right = FALSE;
          break;
        case SDLK_a:
        case SDLK_q:
          player->left = FALSE;
          break;
        case SDLK_LSHIFT:
          player->sprint = FALSE;
  break;
      }
      break;
  }
  return Crosshair_process_input(player->crosshair, event);
}

void Player_update(Player *player, Uint32 deltaTime)
{
  if (player->up && player->y > 0)
  {
     player->y -= player->speed * (deltaTime / 1000.0);
  }
  if (player->down && (player->y+player->rect.h) < WINDOW_HEIGHT)
  {
    player->y += player->speed * (deltaTime / 1000.0);
  }
  if (player->right && (player->x+player->rect.w) < WINDOW_WIDTH)
  {
    player->x += player->speed * (deltaTime / 1000.0);
  }
  if (player->left && player->x > 0)
  {
    player->x -= player->speed * (deltaTime / 1000.0);
  }

  player->rect.x = player->x;
  player->rect.y = player->y;

  Crosshair_update(player->crosshair);
}

void Player_render(Player *player, SDL_Renderer *rend)
{
  SDL_RenderCopy(rend, player->texture, NULL, &(player->rect));
  Crosshair_render(player->crosshair, rend);
  Health_Bar_render(player->health_bar, rend);
  Inventory_render(player->inventory, rend);
  
}

void Player_run(Player *player, SDL_Renderer *rend, SDL_Event event, Uint32 deltaTime)
{
  Player_process_input(player, event);
  Player_update(player, deltaTime);
  Player_render(player,rend);
}

void Player_destroy(Player *player)
{
  SDL_DestroyTexture(player->texture);
  Health_Bar_destroy(player->health_bar);
  Inventory_destroy(player->inventory);
  free(player);
}
