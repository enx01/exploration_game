#include "../../../headers/structs.h"

struct Game
{
  SDL_Rect rect;
  SDL_Texture *texture;
  
  // TODO : Game Elements here.

};

Game *create_Game(SDL_Renderer *rend);


void Game_process_input(Game *game);
void Game_update(Game *game);
void Game_render(Game *game, SDL_Renderer *rend);
