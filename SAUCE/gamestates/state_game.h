void state_game(){
	ppu_off();

    scroll_y = 0xEF;
    load_ground(0);

	init_rld(0);
    unrle_first_screen();

    famistudio_music_play(song_stereo_madness_foreverbound);

    ppu_on_all();

    gamemode = 0x01;
    while (1){
        
        ppu_wait_nmi();
        famistudio_update();
        oam_clear();

        pad = pad_poll(0); // read the first controller
		pad_new = get_pad_new(0);
    
        switch (gamemode) {
            case 0x01: cube_movement(); break;
        }

        
        
        oam_meta_spr(high_byte(player.x),high_byte(player.y)-1,Cube_0);
        draw_screen_R();
        gray_line();
    }
}