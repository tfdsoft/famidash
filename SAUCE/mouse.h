#ifndef _MOUSE_H
#define _MOUSE_H

#include "core.h"

#define MIN_X   1
#define MAX_X 255
#define MIN_Y   1
#define MAX_Y 239

typedef struct MouseButton {
  bool press;
  bool click;
} MouseButton;

typedef struct Mouse {
  uint8_t x, y;
  MouseButton left;
  MouseButton right;
  bool connected;
} Mouse;

extern Mouse mouse;
#pragma zpsym("mouse")

extern void __fastcall__ mouse_init(uint8_t x, uint8_t y);
extern void __fastcall__ mouse_clear(void);
extern void __fastcall__ mouse_update(void);

#endif // mouse.h
