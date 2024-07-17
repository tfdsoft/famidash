#pragma code-name(push, "XCD_BANK_03")
#pragma data-name(push, "XCD_BANK_03") 
#pragma rodata-name(push, "XCD_BANK_03")
void savefile_display(){
    multi_vram_buffer_horz("YOUR SAVE FILE", 14, NTADR_A(2,4));
}

void state_savefile_validate(){
    // startup
    #include "defines/bg_charmap.h"
    pal_fade_to(4,0);
    ppu_off();
    pal_col(0x00,0x0f);
    set_scroll_x(0);
    vram_adr(NTADR_A(0,0));
    vram_fill(0xFF, 0x3E0);
    vram_adr(NTADR_A(0,30));
    vram_fill(0x00, 0x20);



    // if save file version is incorrect //
    if ((SRAM_VALIDATE[2] != FLAG_SAVE_VER) && SRAM_VALIDATE[2] != 0x00) {
        savefile_display();
        multi_vram_buffer_horz("IS FOR A", 8, NTADR_A(17,4));
        if (SRAM_VALIDATE[2] > FLAG_SAVE_VER) multi_vram_buffer_horz("NEWER", 5, NTADR_A(2,5));
        else {
            one_vram_buffer('N', NTADR_A(25,4));
            multi_vram_buffer_horz("OLDER", 5, NTADR_A(2,5));
        }
        multi_vram_buffer_horz("VERSION", 7, NTADR_A(8,5));

        multi_vram_buffer_horz("A: CREATE NEW SAVE", 18, NTADR_A(2,8));
        multi_vram_buffer_horz("B: LOAD ANYWAY", 14, NTADR_A(2,9));

        ppu_on_all();
        pal_fade_to(0,4);
        do {
            pad_poll_both();
            if (pad_new[0] & PAD_B) break;
            if (pad_new[0] & PAD_A){
                setdefaultoptions();
                break;
            }
        } while (1);

        gameState = 0x01;
        return; 
    }


    // if header is wrong //
    if (SRAM_VALIDATE[0] != 0x13
    || SRAM_VALIDATE[1] != 0x37
    || SRAM_VALIDATE[2] != FLAG_SAVE_VER
    || SRAM_VALIDATE[3] != 0x21) {
        savefile_display();
        multi_vram_buffer_horz("IS MISSING OR", 13, NTADR_A(17,4));
        multi_vram_buffer_horz("CORRUPT", 7, NTADR_A(2,5));

        multi_vram_buffer_horz("A: CREATE NEW SAVE", 18, NTADR_A(2,8));
        multi_vram_buffer_horz("B: LOAD ANYWAY", 14, NTADR_A(2,9));
        
        ppu_on_all();
        pal_fade_to(0,4);
        do {
            pad_poll_both();
            if (pad_new[0] & PAD_B) break;
            if (pad_new[0] & PAD_A){
                setdefaultoptions();
                break;
            }
        } while (1);

        gameState = 0x01;
        return; 
    }
    

    gameState = 0x01;
    return;
}











#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)