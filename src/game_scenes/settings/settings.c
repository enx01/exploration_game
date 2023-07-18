#include "../../headers/game_scenes/settings/settings.h"
#include "../../headers/game_scenes/game_scene.h"
#include "../../headers/game_scenes/elements/label.h"
#include "../../headers/game_scenes/elements/button.h"
#include "../../headers/globals.h"
#include "../../headers/constants.h"

int sound;

Settings *create_Settings(SDL_Renderer *rend)
{
  Settings *res = malloc(sizeof(Settings));
  res->base = create_Game_Scene();
  
  SDL_Surface *temp_surface = IMG_Load("res/img/settings_background.png");
  if (temp_surface == NULL)
  {
    fprintf(stderr, "Error : Couldn't load image. %s", IMG_GetError());
    return NULL;
  }
  res->texture = SDL_CreateTextureFromSurface(rend, temp_surface);
  SDL_FreeSurface(temp_surface);

  res->mainTitle = create_Label(0, 50, "Settings", rend);
  res->mainTitle->rect.x = (WINDOW_WIDTH/2) - (res->mainTitle->rect.w/2);
  res->nill = create_Button((WINDOW_WIDTH/2) - 100, 225, 200, 75, "nill", void_button_action, COLOR_GREEN,rend);
  printf("%d",WINDOW_WIDTH);
  res->sound = create_Button((WINDOW_WIDTH/2) - 100, 350, 200, 75, "sound", sound_button_action, COLOR_GREEN, rend);
  res->ret = create_Button(850, 520, 100, 50, "return", return_button_action, COLOR_RED, rend);


  res->button_count = 3;

  res->button_list = malloc(res->button_count * sizeof(Button));

  res->button_list[0] = res->nill;
  res->button_list[1] = res->sound;
  res->button_list[2] = res->ret;

  res->base->process_input = (void(*)())Settings_process_input;
  res->base->update = (void(*)())Settings_update;
  res->base->render = (void(*)())Settings_render;

  return res;
}

int Settings_process_input(Settings *settings)
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
        for (int i = 0; i < settings->button_count; ++i)
        {
          action = handleClick(settings->button_list[i], mouseX, mouseY);
          if (action != 0)
          {
            switch (action)
            {
              case BUTTON_SOUND_CLICKED:
                printf("Clicked sound button...\n");

                sound = 0;

                return BUTTON_SOUND_CLICKED;
                break;
              case BUTTON_QUIT_CLICKED:
                printf("Switching to menu...\n");
                return BUTTON_QUIT_CLICKED;
                break;
            }
          }
        }
        

      mouse_clicked = FALSE;
      }
  }
  return 0;
}

void Settings_update(Settings *settings)
{
  
}

void Settings_render(Settings *settings, SDL_Renderer *rend)
{
  SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
  SDL_RenderClear(rend);

  SDL_RenderCopy(rend, settings->texture, NULL, NULL);
  Label_Render(settings->mainTitle, rend);
  Button_Render(settings->nill,rend);
  Button_Render(settings->sound, rend);
  Button_Render(settings->ret, rend);

  SDL_RenderPresent(rend);
}

void Settings_run(Settings *settings, SDL_Renderer *rend)
{
  int processed_input = Settings_process_input(settings);
  Settings_update(settings);
  Settings_render(settings,rend);
  switch (processed_input) 
  {
    case BUTTON_QUIT_CLICKED :
      scene = MENU_SCENE;
      break;
  } 
}

int void_button_action()
{
  return 0;
}

int sound_button_action()
{
  return BUTTON_SOUND_CLICKED;
}

int return_button_action()
{
  return BUTTON_QUIT_CLICKED;
}
