#ifndef BUTTON_H
#include "../../structs.h"

Button *create_Button(int x, int y, int w, int h, const char *label, void(*a)(), SDL_Renderer *rend);
int isMouseHoveringButton(Button *button, int x, int y);
void handleClick(Button *button, int x, int y);
void Button_Render(Button *button, SDL_Renderer *rend);

#endif // !BUTTON_H
