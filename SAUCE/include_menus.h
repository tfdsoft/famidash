
CODE_BANK_PUSH("XCD_BANK_03")

#include "defines/menunametable.h"

#include "menustates/common_xcd_bank_03.c"

#include "menustates/levelselection.c"
#include "menustates/progressbar.c"
#include "menustates/customize_screen.c"
#include "menustates/titlescreen.c"

CODE_BANK("XCD_BANK_05")

#include "menustates/bgmtest.c"


CODE_BANK("XCD_BANK_06")

#include "defines/menunametable2.h"

#if LEVELSET != 'A'
#include "menustates/playmain.c"
#endif

#include "menustates/funsettings.c"
#include "menustates/refreshmenu.c"
#include "menustates/progressbar_pt2.c"


CODE_BANK("XCD_BANK_02")

#include "defines/menunametable3.h"

#include "menustates/instructions.c"
#include "menustates/credits.c"
#include "menustates/settings.c"

CODE_BANK_POP()