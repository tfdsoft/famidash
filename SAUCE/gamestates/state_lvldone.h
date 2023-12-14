void state_lvldone(){
    ppu_off();

    pal_bg((char *)paletteMenu);


    mmc3_tmp_prg_bank_1(0);
    vram_adr(NAMETABLE_A);
    vram_unrle(menunametable);

    vram_adr(NAMETABLE_C);
    vram_unrle(leveldone);
    mmc3_pop_prg_bank_1();

    scroll_y = 0xEF;
    set_scroll_x(0);
    set_scroll_y(scroll_y);

    mmc3_set_2kb_chr_bank_0(8);
    mmc3_set_2kb_chr_bank_1(10);
    mmc3_set_1kb_chr_bank_0(12);
    mmc3_set_1kb_chr_bank_1(13);
    mmc3_set_1kb_chr_bank_2(14);
    mmc3_set_1kb_chr_bank_3(15);

    

    ppu_on_all();

    pal_fade_to(0, 4);


    famistudio_sfx_play(sfx_level_complete, 0);

    
    for (tmp1 = 0; tmp1 < 255; ++tmp1) {
        ppu_wait_nmi();
        music_update();
    }
    for (tmp1 = 0; tmp1 < 7; ++tmp1) {
        ppu_wait_nmi();
        ppu_wait_nmi();
        scroll_y -= (0xf0 - scroll_y);
        set_scroll_y(scroll_y);
    }
    pal_col(0,0x17);
    for (tmp1 = 0; tmp1 < 8; ++tmp1) {
        ppu_wait_nmi();
        ppu_wait_nmi();
        scroll_y >>= 1;
        set_scroll_y(scroll_y);

    }


    
    while (1){
        ppu_wait_nmi();
        music_update();

    }
}