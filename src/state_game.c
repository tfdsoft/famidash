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

    //u24 x_scroll = 0;
    //u16 y_scroll = 0;
    u8 y_offset = 0;

    // forwards is 0, backwards is nonzero
    s8 scroll_direction = 16;

    //u24 player_x = 0, player_y = 0;
    //u16 player_x_speed = 0, player_y_speed = 0;

    // load the global stuff
    se_vram_address(0);
    se_vram_donut_decompress(chr_tiles_global,chr_bank_1);

    // clear nametables
    se_vram_address(0x2000);
    se_memory_fill((void*)0x2007,0,0x1000);

    set_prg_a000(level_bank_0);
    load_metatiles(32,mt_default_blocks,32);
    level_rle_init(lvl_test_header);

    level_rle_fetch_columns(16);
    disable_nmi();
    for(char i=0;i<16;i++){
        level_draw_metatile_column(i<<1, 0);
        se_flush_vram_buffer();
    }
    enable_nmi();
    se_wait_frames(30);

    se_set_palette_background(pal_game);
    se_set_palette_sprites(pal_game);
    se_set_palette_brightness_all(4);

    se_turn_on_rendering();
    

    
    Player.pos.x.word = 0x0080;

    while(1){
        se_wait_vsync();
        se_clear_sprites();


        if(joypad1.right) scroll_direction = 16;
        if(joypad1.left) scroll_direction = -1;
        y_offset = (Camera.y.word >> 3);
        if(((u8)((Camera.x.word>>4) + scroll_direction+1)) != lvl_rle_x_offset){
            if(!(scroll_direction & 0x80)) {
                // scrolling right
                level_rle_fetch_columns(1);
                level_draw_metatile_column(-1+(lvl_rle_x_offset<<1), y_offset);
            } else {
                // scrolling left
                level_rle_fetch_columns(-1);
                level_draw_metatile_column((lvl_rle_x_offset<<1), y_offset);
            }
        }

        //player_y_speed += phys_gravity[0];
        //player_y += player_y_speed;
        //se_draw_sprite(player_x,(player_y>>8),0x04,0);
        //se_draw_sprite(8+player_x,(player_y>>8),0x06,0);

        move_player(&Player);

        se_draw_sprite(
            (Player.pos.x.word - Camera.x.word),
            (Player.pos.y.word - Camera.y.word),
            4,
            0
        );
        se_draw_sprite(
            8+(Player.pos.x.word - Camera.x.word),
            (Player.pos.y.word - Camera.y.word),
            6,
            0
        );


        se_set_scroll(Camera.x.word,Camera.y.word);
        se_gray_line();
        //se_one_vram_buffer_repeat_vertical(
        //    0,
        //    30,
        //    nametable_address_A(28,0)
        //);
        
        



        if(joypad1.press_b) {gamestate = 0xff; break;}
    }
}