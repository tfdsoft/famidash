/*
	Calls the movement routine of the current gamemode
	Implemented in asm
*/
void __fastcall__ movement(void);
void __fastcall__ movement2(void);

void x_movement_coll() {
	// no L/R collision required, since that is accounted for with the death script
	if (high_byte(currplayer_x) > 0x10) {
		bg_coll_floor_spikes(); // check for spikes at the left of the player (fixes standing on spikes)
		if (bg_coll_R()) {
			if (!platformer) {cube_data[currplayer] |= 0x01; }
			else {currplayer_vel_x = 0; }
		}
	}	
}

extern unsigned char* PARALLAX_CHR;
unsigned char END_LEVEL_TIMER;

void state_game(){
	ppu_off();

//	twoplayer = 1;

//	mini = 1;
    pal_bg((char *)paletteDefault);
    pal_spr((char *)paletteDefaultSP);

    load_ground(0);

	mmc3_set_8kb_chr(0);
    mmc3_set_1kb_chr_bank_2(GET_BANK(PARALLAX_CHR));
    
	currplayer = 0;
	reset_level();

    END_LEVEL_TIMER = 0;

	kandoframecnt = 0;

    while (1) {
	    
	    pal_col(0x1F,color2);
	    pal_col(0x1D,color3);
	    pal_col(0x1E,color1);
		// {	// done in reset_level and after storing player 1
		// 	currplayer_x = player_x[0];
		// 	currplayer_y = player_y[0];
		// 	currplayer_vel_x = player_vel_x[0];
		// 	currplayer_vel_y = player_vel_y[0];
		// 	currplayer_gravity = player_gravity[0];
		// }

		kandoframecnt++;
        ppu_wait_nmi();
        mmc3_set_1kb_chr_bank_0((parallax_scroll_x & 1) * 8 + 0);
        mmc3_set_1kb_chr_bank_1((parallax_scroll_x & 1) * 8 + 1);
        mmc3_set_1kb_chr_bank_2(parallax_scroll_x + GET_BANK(PARALLAX_CHR));
        mmc3_set_1kb_chr_bank_3((parallax_scroll_x & 1) * 8 + 3);
        music_update();
        

        pad[0] = pad_poll(0); // read the first controller
		pad_new[0] = get_pad_new(0);

		if (platformer) twoplayer = 0;

		if (oneptwoplayer && twoplayer) {
			pad[1] = pad[0] << 4; // read the second controller
			pad_new[1] = pad_new[0] << 4;
			dual = 1;
		}
		else if (twoplayer) {
			pad[1] = pad_poll(1); // read the second controller
			pad_new[1] = get_pad_new(1);
			dual = 1;
		}
		
		if (jumpsound) {
			if (pad_new[0] & PAD_A) {
				sfx_play(sfx_click, 0);
			}
		}

		if (pad[controllingplayer] & PAD_SELECT && pad_new[controllingplayer] & PAD_UP) currplayer_gravity ^= 0x01;


		if ((pad_new[controllingplayer] & PAD_B) && PRACTICE_ENABLED) {
			// player_gravity[currplayer] ^= 0x01;			//DEBUG GRAVITY
			practice_player_x[0] = player_x[0];
			long_temp_x = high_byte(player_x[0]);
			practice_player_x[1] = player_x[1];
			practice_player_y[0] = player_y[0];
			practice_player_y[1] = player_y[1];
			practice_player_vel_x[0] = player_vel_x[0];
			practice_player_vel_x[1] = player_vel_x[1];
			practice_player_vel_y[0] = player_vel_y[0];
			practice_player_vel_y[1] = player_vel_y[1];
			practice_player_gravity[0] = player_gravity[0];
			practice_player_gravity[1] = player_gravity[1];
			practice_player_gamemode = gamemode;
			practice_mini = mini;
			practice_dual = dual;
			practice_speed = speed;
			practice_scroll_x = scroll_x;
			practice_scroll_y = scroll_y;
			memcpy(practice_famistudio_state, famistudio_state, sizeof(practice_famistudio_state));
			// practice_parallax_scroll_column = parallax_scroll_column;
			// practice_parallax_scroll_column_start = parallax_scroll_column_start;
			has_practice_point = 1;
		}

		if (pad_new[0] & PAD_START) {
			pad_new[0] = 0;
			famistudio_music_pause(1);
			famistudio_update();
			// ppu_off();
			// mmc3_set_8kb_chr(16);
			// vram_adr(NAMETABLE_B);
			// vram_unrle(pausescreen); 	
			ppu_on_all();
			while (!(pad_new[0] & PAD_START)) {
				// ppu_wait_nmi();
				pad[0] = pad_poll(0); // read the second controller
				pad_new[0] = get_pad_new(0);	
				if (pad_new[0] & PAD_SELECT) { gameState = 1; 
					sfx_play(sfx_exit_level,0);
					music_update();
					return;
				}
			}
			famistudio_music_pause(0);
			// ppu_off();
			// mmc3_set_8kb_chr(0);
			// ppu_on_all();
			// famistudio_update();
		}
        if (pad_new[0] & PAD_SELECT) { DEBUG_MODE = !DEBUG_MODE; cube_data[0] &= 2; cube_data[1] &= 2; }

		if (pad_new[0] & PAD_DOWN) {
			mini ^= 1;
		}

        if (pad[0] & PAD_SELECT) {
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
		
		mmc3_set_prg_bank_1(GET_BANK(x_movement));
		x_movement();
	
		x_movement_coll();

		mmc3_set_prg_bank_1(GET_BANK(movement));
		movement();


		if (!DEBUG_MODE && !invincible_counter) {
			if ((dual && (kandoframecnt & 0x01)) || !dual)
				bg_coll_death();
		}
		if (invincible_counter) invincible_counter--;

		if (DEBUG_MODE) color_emphasis(COL_EMP_RED);

		mmc3_set_prg_bank_1(GET_BANK(do_the_scroll_thing));
		do_the_scroll_thing(); 

		check_spr_objects();

		if (!DEBUG_MODE) {
			if (cube_data[0] == 1) reset_level();
			if (cube_data[1] == 1) reset_level();
		}

		mmc3_set_prg_bank_1(GET_BANK(sprite_collide));
		sprite_collide();
		{	// always store it back for practice mode
			player_x[0] = currplayer_x;
			player_y[0] = currplayer_y;
			player_vel_x[0] = currplayer_vel_x;
			player_vel_y[0] = currplayer_vel_y;
			player_gravity[0] = currplayer_gravity;
		}


		if (dual) { 
			currplayer = 1;					//take focus

			if (twoplayer) controllingplayer = 1;		//take controls
			if (dual && platformer && !twoplayer) { player_x[1] = player_x[0]; player_vel_x[1] = player_vel_x[0]; }
			else if (dual && !platformer) { player_x[1] = player_x[0]; player_vel_x[1] = player_vel_x[0]; }

			{	
				currplayer_x = player_x[1];
				currplayer_y = player_y[1];
				currplayer_vel_x = player_vel_x[1];
				currplayer_vel_y = player_vel_y[1];
				currplayer_gravity = player_gravity[1];
			}

			if (pad_new[controllingplayer] & PAD_UP) currplayer_gravity ^= 0x01;			//DEBUG GRAVITY

			mmc3_set_prg_bank_1(GET_BANK(movement));
			movement();

			if (!DEBUG_MODE) {
				if (!invincible_counter && !(kandoframecnt & 0x01)) bg_coll_death();
			}

			mmc3_set_prg_bank_1(GET_BANK(do_the_scroll_thing2));
			// x_movement();
			x_movement_coll();

			do_the_scroll_thing2();

			mmc3_set_prg_bank_1(GET_BANK(sprite_collide));
			sprite_collide();

			currplayer = 0;					//give back focus
			if (twoplayer) controllingplayer = 0;		//give back controls
			{
				player_x[1] = currplayer_x;
				player_y[1] = currplayer_y;
				player_vel_x[1] = currplayer_vel_x;
				player_vel_y[1] = currplayer_vel_y;
				player_gravity[1] = currplayer_gravity;

				currplayer_x = player_x[0];
				currplayer_y = player_y[0];
				currplayer_vel_x = player_vel_x[0];
				currplayer_vel_y = player_vel_y[0];
				currplayer_gravity = player_gravity[0];
			}
		}
		// mmc3_set_prg_bank_1(GET_BANK(check_spr_objects));	// it's in a const bank
        check_spr_objects();

        if (DEBUG_MODE) color_emphasis(COL_EMP_GREEN);
  
  		oam_clear();

		// mmc3_set_prg_bank_1(GET_BANK(draw_screen_R)); // it's in a const bank
        draw_screen_R(); 
		mmc3_set_prg_bank_1(GET_BANK(draw_sprites));	
        draw_sprites();
        
        color_emphasis(0);
        
        
        // if (DEBUG_MODE) gray_line();
        if (gameState != 0x02) return;
    }
}

