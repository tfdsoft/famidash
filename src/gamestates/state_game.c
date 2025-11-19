putinbank(fixed_lo.game)
void state_game(){

    // PAGE 0 (global stuff)
    set_bg_chr_page(0);
    donut_decompress_vram(chr_tiles_global,chr_bank_1); //1k
    donut_decompress_vram(chr_g[ground_set],chr_bank_3); //1k
    // TODO: pause menu graphics in page 0

    // PAGE 1 (tiles)
    vram_adr(0);
    set_bg_chr_page(1);
    donut_decompress_vram(chr_tiles_grid,chr_bank_1); //256b
    donut_decompress_vram(chr_tiles_grid,chr_bank_1); //256b
    donut_decompress_vram(chr_tiles_grid,chr_bank_1); //256b
    donut_decompress_vram(chr_tiles_grid,chr_bank_1); //256b



    if(loaded_bg_set != background_set){
        donut_decompress_vram(chr_bg[background_set], chr_bank_2);
        vram_generate_parallax(background_set);
        loaded_bg_set = background_set;
    }

    // CLEAR NAMETABLES
    vram_adr(0x2000);
    vram_fill(0, 0x1000);


    set_bg_chr_page(0);


    ppu_on_all();
    pal_fade_to(0,4);

    automatic_fs_updates = 0;
    while(1){
        ppu_wait_nmi();
        ppu_emphasis(0b111);
        music_update();
        oam_clear();

        ppu_emphasis(0b000);

        if(player1_pressed & PAD_B){
            gamestate = return_gamestate;
            famistudio_music_stop();
            sfx_play(sfx_quitsound_01,0);
            automatic_fs_updates = 1;
            pal_fade_to(4,0);
            break;
        }
    }
}