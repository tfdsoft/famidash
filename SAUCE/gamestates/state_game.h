/*
	Calls the movement routine of the current gamemode
	Implemented in asm
*/
void __fastcall__ movement(void);

void state_game(){
	ppu_off();

    pal_bg((char *)paletteDefault);

    load_ground(0);

	mmc3_set_8kb_chr(0);
    mmc3_set_1kb_chr_bank_2(16);
    
	reset_level();


    while (1){
        
        ppu_wait_nmi();
        mmc3_set_1kb_chr_bank_2(parallax_scroll_x + 16);
        music_update();
        

        pad = pad_poll(0); // read the first controller
		pad_new = get_pad_new(0);

        //if (pad_new & PAD_A) famistudio_sfx_play(sfx_click, 0);
        if (pad_new & PAD_B) gravity ^= 0x01;			//DEBUG GRAVITY

        x_movement();
        movement();
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