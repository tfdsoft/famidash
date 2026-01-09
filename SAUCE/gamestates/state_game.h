/*
	Calls the movement routine of the current gamemode
	Implemented in asm
*/
// void set_tile_banks();
void decrement_was_on_slope();
void __fastcall__ movement();
void everything_else();


void check_for_cube_data_2_set() {
	if ((controllingplayer->press & (PAD_A | PAD_UP)) && currplayer_vel_y != 0 && (gamemode != GAMEMODE_UFO && gamemode != GAMEMODE_SHIP)) idx8_store(cube_data, currplayer, cube_data[currplayer] | 0x02);
}

void x_minus_15();
void y_minus_15();
void x_plus_15();
void y_plus_15();
void runthecolls();
void set_player_banks();

extern unsigned char* PARALLAX_CHR;





void state_game(){

	orbactive = 0;
	

	if (trueFramerate == SPEED_PAL && options & fullpalspeed)
		framerate = SPEED_PAL;
	else
		framerate = SPEED_NTSC;

	// set_tile_banks();
	
	nocamlock = 0;

  
	currplayer = 0;
	controllingplayer = &joypad1;
//	current_transition_timer_length = 0;
	mmc3_set_prg_bank_1(GET_BANK(reset_level));
	reset_level();

	scroll_y = spawn_scroll_y_pos;
	seam_scroll_y = (spawn_scroll_y_pos - 0x78); // [temp]	
	set_scroll_y(scroll_y);

	player_y[0] = spawn_y_pos;
	player_y[1] = spawn_y_pos;
	currplayer_y = spawn_y_pos;	
	
	update_currplayer_table_idx();

	END_LEVEL_TIMER = 0;
	kandoframecnt = 0;

    while (1) {

		kandoframecnt++;
		if ((slowmode && !(kandoframecnt & 1)) { 
			ppu_wait_nmi(); 
			check_for_cube_data_2_set();
		}
		else {
			everything_else();				//do the normal state_game stuff
		}

		if (high_byte(player_x[0]) > 0x20) {
			if (cube_data[0] & 1 || cube_data[1] & 1) {
				death_animation();
				mmc3_set_prg_bank_1(GET_BANK(reset_level));
				reset_level();
			}
		} else cube_data[0] = cube_data[1] = 0;
	}

        if (gameState != STATE_GAME) return;

    }
    
}

void runthecolls() {
	if (!invincible_counter) {
		x_movement_coll();
	}

	if (processXMovement) {
		x_movement();
	}	



	if (!invincible_counter) {
		crossPRGBankJump0(bg_coll_death);
	}
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


void everything_else() {
			jumpedonthisframe[0] = 0;
			jumpedonthisframe[1] = 0;

			if (nullscapes_active && !(kandoframecnt & 7)) nullscapes_orb_type++;
			if (nullscapes_active == 1 && nullscapes_orb_type >= 4) nullscapes_orb_type = 0;
			else if (nullscapes_active == 2 && nullscapes_orb_type >= 6) nullscapes_orb_type = 0;
			else if (!nullscapes_active && nullscapes_orb_type >= 1) nullscapes_orb_type = 0;


			if (!(joypad1.hold & (PAD_A | PAD_UP))) {
				if (dashing[0]) currplayer_vel_y = DASH_END_VEL_RESET(currplayer_table_idx);
				dashing[0] = 0;
			}

		crossPRGBankJump0(decrement_was_on_slope);

		check_for_cube_data_2_set();

	if (orbed[currplayer]) {
		if (!(controllingplayer->hold & (PAD_A | PAD_UP))) orbed[currplayer] = 0;
	}

		crossPRGBankJump0(sprite_collide);

		crossPRGBankJump0(movement);

		processXMovement = 1;

		runthecolls();
		
		processXMovement = 0;
		
		dblocked[currplayer] = 0;
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
			player_mini[0] = currplayer_mini;
			slope_frames[0] = currplayer_slope_frames;
			was_on_slope_counter[0] = currplayer_was_on_slope_counter;
			slope_type[0] = currplayer_slope_type;
			last_slope_type[0] = currplayer_last_slope_type;
		}

				currplayer_x = player_x[0];
				currplayer_y = player_y[0];
				currplayer_vel_x = player_vel_x[0];
				currplayer_vel_y = player_vel_y[0];
				currplayer_gravity = player_gravity[0];
				currplayer_mini = player_mini[0];
				currplayer_slope_frames = slope_frames[0];
				currplayer_was_on_slope_counter = was_on_slope_counter[0];
				currplayer_slope_type = slope_type[0];
				currplayer_last_slope_type = last_slope_type[0];
				update_currplayer_table_idx();
		
	
}

