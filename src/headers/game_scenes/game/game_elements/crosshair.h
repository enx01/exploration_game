#ifndef CROSSHAIR_H
#include "../../../structs.h"

struct Crosshair
{
  SDL_Rect rect;
  SDL_Texture *texture;

  int posID;

  float x,y,speed,angle;

  int distance,rotation_dir;
  
  
  Player *p;
};

Crosshair *create_Crosshair(SDL_Renderer *rend, Player *p);
SDL_Point Crosshair_process_input(Crosshair *crosshair, SDL_Event event);
void Crosshair_update(Crosshair *crosshair);
void Crosshair_render(Crosshair *crosshair, SDL_Renderer *rend);

void Crosshair_destroy(Crosshair *crosshair);

#endif // !CROSSHAIR_H
