#ifndef PLAYER_H
#include "../../../structs.h"

struct Player
{
  SDL_Rect rect;
  SDL_Texture *texture;
  int hp;

  float x,y,speed;

  Health_Bar *health_bar;
  Inventory *inventory;
  Crosshair *crosshair;

  int up,down,left,right,sprint;
};

Player *create_Player(SDL_Renderer *rend, int x, int y);

void Player_process_input(Player *player, SDL_Event event);
void Player_update(Player *player, Uint32 deltaTime);
void Player_render(Player *player, SDL_Renderer *rend);
void Player_run(Player *player, SDL_Renderer *rend, SDL_Event event, Uint32 deltaTime);

void Player_move_up(Player *player);
void Player_move_down(Player *player);
void Player_move_left(Player *player);
void Player_move_right(Player *player);

void Player_destroy(Player *player);

#endif // !PLAYER_H
