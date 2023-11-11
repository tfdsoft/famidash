void state_game(){
	ppu_off();

    famistudio_music_play(song_stereo_madness_foreverbound);

	init_rld(0);
    unrle_first_screen();


    ppu_on_all();

    while (1){
        
        ppu_wait_nmi();
        famistudio_update();

        pad = pad_poll(0); // read the first controller
		pad_new = get_pad_new(0);
    
        switch (gamemode) {
            case 0x01: break;
        }

        //cube_movement();

        do_the_scroll_thing();
        draw_screen_R();
        gray_line();
    }
}