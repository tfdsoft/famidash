/*==============================================
 *  RAM HEADER
 *  any global variables your game uses
 *  should go here.
**==============================================
 *  for battery-backed variables:
 *    - add `sram` to the beginning of your
 *      declaration.
**============================================*/




__attribute__((retain)) u8  loaded_bg_set = 0xff, loaded_g_set = 0xff,
    return_gamestate;
sram u8 sram_buffer[2048], background_set, ground_set;
//sram u8 saved_menu_theme;










/*==============================================
 *  You shouldn't have to touch anything
 *  below this point.
**============================================*/

// generally, you want a state machine to
// control your game loop with
u8 gamestate = 0xfe;

