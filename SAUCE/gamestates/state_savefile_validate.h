#if !__THE_ALBUM
CODE_BANK_PUSH("XCD_BANK_02")
#else
CODE_BANK_PUSH("XCD_BANK_01")
#endif

void setdefaultoptions();

void mouse_and_cursor();

void state_savefile_validate(){
    // startup
    set_scroll_x(0);
    ppu_wait_nmi();

    // if save file version is incorrect //
    if ((SRAM_VALIDATE[2] != FLAG_SAVE_VER) && SRAM_VALIDATE[2] != 0x00) {
        setdefaultoptions();
    }

    // if header is wrong //
    if (SRAM_VALIDATE[0] != 0x13 || SRAM_VALIDATE[1] != 0x37 || SRAM_VALIDATE[2] != FLAG_SAVE_VER) {
        setdefaultoptions();
    }
    
    // if poweroff check is not zero //

    #if !__VS_SYSTEM && !__THE_ALBUM
        mmc3_set_8kb_chr(MENUBANK);
        mmc3_set_2kb_chr_bank_0(0xFF);  
        mmc3_set_2kb_chr_bank_1(MOUSEBANK); 

        include_nested_dialog_string(dialogBox_saveFileSafetyHeader);
        draw_dialog_box(dialogBox_pleasePressB);

        mmc3_disable_irq();

        ppu_on_all();

        pal_fade_to_withmusic(0,4);

        do {
            ppu_wait_nmi();
            music_update();
            oam_clear();
            mouse_and_cursor();
            newrand();
            if (joypad1.press || mouse.left_press || mouse.right_press) break;
            kandoframecnt++;
            if (kandoframecnt & 1 && mouse_timer) mouse_timer--;    
        } while (1);

        pal_fade_to_withmusic(4,0);
        ppu_off();
    #endif

    gameState = STATE_CREDITS;
    return;
}

CODE_BANK_POP()
