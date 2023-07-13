#include "../headers/game_scenes/game_scene.h"

Game_Scene *create_Game_Scene()
{
  Game_Scene *res = malloc(sizeof(Game_Scene));
  return res;
}

void GS_process_input(Game_Scene *base)
{
  base->process_input();
}

void GS_update(Game_Scene *base)
{
  base->update();
}

void GS_render(Game_Scene *base)
{
  base->render();
}
