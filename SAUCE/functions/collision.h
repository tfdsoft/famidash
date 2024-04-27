/* 
	Gets the collision of the current tile
	Implemented in asm
*/
__fastcall__ char bg_collision_sub(void);

#define rpt_bg_col_sub() (__asm__("ldx #0\nLDY %v\nLDA %v,Y", collision, is_solid), __A__)

char bg_coll_L(void){
    // check 2 points on the right side
	temp_x = Generic.x + low2bytes(scroll_x); // automatically only the low byte

	tmp1 = Generic.y + Generic.height - 8;
	if (mini) {
		tmp1 = Generic.y + ((0x10 - Generic.height) >> 1);	
	}
	tmp5 = add_scroll_y(tmp1, scroll_y);
	temp_y = low_byte(tmp5);
	temp_room = high_byte(tmp5);

	tmp3 = bg_collision_sub();
	if(tmp3 & COL_BOTTOM) {
		tmp2 = temp_y & 0x08;
		if (tmp2) return 1;
	} else if (tmp3 & COL_TOP) {
		tmp2 = temp_y & 0x08;
		if (!tmp2) return 1;
	} else if(tmp3 & COL_ALL) return 1;
	else if (tmp3 & COL_DEATH_RIGHT) {
		tmp2 = temp_x & 0x0f;
		if (tmp2 < 0x08) return 0;
	} else if (tmp3 & COL_DEATH_LEFT) {
		tmp2 = temp_x & 0x0f;
		if (tmp2 >= 0x08) return 0;
	} else if(tmp3 & COL_DEATH_TOP) {
		tmp2 = temp_y & 0x0f;
		if (tmp2 < 0x08) cube_data[currplayer] = 1;
		else return 0;
	} else if (tmp3 & COL_DEATH_BOTTOM) {
		tmp2 = temp_y & 0x0f;
		if (tmp2 >= 0x08) cube_data[currplayer] = 1;
		else return 0;
	}

    
    return 0;
}
char bg_coll_R(void){
    // check 2 points on the right side
	temp_x = Generic.x + low2bytes(scroll_x) + Generic.width; // automatically only the low byte

	tmp1 = Generic.y + Generic.height - 8;
	if (mini) {
		tmp1 = Generic.y + ((0x10 - Generic.height) >> 1);	
	}
	tmp5 = add_scroll_y(tmp1, scroll_y);
	temp_y = low_byte(tmp5);
	temp_room = high_byte(tmp5);

	tmp3 = bg_collision_sub();
	if(tmp3 & COL_BOTTOM) {
		tmp2 = temp_y & 0x08;
		if (tmp2) return 1;
	} else if (tmp3 & COL_TOP) {
		tmp2 = temp_y & 0x08;
		if (!tmp2) return 1;
	} else if(tmp3 & COL_ALL) return 1;		
	else if (tmp3 & COL_DEATH_RIGHT) {
		tmp2 = temp_x & 0x0f;
		if (tmp2 < 0x08) return 0;
	} else if (tmp3 & COL_DEATH_LEFT) {
		tmp2 = temp_x & 0x0f;
		if (tmp2 >= 0x08) return 0;
	} else if(tmp3 & COL_DEATH_TOP) {
		tmp2 = temp_x & 0x0f;
		if (tmp2 < 0x06) return 0;
		tmp2 = temp_y & 0x0f;
		if (tmp2 < 0x08) cube_data[currplayer] = 1;
		else return 0;
	} else if (tmp3 & COL_DEATH_BOTTOM) {
		tmp2 = temp_x & 0x0f;
		if (tmp2 < 0x06) return 0;
		tmp2 = temp_y & 0x0f;
		if (tmp2 >= 0x08) cube_data[currplayer] = 1;
		else return 0;
	}

    
    return 0;
}

char bg_coll_U(void){
	if (player_vel_y[currplayer] > 0) return 0;
	
	temp_x = Generic.x + low2bytes(scroll_x); // automatically only the low byte

	tmp1 = Generic.y;
	
	if (mini) {
		tmp1 += (0x10 - Generic.height) >> 1;	
	}
	tmp5 = add_scroll_y(tmp1, scroll_y);
	temp_y = low_byte(tmp5);
	temp_room = high_byte(tmp5);
	eject_U = (temp_y) | 0xf0;	 
	
	
	for (tmp1 = 0; tmp1 < 2; tmp1++) {
		tmp3 = bg_collision_sub();
		if (tmp3 & COL_ALL) return 1;
		else if (tmp3 & (COL_TOP | COL_DEATH_TOP)) {
			tmp2 = temp_y & 0x0f;	
			eject_U = (temp_y) | 0xf8;	 
			if (tmp2 < 0x08) {
				if (tmp3 & COL_DEATH_TOP) {
					if (tmp2 < 0x04) {
						cube_data[currplayer] = 1;
					} else {
						return 0;
					}
				}
				return 1;
			}
		} else if (tmp3 & (COL_BOTTOM | COL_DEATH_BOTTOM)) {
			tmp2 = temp_y & 0x0f;
			eject_U = (temp_y) | 0xf8;	 
			if (tmp2 >= 0x08) {
				if (tmp3 & COL_DEATH_BOTTOM) {
					if (tmp2 >= 0x0c) {
						cube_data[currplayer] = 1;
					} else {
						return 0;
					}
				}
				return 1;
			}
		} else if (tmp3 & COL_DEATH_RIGHT) {
			tmp2 = temp_x & 0x0f;
			if (tmp2 < 0x0A) {
				tmp2 = temp_y & 0x0f;
				if (tmp2 >= 0x06 && tmp2 < 0x0A) cube_data[currplayer] = 1;
			};
		} else if (tmp3 & COL_DEATH_LEFT) {
			tmp2 = temp_x & 0x0f;
			if (tmp2 >= 0x04) {return 0;
				tmp2 = temp_y & 0x0f;
				if (tmp2 >= 0x06 && tmp2 < 0x0A) cube_data[currplayer] = 1;
			}
		}

		temp_x = Generic.x + low2bytes(scroll_x) + Generic.width; // automatically only the low byte
	}	
	return 0;
	
}

char bg_coll_D(void){
	if (player_vel_y[currplayer] < 0) return 0;
	 // check 2 points on the right side
	temp_x = Generic.x + low2bytes(scroll_x); // automatically only the low byte

	tmp1 = Generic.y + Generic.height;
	if (mini) {
		tmp1 += (0x10 - Generic.height) >> 1;	
	}
	tmp5 = add_scroll_y(tmp1, scroll_y);
	temp_y = low_byte(tmp5);
	temp_room = high_byte(tmp5);
	eject_D = (temp_y) & 0x0f;

	for (tmp1 = 0; tmp1 < 2; tmp1++) {
		tmp3 = bg_collision_sub();
		if (tmp3 & COL_ALL) return 1;
		else if (tmp3 & (COL_TOP | COL_DEATH_TOP)) {
			tmp2 = temp_y & 0x0f;	
			eject_D = (temp_y) & 0x07;
			if (tmp2 < 0x08) {
				if (tmp3 & COL_DEATH_TOP) {
					if (tmp2 < 0x04) {
						cube_data[currplayer] = 1;
					} else {
						return 0;
					}
				}
				return 1;
			}
		} else if (tmp3 & (COL_BOTTOM | COL_DEATH_BOTTOM)) {
			tmp2 = temp_y & 0x0f;
			eject_D = (temp_y) & 0x07;
			if (tmp2 >= 0x08) {
				if (tmp3 & COL_DEATH_BOTTOM) {
					if (tmp2 >= 0x0c) {
						if (high_byte(player_x[currplayer]) < 0x10) return 0;
						cube_data[currplayer] = 1;
					} else {
						return 0;
					}
				}
				return 1;
			}
		} else if (tmp3 & COL_DEATH_RIGHT) {
			tmp2 = temp_x & 0x0f;
			if (tmp2 < 0x0A) {
				tmp2 = temp_y & 0x0f;
				if (tmp2 >= 0x06 && tmp2 < 0x0A) cube_data[currplayer] = 1;
			};
		} else if (tmp3 & COL_DEATH_LEFT) {
			tmp2 = temp_x & 0x0f;
			if (tmp2 >= 0x04) {return 0;
				tmp2 = temp_y & 0x0f;
				if (tmp2 >= 0x06 && tmp2 < 0x0A) cube_data[currplayer] = 1;
			}
		}

		temp_x = Generic.x + low2bytes(scroll_x) + Generic.width; // automatically only the low byte
	}	
	return 0;
}






void bg_coll_death(void) {


	// middle point collision to kill, since hitboxes don't exist

	temp_x = Generic.x + low2bytes(scroll_x) + (Generic.width >> 1)-1; // automatically only the low byte

	tmp1 = Generic.y + (Generic.width >> 1);

	tmp5 = add_scroll_y(tmp1, scroll_y);
    temp_y = low_byte(tmp5);
    temp_room = high_byte(tmp5);

	tmp3 = bg_collision_sub();
	if (tmp3 & COL_DEATH_TOP) {
		tmp2 = temp_y & 0x0f;	
		eject_D = (temp_y) & 0x07;
		if (tmp2 < 0x04) {
			tmp2 = temp_x & 0x0f;
			if (tmp2 > 0x06 && tmp2 < 0x0a)
				cube_data[currplayer] = 1;
		}
	} else if (tmp3 & COL_DEATH_BOTTOM) {
		tmp2 = temp_y & 0x0f;
		eject_D = (temp_y) & 0x07;
		if (tmp2 >= 0x0c) {
			tmp2 = temp_x & 0x0f;
			if (tmp2 > 0x06 && tmp2 < 0x0a)
				cube_data[currplayer] = 1;
		}
	}
	else if(!player_gravity[currplayer] && tmp3 & COL_BOTTOM) { }
	else if(player_gravity[currplayer] && tmp3 & COL_TOP) { }
	else if(tmp3 & (COL_DEATH_RIGHT | COL_DEATH_LEFT)) { }
	else {
		if (!platformer) { if(tmp3) cube_data[0] = 0x01; }
		else { if(tmp3 & COL_DEATH) cube_data[0] = 0x01; }
	}

	if(!DEBUG_MODE && cube_data[0] & 0x01) {
		reset_level();
	}
}