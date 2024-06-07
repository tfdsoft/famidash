/* 
	Gets the collision of the current tile
	Implemented in asm
*/
__fastcall__ char bg_collision_sub(void);

#define rpt_bg_col_sub() (__asm__("ldx #0\nLDY %v\nLDA %v,Y", collision, is_solid), __A__)



char bg_coll_sides(void) {
	switch (tmp3) {
		case COL_BOTTOM: 
			if (temp_y & 0x08) return 1;		// If Y pos inside block ≥ 8px
			break;	
		case COL_TOP: 
			if (!(temp_y & 0x08)) return 1;		// If Y pos inside block < 8px
			break;	
		case COL_ALL: 
			return 1;		
		case COL_DEATH_LEFT: 
			// if ((uint8_t)(temp_x & 0x0f) < 0x04)
			if (!(temp_x & 0x0C))
				cube_data[currplayer] = 1;	// If X pos inside block < 4px, die
			break;														
		case COL_DEATH_RIGHT: 
			if ((uint8_t)(temp_x & 0x0f) >= 0x0c)
				cube_data[currplayer] = 1;	// If X pos inside block ≥ 12px, die
			break;	
		case COL_DEATH_TOP:
			if ((uint8_t)(temp_x & 0x0f) < 0x06)
				return 0;					// If X pos inside block < 6px, collide
			// if ((uint8_t)(temp_y & 0x0f) < 0x04)
			if (!(temp_y & 0x0C))
				cube_data[currplayer] = 1;	// If Y pos inside block < 4px, die
			break;
		case COL_DEATH_BOTTOM:
			if ((uint8_t)(temp_x & 0x0f) < 0x06)
				return 0;					// If X pos inside block < 6px, collide
			if ((uint8_t)(temp_y & 0x0f) >= 0x0c)
				cube_data[currplayer] = 1;	// If Y pos inside block ≥ 12px, die
	};
	return 0;
}

char bg_coll_floor_spikes(void){ // used just for checking ground spikes on the floor
	temp_x = Generic.x + low_word(scroll_x); // automatically only the low byte

	tmp1 = Generic.y + (mini ? (byte(0x10 - Generic.height) >> 1) : 4);
	storeWordSeparately(add_scroll_y(tmp1, scroll_y), temp_y, temp_room);

	for (tmp8 = mini; tmp8 < 2; tmp8++) {
		tmp3 = bg_collision_sub();
		if(tmp3 == COL_DEATH_TOP) {
			if (!(temp_y & 0x08)) {							// If Y pos inside block < 8px, die
				if ((uint8_t)(temp_x & 0x0f) < 0x0c) {		// If X pos even insider, die even more
					cube_data[currplayer] = 1;						
				}
			}								// else nothing
		} else if (tmp3 == COL_DEATH_BOTTOM) {
			if ((temp_y & 0x08)) {							// If Y pos inside block ≥ 8px, die
				if ((uint8_t)(temp_x & 0x0f) < 0x0c) {		// If X pos even insider, die even more
					cube_data[currplayer] = 1;						
				}
			}								// else nothing
		}
		tmp1 = Generic.y + Generic.height - 4;
		storeWordSeparately(add_scroll_y(tmp1, scroll_y), temp_y, temp_room);
	}

    return 0;
}
char bg_coll_R(void){
    // check 2 points on the right side
	temp_x = Generic.x + low_word(scroll_x) + Generic.width + (platformer ? 3 : 0); // automatically only the low byte

	tmp1 = Generic.y + (byte(0x10 - Generic.height) >> 1) + (mini ? 4 : (Generic.height >> 1));

	if (slope_frames > 0) { // if we are on a slope, make right_col a little more upwards so it doesn't hit blocks to the side of the slope
		tmp1 -= 8;
		slope_frames -= 1;
	}

	storeWordSeparately(add_scroll_y(tmp1, scroll_y), temp_y, temp_room);


	tmp3 = bg_collision_sub();
	
	return bg_coll_sides();
}

char bg_coll_L(void){
    // check 2 points on the right side
	temp_x = Generic.x + low_word(scroll_x) - (platformer ? 3 : 0); // automatically only the low byte

	tmp1 = Generic.y + (byte(0x10 - Generic.height) >> 1) + (mini ? 4 : (Generic.height >> 1));

	storeWordSeparately(add_scroll_y(tmp1, scroll_y), temp_y, temp_room);

	tmp3 = bg_collision_sub();
	
	return bg_coll_sides();
}

char bg_coll_U_D_checks(void) {
	switch (tmp3) {
		case COL_ALL: 
			return 1;
		case COL_TOP:
		case COL_DEATH_TOP:
			tmp2 = temp_y & 0x0f;	
			tmp8 = tmp2 & 0x07;	 
			// if (tmp2 < 0x08) {
			if (tmp8 == tmp2) {
				if (tmp3 == COL_DEATH_TOP) {
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
		case COL_BOTTOM:
		case COL_DEATH_BOTTOM:
			tmp2 = temp_y & 0x0f;
			tmp8 = tmp2 & 0x07;	 
			// if (tmp2 >= 0x08) {
			if (tmp8 != tmp2) {
				if (tmp3 == COL_DEATH_BOTTOM) {
					if (tmp2 >= 0x0c) {
						// if ((temp_x & 0x0f) >= 0x04 && (temp_x & 0x0f) < 0x0c) {
						if (!((temp_x - 0x04) & 0x08)) {
							cube_data[currplayer] = 1;
						}
					}
				} else return 1;
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

char bg_coll_slope(void) {	
	switch (tmp3) {
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

char bg_coll_return_D (void) {
	tmp1 = bg_coll_U_D_checks();
	eject_D = tmp8;
	return tmp1;
}

char bg_coll_return_U (void) {
	tmp1 = bg_coll_U_D_checks();
	eject_U = tmp8 | 0xf8;
	return tmp1;
}

char bg_coll_return_slope_D (void) {
	tmp1 = bg_coll_slope();
	eject_D = tmp8;
	return tmp1;
}

char bg_coll_return_slope_U (void) {
	tmp1 = bg_coll_slope();
	eject_U = tmp8 | 0xf0;
	return tmp1;
}

char bg_coll_U(void){
	if (currplayer_vel_y > 0) return 0;
	
	// Slopes

	if (high_byte(currplayer_x) >= 0x10) {
		tmp1 = Generic.y + 2;
		if (mini) {
			tmp1 += byte(0x10 - Generic.height) >> 1;	
		}
		storeWordSeparately(add_scroll_y(tmp1, scroll_y), temp_y, temp_room);
		temp_x = Generic.x + low_word(scroll_x); // middle of the cube

		for (tmp2 = 0; tmp2 < 2; tmp2++) {
			tmp3 = bg_collision_sub(); // do again but this time in the center of the cube
			if(bg_coll_return_slope_U()) return 1;
			temp_x += Generic.width; // automatically only the low byte
		}			
	}

	if (!slope_frames) {
		temp_x = Generic.x + low_word(scroll_x); // automatically only the low byte

		tmp1 = Generic.y + (mini ? byte(0x10 - Generic.height) >> 1 : 0);
		
		storeWordSeparately(add_scroll_y(tmp1, scroll_y), temp_y, temp_room);
		tmp8 = temp_y | 0xf0;	 
		
		
		for (tmp2 = 0; tmp2 < 2; tmp2++) {
			tmp3 = bg_collision_sub();
			
			if (bg_coll_return_U()) return 1;

			temp_x += Generic.width; // automatically only the low byte
		}	
	}
	return 0;
	
}

char bg_coll_D(void){
	if (currplayer_vel_y < 0) return 0;

	// Slopes
	if (high_byte(currplayer_x) >= 0x10) {
		tmp1 = Generic.y + Generic.height - 2;
		if (mini) {
			tmp1 += byte(0x10 - Generic.height) >> 1;	
		}
		storeWordSeparately(add_scroll_y(tmp1, scroll_y), temp_y, temp_room);
		temp_x = Generic.x + low_word(scroll_x); // middle of the cube

		for (tmp2 = 0; tmp2 < 2; tmp2++) {
			tmp3 = bg_collision_sub(); // do again but this time in the center of the cube
			if(bg_coll_return_slope_D()) return 1;
			temp_x += Generic.width; // automatically only the low byte
		}			
	}

	if (!slope_frames) {
		// check 2 points on the right side
		temp_x = Generic.x + low_word(scroll_x); // automatically only the low byte

		tmp1 = Generic.y + Generic.height + (mini ? byte(0x10 - Generic.height) >> 1 : 0);

		storeWordSeparately(add_scroll_y(tmp1, scroll_y), temp_y, temp_room);
		tmp8 = (temp_y) & 0x0f;

		for (tmp2 = 0; tmp2 < 2; tmp2++) {
			tmp3 = bg_collision_sub();
			
			if (bg_coll_return_D()) return 1;

			temp_x += Generic.width; // automatically only the low byte
		}	
	}

	return 0;
}


void bg_coll_death(void) {


	// middle point collision to kill, since hitboxes don't exist

	temp_x = Generic.x + low_word(scroll_x) + (Generic.width >> 1)-1; // automatically only the low byte

	tmp1 = Generic.y + (Generic.width >> 1);

	storeWordSeparately(add_scroll_y(tmp1, scroll_y), temp_y, temp_room);

	tmp3 = bg_collision_sub();
	if (tmp3 == COL_DEATH_TOP) {
		eject_D = (temp_y) & 0x07;
		// tmp2 = temp_y & 0x0f;	
		// if (tmp2 < 0x04) {
		if (!(temp_y & 0x0C)) {
			tmp2 = temp_x & 0x0f;
			if (tmp2 > 0x06 && tmp2 < 0x0a)
				cube_data[currplayer] = 1;
		}
	} else if (tmp3 == COL_DEATH_BOTTOM) {
		eject_D = (temp_y) & 0x07;
		// tmp2 = temp_y & 0x0f;
		// if (tmp2 >= 0x0c) {
		if ((temp_y & 0x0C) == 0x0C) {
			tmp2 = temp_x & 0x0f;
			if (tmp2 > 0x06 && tmp2 < 0x0a)
				cube_data[currplayer] = 1;
		}
	}
	else if(!currplayer_gravity && tmp3 == COL_BOTTOM) { }
	else if(currplayer_gravity && tmp3 == COL_TOP) { }
	else if(tmp3 == COL_DEATH_RIGHT || tmp3 == COL_DEATH_LEFT) { }
	else {
		if (tmp3 == COL_ALL && gamemode != 0x06) {  // wave
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
		else if(tmp3 == COL_DEATH) cube_data[currplayer] = 0x01;
	}

//	if(!DEBUG_MODE && cube_data[0] & 0x01) {
//		reset_level();
//	}
}

