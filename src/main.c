#include "headers/game_scenes/elements/button.h"
#include <SDL2/SDL_render.h>

int running = 0;
int mouseX, mouseY;
int mouseClicked = FALSE;
SDL_Window *window = NULL;
SDL_Renderer *rend = NULL;
Button *test_Button = NULL;

void lol()
{
  printf("splash\n");
}

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
  test_Button = create_Button(10, 10, 300, 200, "test",lol, rend);
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
    handleClick(test_Button, mouseX, mouseY);
    mouseClicked = FALSE;
  }
}

void render()
{
  SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
  SDL_RenderClear(rend);
  Button_Render(test_Button, rend);
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
