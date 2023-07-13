#include "headers/structs.h"
#include "lib/include.h"

int running = 0;
int mouseX, mouseY;
int mouseClicked = FALSE;
SDL_Window *window = NULL;
SDL_Renderer *rend = NULL;
Game_Scene *current_Game_Scene = NULL;

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
                            WINDOW_HEIGHT,
                            WINDOW_WIDTH,
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

}


// While loop functions

void process_input()
{
  SDL_Event event;
  SDL_PollEvent(&event);

  switch (event.type) 
  {
    case SDL_QUIT:
      running = FALSE;
      break;
    case SDL_KEYDOWN:
      if (event.key.keysym.sym == SDLK_ESCAPE)
        running = FALSE;
      break;
    case SDL_MOUSEBUTTONDOWN: 
      SDL_GetMouseState(&mouseX, &mouseY);
      mouseClicked = TRUE;
  }
}

void update()
{
  if (mouseClicked)
  {
    
    mouseClicked = FALSE;
  }
}

void render()
{
  SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
  SDL_RenderClear(rend);
  // Render stuff here

  SDL_RenderPresent(rend);
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
    process_input();
    update();
    render();
  }

  destroy_window();

  return EXIT_SUCCESS;
}
