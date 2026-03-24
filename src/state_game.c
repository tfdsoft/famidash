banked(fixed.data) const u8 pal_game[] = {
    0x11, 0x0f, 0x01, 0x30,
    0x0f, 0x00, 0x10, 0x20,
    0x0f, 0x00, 0x10, 0x20,
    0x0f, 0x00, 0x10, 0x20,
};


banked(fixed.func) void level_load_assets(struct Level passthru){
    set_prg_a000(level_header_bank);

    active_lvl = passthru;

    se_memory_fill(sram_buffer, 0, 0x400);

    // load default blocks
    se_vram_address(0);
    se_vram_donut_decompress(chr_tiles_global,chr_bank_1);
    load_metatiles(mt_default_blocks,16,0,48);

    for(u8 i=0; i<4; i++){
        se_vram_address((0x400 + (i<<8)));
        if(active_lvl.tileset.blocks[i]){
            se_vram_donut_decompress(active_lvl.tileset.blocks[i],chr_bank_1);
        }
    }
    for(u8 i=0; i<4; i++){
        if(active_lvl.tileset.metatiles[i]){
            load_metatiles(
                active_lvl.tileset.metatiles[i],
                (0x40+(i<<4)),
                (i<<4),
                16
            );
        }
    }

    se_vram_address(0xc00);
    se_vram_donut_decompress(chr_ground_0,chr_bank_3);
}

banked(fixed.func) void state_game() {
    se_play_sample((pcm_playsound_01+0x2000),sample_bank_2,1);
    __asm__("cli");

    //u24 x_scroll = 0;
    //u16 y_scroll = 0;
    u8 y_offset = 0;

    // forwards is 0, backwards is nonzero
    s8 scroll_direction = 16;

    //u24 player_x = 0, player_y = 0;
    //u16 player_x_speed = 0, player_y_speed = 0;

    // load the global stuff
    

    // clear nametables
    se_vram_address(0x2000);
    se_memory_fill((void*)0x2007,0,0x1000);
    
    // clear collision map
    se_memory_fill((void*)collision_map_0,0,720); 

    level_load_assets(lvl_test_header);
    level_rle_init(lvl_test_header);
    level_generate_ground_metatiles();

    Player.pos.x.word = 0;
    Player.pos.y.word = (active_lvl.height<<4)-0x10;
    Camera.x.word = 0;
    Camera.y.word = (active_lvl.height<<4)-0xc0;

    se_set_palette_background(pal_game);
    se_set_palette_sprites(pal_game);
    se_set_palette_brightness_all(4);

    se_post_nmi_ptr = nofunction;
    se_turn_on_rendering();
    se_music_play(song_desert_city);
    

    while(1){
        se_wait_vsync();
        se_clear_sprites();
        se_music_update();

        move_player(&Player);

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

        u16 tmp = (Camera.y.word + ((Camera.y.word / 0xf0)<<4));
        
        se_set_scroll(Camera.x.word,tmp);
        se_gray_line();
        //se_one_vram_buffer_repeat_vertical(
        //    0,
        //    30,
        //    nametable_address_A(28,0)
        //);
        
        



        if(joypad1.press_b) {gamestate = 0xff; break;}
    }

    se_post_nmi_ptr = se_music_update;
}