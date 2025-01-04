
CODE_BANK_PUSH("XCD_BANK_01")

#define SLOPE_NONE			0b0000

#define SLOPE_45DEG_UP 		(SLOPE_45DEG | SLOPE_RISING) 	// 0101
#define SLOPE_45DEG_DOWN 	(SLOPE_45DEG)					// 0001
#define SLOPE_22DEG_UP 		(SLOPE_22DEG | SLOPE_RISING)	// 0110
#define SLOPE_22DEG_DOWN 	(SLOPE_22DEG)					// 0010
#define SLOPE_66DEG_UP 		(SLOPE_66DEG | SLOPE_RISING)	// 0111
#define SLOPE_66DEG_DOWN 	(SLOPE_66DEG)					// 0011

#define SLOPE_45DEG_UP_UD 	(SLOPE_45DEG | SLOPE_RISING | SLOPE_UPSIDEDOWN)	// 1101
#define SLOPE_45DEG_DOWN_UD (SLOPE_45DEG | SLOPE_UPSIDEDOWN)				// 1001
#define SLOPE_22DEG_UP_UD 	(SLOPE_22DEG | SLOPE_RISING | SLOPE_UPSIDEDOWN)	// 1110
#define SLOPE_22DEG_DOWN_UD (SLOPE_22DEG | SLOPE_UPSIDEDOWN)				// 1010
#define SLOPE_66DEG_UP_UD 	(SLOPE_66DEG | SLOPE_RISING | SLOPE_UPSIDEDOWN)	// 1111
#define SLOPE_66DEG_DOWN_UD (SLOPE_66DEG | SLOPE_UPSIDEDOWN)				// 1011

#define SLOPE_45DEG 0b01
#define SLOPE_22DEG 0b10
#define SLOPE_66DEG 0b11

// slope flags

#define SLOPE_RISING    		 0b0100
#define SLOPE_UPSIDEDOWN 		 0b1000
#define SLOPE_RISING_MASK        0b0111
#define SLOPE_DEGREES_MASK       0b0011



/* 
	Gets the collision of the current tile
	Implemented in asm
*/
char bg_collision_sub();
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
		case COL_ALL: 
			return 1;	
		case COL_BOTTOM: 
			if ((uint8_t)(temp_y & 0x08)) return 1;		// If Y pos inside block ≥ 8px
			break;
		case COL_TOP: 
			if (!(uint8_t)(temp_y & 0x08)) return 1;		// If Y pos inside block < 8px
			break;
		case COL_FLOOR_CEIL:
			if (gamemode == GAMEMODE_WAVE) return 0;
			
	};
	return 0;
}

char col_death_bottom_routine() {
	if ((uint8_t)(temp_y & 0x0f) > 0x0a) {							// If Y pos inside block ≥ 8px, die
		tmp20f();				// If Y pos inside block < 8px, die
		if (tmp2 >= 0x04 && tmp2 < 0x09) {		// If X pos even insider, die even more
			cube_data[currplayer] = 1;
			return 1;
		}
	}	
	return 0;
}

char col_death_top_routine() {
	if ((uint8_t)(temp_y & 0x0f) < 0x06) {			
		tmp20f();				// If Y pos inside block < 8px, die
		if (tmp2 >= 0x04 && tmp2 < 0x09) {		// If X pos even insider, die even more
			cube_data[currplayer] = 1;
			return 1;
		}
	}	
	return 0;
}

char col_death_right_routine() {
	if ((uint8_t)(temp_x & 0x0f) >= 0x0a) {
		tmp2 = temp_y & 0x0f;
		if (tmp2 >= 0x06 && tmp2 < 0x09) {
			cube_data[currplayer] = 1;
			return 1;
		}
	}
	return 0;
}

char col_death_left_routine() {
	if ((uint8_t)(temp_x & 0x0f) < 0x06) {
		tmp2 = temp_y & 0x0f;
		if (tmp2 >= 0x06 && tmp2 < 0x09) {
			cube_data[currplayer] = 1;
			return 1;
		}
	}
	return 0;
}

/*
	Clobbers:
	tmp2
*/
char bg_coll_spikes() {
	switch (collision) {
		case COL_DEATH_LEFT:
			return col_death_left_routine();

		case COL_DEATH_RIGHT:
			return col_death_right_routine();

		case COL_DEATH_TOP:
			return col_death_top_routine();	

		case COL_TOP_SPIKES:
		case COL_DEATH_BOTTOM:
			return col_death_bottom_routine();	
			
		case COL_DEATH_BOTTOM_LEFT:
			return col_death_left_routine() | col_death_bottom_routine();

		case COL_DEATH_BOTTOM_RIGHT:
			return col_death_right_routine() | col_death_bottom_routine();

		case COL_DEATH_TOP_LEFT:
			return col_death_left_routine() | col_death_top_routine();
		
		case COL_DEATH_TOP_RIGHT:
			return col_death_right_routine() | col_death_top_routine();

		case COL_DEATH:	
			tmp2 = (uint8_t)(temp_y & 0x0f);
			if (tmp2 >= 0x04 && tmp2 < 0x0c) {
				tmp20f();
				if (tmp2 >= 0x04 && tmp2 < 0x09) {
					break;
				}
			}
			return 0;
		case COL_LEFT_SPIKE_BLOCK:
		case COL_BOTTOM_LEFT_SPIKE:
			if (!(uint8_t)(temp_y & 0x08)) {
				tmp20f();
				if (tmp2 >= 0x02 && tmp2 < 0x06)
					break;
			}
			return 0;
		case COL_RIGHT_SPIKE_BLOCK:
		case COL_BOTTOM_RIGHT_SPIKE:
			if (!(uint8_t)(temp_y & 0x08)) {
				tmp20f();
				if (tmp2 >= 0x0a && tmp2 < 0x0d)
					break;
			}
			return 0;
		case COL_BOTTOM_SPIKES:
			if (!(uint8_t)(temp_y & 0x08)) {
				tmp2 = (uint8_t)(temp_x & 0x07);
				if (tmp2 >= 0x02 && tmp2 < 0x06)
					break;
			}
			return 0;
			case COL_UP_LEFT_SPIKE:
			if (!(uint8_t)(temp_y & 0x08)) {
				tmp20f();
				if (tmp2 >= 0x02 && tmp2 < 0x06)
					break;
			}
			return 0;
		case COL_UP_RIGHT_SPIKE:
			if (!(uint8_t)(temp_y & 0x08)) {
				tmp20f();
				if (tmp2 >= 0x0a && tmp2 < 0x0d)
					break;
			}
			return 0;
		case COL_UP_BOTH_SPIKES:
			if (!(uint8_t)(temp_y & 0x08)) {
				tmp2 = (uint8_t)(temp_x & 0x07);
				if (tmp2 >= 0x02 && tmp2 < 0x06)
					break;
			}
			return 0;
		case COL_DOWN_LEFT_SPIKE:
			if ((uint8_t)(temp_y & 0x08)) {
				tmp20f();
				if (tmp2 >= 0x02 && tmp2 < 0x06)
					break;
			}
			return 0;
		case COL_DOWN_RIGHT_SPIKE:
			if ((uint8_t)(temp_y & 0x08)) {
				tmp20f();
				if (tmp2 >= 0x0a && tmp2 < 0x0d)
					break;
			}
			return 0;
		case COL_DOWN_BOTH_SPIKES:
			if ((uint8_t)(temp_y & 0x08)) {
				tmp2 = (uint8_t)(temp_x & 0x07);
				if (tmp2 >= 0x02 && tmp2 < 0x06)
					break;
			}
			return 0;
		default: return 0;
	}
	cube_data[currplayer] = 1;		
	return 1;					
}

/*
	Clobbers:
	tmp8
*/
void bg_coll_floor_spikes() { // used for spike collision
	if (currplayer_vel_y != 0) {
		currplayer_direction = high_byte(currplayer_vel_y) & 0x80;
	}

	// TOP	
	temp_x = Generic.x + low_word(scroll_x) + 3; // automatically only the low byte

	commonly_used_store();

	bg_collision_sub();

	if (collision) {
		if (bg_coll_spikes()) return;
	}

	temp_x += Generic.width - 6; // automatically only the low byte
	
	bg_collision_sub();

	if (collision) {
		if (bg_coll_spikes()) return;
	}

	// BOTTOM
	temp_x = Generic.x + low_word(scroll_x) + 3; // automatically only the low byte

	commonly_stored_routine_2();

	bg_collision_sub();

	if (collision) {
		if (bg_coll_spikes()) return;
	}

	temp_x += Generic.width - 6; // automatically only the low byte

	bg_collision_sub();

	if (collision) {
		if (bg_coll_spikes()) return;
	}
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
		case COL_TOP_SPIKES:
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
		case COL_TOP_RIGHT_STAIRS:
			tmp2 = (uint8_t)(temp_y & 0x0f);	
			tmp4 = (uint8_t)(temp_x & 0x0f);	 
			tmp8 = tmp2 & 0x07;	 

			if (tmp2 >= 0x08 && tmp4 < 0x08) {
				break;
			}
			return 1;
			
		case COL_TOP_LEFT_STAIRS:
			tmp2 = (uint8_t)(temp_y & 0x0f);	
			tmp4 = (uint8_t)(temp_x & 0x0f);	 
			tmp8 = tmp2 & 0x07;	 

			if (tmp2 >= 0x08 && tmp4 >= 0x08) {
				break;
			}
			return 1;
		
		case COL_BOTTOM_RIGHT_STAIRS:
			tmp2 = (uint8_t)(temp_y & 0x0f);	
			tmp4 = (uint8_t)(temp_x & 0x0f);	 
			tmp8 = tmp2 & 0x07;	 

			if (tmp2 < 0x08 && tmp4 < 0x08) {
				break;
			}
			return 1;
		
		case COL_BOTTOM_LEFT_STAIRS:
			tmp2 = (uint8_t)(temp_y & 0x0f);	
			tmp4 = (uint8_t)(temp_x & 0x0f);	 
			tmp8 = tmp2 & 0x07;	 

			if (tmp2 < 0x08 && tmp4 >= 0x08) {
				break;
			}
			return 1;
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

	if (currplayer_mini && (gamemode == GAMEMODE_CUBE || gamemode == GAMEMODE_ROBOT)) {
		tmp1 += (currplayer_gravity ? 3 : -2);
	}
	
	if (currplayer_was_on_slope_counter | currplayer_slope_frames) { // if we are on a slope, make right_col a little more upwards so it doesn't hit blocks to the side of the slope
		return 0;
	}

	storeWordSeparately(add_scroll_y(tmp1, scroll_y), temp_y, temp_room);

	bg_collision_sub();
	if (collision) {
		if (gamemode == GAMEMODE_WAVE) {
			if (bg_coll_slope()) {
				if (!dblocked[currplayer]) {
					idx8_store(cube_data, currplayer, cube_data[currplayer] | 1);
				} 
			}	
			dblocked[currplayer] = 0;
		} else {
			if (!currplayer_was_on_slope_counter && bg_coll_slope()) {
				high_byte(currplayer_y) += (currplayer_slope_type & SLOPE_UPSIDEDOWN ? 2 : -2);
			}
		}

		if (bg_coll_spikes()) return 0;

		return bg_coll_sides() || bg_coll_mini_blocks();
	} 
	
	return 0;
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
			return 1;		
		case COL_ALL: 
			if (high_byte(currplayer_x) < 0x10) return 0;
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
void unstick() {
	tmp8 = 4;
}

void clear_slope_vars() {
	currplayer_was_on_slope_counter = 0;
	currplayer_slope_frames = 0;
	currplayer_slope_type = 0;
	currplayer_last_slope_type = 0;
}

char a_check_lookup[] = {
	1, 0, 0, 1, 1, 0, 0, 1
};
/*
	Clobbers:
	tmp4, tmp7
	Out:
	A, tmp8
*/
char bg_coll_slope() {	

	static const void * const jumpTable[] = {
		&&col_default,	&&col_default,	&&col_default,	&&col_default,	// 0x00 - 0x03
		&&col_default,	&&col_default,	&&col_default,	&&col_default,	// 0x04 - 0x07
		&&col_default,	&&col_default,	&&col_default,	// 0x08 - 0x0A

		&&col_slope_RD45,	&&col_slope_LD45,
		&&col_slope_RD22_RIGHT,	&&col_slope_LD22_RIGHT,
		&&col_slope_RD22_LEFT,	&&col_slope_LD22_LEFT,
		&&col_slope_RD66_TOP,	&&col_slope_LD66_TOP,
		&&col_slope_RD66_BOT,	&&col_slope_LD66_BOT,
		&&col_slope_RU45,	&&col_slope_LU45,
		&&col_slope_RU22_LEFT,	&&col_slope_RU22_RIGHT,
		&&col_slope_LU22_LEFT,	&&col_slope_LU22_RIGHT,
		&&col_slope_RU66_TOP,	&&col_slope_LU66_TOP,
		&&col_slope_RU66_BOT,	&&col_slope_LU66_BOT
	};

	tmp8 = (temp_y) & 0x0f;

	do_if_not_in_range(collision, COL_SLOPE_RD45, COL_SLOPE_LU66_BOT, {return 0;});
	goto *jumpTable[collision];

	col_default:
		return 0;

	// 45 degrees

	col_slope_LU45:
		tmp7 = (temp_x & 0x0f);	// = 0x0F - (temp_x & 0x0F)
		tmp4 = (temp_y & 0x0f) ^ 0x0f;

		currplayer_slope_type = SLOPE_45DEG_DOWN_UD;
		goto col_end;

	col_slope_LD45:
		tmp7 = (temp_x & 0x0f);	// = 0x0f - (0x10 - (temp_x & 0x0f))
		tmp4 = (temp_y & 0x0f);
		
		currplayer_slope_type = SLOPE_45DEG_DOWN;
		goto col_end;

	col_slope_RU45:
		tmp7 = (temp_x & 0x0f) ^ 0x0f;	// = 0x0F - (temp_x & 0x0F)
		tmp4 = (temp_y & 0x0f) ^ 0x0f;

		currplayer_slope_type = SLOPE_45DEG_UP_UD;
		goto col_end;

	col_slope_RD45:
		tmp7 = (temp_x & 0x0f) ^ 0x0f;	// = 0x0F - (temp_x & 0x0F)
		tmp4 = temp_y & 0x0f;

		currplayer_slope_type = SLOPE_45DEG_UP;
		goto col_end;
		
	// 22 degrees

	col_slope_RU22_RIGHT:
		tmp7 = ((temp_x >> 1) & 0x07) ^ 0x0f;	// = 0x0F - (temp_x & 0x0F)
		tmp4 = (temp_y & 0x0f) ^ 0x0f;
		
		currplayer_slope_type = SLOPE_22DEG_UP_UD;
		goto col_end;

	col_slope_RU22_LEFT:
		tmp7 = (((temp_x >> 1) | 0x8) & 0x0f) ^ 0x0f;	// = 0x0F - (temp_x & 0x0F)
		tmp4 = (temp_y & 0x0f) ^ 0x0f;
	
		currplayer_slope_type = SLOPE_22DEG_UP_UD;
		goto col_end;
	
	col_slope_RD22_RIGHT:
		tmp7 = ((temp_x >> 1) & 0x07) ^ 0x0f;	// = 0x0F - (temp_x & 0x0F)
		tmp4 = (temp_y & 0x0f);

		currplayer_slope_type = SLOPE_22DEG_UP;
		goto col_end;	

	col_slope_RD22_LEFT:
		tmp7 = (((temp_x >> 1) | 0x8) & 0x0f) ^ 0x0f;	// = 0x0F - (temp_x & 0x0F)
		tmp4 = (temp_y & 0x0f);
	
		currplayer_slope_type = SLOPE_22DEG_UP;
		goto col_end;

	col_slope_LU22_RIGHT:
		tmp7 = ((temp_x >> 1) & 0x07);	// = 0x0F - (temp_x & 0x0F)
		tmp4 = (temp_y & 0x0f) ^ 0x0f;
		
		currplayer_slope_type = SLOPE_22DEG_DOWN_UD;
		goto col_end;

	col_slope_LU22_LEFT:
		tmp7 = (((temp_x >> 1) | 0x8) & 0x0f);	// = 0x0F - (temp_x & 0x0F)
		tmp4 = (temp_y & 0x0f) ^ 0x0f;
	
		currplayer_slope_type = SLOPE_22DEG_DOWN_UD;
		goto col_end;

	col_slope_LD22_RIGHT:
		tmp7 = ((temp_x >> 1) & 0x07);	// = 0x0F - (temp_x & 0x0F)
		tmp4 = (temp_y & 0x0f);

		currplayer_slope_type = SLOPE_22DEG_DOWN;
		goto col_end;	

	col_slope_LD22_LEFT:
		tmp7 = (((temp_x >> 1) | 0x8) & 0x0f);	// = 0x0F - (temp_x & 0x0F)
		tmp4 = (temp_y & 0x0f);
	
		currplayer_slope_type = SLOPE_22DEG_DOWN;
		goto col_end;
	
	// 66 degrees

	col_slope_RD66_TOP:
		if ((uint8_t)(temp_x & 0x0f) < 0x08) return 0;
		tmp7 = (((temp_x & 0x07) << 1) & 0x0f) ^ 0x0f;	// = 0x0F - (temp_x & 0x0F)
		tmp4 = ((temp_y) & 0x0f);

		currplayer_slope_type = SLOPE_66DEG_UP;
		goto col_end;	

	col_slope_RD66_BOT:
		if ((uint8_t)(temp_x & 0x0f) >= 0x08) return 1;
		tmp7 = (((temp_x & 0x0f) << 1) & 0x0f) ^ 0x0f;	// = 0x0F - (temp_x & 0x0F)
		tmp4 = ((temp_y) & 0x0f);

		currplayer_slope_type = SLOPE_66DEG_UP;
		goto col_end;	
		
	col_slope_LD66_TOP:
		if ((uint8_t)(temp_x & 0x0f) >= 0x08) return 0;
		tmp7 = (((temp_x & 0x07) << 1) & 0x0f);	// = 0x0F - (temp_x & 0x0F)
		tmp4 = ((temp_y) & 0x0f);

		currplayer_slope_type = SLOPE_66DEG_DOWN;
		goto col_end;		

	col_slope_LD66_BOT:
		if ((uint8_t)(temp_x & 0x0f) < 0x08) return 1;
		tmp7 = (((temp_x & 0x0f) << 1) & 0x0f);	// = 0x0F - (temp_x & 0x0F)
		tmp4 = ((temp_y) & 0x0f);

		currplayer_slope_type = SLOPE_66DEG_DOWN;
		goto col_end;	

	col_slope_RU66_TOP:
		if ((uint8_t)(temp_x & 0x0f) < 0x08) return 0;
		tmp7 = (((temp_x & 0x07) << 1) & 0x0f) ^ 0x0f;	// = 0x0F - (temp_x & 0x0F)
		tmp4 = ((temp_y) & 0x0f) ^ 0x0f;

		currplayer_slope_type = SLOPE_66DEG_UP_UD;
		goto col_end;	

	col_slope_RU66_BOT:
		if ((uint8_t)(temp_x & 0x0f) >= 0x08) return 1;
		tmp7 = (((temp_x & 0x0f) << 1) & 0x0f) ^ 0x0f;	// = 0x0F - (temp_x & 0x0F)
		tmp4 = ((temp_y) & 0x0f) ^ 0x0f;

		currplayer_slope_type = SLOPE_66DEG_UP_UD;
		goto col_end;	

	col_slope_LU66_TOP:
		if ((uint8_t)(temp_x & 0x0f) >= 0x08) return 0;
		tmp7 = (((temp_x & 0x07) << 1) & 0x0f);	// = 0x0F - (temp_x & 0x0F)
		tmp4 = ((temp_y) & 0x0f) ^ 0x0f;

		currplayer_slope_type = SLOPE_66DEG_DOWN_UD;
		goto col_end;		

	col_slope_LU66_BOT:
		if ((uint8_t)(temp_x & 0x0f) < 0x08) return 1;
		tmp7 = (((temp_x & 0x0f) << 1) & 0x0f);	// = 0x0F - (temp_x & 0x0F)
		tmp4 = ((temp_y) & 0x0f) ^ 0x0f;

		currplayer_slope_type = SLOPE_66DEG_DOWN_UD;
	
	col_end:
	if ((uint8_t)(tmp4) >= tmp7) {
			tmp8 = tmp4 - tmp7;

			if (gamemode == GAMEMODE_CUBE || gamemode == GAMEMODE_ROBOT) {
				if ((controllingplayer->a || controllingplayer->up)) {
					make_cube_jump_higher = 1;
					
				} else {
					currplayer_slope_frames = 1; //signal BG_COLL_R to not check stuff
					currplayer_was_on_slope_counter = 3;
				}
			} else {
				tmp4 = 0;
				if (currplayer_slope_type & SLOPE_RISING) {
					tmp4 |= 0b100;
				}
				if (currplayer_slope_type & SLOPE_UPSIDEDOWN) {
					tmp4 |= 0b010;
				}
				if (currplayer_gravity) {
					tmp4 |= 0b001;
				}

				if (a_check_lookup[tmp4]) {
					if (controllingplayer->a || controllingplayer->up) {
						unstick();
					}
				} else {
					if (!(controllingplayer->a || controllingplayer->up)) {
						unstick();
					}
				}	

				currplayer_slope_frames = 1; //signal BG_COLL_R to not check stuff
				currplayer_was_on_slope_counter = 3;
			}
			
			return 1;
	} else if (!currplayer_was_on_slope_counter) {
			currplayer_slope_type = 0;
			tmp8 = 0;
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
	tmp3 = bg_coll_U_D_checks();
	tmp1 = bg_coll_mini_blocks();
	eject_U = tmp8 | (tmp3 ? 0xf0 : 0xf8);
	return tmp1 | tmp3;
}

/*
	Clobbers:
	tmp1
	Recursively clobbers:
	tmp4, tmp7, tmp8
*/
char bg_coll_return_slope_D () {
	tmp1 = bg_coll_slope();
	
	if (!tmp2) {
		// LEFT CHECK
		if (currplayer_slope_type & SLOPE_RISING) {
			currplayer_slope_type = currplayer_last_slope_type;
			return 0;
		}
	} else {
		// RIGHT CHECK
		if (!(currplayer_slope_type & SLOPE_RISING)) {
			currplayer_slope_type = currplayer_last_slope_type;
			return 0;
		}
	}
	if (tmp1) {
		if ((currplayer_last_slope_type & SLOPE_RISING) && !(currplayer_slope_type & SLOPE_RISING)) {
			if (currplayer_last_slope_type != 0 && currplayer_slope_type != 0) {
				currplayer_slope_type = currplayer_last_slope_type;
				tmp8 = high_byte(currplayer_vel_x);
			}
		}
		if (currplayer_slope_type != 0) currplayer_last_slope_type = currplayer_slope_type;	
		eject_D = tmp8;
	}
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

	if (!tmp2) {
		// LEFT CHECK
		if (currplayer_slope_type & SLOPE_RISING) {
			currplayer_slope_type = currplayer_last_slope_type;
			return 0;
		}
	} else {
		// RIGHT CHECK
		if (!(currplayer_slope_type & SLOPE_RISING)) {
			currplayer_slope_type = currplayer_last_slope_type;
			return 0;
		}
	}

	if (tmp1) {
		if ((currplayer_last_slope_type & SLOPE_RISING) && !(currplayer_slope_type & SLOPE_RISING)) {
			if (currplayer_last_slope_type != 0 && currplayer_slope_type != 0) {
				currplayer_slope_type = currplayer_last_slope_type;
				tmp8 = high_byte(currplayer_vel_x);
			}
		}
		if (currplayer_slope_type != 0) currplayer_last_slope_type = currplayer_slope_type;	
		eject_U = -tmp8;
	}
	return tmp1;
}

/*
	Clobbers:
	tmp2, tmp4
	Recursively clobbers:
	tmp1, tmp2, tmp4, tmp7, tmp8
*/

// in case of snap, dont kill player	
#define COLL_CHECK_BOTTOM \
			bg_collision_sub(); \
			if (collision) { \
				if (bg_coll_return_D()) { \
					idx8_store(cube_data, currplayer, cube_data[currplayer] & 0b1111110); \
					return 1; \
				} \
			}
			
// in case of snap, dont kill player	
#define COLL_CHECK_TOP \
			bg_collision_sub(); \
			if (collision) { \
				if (bg_coll_return_U()) { \
					idx8_store(cube_data, currplayer, cube_data[currplayer] & 0b1111110); \
					return 1; \
				} \
			}
			


char bg_coll_U() {
	
	// Slopes

	if (high_byte(currplayer_x) >= 0x10) {
		storeWordSeparately(
			add_scroll_y(
				Generic.y + (byte(0x10 - Generic.height) >> 1) + (currplayer_mini ? 1 : 2) + (gamemode == GAMEMODE_SHIP ? 1 : 0),
				scroll_y
			), temp_y, temp_room);
		temp_x = Generic.x + low_word(scroll_x); // middle of the cube

		tmp2 = 0;
		low_byte(tmp3) = 0;
		do {
			bg_collision_sub(); // do again but this time in the center of the cube

			if (collision) {
				// Clobbers 1, 4, 7, 8
				low_byte(tmp3) |= bg_coll_return_slope_U();
			}

			temp_x += Generic.width; // automatically only the low byte
		} while (++tmp2 < 2);
		if (low_byte(tmp3)) return 1;
	}

	if (high_byte(currplayer_vel_y) & 0x80) {
		temp_x = Generic.x + low_word(scroll_x) + (gamemode == GAMEMODE_WAVE ? 4 : 0); // automatically only the low byte
		
		storeWordSeparately(
			add_scroll_y(
				Generic.y + (currplayer_mini ? byte(0x10 - Generic.height) >> 1 : 0) + 1,
				scroll_y
			), temp_y, temp_room);
		
		tmp8 = (temp_y) & 0x0f;

		COLL_CHECK_TOP
		
		temp_x += Generic.width >> 1; // automatically only the low byte

		COLL_CHECK_TOP

		temp_x = Generic.x + low_word(scroll_x) + (Generic.width); // automatically only the low byte

		COLL_CHECK_TOP
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
		low_byte(tmp3) = 0;
		do {
			bg_collision_sub(); // do again but this time in the center of the cube
			
			if (collision) {
				// Clobbers 1, 4, 7, 8
				low_byte(tmp3) |= bg_coll_return_slope_D();
			}
			temp_x += Generic.width; // automatically only the low byte
		} while (++tmp2 < 2);	
		if (low_byte(tmp3)) return 1;
	}
	
	if (!(high_byte(currplayer_vel_y) & 0x80)) {
		// check 2 points on the right side
		temp_x = Generic.x + low_word(scroll_x) + (gamemode == GAMEMODE_WAVE ? 4 : 0); // automatically only the low byte

		storeWordSeparately(
			add_scroll_y(
				Generic.y + Generic.height + (currplayer_mini ? byte(0x10 - Generic.height) >> 1 : 0),
				scroll_y
			), temp_y, temp_room);

		tmp8 = (temp_y) & 0x0f;

		COLL_CHECK_BOTTOM
		
		temp_x += Generic.width >> 1; // automatically only the low byte

		COLL_CHECK_BOTTOM

		temp_x = Generic.x + low_word(scroll_x) + (Generic.width); // automatically only the low byte

		COLL_CHECK_BOTTOM
	}

	return 0;
}

#define LEFT_POS tmp7
#define RIGHT_POS tmp9

char bg_coll_U_spider() {
	temp_x = LEFT_POS; // automatically only the low byte
	storeWordSeparately(
		add_scroll_y(
			Generic.y + (currplayer_mini ? byte(0x10 - Generic.height) >> 1 : 0),
			scroll_y
		), temp_y, temp_room);

	tmp8 = (temp_y) & 0x0f;

	COLL_CHECK_TOP

	temp_x = RIGHT_POS; // automatically only the low byte

	COLL_CHECK_TOP

	return 0;
}

char bg_coll_D_spider() {
	temp_x = LEFT_POS; // automatically only the low byte
	storeWordSeparately(
		add_scroll_y(
			Generic.y + Generic.height + (currplayer_mini ? byte(0x10 - Generic.height) >> 1 : 0),
			scroll_y
		), temp_y, temp_room);
	
	tmp8 = (temp_y) & 0x0f;

	COLL_CHECK_BOTTOM

	temp_x = RIGHT_POS; // automatically only the low byte

	COLL_CHECK_BOTTOM

	return 0;
}
#undef LEFT_POS
#undef RIGHT_POS


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
	
	if (collision) {
		if (bg_coll_U_D_checks() | bg_coll_mini_blocks() | bg_coll_spikes() | bg_coll_slope()) {
			cube_data[currplayer] |= 1;
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
