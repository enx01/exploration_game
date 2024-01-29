#include "../../headers/game_scenes/game/game.h"
#include "../../headers/game_scenes/game/game_elements/player.h"
#include "../../headers/game_scenes/game/game_elements/item.h"
#include "../../headers/game_scenes/game/game_elements/inv_item_slot.h"
#include "../../headers/game_scenes/game/game_elements/inventory.h"
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

  res->nb_items = 0;

  Game_add_item(res, create_Item(rend, APPLE, 400, 300));
  Game_add_item(res, create_Item(rend, SWORD, 500, 300));

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
      if (game->player->inventory->is_open) 
      {
        SDL_Point mouse_pos = {mouseX, mouseY};
        for (int i = 0; i < game->player->inventory->item_count; ++i) 
        {
          if (Item_IsPointOnItem(game->player->inventory->content[i]->content, mouse_pos))
          {
            if (DEBUG)
            {
              printf("clicked on item %d\n", i);
            }
            Inventory_remove_item(game->player->inventory, game->player->inventory->content[i]->content);
            game->player->equipped_item = game->player->inventory->content[i]->content;
            break;
          }
        }
      }
      //if (mouse_clicked)
      //{

      // TODO : Game environment interaction 

     // mouse_clicked = FALSE;
    //  }
  }

  SDL_Point player_input = Player_process_input(game->player, event);
  if (player_input.x != 0 && player_input.y != 0)
  {
    fprintf(stderr, "game struct processed : player interacted at x : %d y : %d.\n",player_input.x,player_input.y);
    // TODO : Calculation if player input is in bounds of an item
    for (int i = 0; i < game->nb_items; i++)
      {
        if (Item_IsPointOnItem(game->items_in_game[i], player_input))
        {
        fprintf(stderr, "game struct processed : player interacted with item %d at x : %d y : %d.\n",game->items_in_game[i]->id ,player_input.x,player_input.y);
        Game_give_item_to_player(game, i);
        break;
        }
      }
        
  }

  return 0;
}

void Game_give_item_to_player(Game *game, int i)
{
  Player_add_item(game->player, game->items_in_game[i]);
  Game_remove_item(game, i);
}

void Game_add_item(Game *game, Item *item)
{
  game->items_in_game[game->nb_items] = item;
  ++game->nb_items;
}

void Game_remove_item(Game *game, int id)
{
  game->items_in_game[id]->showing = FALSE;

  if (id == game->nb_items-1)
  {
    game->items_in_game[id] = NULL;
  }
  else 
  {
    for (int i = id; i < game->nb_items-1; ++i)
    {
      game->items_in_game[i] = game->items_in_game[i+1];
    }
  }
  --game->nb_items;
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
}

void Game_destroy(Game *game)
{
  SDL_DestroyTexture(game->texture);
  Player_destroy(game->player);
  free(game);
}
