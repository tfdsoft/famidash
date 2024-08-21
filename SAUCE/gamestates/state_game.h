/*
	Calls the movement routine of the current gamemode
	Implemented in asm
*/
void set_tile_banks();
void __fastcall__ movement(void);
void __fastcall__ movement2(void);

const uint8_t BG_Table[]={
	0x11,
	0x12,
	0x13,
	0x14,
	0x15,
	0x16,
	0x17,
	0x18,
	0x19,
	0x1A,
	0x1B,
	0x1C
};

const uint8_t G_Table[]={
	0x21,
	0x22,
	0x23,
	0x24,
	0x25,
	0x26,
	0x27,
	0x28,
	0x29,
	0x2A,
	0x2B,
	0x2C
};

#define stereo_madness  
#define back_on_track  1
#define polargeist  2
#define dryout  3
#define base_after_base  4
#define cant_let_go  5
#define jumper  6
#define time_machine  7
#define cycles  8
#define xstep  9
#define clutterfunk  0x0A
#define theory_of_everything  0x0B
#define electroman_adventures  0x0C
#define decode  0x0D
#define test  0x0E
#define test2  0x0F
#define test3  0x10
#define test4  0X11

void runthecolls();
void set_player_banks();
void gameboy_check();

void x_movement_coll() {
	if (slope_type && !slope_frames && gamemode != 6) {
	// we we're on an slope and now we aren't, so push the player upwards a bit
		switch (slope_type & 0x07) {
			case SLOPE_22DEG_DOWN:
			case SLOPE_22DEG_UP:
				tmp5 = currplayer_vel_x >> 2;
				break;
			case SLOPE_45DEG_DOWN:
			case SLOPE_45DEG_UP:
				tmp5 = currplayer_vel_x >> 1;
				break;
			case SLOPE_66DEG_DOWN:
			case SLOPE_66DEG_UP:
				tmp5 = (currplayer_vel_x >> 1); 
				tmp5 = (tmp5 >> 1) + tmp5;	
		}
		if (slope_type & 1) {
			if (currplayer_gravity) {
				currplayer_vel_y = tmp5 + 0x200;
			} else {
				currplayer_vel_y = (tmp5 + 0x200)^0xFFFF;
			}
		}
	}
	if (slope_frames) {
		slope_frames -= 1;
	}
	
	Generic.x = high_byte(currplayer_x);
	Generic.y = high_byte(currplayer_y);
	// no L/R collision required, since that is accounted for with the death script
	if (high_byte(currplayer_x) > 0x10) {
		bg_coll_floor_spikes(); // check for spikes at the left of the player (fixes standing on spikes)
		if (bg_coll_R()) {
			if (!(options & platformer)) {uint8_store(cube_data, currplayer, cube_data[currplayer] | 0x01);}
			else {currplayer_vel_x = 0; }
		}
	}	
}

extern unsigned char* PARALLAX_CHR;
unsigned char END_LEVEL_TIMER;




void state_game(){
	if (level == decode || level == test || level == test4) no_parallax = 1;
	else no_parallax = 0;

	mmc3_disable_irq();
	//no_parallax = 0;
	
	outline_color = 0x30;		//hwhite

	lastgcolortype = 0xFF;		//set these 2 to pull the initial colors for a level and not pull future color changes until a new practice point is set
	lastbgcolortype = 0xFF;

	set_tile_banks();
	
	ppu_off();

	pal_bg(paletteDefault);
	pal_spr(paletteDefaultSP);

	crossPRGBankJump8(load_ground,0);

	currplayer = 0;
	current_transition_timer_length = 0;
	reset_level();
	
	END_LEVEL_TIMER = 0;
	songtimer = 0;
	kandoframecnt = 0;
	
	iconbank = iconBankTable[icon];

	pal_col(0x0A,0x0F);   //palette 2 set to 0x0F for mountains
	pal_col(0x0B,color1);   //palette 2 set to player color

	for (tmp2 = 0; tmp2 < 9; tmp2++) {
		player_old_posy[tmp2] = 0;
	}
	
	switch (discomode) {
		default: 
			pal_col(0x1D,color3);
			pal_col(0x1E,color1);
			pal_col(0x1F,color2);
			break;
		case 0x01: discorefreshrate = 0x3F; break;
		case 0x02: discorefreshrate = 0x1F; break;
		case 0x04: discorefreshrate = 0x0F; break;
		case 0x08: discorefreshrate = 0x07; break;
		case 0x10: discorefreshrate = 0x03; break;
		
	};
	
	

    while (1) {
		
		if (kandokidshack2 && !(kandoframecnt & 0x0F)) { icon == MAX_ICONS-1 ? icon = 0 : icon++; 	iconbank = iconBankTable[icon]; }  //nothing to see here

		pal_col(3,outline_color);	//set new outline color persistently
		pal_col(7,outline_color);


		if ((kandoframecnt & 0x1F) == 0x10 ) mmc3_set_2kb_chr_bank_1(DECOTYPE[level] + 2);		//DECO
		else if ((kandoframecnt & 0x1F) == 0x00) mmc3_set_2kb_chr_bank_1(DECOTYPE[level]);		//OR ADDITIONAL SPRITES


		if ((options & platformer) && !has_practice_point) {
			songtimer++;
			// DANGER ALERT
			if ( songtimer > songtime[song & 0x7F] ) { songtimer = 0; music_play(song); }

		}		    

		if (trails || forced_trails || gamemode == 6) {
			if (!(kandoframecnt & 0x01)) {
				if (old_scroll_y >= scroll_y) {
					tmp6 = sub_scroll_y_ext(scroll_y, old_scroll_y);
				} else {
					tmp6 = sub_scroll_y_ext(old_scroll_y, scroll_y);
					tmp6 ^= 0xFFFF; tmp6++;
				}
				for (tmp3 = 7; !(tmp3 & 0x80); tmp3--) {
					tmp5 = player_old_posy[tmp3] + tmp6;
					if (high_byte(tmp5) != 0) low_byte(tmp5) = 0;
					(&player_old_posy[1])[tmp3] = tmp5;
				}
				player_old_posy[0] = high_byte(player_y[0]);
				old_scroll_y = scroll_y;
			}
		}
		if (discomode && !(kandoframecnt & discorefreshrate)) {
			tmp3 = G_Table[discoframe] + 0x80;
			
			tmp2 = (tmp3 & 0x3F);  		    
				pal_col(0, tmp2);
				pal_col(1, oneShadeDarker(tmp2)); 
				pal_col(9, oneShadeDarker(tmp2)); 

			tmp3 = 0xC0 + BG_Table[discoframe];
			
			tmp2 = (tmp3 & 0x3F);  		    
				pal_col(6, tmp2);
				pal_col(5, oneShadeDarker(tmp2)); 
			discoframe++;
			if (discoframe == 12) discoframe = 0;

		}

		kandoframecnt++;
		music_update();
		if (slowmode && (kandoframecnt & 1)) { ppu_wait_nmi(); }
		else {
			ppu_wait_nmi();
			set_tile_banks();
			set_player_banks();

			pad_poll(0); // read the first controller

			if (!(pad[currplayer] & PAD_A)) dashing[currplayer] = 0;

			if (options & platformer) twoplayer = 0;

			if ((options & oneptwoplayer) && twoplayer) {
				pad[1] = pad[0]<<1; // read the second controller
				pad_new[1] = pad_new[0]<<1;
				dual = 1;
			}
			else if (twoplayer) {
				pad_poll(1); // read the second controller
				dual = 1;
			}
			
			if (options & jumpsound) {
				if (pad_new[0] & PAD_A) {
					sfx_play(sfx_click, 0);
				}
			}



			if (pad_new[controllingplayer] & PAD_UP && DEBUG_MODE)



			kandokidshack3 = 0;
		
			if (pad_new[0] & PAD_START) {
				pad_new[0] = 0;
				famistudio_music_pause(1);
				famistudio_update();
				color_emphasis(COL_EMP_DARK);
				// ppu_off();
				// mmc3_set_8kb_chr(16);
				// vram_adr(NAMETABLE_B);
				// vram_unrle(pausescreen); 	
				// ppu_on_all();
				while (!(pad_new[0] & PAD_START)) {
					
					pad_poll(0); // read the first controller
					if ((pad[0] & PAD_UP) && (pad_new[0] & PAD_B)) {
						kandokidshack3++;
					}

					else if ((pad_new[controllingplayer] & PAD_B) && PRACTICE_ENABLED) {
						mmc3_set_prg_bank_1(GET_BANK(reset_game_vars));
						reset_game_vars();
						has_practice_point = 1;
						pad_new[0] = PAD_START;
					}
					if (pad_new[0] & PAD_SELECT) { gameState = 1; 
						sfx_play(sfx_exit_level,0);
						music_update();
					//	color_emphasis(COL_EMP_NORMAL);
						crossPRGBankJump0(gameboy_check, 0);
						return;
					}
					if ((pad_new[0] & PAD_RIGHT) && DEBUG_MODE) {
						speed == 4 ? speed = 0 : speed++;
					}
					if ((pad_new[0] & PAD_LEFT) && DEBUG_MODE) {
						gravity_mod == 4 ? gravity_mod = 0 : gravity_mod++;
					}
					if ((pad[0] & PAD_DOWN) && (pad_new[0] & PAD_A)) {
						kandokidshack++;
					}
					else if ((pad[0] & PAD_UP) && (pad_new[0] & PAD_A)) {
						kandokidshack2++;
					}
					else if ((pad_new[0] & PAD_A) && DEBUG_MODE) {
#ifdef FLAG_KANDO_FUN_STUFF
						gamemode == 8 ? gamemode = 0 : gamemode++;
#else
						gamemode == 7 ? gamemode = 0 : gamemode++;
#endif			
						ppu_off();
						//one_vram_buffer(0xf5+gamemode, NTADR_A(18,15));	
						set_player_banks();
						oam_clear();
						mmc3_set_prg_bank_1(GET_BANK(drawplayerone));	
						drawplayerone();
						mmc3_set_prg_bank_1(GET_BANK(draw_sprites));	
						draw_sprites();
						ppu_on_all();
					}
				}
			crossPRGBankJump0(gameboy_check, 0);
			famistudio_music_pause(0);
			if (kandokidshack != 9) kandokidshack = 0;
			if (kandokidshack2 != 7) kandokidshack2 = 0;
			if (kandokidshack3 != 12) kandokidshack3 = 0;
			else if (kandokidshack3 == 12) DEBUG_MODE = !DEBUG_MODE;
		}
		if (options & debugtoggle)
        	if (pad_new[0] & PAD_SELECT) //THE BIG DEBUG - DISABLE BEFORE RELEASE
			{ 
				DEBUG_MODE = !DEBUG_MODE; 
				cube_data[0] &= 2; 
				cube_data[1] &= 2; 
			}		

	if ((pad_new[controllingplayer] & PAD_B) && has_practice_point) crossPRGBankJump0(reset_game_vars,0);

	if (pad_new[0] & PAD_UP && DEBUG_MODE) {
		currplayer_gravity ^= 0x01;
	}
	
	if (pad_new[0] & PAD_DOWN && DEBUG_MODE) {
		mini ^= 1;
	}

        if (pad[0] & PAD_SELECT && DEBUG_MODE) {
            if (++END_LEVEL_TIMER > 60) {
                END_LEVEL_TIMER = 0;
                gameState = 3;
                DEBUG_MODE = 0;
                famistudio_music_stop();
            }
        } else {
            END_LEVEL_TIMER = 0;
        }

		if (was_on_slope_counter) {
			was_on_slope_counter--;
		} else slope_type = 0;

		mmc3_set_prg_bank_1(GET_BANK(movement));
		
		movement();

		kandotemp3 = 0;

		runthecolls();
		
		kandotemp3 = 1;
				
#ifdef FLAG_KANDO_FUN_STUFF		
		if (bigboi && !(kandoframecnt & 1) ) {
				high_byte(player_x[0]) += 15;
				high_byte(currplayer_x) += 15;

				runthecolls();
				
				high_byte(player_x[0]) -= 15;
				high_byte(currplayer_x) -= 15;

				high_byte(player_y[0]) -= 15;
				high_byte(currplayer_y) -= 15;

			
				runthecolls();

				high_byte(player_x[0]) += 15;
				high_byte(currplayer_x) += 15;

				runthecolls();

				high_byte(player_x[0]) -= 15;
				high_byte(currplayer_x) -= 15;

				high_byte(player_y[0]) += 15;
				high_byte(currplayer_y) += 15;

		}			
			
		else {
			if (longmode) {

				high_byte(player_x[0]) += 15;
				high_byte(currplayer_x) += 15;

				runthecolls();
				
				high_byte(player_x[0]) -= 15;
				high_byte(currplayer_x) -= 15;

			}
			if (tallmode) {

				high_byte(player_y[0]) -= 15;
				high_byte(currplayer_y) -= 15;

				runthecolls();

				high_byte(player_y[0]) += 15;
				high_byte(currplayer_y) += 15;

			}
		}
#endif
		if (invincible_counter) invincible_counter--;

		mmc3_set_prg_bank_1(GET_BANK(do_the_scroll_thing));
		do_the_scroll_thing(); 

		check_spr_objects();



		mmc3_set_prg_bank_1(GET_BANK(sprite_collide));
		{	// always store it back for practice mode
			player_x[0] = currplayer_x;
			player_y[0] = currplayer_y;
			player_vel_x[0] = currplayer_vel_x;
			player_vel_y[0] = currplayer_vel_y;
			player_gravity[0] = currplayer_gravity;
		}

		
		if (dual) { 
			currplayer = 1;					//take focus
			if (!(pad[currplayer] & PAD_A)) dashing[currplayer] = 0;
			if (twoplayer) controllingplayer = 1;		//take controls
			if (dual && (options & platformer) && !twoplayer) { player_x[1] = player_x[0]; player_vel_x[1] = player_vel_x[0]; }
			else if (dual && !(options & platformer)) { player_x[1] = player_x[0]; player_vel_x[1] = player_vel_x[0]; }

			{	
				currplayer_x = player_x[1];
				currplayer_y = player_y[1];
				currplayer_vel_x = player_vel_x[1];
				currplayer_vel_y = player_vel_y[1];
				currplayer_gravity = player_gravity[1];
			}

			if (pad_new[controllingplayer] & PAD_UP && DEBUG_MODE) currplayer_gravity ^= 0x01;			//DEBUG GRAVITY

			mmc3_set_prg_bank_1(GET_BANK(movement));
			movement();

			runthecolls();
			mmc3_set_prg_bank_1(GET_BANK(do_the_scroll_thing2));
			do_the_scroll_thing2();

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
	}
        check_spr_objects();

	oam_clear();

        crossPRGBankJump0(draw_screen_R,0);
	crossPRGBankJump0(draw_sprites,0);
        
	

        if (DEBUG_MODE) gray_line();
		if (!DEBUG_MODE) {
			if (high_byte(player_x[0]) > 0x20) {
				if (cube_data[0] & 1 || cube_data[1] & 1) reset_level();
			} else cube_data[0] = cube_data[1] = 0;
		}
        if (gameState != 0x02) return;
    }
    
}

void runthecolls() {
	if (!kandotemp3) {
		mmc3_set_prg_bank_1(GET_BANK(x_movement_coll));
		x_movement_coll();

		mmc3_set_prg_bank_1(GET_BANK(x_movement));
		x_movement();

		mmc3_set_prg_bank_1(GET_BANK(sprite_collide));
		sprite_collide();

	}	
		
	else if (!(kandoframecnt & 1)) {
		mmc3_set_prg_bank_1(GET_BANK(sprite_collide));
		sprite_collide();
	}
	if (!DEBUG_MODE && !invincible_counter) {
		bg_coll_death();
	}
}				

void set_player_banks() {
		if (!retro_mode) {
			iconbank1 = 18; iconbank2 = 22; iconbank3 = iconbank;
		}
		else {
			iconbank1 = 20; iconbank2 = 24; iconbank3 = 38;
		}
		
		if (gamemode == 8) mmc3_set_2kb_chr_bank_0(NINJABANK);
		else if ((mini && gamemode != 0) || (gamemode == 7)) mmc3_set_2kb_chr_bank_0(iconbank2);
		else if (mini && gamemode == 0) mmc3_set_2kb_chr_bank_0(iconbank3);
		else if (gamemode == 0 || gamemode == 1 || gamemode == 3) mmc3_set_2kb_chr_bank_0(iconbank3);
		else mmc3_set_2kb_chr_bank_0(iconbank1);

}	

void set_tile_banks() {
	if (!no_parallax) {
		mmc3_set_1kb_chr_bank_0(spike_set[level] + (parallax_scroll_x & 1));
		mmc3_set_1kb_chr_bank_1(block_set[level] + (parallax_scroll_x & 1));	//tile graphics
		mmc3_set_1kb_chr_bank_2(parallax_scroll_x + GET_BANK(PARALLAX_CHR));
		mmc3_set_1kb_chr_bank_3(saw_set[level] + (parallax_scroll_x & 1));
	}
	else {
		mmc3_set_1kb_chr_bank_0(spike_set[level]);
		mmc3_set_1kb_chr_bank_1(block_set[level]);	//tile graphics
		mmc3_set_1kb_chr_bank_2(SLOPESA);
		mmc3_set_1kb_chr_bank_3(saw_set[level]);
	}
}	

		