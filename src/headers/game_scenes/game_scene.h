#ifndef GAME_SCENE_H 
#include "../structs.h"

struct Game_Scene
{
  void(*process_input)();
  void(*update)();
  void(*render)();
};

void GS_process_input(Game_Scene *base);
void GS_update(Game_Scene *base);
void GS_render(Game_Scene *base);

#endif // !GAME_SCENE_H
