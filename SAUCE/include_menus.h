



#if !__THE_ALBUM
CODE_BANK_PUSH("XCD_BANK_03")
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
CODE_BANK_PUSH("XCD_BANK_05")
#include "defines/album_nametable/menunametable_XCD03.c"
#include "menustates/album_titlescreen.c"
#endif


#if __THE_ALBUM
CODE_BANK("XCD_BANK_06")
#include "menustates/bgmtest_album.c"
#else
#if __HUGE_ROM
CODE_BANK("XCD_BANK_07")
#include "menustates/bgmtest_HUGE.c"
#else
CODE_BANK("XCD_BANK_05")
#include "menustates/bgmtest.c"
#endif
#endif

#if __HUGE_ROM
CODE_BANK("XCD_BANK_08")
#include "defines/nametable/menunametable_XCD06.c"
#else
#if !__THE_ALBUM
CODE_BANK("XCD_BANK_06")

#include "defines/nametable/menunametable_XCD06.c"

#endif
#endif
#if LEVELSET != 'A' && !__HUGE_ROM && !__THE_ALBUM
CODE_BANK("XCD_BANK_06")
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
CODE_BANK("XCD_BANK_05")
#include "defines/palette/palettes_XCD02.c"
#include "defines/album_nametable/menunametable_XCD02.c"
#endif

#include "menustates/credits.c"
CODE_BANK_POP()