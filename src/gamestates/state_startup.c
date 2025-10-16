//__attribute__((section(".prg_rom_"STR(extra_code_bank)),retain)) 
void state_startup() {
    ppu_off();

    set_prg_8000(chr_bank_0);
    vram_adr(0x0200);
    vram_copy(chr_font,0x600);
    vram_copy(chr_logo,0x600);

    set_prg_8000(nametable_bank_0);
    vram_adr(0x2000);
    vram_unrle(nt_logo);

    ppu_on_all();
    pal_fade_to(0,4);


    for(char stall=8; stall>0; stall--){
        ppu_wait_nmi();
    }

    sfx_play(1,0);
    //automatic_fs_updates = 1;
    
    for(char stall=90; stall>0; stall--){
        ppu_wait_nmi();
        music_update();

        pal_bright(4);
        if((stall >= 87)) pal_bright(3);
        if((stall >= 80) && (stall < 83)) pal_bright(3);
    }

    pal_fade_to(4,0);
    ppu_off();

    set_prg_8000(nametable_bank_0);
    vram_adr(0x2000);
    vram_unrle(nt_warning);

    pal_col(0,0x11);
    pal_col(1,0x0f);

    ppu_on_all();
    pal_fade_to(0,4);

    song = 1;
    music_play(song);
    
    while(1){
        ppu_wait_nmi();

        ppu_grayscale(1);
        //pad_poll(0);
        
        music_update();

        if((player1_pressed & PAD_LEFT)) music_play(--song);
        
        if((player1_pressed & PAD_RIGHT)) music_play(++song);
        

        //if(player1_pressed & PAD_A) sfx_play(1,0);
        //if(player1_pressed & PAD_B) sfx_play(0,0);
            
        //if(player1_pressed){}
        ppu_grayscale(0);
    }
}