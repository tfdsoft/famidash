#pragma code-name(push, "XCD_BANK_02")
#pragma data-name(push, "XCD_BANK_02") 
#pragma rodata-name(push, "XCD_BANK_02")

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
    set_scroll_x(0);
    ppu_wait_nmi();
    pal_bright(0);



    // if save file version is incorrect //
    if ((SRAM_VALIDATE[2] != FLAG_SAVE_VER) && SRAM_VALIDATE[2] != 0x00) {
        if (SRAM_VALIDATE[2] > FLAG_SAVE_VER) include_nested_dialog_string(dialogBox_newer);
        else include_nested_dialog_string(dialogBox_nolder);
        include_nested_dialog_string(dialogBox_wrongSaveFileVersion);
        draw_dialog_box(dialogBox_saveIssues);
        ppu_on_all();
        pal_fade_to(0,4);

        savefile_reset_check_loop();
    }

    // if header is wrong //
    if (SRAM_VALIDATE[0] != 0x13 || SRAM_VALIDATE[1] != 0x37 || SRAM_VALIDATE[2] != FLAG_SAVE_VER) {
        include_nested_dialog_string(dialogBox_saveFileMissingCorrupt);
        draw_dialog_box(dialogBox_saveIssues);
        ppu_on_all();
        pal_fade_to(0,4);
        
        savefile_reset_check_loop();
    }
    
    // if poweroff check is not zero //
    if (poweroffcheck) {
        ppu_off();
        pal_bright(0);
        include_nested_dialog_string(dialogBox_saveFileSafetyHeader);
        draw_dialog_box(dialogBox_pleasePressB);
        ppu_on_all();
        pal_fade_to(0,4);

        do {
            ppu_wait_nmi();
            pad_poll_both();
            if (pad_new[0]) break;

        } while (1);
    }
    pal_bright(3);
    pal_fade_to(3,0);
    gameState = 0x00;
    return;
}



void state_exit(){
    poweroffcheck = 0x00;

    pal_fade_to(4, 0);
    mmc3_disable_irq();
    // Disable SRAM write
	POKE(0xA001, 0xC0);
    ppu_off();

    famistudio_music_stop();
    music_update();

    include_nested_dialog_string(dialogBox_saveFileSafetyHeader);
    draw_dialog_box(dialogBox_itIsNowSafe);

    set_scroll_x(0);
    set_scroll_y(0);
    ppu_on_all();
    pal_fade_to(0, 4);
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