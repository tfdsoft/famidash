#pragma code-name(push, "XCD_BANK_03")
#pragma data-name(push, "XCD_BANK_03")
#pragma rodata-name(push, "XCD_BANK_03")

#include "defines/bg_charmap.h"
const char TEXT_nothinghere[] = "SORRY NOTHING HERE YET";

void state_sorrynothing() {
    famistudio_music_stop();
    sfx_play(sfx_achievement_get, 0);
    pal_bright(0);
    ppu_off();

    set_scroll_x(0x100);
    vram_adr(NTADR_B(0,0));
    vram_fill(0xff, 0x400);

    multi_vram_buffer_horz(TEXT_nothinghere, sizeof(TEXT_nothinghere)-1, NTADR_B(4,4));
    
    ppu_on_all();
    pal_bright(4);
    while (1) {
        ppu_wait_nmi();
        music_update();

        if (joypad1.b) {
            set_scroll_x(0);
            return;
        }
    }
}


#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)