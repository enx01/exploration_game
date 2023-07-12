#ifndef HEADERS_H
#include "../lib/include.h"

// Elements

// Button
struct Button;

struct Button
{
  SDL_Rect rect;
  SDL_Rect label_rect;
  SDL_Texture *texture;
  void (*action)();
  int isClicked;
};

typedef struct Button Button;

// Label
struct Label;

struct Label
{

};

typedef struct Label Label;

// Game_scenes

// Menu
struct Menu;

struct Menu
{
  Label *labels;
  int labels_count;
  Button *buttons;
  int buttons_count;
};

typedef struct Menu Menu;

#endif // !HEADERS_H
