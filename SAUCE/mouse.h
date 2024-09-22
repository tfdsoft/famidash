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

#pragma bss-name (push, "ZEROPAGE")
Mouse mouse;
#pragma bss-name (pop)

#pragma bss-name (push, "ZEROPAGE")
static uint8_t new_x, new_y;
static int8_t x_velocity;
static int8_t y_velocity;
static uint8_t report[4];
static bool p_left;
static bool p_right;
#pragma bss-name (pop)

extern Mouse mouse;
#pragma zpsym("mouse")

extern void __fastcall__ mouse_init(uint8_t x, uint8_t y);
extern void __fastcall__ mouse_clear(void);
extern void __fastcall__ mouse_update(void);

#endif // mouse.h


#define LATCH_PORT 0x4016
#define DATA_PORT1 0x4016
#define DATA_PORT2 0x4017

// If the mouse is connected on the second
// controller port, use DATA_PORT2 instead
#define MOUSE_PORT DATA_PORT2
// NOTE: If you wish to autodetect the mouse port or
// make configurable, you can use a variable instead

#pragma bss-name (push, "ZEROPAGE")
Mouse mouse;
#pragma bss-name (pop)

#pragma bss-name (push, "ZEROPAGE")
static uint8_t new_x, new_y;
static int8_t x_velocity;
static int8_t y_velocity;
static uint8_t report[4];
static bool p_left;
static bool p_right;
#pragma bss-name (pop)
