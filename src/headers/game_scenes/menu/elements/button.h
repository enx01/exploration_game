#ifndef BUTTON_H
#include "../../../structs.h"

struct Button
{
  SDL_Rect rect;
  SDL_Rect label_rect;
  SDL_Texture *texture;
  int (*action)();
  int isClicked;
};

Button *create_Button(int x, int y, int w, int h, const char *label, int(*a)(), SDL_Renderer *rend);
int isMouseHoveringButton(Button *button, int x, int y);
int handleClick(Button *button, int x, int y);
void Button_Render(Button *button, SDL_Renderer *rend);
void Button_Destroy(Button *button);

#endif // !BUTTON_H
