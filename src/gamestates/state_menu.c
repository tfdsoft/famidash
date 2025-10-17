


__attribute__((section(".prg_rom_"STR(extra_code_bank)".110")))
void state_menu() {
    ppu_off();

    set_prg_8000(chr_bank_0);
    vram_adr(0x0200);
    vram_copy(chr_font,0x600);
    vram_copy(chr_logo,0x600);

    set_prg_8000(nametable_bank_0);
    vram_adr(0x2000);
    vram_unrle(nt_logo);

    //pal_bg();

    ppu_on_all();
    pal_fade_to(0,4);

    music_play(0);


    //automatic_fs_updates=1;
    while(1){
        ppu_wait_nmi();
        //music_update();



        //continue;
    }
}