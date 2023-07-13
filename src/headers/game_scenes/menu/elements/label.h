#ifndef LABEL_H
#include "../../../structs.h"

struct Label
{
  SDL_Rect rect;
  SDL_Texture *texture;
};

Label *create_Label(int x, int y, const char *text, SDL_Renderer *rend);
void Label_Render(Label *label, SDL_Renderer *rend);
void Label_Destroy(Label *label);

#endif // !LABEL_H
