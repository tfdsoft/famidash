void state_game(){
	ppu_off();

    scroll_y = 0xEF;
    load_ground(0);


	init_rld(level);
    unrle_first_screen();

    music_play(song);   // Song set by init_rld

    ppu_on_all();

    while (1){
        
        ppu_wait_nmi();
        music_update();
        

        pad = pad_poll(0); // read the first controller
		pad_new = get_pad_new(0);

        if (pad_new & PAD_A) famistudio_sfx_play(sfx_click, 0);


        x_movement();
        switch (gamemode) {
            case 0x01: cube_movement(); break;
            case 0x02: ship_movement(); break;
            case 0x04: break;
            case 0x08: break;
            default: break;
        } 
        bg_coll_death(); 
        do_the_scroll_thing(); 

        oam_clear();
        draw_sprites();
        draw_screen_R(); 
        
        gray_line();
    }
}