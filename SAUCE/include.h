// you probably shouldn't change anything  //
// here unless you know what you're doing. //

#include "../LIB/neslib.h"  // common nes library
#include "../LIB/nesdoug.h" // slightly less common nes library (thanks nesdoug)
#include "../LIB/nesdash.h" // custom stuff made specifically for famidash
#include "../LIB/famistudio_cc65.h" // sound driver

#include "../MUSIC/EXPORTS/musicDefines.h" // sound driver C defines


// grounds goes here
#include "../LEVELS/ground0.h"
#include "../LEVELS/ground.h"


#include "../LEVELS/leveldata.h"    // level data goes here
#include "../LEVELS/levellist.h"    // level order goes here


#include "famidash.h"   // where everything is declared. don't move this

#include "defines/metatiles.h"  // metatile defines
#include "defines/sprites.h"    // metasprite defines

#include "level_loading.h"  // goofy ass screen drawing routines
#include "scroll.h"

#include "functions/draw_sprites.h"  // sproit drawlign
#include "functions/collision.h"  // collision
#include "functions/reset_level.h"  // reset the stage





#include "defines/menutext.h" // menu text. obviously.


// THE GAME MODE DEFINES //
#include "gamemodes/gamemode_cube.h"


// THE GAME STATE DEFINES //
#include "gamestates/state_menu.h"
#include "gamestates/state_game.h"






