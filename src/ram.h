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

// ok so here's where the metatiles are
#define metatiles_TL (*(u8*)&sram_buffer[0])    // top left
#define metatiles_TR (*(u8*)&sram_buffer[256])  // top right
#define metatiles_BL (*(u8*)&sram_buffer[512])  // bottom left
#define metatiles_BR (*(u8*)&sram_buffer[768])  // bottom right

#define metatiles_collision (*(u8*)&sram_buffer[1024])  // collision

#define collision_map_0 (*(u8*)&sram_buffer[1280])
#define collision_map_1 (*(u8*)&sram_buffer[1536-16])
#define collision_map_2 (*(u8*)&sram_buffer[1792-32])












/*==============================================
 *  You shouldn't have to touch anything
 *  below this point.
**============================================*/

// generally, you want a state machine to
// control your game loop with
u8 gamestate = 0xfe;

