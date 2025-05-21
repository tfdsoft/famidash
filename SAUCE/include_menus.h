
CODE_BANK_PUSH("XCD_BANK_03")

#include "defines/nametable/menunametable_XCD03.c"

#include "menustates/common_xcd_bank_03.c"

#include "menustates/levelselection.c"
#include "menustates/progressbar.c"
#include "menustates/customize_screen.c"
#include "menustates/titlescreen.c"

CODE_BANK("XCD_BANK_05")

#include "menustates/bgmtest.c"


CODE_BANK("XCD_BANK_06")

#include "defines/nametable/menunametable_XCD06.c"

#if LEVELSET != 'A'
#include "menustates/playmain.c"
#endif

#include "menustates/funsettings.c"
#include "menustates/refreshmenu.c"
#include "menustates/progressbar_pt2.c"


CODE_BANK("XCD_BANK_02")

#include "defines/nametable/menunametable_XCD02.c"
#include "defines/palette/palettes_XCD02.c"

#include "menustates/instructions.c"
#include "menustates/credits.c"
#include "menustates/settings.c"

CODE_BANK_POP()