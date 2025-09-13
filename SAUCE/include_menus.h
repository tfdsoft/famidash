
CODE_BANK_PUSH("XCD_BANK_03")



#if !__THE_ALBUM
#include "defines/nametable/menunametable_XCD03.c"
#include "menustates/common_xcd_bank_03.c"
#include "menustates/levelselection.c"
#include "menustates/progressbar.c"
#include "menustates/customize.c"
#include "menustates/titlescreen.c"
	#if __VS_SYSTEM
	#include "menustates/gameover.c"
	#endif
#else
#include "defines/album_nametable/menunametable_XCD03.c"
#include "menustates/album_titlescreen.c"
#endif

CODE_BANK("XCD_BANK_05")

#if __THE_ALBUM
#include "menustates/bgmtest_album.c"
#else
#include "menustates/bgmtest.c"
#endif

CODE_BANK("XCD_BANK_06")

#include "defines/nametable/menunametable_XCD06.c"

#if LEVELSET != 'A' && LEVELSET != 0xA1B73
#include "menustates/playmain.c"
#endif

#if !__THE_ALBUM
#include "menustates/funsettings.c"
#include "menustates/refreshmenu.c"
#include "menustates/progressbar_pt2.c"
#endif


#if !__THE_ALBUM
CODE_BANK("XCD_BANK_02")

#include "defines/palette/palettes_XCD02.c"
#include "defines/nametable/menunametable_XCD02.c"
#include "menustates/instructions.c"
	#if !__VS_SYSTEM
	#include "menustates/settings.c"
	#endif
#else
CODE_BANK("XCD_BANK_03")
#include "defines/palette/palettes_XCD02.c"
#include "defines/album_nametable/menunametable_XCD02.c"
#endif

#include "menustates/credits.c"
CODE_BANK_POP()