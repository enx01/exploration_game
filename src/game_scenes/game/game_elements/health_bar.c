#include "../../../headers/game_scenes/game/game_elements/health_bar.h"

Health_Bar *create_Health_Bar(SDL_Renderer *rend, Player *player)
{
  Health_Bar *res = malloc(sizeof(Health_Bar));
  res->player = player;

  return res;
}

void Health_Bar_destroy(Health_Bar *hb)
{
  hb->player = NULL;
  free(hb);
}
