#ifndef GAME_H
#include "../../structs.h"

struct Game {
  SDL_Rect rect;
  SDL_Texture *texture;
  Item **items_in_game;
  int nb_items;
  Player *player;
};

Game *create_Game(SDL_Renderer *rend);
void Game_give_item_to_player(Game *game, int i);
void Game_add_item(Game *game, Item *item);
void Game_remove_item(Game *game, int i);
int Game_process_input(Game *game);
void Game_update(Game *game, Uint32 deltaTime);
void Game_render(Game *game, SDL_Renderer *rend);
void Game_run(Game *game, SDL_Renderer *rend, Uint32 deltaTime);
void Game_destroy(Game *game);

#endif // !MENU_H
