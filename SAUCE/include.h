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



#include "famidash.h"   // where everything is declared. don't move this

#include "defines/sprites.h"    // metasprite defines
#include "defines/metatiles.h"  // metatile defines
#include "level_loading.h"  // goofy ass screen drawing routines
#include "scroll.h"     



// THE GAME STATE DEFINES //
#include "gamestates/state_menu.h"


#include "defines/menutext.h"