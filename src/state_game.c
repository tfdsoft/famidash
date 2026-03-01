banked(fixed.data) const u8 pal_game[] = {
    0x11, 0x0f, 0x01, 0x30,
    0x0f, 0x00, 0x10, 0x20,
    0x0f, 0x00, 0x10, 0x20,
    0x0f, 0x00, 0x10, 0x20,
};


banked(fixed.func) void state_game() {
    se_play_sample((pcm_playsound_01+0x2000),sample_bank_2,1);
    __asm__("cli");

    se_music_play(song_desert_city);

    u24 x_scroll = 0;
    u16 y_scroll = 0;
    u8 y_offset = 0;

    u24 player_x = 0, player_y = 0;
    u16 player_x_speed = 0, player_y_speed = 0;

    // load the global stuff
    se_vram_address(0);
    se_vram_donut_decompress(chr_tiles_global,chr_bank_1);

    // clear nametables
    se_vram_address(0x2000);
    se_memory_fill((void*)0x2007,0,0x1000);

    set_prg_a000(level_bank_0);
    load_metatiles(0,mt_default_blocks,16);
    level_rle_init(lvl_test_header);

    se_set_palette_background(pal_game);
    se_set_palette_sprites(pal_game);
    se_set_palette_brightness_all(4);

    se_turn_on_rendering();
    level_rle_fetch_columns(16,0);
    for(char i=0;i<16;i++){
        level_draw_metatile_column(i<<1, 0);
        se_wait_vsync();
    }

    


    while(1){
        se_wait_vsync();
        se_clear_sprites();

        if(joypad1.up) y_scroll--;
        if(joypad1.down) y_scroll++;
        //if(joypad1.left) se_scroll_x-=2;
        if(joypad1.right) x_scroll += phys_speed[1];

        se_set_scroll((x_scroll>>8),y_scroll);



        y_offset = (y_scroll >> 3);

        if((1+(se_scroll_x>>4)&0x0f) != lvl_rle_x_offset){
            level_rle_fetch_columns(1,0);
            level_draw_metatile_column(32+(se_scroll_x>>3), y_offset);
        }

        player_y_speed += phys_gravity[0];
        player_y += player_y_speed;
        se_draw_sprite(player_x,(player_y>>8),0x04,0);
        se_draw_sprite(8+player_x,(player_y>>8),0x06,0);


        

        se_gray_line();
        //se_one_vram_buffer_repeat_vertical(
        //    0,
        //    30,
        //    nametable_address_A(28,0)
        //);
        
        



        if(joypad1.press_b) {gamestate = 0xff; break;}
    }
}