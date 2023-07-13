#include "headers/structs.h"
#include "lib/include.h"
#include "headers/game_scenes/menu/menu.h"

int scene = MENU_SCENE;
SDL_Window *window = NULL;
SDL_Renderer *rend = NULL;
Menu *main_menu = NULL;

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
  main_menu = create_Menu(rend);
}


// While loop functions

void process_input()
{

}

void update()
{

}

void render()
{
    // Render stuff here
  
}

void destroy_window() 
{
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
    //process_input();
    //update();
    //render();

    switch(scene)
    {
      case MENU_SCENE:
        Menu_run(main_menu, rend);
        break;
      default:
        break;
    }
  }

  destroy_window();

  return EXIT_SUCCESS;
}
