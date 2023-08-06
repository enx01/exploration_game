#include "../../headers/game_scenes/menu/menu.h"
#include "../../headers/game_scenes/elements/label.h"
#include "../../headers/game_scenes/elements/button.h"
#include "../../headers/game_scenes/game/game_elements/player.h"
#include "../../headers/globals.h"
#include "../../headers/constants.h"
#include <SDL2/SDL_render.h>

int mouseX,mouseY, mouse_clicked;
int running, scene;

Menu *create_Menu(SDL_Renderer *rend)
{
  Menu *res = malloc(sizeof(Menu));

  res->p = create_Player(rend, 100, 100);
    
  SDL_Surface *temp_surface = IMG_Load("res/img/menu_background.png");
  if (temp_surface == NULL)
  {
    fprintf(stderr, "Error : Couldn't load image. %s", IMG_GetError());
    return NULL;
  }
  res->texture = SDL_CreateTextureFromSurface(rend, temp_surface);
  SDL_FreeSurface(temp_surface);

  res->mainTitle = create_Label(0, 50, "Explore", rend);
  res->mainTitle->rect.x = (WINDOW_WIDTH/2) - (res->mainTitle->rect.w/2);
  res->play = create_Button((WINDOW_WIDTH/2) - 100, 225, 200, 75, "play", play_button_action, COLOR_GREEN,rend);
  printf("%d",WINDOW_WIDTH);
  res->settings = create_Button((WINDOW_WIDTH/2) - 100, 350, 200, 75, "settings", settings_button_action, COLOR_GREEN, rend);
  res->quit = create_Button(850, 520, 100, 50, "quit", quit_button_action, COLOR_RED, rend);


  res->button_count = 3;

  res->button_list = malloc(res->button_count * sizeof(Button));

  res->button_list[0] = res->play;
  res->button_list[1] = res->settings;
  res->button_list[2] = res->quit;

  return res;
}

int Menu_process_input(Menu *menu)
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
      mouse_clicked = TRUE;
      if (DEBUG)
      {
        printf("clicked at :\nx : %d\ny : %d\n",mouseX,mouseY); 
      }
      int action = 0;
      if (mouse_clicked)
      {
        for (int i = 0; i < menu->button_count; ++i)
        {
          action = handleClick(menu->button_list[i], mouseX, mouseY);
          if (action != 0)
          {
            switch (action)
            {
              case BUTTON_PLAY_CLICKED:
                printf("Switching to game...\n");
                return BUTTON_PLAY_CLICKED;
                break;
              case BUTTON_SETTINGS_CLICKED:
                printf("Switching to settings...\n");
                return BUTTON_SETTINGS_CLICKED;
                break;
              case BUTTON_QUIT_CLICKED:
                printf("Quitting program...\n");
                running = FALSE;
                break;
            }
          }
        }

      mouse_clicked = FALSE;
      }
  }

  Player_process_input(menu->p, event);


  return 0;
}

void Menu_update(Menu *menu)
{
  Player_update(menu->p); 
}

void Menu_render(Menu *menu, SDL_Renderer *rend)
{
  SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
  SDL_RenderClear(rend);

  SDL_RenderCopy(rend, menu->texture, NULL, NULL);
  Label_Render(menu->mainTitle, rend);
  Button_Render(menu->play, rend);
  Button_Render(menu->settings, rend);
  Button_Render(menu->quit, rend);

  Player_render(menu->p, rend);

  SDL_RenderPresent(rend);
}

void Menu_run(Menu *menu, SDL_Renderer *rend)
{
  int processed_input = Menu_process_input(menu);
  Menu_update(menu);
  Menu_render(menu,rend);
  switch (processed_input) 
  {
    case BUTTON_SETTINGS_CLICKED:
      scene = SETTINGS_SCENE;
      break;
    case BUTTON_PLAY_CLICKED:
      scene = GAME_SCENE;
      break;
    case BUTTON_QUIT_CLICKED:
      scene = 0;
      break;
  }
}

int play_button_action()
{
  return BUTTON_PLAY_CLICKED;
}

int settings_button_action()
{
  return BUTTON_SETTINGS_CLICKED;
}

int quit_button_action()
{
  return BUTTON_QUIT_CLICKED;
}

void Menu_destroy(Menu *menu)
{
  SDL_DestroyTexture(menu->texture);
  Label_Destroy(menu->mainTitle);
  for (int i = 0; i < menu->button_count; ++i)
  {
    Button_Destroy(menu->button_list[i]);
  }
  free(menu->button_list);
  free(menu);
}
