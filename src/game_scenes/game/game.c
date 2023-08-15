#include "../../headers/game_scenes/game/game.h"
#include "../../headers/game_scenes/game/game_elements/player.h"
#include "../../headers/game_scenes/game/game_elements/item.h"
#include "../../headers/game_scenes/game/game_elements/inv_item_slot.h"
#include "../../headers/globals.h"
#include "../../headers/constants.h"
#include <SDL2/SDL_render.h>

Game *create_Game(SDL_Renderer *rend)
{
  Game *res = malloc(sizeof(Game));
    
  SDL_Surface *temp_surface = IMG_Load("res/img/game_background.png");
  if (temp_surface == NULL)
  {
    fprintf(stderr, "Error : Couldn't load image. %s", IMG_GetError());
    return NULL;
  }
  res->texture = SDL_CreateTextureFromSurface(rend, temp_surface);
  SDL_FreeSurface(temp_surface);

  res->player = create_Player(rend, 300,300);

  res->items_in_game = malloc(20* sizeof(Item));

  res->items_in_game[0] = create_Item(rend, APPLE, 400, 300);

  res->nb_items = 1;

  return res;
}

int Game_process_input(Game *game)
{
  SDL_Event event;
  SDL_PollEvent(&event);
  switch (event.type) 
  {
    case SDL_QUIT:
      running = FALSE;
      break;
    case SDL_KEYDOWN:
      if (event.key.keysym.sym == SDLK_ESCAPE)
        running = FALSE;
      break;
    case SDL_MOUSEBUTTONDOWN: 
      SDL_GetMouseState(&mouseX, &mouseY);
      mouse_clicked = TRUE;
      if (DEBUG)
      {
        printf("clicked at :\nx : %d\ny : %d\n",mouseX,mouseY); 
      }
      int action = 0;
      if (mouse_clicked)
      {

      // TODO : Game environment interaction 

      mouse_clicked = FALSE;
      }
  }

  Player_process_input(game->player, event);

  return 0;
}

void Game_update(Game *game, Uint32 deltaTime)
{
  Player_update(game->player, deltaTime);
  for (int i = 0; i < game->nb_items; ++i)
  {
    Item_update(game->items_in_game[i],game->player); 
  }
}

void Game_render(Game *game, SDL_Renderer *rend)
{
  SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
  SDL_RenderClear(rend);

  SDL_RenderCopy(rend, game->texture, NULL, NULL);
  
  for (int i = 0; i < game->nb_items; ++i)
  {
    Item_render(game->items_in_game[i],rend); 
  }

  Player_render(game->player, rend);

  SDL_RenderPresent(rend);
}

void Game_run(Game *game, SDL_Renderer *rend, Uint32 deltaTime)
{
  int processed_input = Game_process_input(game);
  Game_update(game,deltaTime);
  Game_render(game,rend);
  switch (processed_input) 
  {
    // TODO : Handle buttons inputs
  }
}

void Game_destroy(Game *game)
{
  SDL_DestroyTexture(game->texture);
  Player_destroy(game->player);
  free(game);
}
