/* 
	Gets the collision of the current tile
	Implemented in asm
*/
__fastcall__ char bg_collision_sub(void);

#define rpt_bg_col_sub() (__asm__("ldx #0\nLDY %v\nLDA %v,Y", collision, is_solid), __A__)

char bg_coll_R(void){
    // check 2 points on the right side
	temp_x = Generic.x + low_word(scroll_x) + Generic.width; // automatically only the low byte

	tmp1 = Generic.y + Generic.height - 6;
	if (mini) {
		tmp1 = Generic.y + ((0x10 - Generic.height) >> 1);	
	}
	tmp5 = add_scroll_y(tmp1, scroll_y);
	temp_y = low_byte(tmp5);
	temp_room = high_byte(tmp5);
	for (tmp1 = mini; tmp1 < 2; tmp1++) {
		if(bg_collision_sub() & COL_BOTTOM) {
			tmp5 = temp_y & 0x08;
			if (tmp5) return 1;
		} else if (rpt_bg_col_sub() & COL_TOP) {
			tmp5 = temp_y & 0x08;
			if (!tmp5) return 1;
		} else if(rpt_bg_col_sub() & COL_ALL) return 1;
		else if(mini) {
			temp_x = Generic.x + low_word(scroll_x); // automatically only the low byte
			tmp5 = temp_y & 0x0f;
			if(bg_collision_sub() & COL_DEATH_TOP) {
				return tmp5 < 0x08;
			} else if (rpt_bg_col_sub() & COL_DEATH_BOTTOM) {
				return tmp5 >= 0x08;
			}
		} else if (rpt_bg_col_sub() & COL_DEATH_RIGHT) {
			tmp5 = temp_x & 0x0f;
			if (tmp5 < 0x08) return 0;
		} else if (rpt_bg_col_sub() & COL_DEATH_LEFT) {
			tmp5 = temp_x & 0x0f;
			if (tmp5 >= 0x08) return 0;
		}

		tmp5 = add_scroll_y(Generic.y + 6, scroll_y);
		temp_y = low_byte(tmp5);
		temp_room = high_byte(tmp5);
	}
    
    return 0;
}

char bg_coll_U(void){
	if (player_vel_y[currplayer] > 0) return 0;
	
	temp_x = Generic.x + low_word(scroll_x); // automatically only the low byte

	tmp1 = Generic.y;
	
	if (mini) {
		tmp1 += (0x10 - Generic.height) >> 1;	
	}
	tmp5 = add_scroll_y(tmp1, scroll_y);
	temp_y = low_byte(tmp5);
	temp_room = high_byte(tmp5);
	eject_U = (temp_y) | 0xf0;	 
	
	
	for (tmp1 = 0; tmp1 < 2; tmp1++) {
		if(bg_collision_sub() & COL_ALL) return 1;
		else if (rpt_bg_col_sub() & (COL_TOP | COL_DEATH_TOP)) {
			tmp5 = temp_y & 0x0f;	
			eject_U = (temp_y) | 0xf8;	 
			if (tmp5 < 0x08) {
				if (rpt_bg_col_sub() & COL_DEATH_TOP) {
					if (tmp5 < 0x04) {
						cube_data[currplayer] = 1;
					} else {
						return 0;
					}
				}
				return 1;
			}
		} else if (rpt_bg_col_sub() & (COL_BOTTOM | COL_DEATH_BOTTOM)) {
			tmp5 = temp_y & 0x0f;
			eject_U = (temp_y) | 0xf8;	 
			if (tmp5 >= 0x08) {
				if (rpt_bg_col_sub() & COL_DEATH_BOTTOM) {
					if (tmp5 >= 0x0c) {
						cube_data[currplayer] = 1;
					} else {
						return 0;
					}
				}
				return 1;
			}
		} else if (rpt_bg_col_sub() & COL_DEATH_RIGHT) {
			tmp5 = temp_x & 0x0f;
			if (tmp5 < 0x0A) {
				tmp5 = temp_y & 0x0f;
				if (tmp5 >= 0x06 && tmp5 < 0x0A) cube_data[currplayer] = 1;
			};
		} else if (rpt_bg_col_sub() & COL_DEATH_LEFT) {
			tmp5 = temp_x & 0x0f;
			if (tmp5 >= 0x04) {return 0;
				tmp5 = temp_y & 0x0f;
				if (tmp5 >= 0x06 && tmp5 < 0x0A) cube_data[currplayer] = 1;
			}
		}

		temp_x = Generic.x + low_word(scroll_x) + Generic.width; // automatically only the low byte
	}	
	return 0;
	
}

char bg_coll_D(void){
	if (player_vel_y[currplayer] < 0) return 0;
	 // check 2 points on the right side
	temp_x = Generic.x + low_word(scroll_x); // automatically only the low byte

	tmp1 = Generic.y + Generic.height;
	if (mini) {
		tmp1 += (0x10 - Generic.height) >> 1;	
	}
	tmp5 = add_scroll_y(tmp1, scroll_y);
	temp_y = low_byte(tmp5);
	temp_room = high_byte(tmp5);
	eject_D = (temp_y) & 0x0f;

	for (tmp1 = 0; tmp1 < 2; tmp1++) {
		if(bg_collision_sub() & COL_ALL) return 1;
		else if (rpt_bg_col_sub() & (COL_TOP | COL_DEATH_TOP)) {
			tmp5 = temp_y & 0x0f;	
			eject_D = (temp_y) & 0x07;
			if (tmp5 < 0x08) {
				if (rpt_bg_col_sub() & COL_DEATH_TOP) {
					if (tmp5 < 0x04) {
						cube_data[currplayer] = 1;
					} else {
						return 0;
					}
				}
				return 1;
			}
		} else if (rpt_bg_col_sub() & (COL_BOTTOM | COL_DEATH_BOTTOM)) {
			tmp5 = temp_y & 0x0f;
			eject_D = (temp_y) & 0x07;
			if (tmp5 >= 0x08) {
				if (rpt_bg_col_sub() & COL_DEATH_BOTTOM) {
					if (tmp5 >= 0x0c) {
						if (high_byte(player_x[currplayer]) < 0x10) return 0;
						cube_data[currplayer] = 1;
					} else {
						return 0;
					}
				}
				return 1;
			}
		} else if (rpt_bg_col_sub() & COL_DEATH_RIGHT) {
			tmp5 = temp_x & 0x0f;
			if (tmp5 < 0x0A) {
				tmp5 = temp_y & 0x0f;
				if (tmp5 >= 0x06 && tmp5 < 0x0A) cube_data[currplayer] = 1;
			};
		} else if (rpt_bg_col_sub() & COL_DEATH_LEFT) {
			tmp5 = temp_x & 0x0f;
			if (tmp5 >= 0x04) {return 0;
				tmp5 = temp_y & 0x0f;
				if (tmp5 >= 0x06 && tmp5 < 0x0A) cube_data[currplayer] = 1;
			}
		}

		temp_x = Generic.x + low_word(scroll_x) + Generic.width; // automatically only the low byte
	}	
	return 0;
}






void bg_coll_death(void) {


	// middle point collision to kill, since hitboxes don't exist
//	if (!mini) 
	temp_x = Generic.x + low_word(scroll_x) + (Generic.width >> 1)-1; // automatically only the low byte
	//else tmp5 = Generic.x + low_word(scroll_x) + (Generic.width >> 1)-4;

//	if (!player_gravity[currplayer]) {
//		if (!mini) 	tmp1 = Generic.y + (Generic.width >> 1);
//		else tmp1 = Generic.y-6 + Generic.width;
//	}
//	else {
//		if (!mini) 
			tmp1 = Generic.y + (Generic.width >> 1);
//		else {
//			if (gamemode == 5) tmp1 = Generic.y+6 + Generic.width;
//			else if (gamemode == 2 || gamemode == 0) { tmp1 = Generic.y-2 + Generic.width; }
//			else { tmp1 = Generic.y-2 + Generic.width; }
//		}
//	}
	tmp5 = add_scroll_y(tmp1, scroll_y);
    temp_y = low_byte(tmp5);
    temp_room = high_byte(tmp5);


	if(bg_collision_sub() & (COL_DEATH_BOTTOM | COL_DEATH_TOP)) {
			if (rpt_bg_col_sub() & COL_DEATH_BOTTOM) tmp1 = Generic.y-14 + Generic.width;
			else tmp1 = Generic.y+12 + Generic.width;
			tmp5 = add_scroll_y(tmp1, scroll_y);
			temp_y = low_byte(tmp5);
			temp_room = high_byte(tmp5);
			if(bg_collision_sub() ) cube_data[0] = 0x01;
		}
	else if(!player_gravity[currplayer] && rpt_bg_col_sub() & COL_BOTTOM) { }
	else if(player_gravity[currplayer] && rpt_bg_col_sub() & COL_TOP) { }
	else if(rpt_bg_col_sub() & (COL_DEATH_RIGHT | COL_DEATH_LEFT)) { }
	else if(rpt_bg_col_sub() ) cube_data[0] = 0x01;


    
	++temp_x; // low byte
	if(bg_collision_sub() & (COL_DEATH_BOTTOM | COL_DEATH_TOP)) { 
			if (rpt_bg_col_sub() & COL_DEATH_BOTTOM) tmp1 = Generic.y-14 + Generic.width;
			else tmp1 = Generic.y+12 + Generic.width;
			tmp5 = add_scroll_y(tmp1, scroll_y);
			temp_y = low_byte(tmp5);
			temp_room = high_byte(tmp5);
			if(bg_collision_sub() ) cube_data[0] = 0x01;	
	}
	else if(!player_gravity[currplayer] && rpt_bg_col_sub() & COL_BOTTOM) { }
	else if(player_gravity[currplayer] && rpt_bg_col_sub() & COL_TOP) { }
	else if(rpt_bg_col_sub() & (COL_DEATH_RIGHT | COL_DEATH_LEFT)) { }
	else if(rpt_bg_col_sub() ) cube_data[0] = 0x01;

    

	if(!DEBUG_MODE && cube_data[0] & 0x01) {
		reset_level();
	}
}