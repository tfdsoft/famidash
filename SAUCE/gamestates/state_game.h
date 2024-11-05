/*
	Calls the movement routine of the current gamemode
	Implemented in asm
*/
// void set_tile_banks();
void __fastcall__ movement(void);
void __fastcall__ movement2(void);
void mouse_and_cursor();
extern uint8_t famistudio_song_speed;
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



void x_minus_15();
void y_minus_15();
void x_plus_15();
void y_plus_15();
void runthecolls();
void set_player_banks();
void gameboy_check();

extern unsigned char* PARALLAX_CHR;
unsigned char END_LEVEL_TIMER;


void state_game(){
	if ((level >= decode) || twoplayer) no_parallax = 1;
	else no_parallax = 0;
	coin1_timer = 0;
	coin2_timer = 0;
	coin3_timer = 0;
	kandokidshack = 0;
	kandokidshack2 = 0;
	kandokidshack3 = 0;
	kandokidshack4 = 0;
	animating = 0;
	memfill(trail_sprites_visible, 0, sizeof(trail_sprites_visible));
	orbactive = 0;
	mmc3_disable_irq();
	
	outline_color = 0x30;

	lastgcolortype = 0xFF;
	lastbgcolortype = 0xFF;

	// set_tile_banks();
	
	ppu_off();
	nocamlock = 0;
	use_auto_chrswitch = 1;

	pal_bg(paletteDefault);
	pal_spr(paletteDefaultSP);  //needed

	crossPRGBankJump8(load_ground,0);

    
	currplayer = 0;
	controllingplayer = &joypad1;
//	current_transition_timer_length = 0;
	reset_level();

	END_LEVEL_TIMER = 0;
	kandoframecnt = 0;

	
	iconbank = (icon<<1) + 38;

	pal_col(0x0A,0x0F);   //palette 2 set to 0x0F for mountains
	pal_col(0x0B,color1);   //palette 2 set to player color

	memfill(player_old_posy, 0, sizeof(player_old_posy));
	
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

	pal_set_update();

    while (1) {
		newrand();
		if (kandokidshack2 && !(kandoframecnt & 0x0F)) { icon == MAX_ICONS-1 ? icon = 0 : icon++; 	iconbank = (icon<<1) + 38; }
		pal_col(3,outline_color);
		pal_col(7,outline_color);
		pal_set_update();


		if ((kandoframecnt & 0x1F) == 0x10 ) mmc3_set_2kb_chr_bank_1(DECOTYPE[level] + 2);		//DECO
		else if ((kandoframecnt & 0x1F) == 0x00) mmc3_set_2kb_chr_bank_1(DECOTYPE[level]);		//OR ADDITIONAL SPRITES									//

		if ((options & platformer) && !has_practice_point) {
			
			if (famistudio_song_speed == 0x80) music_play(song);
		}		    

		if (((forced_trails == 2) || trails == 2 || !(kandoframecnt & 0x1))) {
			if (!(kandoframecnt & 0x01)) {
				if (old_trail_scroll_y >= scroll_y) {
					tmp6 = calculate_linear_scroll_y(sub_scroll_y_ext(scroll_y, old_trail_scroll_y));
				} else {
					tmp6 = calculate_linear_scroll_y(sub_scroll_y_ext(old_trail_scroll_y, scroll_y));
					tmp6 ^= 0xFFFF; tmp6++;
				}
				tmp3 = 7;
				do {
					tmp5 = player_old_posy[tmp3] + tmp6;
					if (high_byte(tmp5) != 0) low_byte(tmp5) = 0;
					(&player_old_posy[1])[tmp3] = tmp5;
					--tmp3;
				} while ((int8_t)tmp3 >= 0);
				player_old_posy[0] = high_byte(player_y[0]);
				old_trail_scroll_y = scroll_y;
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
			pal_set_update();

			discoframe++;
			if (discoframe == 12) discoframe = 0;
		}

		kandoframecnt++;
		if ((slowmode || (kandokidshack4 == 15)) && (kandoframecnt & 1)) { ppu_wait_nmi(); 
			if (!(kandokidshack4 == 15)) music_update();
//			oam_clear();
//			mmc3_set_prg_bank_1(GET_BANK(draw_screen));
//			draw_screen(); 
//			mmc3_set_prg_bank_1(GET_BANK(draw_sprites));	
//			draw_sprites();
			if ((controllingplayer->press_a || controllingplayer->press_up) && currplayer_vel_y != 0) idx8_store(cube_data, currplayer, cube_data[currplayer] | 0x02);
			crossPRGBankJump0(sprite_collide);

		}
		else {
			music_update();
			ppu_wait_nmi();

			// set_tile_banks();
		
			set_player_banks();

			if (!kandodebugmode) {
				// crossPRGBankJump0(mouse_update);
				// pad_poll(0); // read the first controller
			}
			else {
				mouse_and_cursor();
			}

			if (mouse.left_press) joypad1.press_a = 1;
			if (mouse.left) joypad1.a = 1;

			if (options & platformer) twoplayer = 0;

			if ((options & oneptwoplayer) && twoplayer) {
				// yo actually wtf is this
				joypad2.hold = joypad1.hold<<1; // read the second controller
				joypad2.press = joypad1.press<<1;
				dual = 1;
			}
			else if (twoplayer) {
				// pad_poll(1); // read the second controller
				dual = 1;
			}
			
			if (!(joypad1.a) && !(joypad1.up)) {
				if (dashing[0]) currplayer_vel_y = 0x0100^(0x0000 - currplayer_gravity);
				dashing[0] = 0;
			}

			//mouse debug here
			if (kandodebugmode) {
				
				if (mouse.left) {
					kandodebugmode = 2;
					//high_byte(currplayer_x) = mouse.x + high_byte(scroll_x);
					target_x_scroll_stop = 0xE000;
					curr_x_scroll_stop = 0xE000;
					high_byte(currplayer_y) = (mouse.y + high_byte(scroll_y)) - 10;
					high_byte(currplayer_x) = mouse.x - 10 < 0 ? mouse.x : mouse.x - 10;
					if (high_byte(currplayer_x) > 226) high_byte(currplayer_x) = 226;
					
				}
				else {
					kandodebugmode = 1;
					target_x_scroll_stop = 0x5000;
					cube_data[0] = 0;
				}
				
			}
			//end mouse debug
			
			if (options & jumpsound) {
				if (joypad1.press_a || joypad1.press_up) {
					sfx_play(sfx_click, 0);
				}
			}



			if (joypad1.press_start || mouse.right_press) {
				joypad1.press = 0;
				mouse.right_press = 0;
				famistudio_music_pause(1);
				famistudio_update();
				color_emphasis(COL_EMP_DARK);
				exittimer = 0;
				// ppu_off();
				// mmc3_set_8kb_chr(16);
				// vram_adr(NAMETABLE_B);
				// vram_unrle(pausescreen); 	
				// ppu_on_all();
				kandokidshack3 = 0;
				kandokidshack4 = 0;
				while (!(joypad1.press & PAD_START) && !(mouse.right_press)) {
					if (VRAM_UPDATE == 1) {
						ppu_wait_nmi();
					}
					// force re-enable NMI every frame.
					VRAM_UPDATE = 1;

					if (mouse.right) exittimer++;
					else exittimer = 0;
					if ((joypad1.up) && (joypad1.press_b)) {
						kandokidshack3++;
					}
					if ((joypad1.down) && (joypad1.press_b)) {
						kandokidshack4++;
					}

					else if ((controllingplayer->press_b || mouse.left_press) && PRACTICE_ENABLED) {
						mmc3_set_prg_bank_1(GET_BANK(reset_game_vars));
						reset_game_vars();
						//has_practice_point = 1;
						joypad1.press = PAD_START;
					}
					if (joypad1.press_select || exittimer == 100) { 
						gameState = 1; 
						sfx_play(sfx_exit_level,0);
						music_update();
						crossPRGBankJump0(gameboy_check);
						return;
					}
					if ((joypad1.press_right) && DEBUG_MODE) {
						speed == 4 ? speed = 0 : speed++;
					}
					if ((joypad1.press_left) && DEBUG_MODE) {
						gravity_mod == 4 ? gravity_mod = 0 : gravity_mod++;
					}
					if ((joypad1.down) && (joypad1.press_a)) {
						kandokidshack++;
					}
					else if ((joypad1.up) && (joypad1.press_a)) {
						kandokidshack2++;
					}
					else if ((joypad1.press_a) && DEBUG_MODE) {
						nocamlock = 1;
	#ifdef FLAG_KANDO_FUN_STUFF
						gamemode == 8 ? gamemode = 0 : gamemode++;
	#else
						gamemode == 7 ? gamemode = 0 : gamemode++;
	#endif			
						cube_data[0] = 0;
						ppu_off();
						set_player_banks();
						oam_clear();
						crossPRGBankJump0(drawplayerone);
						mmc3_set_prg_bank_1(GET_BANK(draw_sprites));	
						draw_sprites();
						ppu_on_all();
					}
				}
				crossPRGBankJump0(gameboy_check);
				famistudio_music_pause(0);
				if (kandokidshack != 9) kandokidshack = 0;
				if (kandokidshack2 != 7) kandokidshack2 = 0;
				if (kandokidshack3 == 12) DEBUG_MODE = !DEBUG_MODE;
				else if (kandokidshack3 == 20) kandodebugmode ^= 1;
				else kandokidshack3 = 0;
			}
//		if (options & debugtoggle) {
			if (joypad1.press_select) //THE BIG DEBUG - DISABLE BEFORE RELEASE
				{ 
					DEBUG_MODE = !DEBUG_MODE; 
					cube_data[0] &= 2; 
					cube_data[1] &= 2; 
					if (!DEBUG_MODE) nocamlock = 0;
				}		
//		}

		if (has_practice_point > 1 && (joypad1.press_select || (mouse.left && mouse.right_press))) { has_practice_point--; curr_practice_point = 0; }
		
		if ((controllingplayer->press_b) && has_practice_point && !(twoplayer && (options & oneptwoplayer))) crossPRGBankJump0(reset_game_vars);

		if (joypad1.press_right && DEBUG_MODE && !(options & platformer)) {
			currplayer_gravity ^= 0x01;
		}
		
		if (joypad1.press_down && DEBUG_MODE) {
			currplayer_mini ^= 1;
		}

		if (joypad1.select && DEBUG_MODE) {
		    if (++END_LEVEL_TIMER > 60) {
			END_LEVEL_TIMER = 0;
			gameState = 3;
			//DEBUG_MODE = 0;
			famistudio_music_stop();
		    }
		} else {
		    END_LEVEL_TIMER = 0;
		}

		//if (DEBUG_MODE) color_emphasis(COL_EMP_BLUE);
//		if (DEBUG_MODE) gray_line();

		if (was_on_slope_counter) {
			was_on_slope_counter--;
		} else slope_type = 0;

		if ((controllingplayer->press_a || controllingplayer->press_up) && currplayer_vel_y != 0) idx8_store(cube_data, currplayer, cube_data[currplayer] | 0x02);

	if (orbed[currplayer]) {
		if (!(controllingplayer->a) && !(controllingplayer->up)) orbed[currplayer] = 0;
	}

		crossPRGBankJump0(sprite_collide);

		crossPRGBankJump0(movement);

		kandotemp3 = 0;

		runthecolls();
		
		kandotemp3 = 1;
		
#ifdef FLAG_KANDO_FUN_STUFF		
		if (bigboi && !(kandoframecnt & 1) ) {

			x_plus_15();

			runthecolls();
			
			x_minus_15();

			y_minus_15();

		
			runthecolls();

			x_plus_15();

			runthecolls();

			x_minus_15();

			y_plus_15();

		}			
			
		else {
			if (longmode) {

				x_plus_15();

				runthecolls();
				
				x_minus_15();

			}

			if (tallmode) {

				y_minus_15();

				runthecolls();

				y_plus_15();

			}
		}
		kandotemp3 = 0;
#endif
		if (invincible_counter) invincible_counter--;

		crossPRGBankJump0(do_the_scroll_thing);

		check_spr_objects();



		mmc3_set_prg_bank_1(GET_BANK(sprite_collide));
		{	// always store it back for practice mode
			player_x[0] = currplayer_x;
			player_y[0] = currplayer_y;
			player_vel_x[0] = currplayer_vel_x;
			player_vel_y[0] = currplayer_vel_y;
			player_gravity[0] = currplayer_gravity;
			mini[0] = currplayer_mini;
		}

		
		if (dual) { 
			currplayer = 1;					//take focus
			if (!(joypad2.a) && !(joypad2.up)) {
				if (dashing[1]) currplayer_vel_y = 0x0100^(0x0000 - currplayer_gravity);
				dashing[1] = 0;
			}
			if (twoplayer) controllingplayer = &joypad2;		//take controls
			if (dual && (options & platformer) && !twoplayer) { player_x[1] = player_x[0]; player_vel_x[1] = player_vel_x[0]; }
			else if (dual && !(options & platformer)) { player_x[1] = player_x[0]; player_vel_x[1] = player_vel_x[0]; }

			{	
				currplayer_x = player_x[1];
				currplayer_y = player_y[1];
				currplayer_vel_x = player_vel_x[1];
				currplayer_vel_y = player_vel_y[1];
				currplayer_gravity = player_gravity[1];
				currplayer_mini = mini[1];
			}

			if (controllingplayer->press_right && DEBUG_MODE && !(options & platformer)) currplayer_gravity ^= 0x01;			//DEBUG GRAVITY
			if (((controllingplayer->press_a || controllingplayer->press_up)) && currplayer_vel_y != 0) idx8_store(cube_data, currplayer, cube_data[currplayer] | 0x02);
	if (orbed[currplayer]) {
		if (!(controllingplayer->a) && !(controllingplayer->up)) orbed[currplayer] = 0;
	}

			crossPRGBankJump0(sprite_collide);

			crossPRGBankJump0(movement);

			kandotemp3 = 1;
			runthecolls();
			kandotemp3 = 0;
			
	//		crossPRGBankJump0(do_the_scroll_thing2);

			currplayer = 0;					//give back focus

			if (twoplayer) controllingplayer = &joypad1;		//give back controls

			{
				player_x[1] = currplayer_x;
				player_y[1] = currplayer_y;
				player_vel_x[1] = currplayer_vel_x;
				player_vel_y[1] = currplayer_vel_y;
				player_gravity[1] = currplayer_gravity;
				mini[1] = currplayer_mini;

				currplayer_x = player_x[0];
				currplayer_y = player_y[0];
				currplayer_vel_x = player_vel_x[0];
				currplayer_vel_y = player_vel_y[0];
				currplayer_gravity = player_gravity[0];
				currplayer_mini = mini[0];
			}
		}

	}
   //     check_spr_objects();

  		oam_clear();

		mmc3_set_prg_bank_1(GET_BANK(draw_screen));
		draw_screen(); 
		mmc3_set_prg_bank_1(GET_BANK(draw_sprites));	
		draw_sprites();
        
		if (kandodebugmode) { if (mouse_timer) oam_spr(mouse.x, mouse.y - 1, (0xAD), 2); }	
 //       color_emphasis(0);

		if (DEBUG_MODE) gray_line();
		if (!DEBUG_MODE && kandodebugmode != 2) {
		if (high_byte(player_x[0]) > 0x20) {
			if (cube_data[0] & 1 || cube_data[1] & 1) reset_level();
		} else cube_data[0] = cube_data[1] = 0;
	}

        if (gameState != 0x02) return;
	if (mouse_timer) mouse_timer--;

    }
    
}

void runthecolls() {
	if (!invincible_counter) {
		x_movement_coll();
	}

	if (!kandotemp3) {
		x_movement();
	}	



	if (!DEBUG_MODE && !invincible_counter) {
		crossPRGBankJump0(bg_coll_death);
	}
}				

void set_player_banks() {
		if (!retro_mode) {
			iconbank1 = 18; iconbank2 = 22; iconbank3 = iconbank;
		}
		else {
			iconbank1 = 20; iconbank2 = 24; iconbank3 = 16;
		}
		
		if (gamemode == 8) mmc3_set_2kb_chr_bank_0(NINJABANK);
		else if ((currplayer_mini && (gamemode != 0 && gamemode != 2 && gamemode != 4)) || (gamemode == 7) || (gamemode == 6)) mmc3_set_2kb_chr_bank_0(iconbank2);
		else if (gamemode == 0 || gamemode == 1 || gamemode == 3) mmc3_set_2kb_chr_bank_0(iconbank3);
		else mmc3_set_2kb_chr_bank_0(iconbank1);

}

void x_minus_15() {
	high_byte(player_x[0]) -= 15;
	high_byte(currplayer_x) -= 15;	
}
void x_plus_15() {
	high_byte(player_x[0]) += 15;
	high_byte(currplayer_x) += 15;	
}
void y_minus_15() {
	high_byte(player_y[0]) -= 15;
	high_byte(currplayer_y) -= 15;	
}
void y_plus_15() {
	high_byte(player_y[0]) += 15;
	high_byte(currplayer_y) += 15;	
}

void mouse_and_cursor() {
	if (mouse.connected) {
		if (mouse.left || mouse.right || mouse.x != prev_mouse_x || mouse.y != prev_mouse_y) mouse_timer = 120;
		if (mouse.right_press) joypad1.press_b = true;
		if (mouse.right) joypad1.b = true;
		if (!(kandoframecnt & 0x07)) mouseframe += mouseframe == 7 ? -7 : 1;
		if (kandoframecnt > 0xFC) kandoframecnt = 0;
		if (gameState != 2) { if (mouse_timer) oam_spr(mouse.x, mouse.y - 1, (0xA1 + (2*mouseframe)), 2); }

		prev_mouse_x = mouse.x;
		prev_mouse_y = mouse.y;
	}
}
