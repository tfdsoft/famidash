// you probably shouldn't change anything  //
// here unless you know what you're doing. //

#include "../LIB/neslib.h"  // common nes library
#include "../LIB/nesdoug.h" // slightly less common nes library (thanks nesdoug)
#include "../LIB/mapper.h"  // MMC3 functions
#include "../LIB/nesdash.h" // custom stuff made specifically for famidash
#include "../LIB/famistudio_cc65.h" // sound driver

#include "../MUSIC/EXPORTS/musicDefines.h" // sound driver C defines




// grounds goes here
#pragma rodata-name (push, "LVL_BANK_00")
#include "../LEVELS/grounddata.h"
#include "defines/menunametable.h"
#pragma rodata-name (pop)
#include "../LEVELS/groundlist.h"




// banks set inside level data due to banking
#include "../LEVELS/objdefines.h"   // object defines for easier implementation
                                    // stolen from the old repo lol

#include "../LEVELS/leveldata.h"    // level data goes here




#pragma rodata-name (push, "RODATA_2")
#include "../LEVELS/levellist.h"    // level order goes here
#pragma rodata-name (pop)




#include "famidash.h"   // where everything is declared. don't move this



#include "../METATILES/metatiles.h"  // metatile defines
#include "defines/sprites.h"    // metasprite defines

#include "functions/level_loading.h"  // goofy ass screen drawing routines
#include "functions/scroll.h"
#include "functions/draw_sprites.h"  // sproit drawlign
#include "functions/collision.h"  // collision
#include "functions/reset_level.h"  // reset the stage
#include "functions/sprite_loading.h"




#include "defines/menutext.h" // menu text. obviously.


// THE GAME MODE DEFINES //
#include "functions/x_movement.h"

#include "gamemodes/gamemode_ufo.h"
#include "gamemodes/gamemode_ball.h"
#include "gamemodes/gamemode_cube.h"
#include "gamemodes/gamemode_ship.h"
#include "gamemodes/gamemode_spider.h"

// THE GAME STATE DEFINES //
#include "gamestates/state_menu.h"
#include "gamestates/state_game.h"
#include "gamestates/state_lvldone.h"
//#include "gamestates/state_demo.h"






