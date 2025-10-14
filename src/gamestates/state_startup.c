void state_startup() {
    ppu_off();

    set_prg_8000(32);
    vram_adr(0x0200);
    vram_copy(chr_font,0x600);
    vram_copy(chr_logo,0x600);

    vram_adr(0x2000);
    vram_unrle(nt_logo);

    ppu_on_all();
    pal_fade_to(0,4);

    //music_play(0);

    set_prg_a000(music_bank_1);
    famistudio_music_play(0);
    while(1){
        ppu_wait_nmi();
        set_prg_a000(music_bank_1);
        famistudio_update();
    }
}