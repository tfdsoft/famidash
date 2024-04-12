/*
	Calls the movement routine of the current gamemode
	Implemented in asm
*/
void __fastcall__ movement(void);
void __fastcall__ movement2(void);

extern unsigned char* PARALLAX_CHR;
unsigned char END_LEVEL_TIMER;

void state_game(){
	ppu_off();



//	mini = 1;
    pal_bg((char *)paletteDefault);
    pal_spr((char *)paletteDefaultSP);

    load_ground(0);

	mmc3_set_8kb_chr(0);
    mmc3_set_1kb_chr_bank_2(GET_BANK(PARALLAX_CHR));
    
	reset_level();

    END_LEVEL_TIMER = 0;

    while (1) {
        
        ppu_wait_nmi();
        mmc3_set_1kb_chr_bank_0((parallax_scroll_x & 1) * 8 + 0);
        mmc3_set_1kb_chr_bank_1((parallax_scroll_x & 1) * 8 + 1);
        mmc3_set_1kb_chr_bank_2(parallax_scroll_x + GET_BANK(PARALLAX_CHR));
        music_update();
        

        pad = pad_poll(0); // read the first controller
	pad_new = get_pad_new(0);

	if (twoplayer) {
		pad2 = pad_poll(1); // read the second controller
		pad_new2 = get_pad_new(1);
		dual = 1;
	}
        //if (pad_new & PAD_A) famistudio_sfx_play(sfx_click, 0);

	

        if (pad_new & PAD_B) gravity ^= 0x01;			//DEBUG GRAVITY

        if (pad_new & PAD_SELECT) DEBUG_MODE = !DEBUG_MODE;

        if (pad & PAD_SELECT) {
            if (++END_LEVEL_TIMER > 60) {
                END_LEVEL_TIMER = 0;
                gameState = 3;
                DEBUG_MODE = 0;
                famistudio_music_stop();
            }
        } else {
            END_LEVEL_TIMER = 0;
        }

        if (DEBUG_MODE) color_emphasis(COL_EMP_BLUE);
	mmc3_set_prg_bank_1(0);
        x_movement();
	
	mmc3_set_prg_bank_1(GET_BANK(movement));	
        movement();


        if (!invincible_counter) bg_coll_death();
        else invincible_counter--;
        

        if (DEBUG_MODE) color_emphasis(COL_EMP_RED);
	mmc3_set_prg_bank_1(0);
        do_the_scroll_thing(); 

	mmc3_set_prg_bank_1(0);
        check_spr_objects();

        sprite_collide();
	if (dual) { 
		if (twoplayer) gravity ^= 1;
		mmc3_set_prg_bank_1(GET_BANK(movement));
		movement2();
		if (!invincible_counter)  bg_coll_death();
		mmc3_set_prg_bank_1(0);
		x_movement2();
		sprite_collide2();
		if (twoplayer) gravity ^= 1;
	}
        if (DEBUG_MODE) color_emphasis(COL_EMP_GREEN);
        oam_clear();

        draw_screen_R(); 
	mmc3_set_prg_bank_1(0x14);	
        draw_sprites();
        
        color_emphasis(0);
        
        
         if (DEBUG_MODE) gray_line();
        if (gameState != 0x02) return;
    }
}