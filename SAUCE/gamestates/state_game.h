void state_game(){
	ppu_off();
    load_ground(0);

    mmc3_set_2kb_chr_bank_0(0);
    mmc3_set_2kb_chr_bank_1(2);
    mmc3_set_1kb_chr_bank_0(4);
    mmc3_set_1kb_chr_bank_1(5);
    mmc3_set_1kb_chr_bank_2(6);
    mmc3_set_1kb_chr_bank_3(7);
    
	reset_level();


    while (1){
        
        ppu_wait_nmi();
        music_update();
        

        pad = pad_poll(0); // read the first controller
		pad_new = get_pad_new(0);

        //if (pad_new & PAD_A) famistudio_sfx_play(sfx_click, 0);
        if (pad_new & PAD_B) gravity ^= 0x01;

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

        check_spr_objects();
        sprite_collide();

        oam_clear();
        draw_screen_R(); 
        draw_sprites();
        
        
        //gray_line();
        if (gameState != 0x02) return;
    }
}