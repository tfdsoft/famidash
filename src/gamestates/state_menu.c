



void state_menu() {
    ppu_off();

    set_prg_8000(chr_bank_0);
    vram_adr(0x0200);
    vram_copy(chr_font,0x600);
    vram_copy(chr_logo,0x600);

    set_prg_8000(nametable_bank_0);
    vram_adr(0x2000);
    vram_unrle(nt_logo);

    pal_bg(test_palette);

    ppu_on_all();
    pal_fade_to(0,4);

    music_play(0);

    while(1){
        ppu_wait_nmi();
        music_update();




    }
}