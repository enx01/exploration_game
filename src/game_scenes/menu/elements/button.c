#include "../../../headers/game_scenes/menu/elements/button.h"
#include <SDL2/SDL_render.h>

Button *create_Button(int x, int y, int w, int h, const char *label, void(*a)(), SDL_Renderer *rend)
{
  Button *res = malloc(sizeof(Button));
  res->rect.x = x;
  res->rect.y = y;
  res->rect.w = w;
  res->rect.h = h;

  SDL_Rect rect_copy = {res->rect.x, res->rect.y, res->rect.w, res->rect.h};
  res->label_rect = rect_copy;

  res->isClicked = FALSE;

  // Creating the label
  TTF_Font *font = TTF_OpenFont("res/fonts/typewriter.ttf", 64);
  
  if (font == NULL)
  {
    fprintf(stderr, "Error : Couldn't open font. %s\n", TTF_GetError());
    return NULL;
  }

  SDL_Surface *temp_surface = TTF_RenderText_Blended(font, label, (SDL_Color){0,0,0,255});

  res->texture = SDL_CreateTextureFromSurface(rend, temp_surface);
  SDL_FreeSurface(temp_surface);

  res->action = a;

  return res;
}

int isMouseHoveringButton(Button *button, int x, int y)
{
  int res;
  if  ( x >= button->rect.x &&
        x <= (button->rect.x + button->rect.w) &&
        y >= button->rect.y &&
        y <= (button->rect.y + button->rect.h)
      )
  {
    res = TRUE;
  }
  else
  {
    res = FALSE;
  }

  return res;
}

void handleClick(Button *button, int x, int y)
{
  if (isMouseHoveringButton(button, x, y))
  {
    button->isClicked = TRUE;
    button->action();
  }
}

void Button_Render(Button *button, SDL_Renderer *rend)
{
  // Button background
  SDL_SetRenderDrawColor(rend, 169, 169, 169, 55);
  SDL_RenderFillRect(rend, &button->rect);

  // Button label
  SDL_RenderCopy(rend, button->texture, NULL, &button->label_rect);
}

void Button_Destroy(Button *button)
{
  SDL_DestroyTexture(button->texture);
  free(button);
}
