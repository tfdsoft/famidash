
CODE_BANK_PUSH("XCD_BANK_01")

#define SLOPE_NONE			0b0000

#define SLOPE_45DEG_UP 		0b0001
#define SLOPE_45DEG_DOWN 	0b0010
#define SLOPE_22DEG_UP 		0b0011
#define SLOPE_22DEG_DOWN 	0b0100
#define SLOPE_66DEG_UP 		0b0101
#define SLOPE_66DEG_DOWN 	0b0110

#define SLOPE_45DEG_UP_UD 	0b1001
#define SLOPE_45DEG_DOWN_UD 0b1010
#define SLOPE_22DEG_UP_UD 	0b1011
#define SLOPE_22DEG_DOWN_UD 0b1100
#define SLOPE_66DEG_UP_UD 	0b1101
#define SLOPE_66DEG_DOWN_UD 0b1110



/* 
	Gets the collision of the current tile
	Implemented in asm
*/
__fastcall__ char bg_collision_sub(void);
void commonly_used_store();
void commonly_stored_routine_2();
void commonly_used_death_check();
void tmp20f();


/*
	Out:
	A
*/
char bg_coll_sides() {
	switch (collision) {
		case COL_BOTTOM: 
			if ((uint8_t)(temp_y & 0x08)) return 1;		// If Y pos inside block ≥ 8px
			break;
		case COL_TOP: 
			if (!(uint8_t)(temp_y & 0x08)) return 1;		// If Y pos inside block < 8px
			break;
		case COL_ALL: 
		case COL_FLOOR_CEIL:
			return 1;		
		case COL_UP_LEFT:
			tmp2 = temp_y & 0x0f;	
			tmp8 = tmp2 & 0x07;	 
			if (tmp2 < 0x08 && ((uint8_t)(temp_x & 0x0f) < 0x08)) {
				return 1;
			}
			
	};
	return 0;
}

void col_death_bottom_routine() {
	if ((uint8_t)(temp_y & 0x0f) > 0x0a) {							// If Y pos inside block ≥ 8px, die
		tmp20f();				// If Y pos inside block < 8px, die
		if (tmp2 >= 0x04 && tmp2 < 0x09) {		// If X pos even insider, die even more
			cube_data[currplayer] = 1;
		}
	}	
}

void col_death_top_routine() {
	if ((uint8_t)(temp_y & 0x0f) < 0x06) {			
		tmp20f();				// If Y pos inside block < 8px, die
		if (tmp2 >= 0x04 && tmp2 < 0x09) {		// If X pos even insider, die even more
			cube_data[currplayer] = 1;
		}
	}	
}

void col_death_right_routine() {
	if ((uint8_t)(temp_x & 0x0f) >= 0x0a) {
		tmp2 = temp_y & 0x0f;
		if (tmp2 >= 0x06 && tmp2 < 0x09) {
			cube_data[currplayer] = 1;
		}
	}
}

void col_death_left_routine() {
	if ((uint8_t)(temp_x & 0x0f) < 0x06) {
		tmp2 = temp_y & 0x0f;
		if (tmp2 >= 0x06 && tmp2 < 0x09) {
			cube_data[currplayer] = 1;
		}
	}
}

/*
	Clobbers:
	tmp2
*/
void bg_coll_spikes() {
	switch (collision) {
		case COL_UP_LEFT_SPIKE:
			if (!(uint8_t)(temp_y & 0x08)) {
				tmp20f();
				if (tmp2 >= 0x02 && tmp2 < 0x06)
					break;
			}
			return;
		case COL_UP_RIGHT_SPIKE:
			if (!(uint8_t)(temp_y & 0x08)) {
				tmp20f();
				if (tmp2 >= 0x0a && tmp2 < 0x0d)
					break;
			}
			return;
		case COL_UP_BOTH_SPIKES:
			if (!(uint8_t)(temp_y & 0x08)) {
				tmp2 = (uint8_t)(temp_x & 0x07);
				if (tmp2 >= 0x02 && tmp2 < 0x06)
					break;
			}
			return;
		case COL_DOWN_LEFT_SPIKE:
			if ((uint8_t)(temp_y & 0x08)) {
				tmp20f();
				if (tmp2 >= 0x02 && tmp2 < 0x06)
					break;
			}
			return;
		case COL_DOWN_RIGHT_SPIKE:
			if ((uint8_t)(temp_y & 0x08)) {
				tmp20f();
				if (tmp2 >= 0x0a && tmp2 < 0x0d)
					break;
			}
			return;
		case COL_DOWN_BOTH_SPIKES:
			if ((uint8_t)(temp_y & 0x08)) {
				tmp2 = (uint8_t)(temp_x & 0x07);
				if (tmp2 >= 0x02 && tmp2 < 0x06)
					break;
			}
			return;
		case COL_DEATH_LEFT:
			col_death_left_routine();
			return;
		case COL_DEATH_RIGHT:
			col_death_right_routine();
			return;
		case COL_DEATH_TOP:
			col_death_top_routine();	
			return;
		case COL_DEATH_BOTTOM:
			col_death_bottom_routine();	
			return;
			
		case COL_DEATH_BOTTOM_LEFT:
			col_death_left_routine();
			col_death_bottom_routine();
			return;

		case COL_DEATH_BOTTOM_RIGHT:
			col_death_right_routine();
			col_death_bottom_routine();
			return;

		case COL_DEATH_TOP_LEFT:
			col_death_left_routine();
			col_death_top_routine();
			return;

		case COL_DEATH_TOP_RIGHT:
			col_death_right_routine();
			col_death_top_routine();
			return;

		case COL_DEATH:	
			tmp2 = (uint8_t)(temp_y & 0x0f);
			if (tmp2 >= 0x04 && tmp2 < 0x0c) {
				tmp20f();
				if (tmp2 >= 0x04 && tmp2 < 0x09) {
					break;
				}
			}
			return;
		case COL_LEFT_SPIKE_BLOCK:
		case COL_BOTTOM_LEFT_SPIKE:
			if (!(uint8_t)(temp_y & 0x08)) {
				tmp20f();
				if (tmp2 >= 0x02 && tmp2 < 0x06)
					break;
			}
			return;
		case COL_RIGHT_SPIKE_BLOCK:
		case COL_BOTTOM_RIGHT_SPIKE:
			if (!(uint8_t)(temp_y & 0x08)) {
				tmp20f();
				if (tmp2 >= 0x0a && tmp2 < 0x0d)
					break;
			}
			return;
		case COL_BOTTOM_SPIKES:
			if (!(uint8_t)(temp_y & 0x08)) {
				tmp2 = (uint8_t)(temp_x & 0x07);
				if (tmp2 >= 0x02 && tmp2 < 0x06)
					break;
			}
			return;
		default: return;
	}
	cube_data[currplayer] = 1;							
}

/*
	Clobbers:
	tmp8
*/
void bg_coll_floor_spikes() { // used just for checking ground spikes on the floor
	temp_x = Generic.x + low_word(scroll_x) + (Generic.width >> 1); // automatically only the low byte

	commonly_stored_routine_2();

	tmp8 = 0;
	do {
		bg_collision_sub();
	
		bg_coll_spikes();
			
		commonly_used_store();
	} while (++tmp8 < 2);

	// Check middle of cube

	storeWordSeparately(
		add_scroll_y(
			Generic.y + (currplayer_mini ? (byte(0x10 - Generic.height) >> 1) : 0) + (Generic.height >> 1), scroll_y
		), temp_y, temp_room);

	bg_collision_sub();

	bg_coll_spikes();

	commonly_stored_routine_2();

	temp_x = Generic.x + low_word(scroll_x) + (Generic.width); // automatically only the low byte

	tmp8 = 0;
	do {
		bg_collision_sub();

		bg_coll_spikes();

		commonly_used_store();
	} while (++tmp8 < 2);

	temp_x -= (Generic.width >> 1); // automatically only the low byte

	commonly_stored_routine_2();

	tmp8 = 0;
	do {
		bg_collision_sub();
	
		bg_coll_spikes();
			
		commonly_used_store();
	} while (++tmp8 < 2);
}
/*
	Clobbers:
	tmp2, tmp8
*/
char bg_coll_mini_blocks() {
	if (collision != COL_FLOOR_CEIL && high_byte(currplayer_x) < 0x10) return 0;
	switch (collision) {
		case COL_UP_LEFT:
			tmp2 = (uint8_t)(temp_y & 0x0f);	
			tmp8 = tmp2 & 0x07;	 
			if (tmp2 < 0x08 && ((uint8_t)(temp_x & 0x0f) < 0x08)) {
				return 1;
			}
			break;
		case COL_UP_RIGHT:
			tmp2 = (uint8_t)(temp_y & 0x0f);	
			tmp8 = tmp2 & 0x07;	 
			if (tmp2 < 0x08 && ((uint8_t)(temp_x & 0x0f) >= 0x08)) {
				return 1;
			}
			break;
		case COL_DOWN_LEFT:
		case COL_LEFT_SPIKE_BLOCK:
			tmp2 = (uint8_t)(temp_y & 0x0f);	
			tmp8 = tmp2 & 0x07;	 
			if (tmp2 >= 0x08 && ((uint8_t)(temp_x & 0x0f) < 0x08)) {
				return 1;
			}
			break;
		case COL_DOWN_RIGHT:
		case COL_RIGHT_SPIKE_BLOCK:
			tmp2 = (uint8_t)(temp_y & 0x0f);	
			tmp8 = tmp2 & 0x07;	 
			if (tmp2 >= 0x08 && ((uint8_t)(temp_x & 0x0f) >= 0x08)) {
				return 1;
			}
			break;
		case COL_BOTTOM_LEFT_SPIKE:
		case COL_BOTTOM_RIGHT_SPIKE:
		case COL_BOTTOM_SPIKES:
		case COL_BOTTOM:
			tmp2 = (uint8_t)(temp_y & 0x0f);
			tmp8 = tmp2 & 0x07;	 
			// if (tmp2 >= 0x08) {
			if (tmp8 != tmp2) {
				return 1;
			}
			break;
		case COL_TOP:
			tmp2 = (uint8_t)(temp_y & 0x0f);
			tmp8 = tmp2 & 0x07;	 
			// if (tmp2 >= 0x08) {
			if (tmp8 == tmp2) {
				return 1;
			}
			break;
		case COL_LEFT:
			tmp8 = (uint8_t)(temp_y & 0x0f) & 0x0f;	 
			if ((uint8_t)(temp_x & 0x0f) < 0x08) {
				return 1;
			}
			break;
		case COL_RIGHT:
			tmp8 = (uint8_t)(temp_y & 0x0f) & 0x0f;	 
			if ((uint8_t)(temp_x & 0x0f) >= 0x08) {
				return 1;
			}
			break;
		case COL_TOP_LEFT_BOTTOM_RIGHT:
			tmp2 = (uint8_t)(temp_y & 0x0f);	
			tmp8 = tmp2 & 0x07;	 
			if ((uint8_t)(temp_x & 0x0f) < 0x08) {
				if (tmp2 < 0x08) return 1;
			} else {
				if (tmp2 >= 0x08) return 1;
			}
			break;
		case COL_TOP_RIGHT_BOTTOM_LEFT:
			tmp2 = (uint8_t)(temp_y & 0x0f);	
			tmp8 = tmp2 & 0x07;	 
			if ((uint8_t)(temp_x & 0x0f) < 0x08) {
				if (tmp2 >= 0x08) return 1;
			} else {
				if (tmp2 < 0x08) return 1;
			}
			break;
	}
	
	return 0;
}

char bg_coll_slope();

/*
	Clobbers:
	Nothing wow

*/
char bg_side_coll_common() {
	tmp1 = Generic.y + (currplayer_mini ? (byte(0x10 - Generic.height) >> 1) : 0) + (Generic.height >> 1);

	if (currplayer_mini && (gamemode == CUBE_MODE || gamemode == ROBOT_MODE)) {
		tmp1 += (currplayer_gravity ? 3 : -2);
	}
	
	if (currplayer_was_on_slope_counter | currplayer_slope_frames) { // if we are on a slope, make right_col a little more upwards so it doesn't hit blocks to the side of the slope
		tmp1 += (currplayer_slope_type & 0b1 ? -16 : 16);
	}

	storeWordSeparately(add_scroll_y(tmp1, scroll_y), temp_y, temp_room);

	bg_collision_sub();
	
	if (gamemode == 6) {
		if (bg_coll_slope()) {
			if (!dblocked[currplayer]) {
				idx8_store(cube_data, currplayer, cube_data[currplayer] | 1);
			} 
		}	
		dblocked[currplayer] = 0;
		if (currplayer_was_on_slope_counter) return 0;
	} else {
		if (bg_coll_slope()) {
			high_byte(currplayer_y) += (high_byte(currplayer_vel_y) & 0x80 ? 2 : -2);
		}
	}

	bg_coll_spikes();

	return bg_coll_sides() || bg_coll_mini_blocks();
}

/*
	Clobbers:
	Nothing l o l
*/
char bg_coll_R() {
    // check 2 points on the right side
	temp_x = Generic.x + low_word(scroll_x) + Generic.width + (platformer ? 3 : 0); // automatically only the low byte
	return bg_side_coll_common();
}

/*
	Clobbers:
	Nothing lmao
*/
char bg_coll_L() {
    // check 2 points on the left side
	temp_x = Generic.x + low_word(scroll_x) - (platformer ? 3 : 0); // automatically only the low byte
	return bg_side_coll_common();
}


/*
	Clobbers:
	tmp2, tmp3
	Out:
	A, tmp8
*/
char bg_coll_U_D_checks() {
	switch (collision) {
		case COL_NO_SIDE:
			tmp8++;
			return 1;		
		case COL_ALL: 
			if (high_byte(currplayer_x) < 0x10 || currplayer_was_on_slope_counter) return 0;
			else return 1;
		case COL_DEATH_TOP:
			col_death_top_routine();
			break;
		case COL_DEATH_BOTTOM:
			col_death_bottom_routine();
			break;
		case COL_FLOOR_CEIL:
			dblocked[currplayer] = 1;
			return 1;
	}

	return 0;
}

void set_slope_stuff() {
	currplayer_slope_frames = (gamemode == 6 ? 3 : 2); //signal BG_COLL_R to not check stuff
	currplayer_was_on_slope_counter = (gamemode == 6 ? 6 : 4);
}

char _slope_LX22_stuff() {
	if ((uint8_t)(tmp4 + (gamemode == 6 ? 8 : 2)) <= (uint8_t)tmp5) {
		set_slope_stuff();
		currplayer_slope_type = xargs[0];
		
		last_slope_type = currplayer_slope_type;
		tmp8 = tmp5 - tmp4 - 5;
		return 1;
	} else return 0;
}
#define slope_LX22_stuff(type) (xargs[0] = type, _slope_LX22_stuff())
/*
	Clobbers:
	tmp4, tmp7
	Out:
	A, tmp8
*/
char bg_coll_slope() {	
	tmp8 = (temp_y) & 0x0f;
	switch (collision) {
		case COL_NO_SIDE:
			
			return 1;
			
		// 45 degrees

		case COL_ALL:
			if (currplayer_was_on_slope_counter | currplayer_slope_frames) {
				high_byte(currplayer_y) += (high_byte(currplayer_y) - player_old_posy[1] & 0x80 ? high_byte(currplayer_vel_x) : -high_byte(currplayer_vel_x));
				return 1;
			}
			return 0;
			

		case COL_SLOPE_LU45:
			tmp7 = (temp_x & 0x0f);	// = 0x0F - (temp_x & 0x0F)
			tmp4 = (temp_y & 0x0f) ^ 0x0f;

			if ((uint8_t)((gamemode == 6 ? 5 : -3) + tmp7) <= (uint8_t)tmp4) {
				set_slope_stuff();
				currplayer_slope_type = SLOPE_45DEG_DOWN_UD;
				tmp8 = tmp4 - tmp7 - 3;
				return 1;
			} else return 0;

		case COL_SLOPE_LD45:
			if (gamemode == 6) return 0;
			tmp7 = (temp_x & 0x0f);	// = 0x0f - (0x10 - (temp_x & 0x0f))
			tmp4 = (temp_y & 0x0f);
			
			if ((uint8_t)tmp4 >= tmp7) {
				set_slope_stuff();
				currplayer_slope_type = SLOPE_45DEG_DOWN;
				tmp8 = tmp4 - tmp7 - 3;
				return 1;
			} else return 0;

		case COL_SLOPE_RU45:
			tmp7 = (temp_x & 0x0f) ^ 0x0f;	// = 0x0F - (temp_x & 0x0F)
			tmp4 = (temp_y & 0x0f) ^ 0x0f;

			currplayer_slope_type = SLOPE_45DEG_UP_UD;
			break;

		case COL_SLOPE_RD45:
			tmp7 = (temp_x & 0x0f) ^ 0x0f;	// = 0x0F - (temp_x & 0x0F)
			tmp4 = temp_y & 0x0f;

			currplayer_slope_type = SLOPE_45DEG_UP;
			break;
		
		// 22 degrees

		case COL_SLOPE_RU22_RIGHT:
			tmp7 = ((temp_x >> 1) & 0x0f) ^ 0x0f;	// = 0x0F - (temp_x & 0x0F)
			tmp4 = (((temp_y) & 0x0e) | 0x1) ^ 0x0f;

			currplayer_slope_type = SLOPE_22DEG_UP_UD;
			break;

		case COL_SLOPE_RU22_LEFT:
			tmp7 = ((temp_x >> 1) & 0x0f) ^ 0x0f;	// = 0x0F - (temp_x & 0x0F)
			tmp4 = ((temp_y) & 0x0f) ^ 0x0f;
		
			currplayer_slope_type = SLOPE_22DEG_UP_UD;
			break;
		
		case COL_SLOPE_RD22_LEFT:
			tmp7 = ((temp_x >> 1) & 0x0f) ^ 0x0f;	// = 0x0F - (temp_x & 0x0F)
			tmp4 = ((temp_y) & 0x0e) | 0x1;

			currplayer_slope_type = SLOPE_22DEG_UP;
			break;	

		case COL_SLOPE_RD22_RIGHT:
			tmp7 = ((temp_x >> 1) & 0x0f) ^ 0x0f;	// = 0x0F - (temp_x & 0x0F)
			tmp4 = (temp_y) & 0x0f;
		
			currplayer_slope_type = SLOPE_22DEG_UP;
			break;
	
		case COL_SLOPE_LU22_RIGHT:
			tmp7 = (temp_x & 0x0f);	// = 0x0F - (temp_x & 0x0F)
			tmp5 = (temp_y & 0x0f) ^ 0x0f;
			tmp4 = (tmp7 >> 1) | 8;
			
			return slope_LX22_stuff(SLOPE_22DEG_DOWN_UD);
	
		case COL_SLOPE_LU22_LEFT:
			tmp7 = (temp_x & 0x0f);	// = 0x0F - (temp_x & 0x0F)
			tmp5 = (temp_y & 0x0f) ^ 0x0f;
			tmp4 = tmp7 >> 1;
		
			return slope_LX22_stuff(SLOPE_22DEG_DOWN_UD);

		case COL_SLOPE_LD22_RIGHT:
			tmp7 = (temp_x & 0x0f);	// = 0x0F - (temp_x & 0x0F)
			tmp5 = (temp_y & 0x0f);
			tmp4 = (tmp7 >> 1) | 8;
			
			return slope_LX22_stuff(SLOPE_22DEG_DOWN);
	
		case COL_SLOPE_LD22_LEFT:
			tmp7 = (temp_x & 0x0f);	// = 0x0F - (temp_x & 0x0F)
			tmp5 = (temp_y & 0x0f);
			tmp4 = tmp7 >> 1;
		
			return slope_LX22_stuff(SLOPE_22DEG_DOWN);
		
		// 66 degrees

		case COL_SLOPE_RD66_TOP:
			if ((uint8_t)(temp_x & 0x0f) < 0x08) return 0;
			tmp7 = (((temp_x & 0x07) << 1) & 0x0f) ^ 0x0f;	// = 0x0F - (temp_x & 0x0F)
			tmp4 = ((temp_y) & 0x0f);

			currplayer_slope_type = SLOPE_66DEG_UP;
			break;	

		case COL_SLOPE_RD66_BOT:
			if ((uint8_t)(temp_x & 0x0f) >= 0x08) return 1;
			tmp7 = (((temp_x & 0x0f) << 1) & 0x0f) ^ 0x0f;	// = 0x0F - (temp_x & 0x0F)
			tmp4 = ((temp_y) & 0x0f);

			currplayer_slope_type = SLOPE_66DEG_UP;
			break;	
			
		case COL_SLOPE_LD66_TOP:
			if ((uint8_t)(temp_x & 0x0f) >= 0x08) return 0;
			tmp7 = (((temp_x & 0x07) << 1) & 0x0f);	// = 0x0F - (temp_x & 0x0F)
			tmp4 = ((temp_y) & 0x0f);

			currplayer_slope_type = SLOPE_66DEG_DOWN;
			break;		

		case COL_SLOPE_LD66_BOT:
			if ((uint8_t)(temp_x & 0x0f) < 0x08) return 1;
			tmp7 = (((temp_x & 0x0f) << 1) & 0x0f);	// = 0x0F - (temp_x & 0x0F)
			tmp4 = ((temp_y) & 0x0f);

			currplayer_slope_type = SLOPE_66DEG_DOWN;
			break;	

		case COL_SLOPE_RU66_TOP:
			if ((uint8_t)(temp_x & 0x0f) < 0x08) return 0;
			tmp7 = (((temp_x & 0x07) << 1) & 0x0f) ^ 0x0f;	// = 0x0F - (temp_x & 0x0F)
			tmp4 = ((temp_y) & 0x0f) ^ 0x0f;

			currplayer_slope_type = SLOPE_66DEG_UP_UD;
			break;	

		case COL_SLOPE_RU66_BOT:
			if ((uint8_t)(temp_x & 0x0f) >= 0x08) return 1;
			tmp7 = (((temp_x & 0x0f) << 1) & 0x0f) ^ 0x0f;	// = 0x0F - (temp_x & 0x0F)
			tmp4 = ((temp_y) & 0x0f) ^ 0x0f;

			currplayer_slope_type = SLOPE_66DEG_UP_UD;
			break;	

		case COL_SLOPE_LU66_TOP:
			if ((uint8_t)(temp_x & 0x0f) >= 0x08) return 0;
			tmp7 = (((temp_x & 0x07) << 1) & 0x0f);	// = 0x0F - (temp_x & 0x0F)
			tmp4 = ((temp_y) & 0x0f) ^ 0x0f;

			currplayer_slope_type = SLOPE_66DEG_DOWN_UD;
			break;		

		case COL_SLOPE_LU66_BOT:
			if ((uint8_t)(temp_x & 0x0f) < 0x08) return 1;
			tmp7 = (((temp_x & 0x0f) << 1) & 0x0f);	// = 0x0F - (temp_x & 0x0F)
			tmp4 = ((temp_y) & 0x0f) ^ 0x0f;

			currplayer_slope_type = SLOPE_66DEG_DOWN_UD;
			break;	
			
		default:
			return 0;
	}
	if ((uint8_t)(tmp4) >= tmp7) {
			tmp8 = tmp4 - tmp7 + (currplayer_mini ? 2 : ((currplayer_slope_type == SLOPE_66DEG_UP) ? 1 : 0));
			
			if ((controllingplayer->a || controllingplayer->up) && (gamemode == 0 || gamemode == 4)) {
				currplayer_slope_frames = 0;
				currplayer_slope_type = 0;
			} else {
				currplayer_slope_frames = (gamemode == 6 ? 3 : 1); //signal BG_COLL_R to not check stuff
				currplayer_was_on_slope_counter = (gamemode == 6 ? 6 : 2);
			}
			return 1;
	} else if (!currplayer_was_on_slope_counter) {
			currplayer_slope_type = 0;
	}
	
	return 0;
}

/*
	Clobbers:
	tmp1
	Recursively clobbers:
	tmp2, tmp8
*/
char bg_coll_return_D () {
	tmp1 = bg_coll_U_D_checks() || bg_coll_mini_blocks();
	eject_D = tmp8;
	return tmp1;
}

/*
	Clobbers:
	tmp1
	Recursively clobbers:
	tmp2, tmp8
*/
char bg_coll_return_U () {
	tmp1 = bg_coll_U_D_checks() || bg_coll_mini_blocks();
	eject_U = tmp8 | 0xf8;
	return tmp1;
}

/*
	Clobbers:
	tmp1
	Recursively clobbers:
	tmp4, tmp7, tmp8
*/
char bg_coll_return_slope_D () {
	tmp1 = bg_coll_slope();
	if (last_slope_type & 0b1 && !(currplayer_slope_type & 0b1)) {
		if (last_slope_type != 0 && currplayer_slope_type != 0) {
			currplayer_slope_type = last_slope_type;
			tmp8 = 0;
		}
	}
	last_slope_type = currplayer_slope_type;	
	eject_D = tmp8;
	return tmp1;
}

/*
	Clobbers:
	tmp1
	Recursively clobbers:
	tmp4, tmp7, tmp8
*/
char bg_coll_return_slope_U () {
	tmp1 = bg_coll_slope();
	if (last_slope_type & 0b1 && !(currplayer_slope_type & 0b1)) {
		if (last_slope_type != 0 && currplayer_slope_type != 0) {
			currplayer_slope_type = last_slope_type;
			tmp8 = 0;
		}
	}
	last_slope_type = currplayer_slope_type;	
	eject_U = -tmp8;
	return tmp1;
}

/*
	Clobbers:
	tmp2, tmp4
	Recursively clobbers:
	tmp1, tmp2, tmp4, tmp7, tmp8
*/

#define COLL_CHECK_BOTTOM \
			bg_collision_sub(); \
			if (collision) { \
				bg_coll_spikes(); \
				if (bg_coll_return_D()) return 1; \
			}

#define COLL_CHECK_BOTTOM_NO_SPIKE \
			bg_collision_sub(); \
			if (collision) { \
				if (bg_coll_return_D()) return 1; \
			}

#define COLL_CHECK_TOP \
			bg_collision_sub(); \
			if (collision) { \
				bg_coll_spikes(); \
				if (bg_coll_return_U()) return 1; \
			}

#define COLL_CHECK_TOP_NO_SPIKE \
			bg_collision_sub(); \
			if (collision) { \
				if (bg_coll_return_U()) return 1; \
			}
			


char bg_coll_U() {
	
	// Slopes

	if (high_byte(currplayer_x) >= 0x10) {
		storeWordSeparately(
			add_scroll_y(
				Generic.y + (byte(0x10 - Generic.height) >> 1) + (currplayer_mini ? 1 : 2),
				scroll_y
			), temp_y, temp_room);
		temp_x = Generic.x + low_word(scroll_x); // middle of the cube

		tmp2 = 0;
		do {
			bg_collision_sub(); // do again but this time in the center of the cube

			if (collision) {
				// Clobbers 1, 4, 7, 8
				if(bg_coll_return_slope_U()) return 1;
			}

			temp_x += Generic.width; // automatically only the low byte
		} while (++tmp2 < 2);
	}

	if (currplayer_vel_y <= 0x00) {
		if (!currplayer_slope_frames) {
			temp_x = Generic.x + low_word(scroll_x) + (gamemode == 6 ? 4 : 0); // automatically only the low byte
			
			storeWordSeparately(
				add_scroll_y(
					Generic.y + (currplayer_mini ? byte(0x10 - Generic.height) >> 1 : 0) + 1,
					scroll_y
				), temp_y, temp_room);
			
			tmp8 = (temp_y) & 0x0f;

			COLL_CHECK_TOP_NO_SPIKE
			
			temp_x += Generic.width >> 1; // automatically only the low byte

			COLL_CHECK_TOP

			temp_x = Generic.x + low_word(scroll_x) + (Generic.width); // automatically only the low byte

			COLL_CHECK_TOP
		}
	}
	return 0;
	
}

/*
	Clobbers:
	tmp2, tmp4
	Recursively clobbers:
	tmp1, tmp2, tmp4, tmp7, tmp8
*/
char bg_coll_D() {

	// Slopes
	if (high_byte(currplayer_x) >= 0x10) {
		storeWordSeparately(
			add_scroll_y(
				Generic.y + Generic.height - 2 + (currplayer_mini ? byte(0x10 - Generic.height) >> 1 : 0), scroll_y
			), temp_y, temp_room);
		temp_x = Generic.x + low_word(scroll_x); // middle of the cube

		tmp2 = 0;
		do {
			bg_collision_sub(); // do again but this time in the center of the cube
			
			if (collision) {
				// Clobbers 1, 4, 7, 8
				if(bg_coll_return_slope_D()) return 1; 
			}
			temp_x += Generic.width; // automatically only the low byte
		} while (++tmp2 < 2);	
	}
	
	if (currplayer_vel_y >= 0x00) {
		if (!currplayer_slope_frames) {
			// check 2 points on the right side
			temp_x = Generic.x + low_word(scroll_x) + (gamemode == 6 ? 4 : 0); // automatically only the low byte

			storeWordSeparately(
				add_scroll_y(
					Generic.y + Generic.height + (currplayer_mini ? byte(0x10 - Generic.height) >> 1 : 0),
					scroll_y
				), temp_y, temp_room);

			tmp8 = (temp_y) & 0x0f;

			COLL_CHECK_BOTTOM_NO_SPIKE
			
			temp_x += Generic.width >> 1; // automatically only the low byte

			COLL_CHECK_BOTTOM

			temp_x = Generic.x + low_word(scroll_x) + (Generic.width); // automatically only the low byte

			COLL_CHECK_BOTTOM
		}
	}

	return 0;
}

#define GENERIC_X_PLUS_SCROLL tmp7
#define GENERIC_X_PLUS_SCROLL_PLUS_HALF_WIDTH tmp9
#define GENERIC_X_PLUS_SCROLL_PLUS_WIDTH tmp3

char bg_coll_U_spider() {
	temp_x = GENERIC_X_PLUS_SCROLL; // automatically only the low byte
	storeWordSeparately(
		add_scroll_y(
			Generic.y + (currplayer_mini ? byte(0x10 - Generic.height) >> 1 : 0),
			scroll_y
		), temp_y, temp_room);

	tmp8 = (temp_y) & 0x0f;

	COLL_CHECK_TOP_NO_SPIKE

	temp_x = GENERIC_X_PLUS_SCROLL_PLUS_HALF_WIDTH; // automatically only the low byte

	COLL_CHECK_TOP

	temp_x = GENERIC_X_PLUS_SCROLL_PLUS_WIDTH; // automatically only the low byte

	COLL_CHECK_TOP

	return 0;
}

char bg_coll_D_spider() {
	temp_x = GENERIC_X_PLUS_SCROLL; // automatically only the low byte
	storeWordSeparately(
		add_scroll_y(
			Generic.y + Generic.height + (currplayer_mini ? byte(0x10 - Generic.height) >> 1 : 0),
			scroll_y
		), temp_y, temp_room);
	
	tmp8 = (temp_y) & 0x0f;

	COLL_CHECK_BOTTOM_NO_SPIKE

	temp_x = GENERIC_X_PLUS_SCROLL_PLUS_HALF_WIDTH; // automatically only the low byte

	COLL_CHECK_BOTTOM

	temp_x = GENERIC_X_PLUS_SCROLL_PLUS_WIDTH; // automatically only the low byte

	COLL_CHECK_BOTTOM

	return 0;
}

#undef GENERIC_X_PLUS_SCROLL
#undef GENERIC_X_PLUS_SCROLL_PLUS_HALF_WIDTH
#undef GENERIC_X_PLUS_SCROLL_PLUS_WIDTH


/*
	Clobbers:
	tmp2
*/
void bg_coll_death() {


	// middle point collision to kill, since hitboxes don't exist

	temp_x = Generic.x + low_word(scroll_x) + (Generic.width >> 1)-1; // automatically only the low byte

	storeWordSeparately(
		add_scroll_y(
			Generic.y + (Generic.height >> 1) + (currplayer_mini ? byte(0x10 - Generic.height) >> 1 : 0),
			scroll_y
		), temp_y, temp_room);

	bg_collision_sub();
	

	if(!currplayer_gravity && collision == COL_BOTTOM) { }
	else if(currplayer_gravity && collision == COL_TOP) { }

	else if(collision >= COL_UP_LEFT && collision <= COL_TOP_RIGHT_BOTTOM_LEFT) {
		if (bg_coll_mini_blocks()) cube_data[currplayer] = 0x01; 
	}
	else {
		if ((collision == COL_ALL || collision == COL_FLOOR_CEIL) && gamemode != 0x06 && !currplayer_was_on_slope_counter) {  // wave
			if (currplayer_gravity) {
				if (currplayer_vel_y > 0) {
					cube_data[currplayer] = 0x01; 
				}
			} else {
				if (currplayer_vel_y < 0) {
					cube_data[currplayer] = 0x01; 
				}
			}

		}
		
	}

//	if(!DEBUG_MODE && cube_data[0] & 0x01) {
//		reset_level();
//	}
}

void commonly_used_store() {
		storeWordSeparately(
			add_scroll_y(
				Generic.y + (currplayer_mini ? (byte(0x10 - Generic.height) >> 1) : 0) + Generic.height - 2, scroll_y
			), temp_y, temp_room);
}			
void commonly_stored_routine_2() {
	storeWordSeparately(
		add_scroll_y(
			Generic.y + (currplayer_mini ? (byte(0x10 - Generic.height) >> 1) : 2),
			scroll_y
		), temp_y, temp_room);
}		
void tmp20f() {
	tmp2 = (uint8_t)(temp_x & 0x0f);	
}

void commonly_used_death_check() {
	if ((uint8_t)(temp_x & 0x0f) >= 0x04 && (uint8_t)(temp_x & 0x0f) < 0x09) {
		cube_data[currplayer] = 1;
	}
}


CODE_BANK_POP()
