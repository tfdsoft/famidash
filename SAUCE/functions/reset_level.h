extern unsigned char scroll_count;

void reset_level(void) {
    unsigned char i;
    famistudio_music_stop();
        coins = 0;

    if (cube_data & 1) {
        famistudio_sfx_play(sfx_death, 0);
        tmp1 = 0;
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
    unrle_first_screen();

    // load the starting ground and bg color
    tmp2 = (level_list[level][3] & 0x3f);
    pal_col(0, tmp2);
    if (tmp2-0x10 & 0xC0) pal_col(1, 0x0f);
    else pal_col(1, (tmp2-0x10));

    tmp2 = (level_list[level][4] & 0x3f);
    pal_col(6, tmp2);
    if (tmp2-0x10 & 0xC0) pal_col(5, 0x0f);
    else pal_col(5, (tmp2-0x10));

    init_sprites();
    player.x = 0x0000;
    player.y = 0xb000;
    gravity = 0x00;
    player.vel_x = 0;
    player.vel_y = 0;
    invincible_counter = 8;
    cube_data = 0;
    ppu_on_all();
    pal_fade_to(0,4);
    music_play(song);
    
}