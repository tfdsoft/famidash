#ifndef _MOUSE_H
#define _MOUSE_H

#include "core.h"

typedef struct mouse_s {
  union {
    uint8_t status_computed;
    struct {
        uint8_t unused : 3;
        uint8_t right_press : 1;
        uint8_t left_press : 1;
        uint8_t right_release : 1;
        uint8_t left_release : 1;
        uint8_t connected : 1;
    };
  };
  union {
    uint8_t status_raw;
    struct {
#if MOUSE_CONFIG_SENSITIVITY
        uint8_t signature : 4;
        uint8_t sensitivity : 2;
#else
        uint8_t signature : 4;
        uint8_t unused2 : 2;
#endif 
        uint8_t left : 1;
        uint8_t right : 1;
    };
  };
  uint8_t y;
  uint8_t x;
} Mouse;

_Static_assert (sizeof (Mouse) == 4, "Mouse struct must be 4 bytes");

extern Mouse mouse;
#pragma zpsym("mouse");
// Set this to the bit for the controller port that the mouse is read from.
// If you are reading it in a standard port, then you just set this to 1
extern uint8_t mouse_mask;
#pragma zpsym("mouse_mask");

#define MOUSE_LEFT 0x40
#define MOUSE_RIGHT 0x80

#endif // mouse.h
