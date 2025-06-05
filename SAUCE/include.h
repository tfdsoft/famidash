// you probably shouldn't change anything  //
// here unless you know what you're doing. //

#include "BUILD_FLAGS.h" 

// C standard library 
#include "stdint.h"	// defines for standard types
#include "stddef.h"	// more defines for standard types
#include "nonstdint.h"
#include "arr_macros.h" // fast array operations

// asm standard library
#include "neslib.h"  // common nes library
#include "nesdoug.h" // slightly less common nes library (thanks nesdoug)
#include "mapper.h"  // MMC3 functions
// #include "mapper_irq.h" // MMC3 IRQ functions
#include "nesdash.h" // custom stuff made specifically for famidash
#if !__THE_ALBUM
#include "famistudio_cc65.h" // sound driver
#else
#include "album-famistudio_cc65.h" // sound driver
#endif
#include "musicDefines.h" // sound driver C defines
#include "sfxDefines.h" // sound driver C defines

// various game-essential defines
#include "level_defines.h"
#include "defines/space_defines.h"
#include "defines/physics_defines.h"

// grounds go here
#pragma rodata-name (push, "XCD_BANK_05")
#include "mouse.h"
//#include "mouse.c"
#pragma rodata-name (pop)
#pragma rodata-name (push, "XCD_BANK_06")
#include "grounddata.h"
#include "groundlist.h"
#pragma rodata-name (pop)




// banks set inside level data due to banking
#include "objdefines.h"   // object defines for easier implementation

#include "levellist.h"    // level order goes here
#include "const_levellist.h"    // colors list and icontable for overflow conservation reasons

#include "defines/dialogbox.h"

#include "famidash.h"   // where everything is declared. don't move this

#include "defines/palette/palettes_PRG.c"

#if !__THE_ALBUM

#include "METATILES/metatiles.h"  // metatile defines
#include "defines/sprites.h"    // metasprite defines
#include "functions/sprite_loading.h"

//#include "functions/fade_timer.h"
#include "functions/reset_game_vars.h"
#include "functions/draw_sprites.h"  // sproit drawlign
#include "functions/level_loading.h"  // goofy ass screen drawing routines
#include "functions/scroll.h"
#include "functions/collision.h"  // collision
#include "functions/reset_level.h"  // reset the stage







// THE GAME MODE DEFINES //

#include "functions/x_movement.h"

#include "gamemodes/gamemode_ufo.h"
#include "gamemodes/gamemode_ball.h"
#include "gamemodes/gamemode_cube.h"
#include "gamemodes/gamemode_ship.h"
#include "gamemodes/gamemode_spider.h"
#include "gamemodes/gamemode_wave.h"

#endif

// THE MENU STATE DEFINES //

#include "include_menus.h"

// THE GAME STATE DEFINES //



#if !__THE_ALBUM
#include "gamestates/state_game.h"
#endif
#include "gamestates/state_savefile_validate.h"
#include "gamestates/state_lvldone.h"

