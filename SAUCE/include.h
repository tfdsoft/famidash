// you probably shouldn't change anything  //
// here unless you know what you're doing. //

#include "BUILD_FLAGS.h" 

// C standard library 
#include "stdint.h"	// defines for standard types
#include "stddef.h"	// more defines for standard types
#include "nonstdint.h"

// asm standard library
#include "neslib.h"  // common nes library
#include "nesdoug.h" // slightly less common nes library (thanks nesdoug)
#include "mapper.h"  // MMC3 functions
// #include "mapper_irq.h" // MMC3 IRQ functions
#include "nesdash.h" // custom stuff made specifically for famidash
#include "famistudio_cc65.h" // sound driver

#include "MUSIC/EXPORTS/musicDefines.h" // sound driver C defines




// grounds goes here
#pragma rodata-name (push, "XCD_BANK_03")
#include "defines/menunametable.h"
#pragma rodata-name (pop)
#pragma rodata-name (push, "LVL_BANK_00")
#include "defines/menunametable2.h"
#include "LEVELS/grounddata.h"
#include "LEVELS/groundlist.h"
#pragma rodata-name (pop)




// banks set inside level data due to banking
#include "LEVELS/objdefines.h"   // object defines for easier implementation
                                    // stolen from the old repo lol

// levels are exported to asm now
// #include "LEVELS/leveldata.h"    // level data goes here




#pragma rodata-name (push, "RODATA")
#include "LEVELS/levellist.h"    // level order goes here
#pragma rodata-name (pop)




#include "famidash.h"   // where everything is declared. don't move this



#include "METATILES/metatiles.h"  // metatile defines
#include "defines/sprites.h"    // metasprite defines
#include "functions/sprite_loading.h"

#pragma rodata-name (push, "XCD_BANK_03")
#include "defines/menutext.h" // menu text. obviously.

#pragma rodata-name ("LVL_BANK_00")
#include "defines/menutext2.h" // end level text, not obviously.
#pragma rodata-name (pop)

#include "functions/fade_timer.h"
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

// THE GAME STATE DEFINES //

#include "gamestates/state_savefile_validate.h"
#include "gamestates/state_menu.h"
#include "gamestates/state_game.h"

#include "gamestates/state_sorrynothing.h"

#include "gamestates/state_lvldone.h"
#include "gamestates/state_demo.h"
#include "gamestates/state_savefile_editor.h"