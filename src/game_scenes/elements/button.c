#include "../../headers/game_scenes/elements/button.h"
#include <SDL2/SDL_pixels.h>

Button *create_Button(int x, int y, int w, int h, const char *label, int(*a)(), int c[4], SDL_Renderer *rend)
{
  Button *res = malloc(sizeof(Button));
  res->rect.x = x;
  res->rect.y = y;
  res->rect.w = w;
  res->rect.h = h;

  SDL_Rect rect_copy = {res->rect.x+30, res->rect.y+15, res->rect.w-60, res->rect.h-30};
  res->label_rect = rect_copy;

  res->isClicked = FALSE;

  SDL_Color temp = {c[0],c[1],c[2],c[3]};
  res->color = temp; 

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

int handleClick(Button *button, int x, int y)
{
  if (isMouseHoveringButton(button, x, y))
  {
    button->isClicked = TRUE;
    return button->action();
  }
  return 0;
}

void Button_Render(Button *button, SDL_Renderer *rend)
{
  // Button background
  SDL_SetRenderDrawColor(rend,button->color.r,button->color.g,button->color.b, button->color.a);
  SDL_RenderFillRect(rend, &button->rect);

  // Button label
  SDL_RenderCopy(rend, button->texture, NULL, &button->label_rect);
}

void Button_Destroy(Button *button)
{
  SDL_DestroyTexture(button->texture);
  free(button);
}
