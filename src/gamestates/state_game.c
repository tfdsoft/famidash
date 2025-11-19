putinbank(fixed_lo.game)
void state_game(){

    // PAGE 0 (global stuff)
    set_bg_chr_page(0);
    donut_decompress_vram(chr_tiles_global,chr_bank_1); //1k
    donut_decompress_vram(chr_g[ground_set],chr_bank_3); //1k

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

    ppu_on_all();
    pal_fade_to(0,4);

    while(1){
        ppu_wait_nmi();
    }
}