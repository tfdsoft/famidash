#include <nes.h>
#include <stdint.h>

#include "ines header.h"
#include "macros.h"

__attribute__((retain))
    #include "ram.h"


// == the compiler/linker figures these out ==
#include "musicDefines.h"
#include "musicBankData.h"
#include "music_soundTestTables.h"
#include "sfx_soundTestTables.h"
// ===========================================
#include "../music/EXPORTS/sfx.h"

#include "libraries.h"
#include "irq.c"
#include "nmi.c"


#include "./defines/physics.h"


#include "./gamestates/state_startup.c"
#include "./gamestates/state_menu.c"
#include "./gamestates/state_debugtools.c"
#include "./gamestates/state_romcheck.c"
#include "./gamestates/state_game.c"






    




