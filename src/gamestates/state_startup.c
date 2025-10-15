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

    music_play(0);
    famistudio_music_stop();

    sfx_play(1,0);
    
    //set_prg_a000(36); 
    //famistudio_init(1,0xa000);
    //famistudio_music_play(0);
    for(char stall=8; stall>0; stall--){
        ppu_wait_nmi();
    }

    for(char stall=90; stall>0; stall--){
        ppu_wait_nmi();
        music_update();

        pal_bright(4);
        if((stall >= 87)) pal_bright(2);
        if((stall >= 80) && (stall < 83)) pal_bright(2);
    }

    music_play(song);

    while(1){
        ppu_wait_nmi();

        ppu_grayscale(1);
        pad_poll(0);
        //get_pad_new();

        
        music_update();
        

        if((PAD_STATET[0] & PAD_LEFT)){
            music_play(--song);
        }
        if((PAD_STATET[0] & PAD_RIGHT)){
            music_play(++song);
        }

        if(PAD_STATET[0] & PAD_A){
            sfx_play(1,0);
        }
        if(PAD_STATET[0] & PAD_B){
            
        }
        ppu_grayscale(0);
    }
}