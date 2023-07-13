#include "../headers/game_scenes/game_scene.h"

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
