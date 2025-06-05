#if !__THE_ALBUM


CODE_BANK_PUSH("XCD_BANK_02")

void mouse_and_cursor();

void state_exit(){
}

void savefile_reset_check_loop(){
        setdefaultoptions();
}

void state_savefile_validate(){
    // startup
    
    mmc3_disable_irq();
    ppu_off();
    set_scroll_x(0);
    ppu_wait_nmi();
    pal_bright(0);



    // if save file version is incorrect //
    if ((SRAM_VALIDATE[2] != FLAG_SAVE_VER) && SRAM_VALIDATE[2] != 0x00) {
        savefile_reset_check_loop();
    }
    ppu_wait_nmi();

    // if header is wrong //
    if (SRAM_VALIDATE[0] != 0x13 || SRAM_VALIDATE[1] != 0x37 || SRAM_VALIDATE[2] != FLAG_SAVE_VER) {
        savefile_reset_check_loop();
    }
    ppu_wait_nmi();
    
    // if poweroff check is not zero //

    #if !__VS_SYSTEM
        ppu_off();
        pal_bright(0);
        include_nested_dialog_string(dialogBox_saveFileSafetyHeader);
        draw_dialog_box(dialogBox_pleasePressB);
        ppu_on_all();
        pal_fade_to(0,4);
        mmc3_set_2kb_chr_bank_0(0xFF);  
        mmc3_set_2kb_chr_bank_1(MOUSEBANK); 

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
        //}
        pal_bright(3);
        pal_fade_to(3,0);
    #endif

    gameState = STATE_CREDITS;
    return;
}



CODE_BANK_POP()



#else
	
//THE ALBUM
//THE ALBUM
//THE ALBUM
//THE ALBUM


CODE_BANK_PUSH("XCD_BANK_01")

void setdefaultoptions();

void state_exit(){
}

void savefile_reset_check_loop(){
        setdefaultoptions();
}

void state_savefile_validate(){
    // startup
    
    mmc3_disable_irq();
    ppu_off();
    set_scroll_x(0);
    ppu_wait_nmi();
    pal_bright(0);



    // if save file version is incorrect //
    if ((SRAM_VALIDATE[2] != FLAG_SAVE_VER) && SRAM_VALIDATE[2] != 0x00) {
        savefile_reset_check_loop();
    }
    ppu_wait_nmi();

    // if header is wrong //
    if (SRAM_VALIDATE[0] != 0x13 || SRAM_VALIDATE[1] != 0x37 || SRAM_VALIDATE[2] != FLAG_SAVE_VER) {
        savefile_reset_check_loop();
    }
    ppu_wait_nmi();
    
    pal_bright(3);
    pal_fade_to(3,0);

    gameState = 0x00;
    return;
}



CODE_BANK_POP()

#endif