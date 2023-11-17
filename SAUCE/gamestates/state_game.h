void state_game(){
	ppu_off();

    scroll_y = 0xEF;
    load_ground(0);

	init_rld(level);
    unrle_first_screen();

    famistudio_music_play(song_custom_ultimatedestruction);

    ppu_on_all();

    gamemode = 0x01;
    while (1){
        
        ppu_wait_nmi();
        famistudio_update();
        

        pad = pad_poll(0); // read the first controller
		pad_new = get_pad_new(0);

        if (pad_new & PAD_A) famistudio_sfx_play(sfx_click, 0);

        switch (gamemode) {
            case 0x01: cube_movement(); break;
            default: break;
        }
        oam_clear();
        draw_sprites();
        draw_screen_R();
        gray_line();
    }
}