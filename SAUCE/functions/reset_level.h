extern unsigned char scroll_count;

void reset_level(void) {
    // unsigned char i;
    famistudio_music_stop();
    coins = 0;

    if (!DEBUG_MODE && (cube_data[0] & 1 || cube_data[1] & 1)) {
        sfx_play(sfx_death, 0);
        tmp1 = 0;
	attempts++;
        while (tmp1 < 30){
            ppu_wait_nmi();
            music_update();
            ++tmp1;
            //gray_line();
        }
    }
    pal_fade_to(4,0);
    oam_clear();
    ppu_off(); // reset the level when you get to this point, and change this later
    scroll_x = 0;
    scroll_count = 0;
    set_scroll_x(scroll_x);
    scroll_y = 0xEF;
    set_scroll_y(scroll_y);
    init_rld(level);

    if (!platformer) {player_x[0] = 0x0000;    player_x[1] = 0x0000; currplayer_x = 0x0000;}
    else {player_x[0] = 0x1110;    player_x[1] = 0x1110; currplayer_x = 0x1110;}
    
    player_y[0] = 0xb000;
    player_y[1] = 0xb000;
    currplayer_y = 0xb000;

    player_gravity[0] = 0x00;
    if (twoplayer) player_gravity[1] = 0x00;
    else player_gravity[1] = 0x01;

    currplayer_gravity = player_gravity[currplayer];

    mini = 0x00;
    dual = 0x00;
    if (twoplayer) dual = 1;
    player_vel_x[0] = 0;
    player_vel_y[0] = 0;
    player_vel_x[1] = 0;
    player_vel_y[1] = 0;
    currplayer_vel_x = 0;
    currplayer_vel_y = 0;
    if (!has_practice_point)    invincible_counter = 8;
    cube_data[0] = 0;
    cube_data[1] = 0;
    
    unrle_first_screen();

    ppu_on_all();
    pal_fade_to(0,4);
    if (!has_practice_point) {
        music_play(song);
    }
    
}