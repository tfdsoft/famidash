#pragma code-name(push, "XCD_BANK_02")
#pragma data-name(push, "XCD_BANK_02") 
#pragma rodata-name(push, "XCD_BANK_02")

#include "defines/bg_charmap.h"
const char TEXT_iamgoingtocommitseveralwarcrimesifcc65doesntstopbeingapieceofshit[] = "YOUR SAVE FILE";

const char TEXT_isfora[] = "IS FOR A";
const char TEXT_new[] = "NEW";
const char TEXT_old[] = "OLD";
const char TEXT_version[] = "VERSION";

const char TEXT_a_createnew[] = "A: CREATE NEW SAVE";
const char TEXT_b_load[] = "B: LOAD ANYWAY";

const char TEXT_exitgame1[] = "IT IS NOW SAFE TO TURN OFF";
const char TEXT_exitgame2[] = "YOUR SYSTEM";
const char TEXT_exitgame3[] = "PLEASE PRESS B ON THE TITLE";
const char TEXT_exitgame4[] = "BEFORE POWERING OFF";

void savefile_display(){
    multi_vram_buffer_horz(TEXT_iamgoingtocommitseveralwarcrimesifcc65doesntstopbeingapieceofshit, sizeof(TEXT_iamgoingtocommitseveralwarcrimesifcc65doesntstopbeingapieceofshit)-1, NTADR_A(2,4));
}

void clear_nametable_a(){
    vram_adr(NTADR_A(0,0));
    vram_fill(0xFF, 0x3C0);
    vram_adr(NTADR_A(0,30));
    vram_fill(0x00, 0x40);
}

void savefile_reset_check_loop(){
    do {
        pad_poll_both();
        if (pad_new[0] & PAD_B) break;
        if (pad_new[0] & PAD_A){
            setdefaultoptions();
            break;
        }
    } while (1);
}

void state_savefile_validate(){
    // startup
    
    mmc3_disable_irq();
    ppu_off();
    pal_bg(splashMenu);
    pal_col(0x00,0x0f);
    pal_col(0x02, 0x10);
    set_scroll_x(0);
    ppu_wait_nmi();
    pal_bright(4);



    // if save file version is incorrect //
    if ((SRAM_VALIDATE[2] != FLAG_SAVE_VER) && SRAM_VALIDATE[2] != 0x00) {
        clear_nametable_a();
        savefile_display();
        multi_vram_buffer_horz(TEXT_isfora, sizeof(TEXT_isfora)-1, NTADR_A(17,4));
        multi_vram_buffer_horz("ER", 2, NTADR_A(5,5));
        if (SRAM_VALIDATE[2] > FLAG_SAVE_VER) multi_vram_buffer_horz(TEXT_new, sizeof(TEXT_new)-1, NTADR_A(2,5));
        else {
            one_vram_buffer('N', NTADR_A(25,4));
            multi_vram_buffer_horz(TEXT_old, sizeof(TEXT_old)-1, NTADR_A(2,5));
        }
        multi_vram_buffer_horz(TEXT_version, sizeof(TEXT_version)-1, NTADR_A(8,5));

        multi_vram_buffer_horz(TEXT_a_createnew, sizeof(TEXT_a_createnew)-1, NTADR_A(2,8));
        multi_vram_buffer_horz(TEXT_b_load, sizeof(TEXT_b_load)-1, NTADR_A(2,9));

        ppu_on_all();

        savefile_reset_check_loop();
    }

    // if header is wrong //
    if (SRAM_VALIDATE[0] != 0x13 || SRAM_VALIDATE[1] != 0x37 || SRAM_VALIDATE[2] != FLAG_SAVE_VER) {
        clear_nametable_a();
        savefile_display();
        multi_vram_buffer_horz("IS MISSING OR", 13, NTADR_A(17,4));
        multi_vram_buffer_horz("CORRUPT", 7, NTADR_A(2,5));

        multi_vram_buffer_horz(TEXT_a_createnew, sizeof(TEXT_a_createnew)-1, NTADR_A(2,8));
        multi_vram_buffer_horz(TEXT_b_load, sizeof(TEXT_b_load)-1, NTADR_A(2,9));
        
        ppu_on_all();
        pal_fade_to(0,4);
        
        savefile_reset_check_loop();
    }
    
    // if poweroff check is not zero //
    if (poweroffcheck) {
        ppu_off();
        clear_nametable_a();
        multi_vram_buffer_horz(TEXT_exitgame3, sizeof(TEXT_exitgame3)-1, NTADR_A(2,13));
        multi_vram_buffer_horz(TEXT_exitgame4, sizeof(TEXT_exitgame4)-1, NTADR_A(6,14));
        multi_vram_buffer_horz(TEXT_exitgame2, sizeof(TEXT_exitgame2)-1, NTADR_A(10,15));
        ppu_on_all();

        do {
            ppu_wait_nmi();
            pad_poll_both();
            if (pad_new[0] & PAD_B) break;

        } while (1);
    }
    pal_bright(3);
    pal_fade_to(3,0);
    gameState = 0x00;
    return;
}



void state_exit(){
    poweroffcheck = 0x00;
    // Disable SRAM write
	POKE(0xA001, 0xC0);

    ppu_off();
    pal_bg(splashMenu);
    
    pal_bright(0);
    mmc3_disable_irq();

    vram_adr(NTADR_A(0,0));
    vram_fill(0xff, 0x3C0);
    vram_fill(0x00, 0x40);

    famistudio_music_stop();
    music_update();

    pal_col(0x00, 0x0f);
    pal_col(0x02, 0x10);
    

    
    multi_vram_buffer_horz(TEXT_exitgame1, sizeof(TEXT_exitgame1)-1, NTADR_A(3,14));
    multi_vram_buffer_horz(TEXT_exitgame2, sizeof(TEXT_exitgame2)-1, NTADR_A(10,15));

    set_scroll_x(0);
    set_scroll_y(0);
    pal_bright(4);
    ppu_on_all();
    do {
        ppu_wait_nmi();
        pad_poll_both();
        // wait for system power off
        if (pad_new[0] & PAD_B) break;
    } while (1);
    kandotemp = 0;
    poweroffcheck = 0xff;
    gameState = 0x01;

    // Enable SRAM write
	POKE(0xA001, 0x80);

    return;
}








#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)