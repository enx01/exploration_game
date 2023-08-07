#ifndef HEALTH_BAR_H
#include "../../../structs.h"

struct Health_Bar
{
  SDL_Rect rect;
  Player *player;

  int width, height;
};

Health_Bar *create_Health_Bar(SDL_Renderer *rend, Player *player);
void Health_Bar_update(Health_Bar *hb);
void Health_Bar_render(Health_Bar *hb, SDL_Renderer *rend);

void Health_Bar_destroy(Health_Bar *hb);

#endif // ! HEALTH_BAR_H
