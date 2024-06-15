/* 
	Gets the collision of the current tile
	Implemented in asm
*/
__fastcall__ char bg_collision_sub(void);

/*
	Out:
	A
*/
char bg_coll_sides() {
	switch (collision) {
		case COL_BOTTOM: 
			if (temp_y & 0x08) return 1;		// If Y pos inside block ≥ 8px
			break;	
		case COL_TOP: 
			if (!(temp_y & 0x08)) return 1;		// If Y pos inside block < 8px
			break;	
		case COL_ALL: 
			return 1;		
		case COL_UP_LEFT:
			tmp2 = temp_y & 0x0f;	
			tmp8 = tmp2 & 0x07;	 
			if (tmp2 < 0x08 && ((uint8_t)(temp_x & 0x0f) < 0x08)) {
				return 1;
			}
			break;
	};
	return 0;
}
/*
	Clobbers:
	tmp2
*/
void bg_coll_spikes() {
	switch (collision) {
		case COL_DOWN_LEFT_SPIKE:
			if ((temp_y & 0x08)) {
				tmp2 = (uint8_t)(temp_x & 0x0f);
				if (tmp2 >= 0x02 && tmp2 < 0x06)
					cube_data[currplayer] = 1;						
			}
			break;
		case COL_DOWN_RIGHT_SPIKE:
			if ((temp_y & 0x08)) {
				tmp2 = (uint8_t)(temp_x & 0x0f);
				if (tmp2 >= 0x0a && tmp2 < 0x0d)
					cube_data[currplayer] = 1;						
			}
			break;
		case COL_DEATH_LEFT:
			if ((uint8_t)(temp_x & 0x0f) < 0x06) {
				tmp2 = temp_y & 0x0f;
				if (tmp2 >= 0x06 && tmp2 < 0x09) cube_data[currplayer] = 1;
			}
			break;
		case COL_DEATH_RIGHT:
			if ((uint8_t)(temp_x & 0x0f) >= 0x0a) {
				tmp2 = temp_y & 0x0f;
				if (tmp2 >= 0x06 && tmp2 < 0x09) cube_data[currplayer] = 1;
			}
			break;
		case COL_DEATH_TOP:
			if ((uint8_t)(temp_y & 0x0f) < 0x04) {			
				tmp2 = (uint8_t)(temp_x & 0x0f);				// If Y pos inside block < 8px, die
				if (tmp2 >= 0x06 && tmp2 < 0x0a) {		// If X pos even insider, die even more
					cube_data[currplayer] = 1;						
				}
			}		
			break;
		case COL_DEATH_BOTTOM:
			if ((uint8_t)(temp_y & 0x0f) > 0x0c) {							// If Y pos inside block ≥ 8px, die
				tmp2 = (uint8_t)(temp_x & 0x0f);				// If Y pos inside block < 8px, die
				if (tmp2 >= 0x06 && tmp2 < 0x0a) {		// If X pos even insider, die even more
					cube_data[currplayer] = 1;						
				}
			}								// else nothing
			break;
		case COL_DEATH:	
			tmp2 = (uint8_t)(temp_y & 0x0f);
			if (tmp2 >= 0x04 && tmp2 < 0x0c) {
				tmp2 = (uint8_t)(temp_x & 0x0f);
				if (tmp2 >= 0x03 && tmp2 < 0x09) {
					cube_data[currplayer] = 0x01;
				}
			}
			break;
		case COL_LEFT_SPIKE_BLOCK:
		case COL_BOTTOM_LEFT_SPIKE:
			if (!(temp_y & 0x08)) {
				tmp2 = (uint8_t)(temp_x & 0x0f);
				if (tmp2 >= 0x02 && tmp2 < 0x06)
					cube_data[currplayer] = 1;						
			}
			break;
		case COL_RIGHT_SPIKE_BLOCK:
		case COL_BOTTOM_RIGHT_SPIKE:
			if (!(temp_y & 0x08)) {
				tmp2 = (uint8_t)(temp_x & 0x0f);
				if (tmp2 >= 0x0a && tmp2 < 0x0d)
					cube_data[currplayer] = 1;											
			}
			break;
		case COL_BOTTOM_SPIKES:
			if (!(temp_y & 0x08)) {
				tmp2 = (uint8_t)(temp_x & 0x07);
				if (tmp2 >= 0x02 && tmp2 < 0x06)
					cube_data[currplayer] = 1;						
			}
			break;
	}
}

/*
	Clobbers:
	tmp8
*/
void bg_coll_floor_spikes() { // used just for checking ground spikes on the floor
	temp_x = Generic.x + low_word(scroll_x) + (Generic.width); // automatically only the low byte

	__A__ = Generic.y + (mini ? (byte(0x10 - Generic.height) >> 1) : 1);
	storeWordSeparately(add_scroll_y(__A__, scroll_y), temp_y, temp_room);

	for (tmp8 = 0; tmp8 < 2; tmp8++) {
		bg_collision_sub();
	
		bg_coll_spikes();
			
		__A__ = Generic.y + (mini ? (byte(0x10 - Generic.height) >> 1) : 0) + Generic.height - 1;
		storeWordSeparately(add_scroll_y(__A__, scroll_y), temp_y, temp_room);
	}
}
/*
	Clobbers:
	tmp2, tmp8
*/
char bg_coll_mini_blocks() {
	switch (collision) {
		case COL_UP_LEFT:
			tmp2 = temp_y & 0x0f;	
			tmp8 = tmp2 & 0x07;	 
			if (tmp2 < 0x08 && ((uint8_t)(temp_x & 0x0f) < 0x08)) {
				return 1;
			}
			break;
		case COL_UP_RIGHT:
			tmp2 = temp_y & 0x0f;	
			tmp8 = tmp2 & 0x07;	 
			if (tmp2 < 0x08 && ((uint8_t)(temp_x & 0x0f) >= 0x08)) {
				return 1;
			}
			break;
		case COL_DOWN_LEFT:
		case COL_LEFT_SPIKE_BLOCK:
			tmp2 = temp_y & 0x0f;	
			tmp8 = tmp2 & 0x07;	 
			if (tmp2 >= 0x08 && ((uint8_t)(temp_x & 0x0f) < 0x08)) {
				return 1;
			}
			break;
		case COL_DOWN_RIGHT:
		case COL_RIGHT_SPIKE_BLOCK:
			tmp2 = temp_y & 0x0f;	
			tmp8 = tmp2 & 0x07;	 
			if (tmp2 >= 0x08 && ((uint8_t)(temp_x & 0x0f) >= 0x08)) {
				return 1;
			}
			break;
		case COL_BOTTOM_LEFT_SPIKE:
		case COL_BOTTOM_RIGHT_SPIKE:
		case COL_BOTTOM_SPIKES:
		case COL_BOTTOM:
			tmp2 = temp_y & 0x0f;
			tmp8 = tmp2 & 0x07;	 
			// if (tmp2 >= 0x08) {
			if (tmp8 != tmp2) {
				return 1;
			}
			break;
		case COL_TOP:
			tmp2 = temp_y & 0x0f;
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
			tmp2 = temp_y & 0x0f;	
			tmp8 = tmp2 & 0x07;	 
			if ((uint8_t)(temp_x & 0x0f) < 0x08) {
				if (tmp2 < 0x08) return 1;
			} else {
				if (tmp2 >= 0x08) return 1;
			}
			break;
		case COL_TOP_RIGHT_BOTTOM_LEFT:
			tmp2 = temp_y & 0x0f;	
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



/*
	Clobbers:
	Nothing wow

*/
char bg_side_coll_common() {
	tmp1 = Generic.y + (mini ? (byte(0x10 - Generic.height) >> 1) : 0) + (Generic.height >> 1);

	if (slope_frames > 0) { // if we are on a slope, make right_col a little more upwards so it doesn't hit blocks to the side of the slope
		tmp1 -= (currplayer_gravity ? 8 : -8);
		slope_frames -= 1;
	}

	storeWordSeparately(add_scroll_y(tmp1, scroll_y), temp_y, temp_room);

	bg_collision_sub();
	
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
		case COL_ALL: 
			return 1;
		case COL_DEATH_TOP:
			tmp2 = temp_y & 0x0f;	
			tmp8 = tmp2 & 0x07;	 
			// if (tmp2 < 0x08) {
			if (tmp8 == tmp2) {
				if (collision == COL_DEATH_TOP) {
					// if (tmp2 < 0x04) {
					if (!(tmp2 & 0x0C)) {
						// if ((temp_x & 0x0f) >= 0x04 && (temp_x & 0x0f) < 0x0c) {
						if (!((temp_x - 0x04) & 0x08)) {
							cube_data[currplayer] = 1;
						}
					}
				} else return 1;
			}
			break;
		case COL_DEATH_BOTTOM:
			tmp2 = temp_y & 0x0f;
			tmp8 = tmp2 & 0x07;	 
			// if (tmp2 >= 0x08) {
			if (tmp8 != tmp2) {
				if (collision == COL_DEATH_BOTTOM) {
					if (tmp2 >= 0x0c) {
						// if ((temp_x & 0x0f) >= 0x04 && (temp_x & 0x0f) < 0x0c) {
						if (!((temp_x - 0x04) & 0x08)) {
							cube_data[currplayer] = 1;
						}
					}
				} else return 1;
			}
			break;
		case COL_FLOOR_CEIL:
			kandowavewalk = 1;
			return 1;
	}

	return 0;
}
#define SLOPE_NONE			0
#define SLOPE_45DEG_UP 		1
#define SLOPE_45DEG_DOWN 	2
#define SLOPE_22DEG_UP 		3
#define SLOPE_22DEG_DOWN 	4
#define SLOPE_66DEG_UP 		5
#define SLOPE_66DEG_DOWN 	6

/*
	Clobbers:
	tmp4, tmp7
	Out:
	A, tmp8
*/
char bg_coll_slope() {	
	switch (collision) {
		case COL_SLOPE_SUPPORT:
			tmp8 = (temp_y + (currplayer_gravity ? -1 : 1));
			if (!(slope_type & 1)) {
				tmp8 += (currplayer_gravity ? -8 : 8);
			}
			tmp8 &= 0x0f;
			slope_frames = 2;
			was_on_slope_counter = 2;
			return 1;
		case COL_SLOPE_RD:
			tmp7 = (temp_x & 0x0f) ^ 0x0f;	// = 0x0F - (temp_x & 0x0F)
			tmp4 = temp_y & 0x0f;

			// if (tmp4 >= (tmp7 - 3)) {
			if ((uint8_t)(tmp4 + 3) >= tmp7) {
				tmp8 = tmp4 - tmp7;
				if (pad[controllingplayer] & PAD_A) {
					slope_frames = 0;
				} else {
					slope_frames = 2; //signal BG_COLL_R to not check stuff
					slope_type = SLOPE_45DEG_UP;
					was_on_slope_counter = 2;
				}
				return 1;
			} 
			break;
		case COL_SLOPE_LD:
			tmp7 = 0x0f - 0x10 + (temp_x & 0x0f);	// = 0x0f - (0x10 - (temp_x & 0x0f))
			tmp4 = temp_y & 0x0f;

			// if (tmp4 >= (tmp7 - 3)) {
			if ((uint8_t)(tmp4 + 3) >= tmp7) {
				tmp8 = tmp4 - tmp7 - 5;
				slope_type = SLOPE_45DEG_DOWN;
				was_on_slope_counter = 2;
				return 1;
			} 
			break;
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
	eject_U = tmp8 | 0xf0;
	return tmp1;
}

/*
	Clobbers:
	tmp2, tmp4
	Recursively clobbers:
	tmp1, tmp2, tmp4, tmp7, tmp8
*/
char bg_coll_U() {
	if (currplayer_vel_y > 0x00) return 0;
	
	// Slopes

	if (high_byte(currplayer_x) >= 0x10) {
		__A__ = Generic.y + 2 + (mini ? byte(0x10 - Generic.height) >> 1 : 0);
		storeWordSeparately(add_scroll_y(__A__, scroll_y), temp_y, temp_room);
		temp_x = Generic.x + low_word(scroll_x); // middle of the cube

		for (tmp2 = 0; tmp2 < 2; tmp2++) {
			bg_collision_sub(); // do again but this time in the center of the cube

			// Clobbers 1, 4, 7, 8
			if(bg_coll_return_slope_U()) return 1;
			
			temp_x += Generic.width; // automatically only the low byte
		}			
	}

	if (!slope_frames) {
		temp_x = Generic.x + low_word(scroll_x); // automatically only the low byte

		__A__ = Generic.y + (mini ? byte(0x10 - Generic.height) >> 1 : 0);
		
		storeWordSeparately(add_scroll_y(__A__, scroll_y), temp_y, temp_room);
		
		for (tmp4 = 0; tmp4 < 3; tmp4++) {
			tmp8 = (temp_y) & 0x0f;
			bg_collision_sub();

			bg_coll_spikes();
			
			// Clobbers 1, 2, 8
			if (bg_coll_return_U()) return 1;

			temp_x += Generic.width >> 1; // automatically only the low byte
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
	if (currplayer_vel_y < 0x00) return 0;

	// Slopes
	if (high_byte(currplayer_x) >= 0x10) {
		__A__ = Generic.y + Generic.height - 2 + (mini ? byte(0x10 - Generic.height) >> 1 : 0);
		storeWordSeparately(add_scroll_y(__A__, scroll_y), temp_y, temp_room);
		temp_x = Generic.x + low_word(scroll_x); // middle of the cube

		for (tmp2 = 0; tmp2 < 2; tmp2++) {
			bg_collision_sub(); // do again but this time in the center of the cube
			
			// Clobbers 1, 4, 7, 8
			if(bg_coll_return_slope_D()) return 1;
			temp_x += Generic.width; // automatically only the low byte
		}			
	}

	if (!slope_frames) {
		// check 2 points on the right side
		temp_x = Generic.x + low_word(scroll_x); // automatically only the low byte

		__A__ = Generic.y + Generic.height + (mini ? byte(0x10 - Generic.height) >> 1 : 0);

		storeWordSeparately(add_scroll_y(__A__, scroll_y), temp_y, temp_room);

		for (tmp4 = 0; tmp4 < 3; tmp4++) {
			tmp8 = (temp_y) & 0x0f;
			bg_collision_sub();
			
			bg_coll_spikes();

			// Clobbers 1, 2, 8
			if (bg_coll_return_D()) return 1;

			temp_x += Generic.width >> 1; // automatically only the low byte
		}	
	}

	return 0;
}

/*
	Clobbers:
	tmp2
*/
void bg_coll_death() {


	// middle point collision to kill, since hitboxes don't exist

	temp_x = Generic.x + low_word(scroll_x) + (Generic.width >> 1)-1; // automatically only the low byte

	__A__ = Generic.y + (Generic.width >> 1);

	storeWordSeparately(add_scroll_y(__A__, scroll_y), temp_y, temp_room);

	bg_collision_sub();
	

	if(!currplayer_gravity && collision == COL_BOTTOM) { }
	else if(currplayer_gravity && collision == COL_TOP) { }

	else if(collision >= COL_UP_LEFT && collision <= COL_TOP_RIGHT_BOTTOM_LEFT) {
		if (bg_coll_mini_blocks()) cube_data[currplayer] = 0x01; 
	}
	else {
		if (collision == COL_ALL && gamemode != 0x06) {  // wave
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

