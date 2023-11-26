void state_game(){
	ppu_off();
    level = 0x00;
    load_ground(0);
	reset_level();

    while (1){
        
        ppu_wait_nmi();
        music_update();
        

        pad = pad_poll(0); // read the first controller
		pad_new = get_pad_new(0);

        if (pad_new & PAD_A) famistudio_sfx_play(sfx_click, 0);
        if (pad_new & PAD_B) gravity = gravity^0x01;

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

        sprite_collide();

        oam_clear();
        draw_sprites();
        draw_screen_R(); 
        
        gray_line();
    }
}