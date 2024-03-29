#include "headers/constants.h"
#include "headers/game_scenes/game/game.h"
#include "headers/game_scenes/game/game_elements/player.h"
#include "headers/game_scenes/settings/settings.h"
#include "headers/game_scenes/menu/menu.h"
#include "headers/structs.h"
#include "lib/include.h"
#include <SDL2/SDL_timer.h>

SDL_Window *window = NULL;
SDL_Renderer *rend = NULL;
Menu *main_menu = NULL;
Settings *settings_menu = NULL;
Game *game = NULL;
Uint32 deltaTime = 0.0;
Uint32 lastFrameTime = 0.0;

int initalize_window(void) 
{
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) 
  {
    fprintf(stderr, "Error : Couldn't initialize SDL. : %s\n", SDL_GetError());
    return FALSE;
  }

  window = SDL_CreateWindow("exploration",
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            WINDOW_WIDTH,
                            WINDOW_HEIGHT,
                            0);
  if (!window) 
  {
    fprintf(stderr, "Error : Couldn't initialize window.");
    return FALSE;
  }

  if (TTF_Init() < 0)
  {
    fprintf(stderr, "Error : Couldn't initialize SDL_TTF. : %s\n", SDL_GetError());
    return FALSE;
  }

  rend = SDL_CreateRenderer(window, -1, 0);
  if (!rend) 
  {
    fprintf(stderr, "Error : Couldn't initialize renderer.");
    return FALSE;
  }
  SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);

  SDL_RenderClear(rend);

  SDL_RenderPresent(rend);

  return TRUE;
}

void setup()
{
  scene = MENU_SCENE;
  main_menu = create_Menu(rend);
  settings_menu = create_Settings(rend);
  game = create_Game(rend);
  lastFrameTime = SDL_GetTicks();
}

void destroy_window() 
{
  Menu_destroy(main_menu);
  Settings_destroy(settings_menu);
  Game_destroy(game);
  SDL_DestroyRenderer(rend);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

int main(void) 
{
  printf("Program started.\n");

  running = initalize_window();

  setup();

  while (running)
  {
    Uint32 currentTime = SDL_GetTicks();
    deltaTime = currentTime - lastFrameTime;
    lastFrameTime = currentTime;

    switch(scene)
    {
      case MENU_SCENE:
        Menu_run(main_menu, rend);
        break;
      case GAME_SCENE:
        Game_run(game, rend, deltaTime);
        break;
      case SETTINGS_SCENE:
        Settings_run(settings_menu, rend);
        break;
      case TEST_SCENE:
        break;
      case 0:
        running = FALSE;
        break;
    }
  }

  destroy_window();

  return EXIT_SUCCESS;
}
