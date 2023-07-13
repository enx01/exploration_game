#include "../../../headers/game_scenes/menu/elements/label.h"

Label *create_Label(int x, int y, const char *text, SDL_Renderer *rend)
{
  Label *res = malloc(sizeof(Label));

  // Creating the label
  TTF_Font *font = TTF_OpenFont("res/fonts/typewriter.ttf", 64);
  
  if (font == NULL)
  {
    fprintf(stderr, "Error : Couldn't open font. %s\n", TTF_GetError());
    return NULL;
  }

  SDL_Surface *temp_surface = TTF_RenderText_Blended(font, text, (SDL_Color){0,0,0,255});

  res->texture = SDL_CreateTextureFromSurface(rend, temp_surface);

  res->rect.x = x;
  res->rect.y = y;
  res->rect.w = temp_surface->w;
  res->rect.h = temp_surface->h;

  SDL_FreeSurface(temp_surface);

  return res;
}

void Label_Render(Label * label, SDL_Renderer *rend)
{
  SDL_RenderCopy(rend, label->texture, NULL, &(label->rect));
  if (DEBUG)
  {
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    SDL_RenderDrawRect(rend, &(label->rect));
  }
}

void Label_Destroy(Label *label)
{
  SDL_DestroyTexture(label->texture);
  free(label);
}
