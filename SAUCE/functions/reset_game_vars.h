CODE_BANK_PUSH("XCD_BANK_04")

void reset_game_vars(){
	if (!practice_point_count) music_play(song_practice);

	tmp1 = practice_point_count;

	if (practice_point_count != MAX_PRACTICE_POINTS) { 
		practice_point_count++;	
		curr_practice_point = practice_point_count;
		practice_player_x[tmp1] = player_x[0];
		long_temp_x = high_byte(player_x[0]);
		practice_player_x[tmp1+1] = player_x[1];
		practice_player_y[tmp1] = player_y[0];
		practice_player_y[tmp1+1] = player_y[1];
		practice_player_vel_x[tmp1] = player_vel_x[0];
		practice_player_vel_x[tmp1+1] = player_vel_x[1];
		practice_player_vel_y[tmp1] = player_vel_y[0];
		practice_player_vel_y[tmp1+1] = player_vel_y[1];
		practice_player_gravity[tmp1] = player_gravity[0];
		practice_player_gravity[tmp1+1] = player_gravity[1];
		practice_cube_rotate[tmp1] = cube_rotate[0];
		practice_cube_rotate[tmp1+1] = cube_rotate[1];
		practice_player_gamemode[tmp1] = gamemode;
		practice_mini[tmp1] = mini[0];
		practice_mini[tmp1+1] = mini[1];
		practice_dual[tmp1] = dual;
		practice_speed[tmp1] = speed;
		practice_parallax_scroll_x[tmp1] = parallax_scroll_x;
		practice_scroll_x[tmp1] = scroll_x;
		practice_scroll_y[tmp1] = scroll_y;
		practice_bg_color_type[tmp1] = lastbgcolortype;
		practice_g_color_type[tmp1] = lastgcolortype;
		practice_orbactive[tmp1] = orbactive;
		practice_target_scroll_y[tmp1] = target_scroll_y;
	}
	else {
		tmp2 = 0;
		tmp3 = 1;
		do {		
			practice_player_x[tmp2] = practice_player_x[tmp3];
			long_temp_x = high_byte(player_x[0]);
			practice_player_x[tmp2+1] = practice_player_x[tmp3+1];
			practice_player_y[tmp2] = practice_player_y[tmp3];
			practice_player_y[tmp2+1] = practice_player_y[tmp3+1];
			practice_player_vel_x[tmp2] = practice_player_vel_x[tmp3];
			practice_player_vel_x[tmp2+1] = practice_player_vel_x[tmp3+1];
			practice_player_vel_y[tmp2] = practice_player_vel_y[tmp3];
			practice_player_vel_y[tmp2+1] = practice_player_vel_y[tmp3+1];
			practice_player_gravity[tmp2] = practice_player_gravity[tmp3];
			practice_player_gravity[tmp2+1] = practice_player_gravity[tmp3+1];
			practice_cube_rotate[tmp2] = practice_cube_rotate[tmp3];
			practice_cube_rotate[tmp2+1] = practice_cube_rotate[tmp3+1];
			practice_player_gamemode[tmp2] = practice_player_gamemode[tmp3];
			practice_mini[tmp2] = practice_mini[tmp3];
			practice_mini[tmp2+1] = practice_mini[tmp3+1];
			practice_dual[tmp2] = practice_dual[tmp3];
			practice_speed[tmp2] = practice_speed[tmp3];
			practice_parallax_scroll_x[tmp2] = practice_parallax_scroll_x[tmp3];
			practice_scroll_x[tmp2] = practice_scroll_x[tmp3];
			practice_scroll_y[tmp2] = practice_scroll_y[tmp3];
			practice_bg_color_type[tmp2] = practice_bg_color_type[tmp3];
			practice_g_color_type[tmp2] = practice_g_color_type[tmp3];
			practice_orbactive[tmp2] = practice_orbactive[tmp3];	
			practice_target_scroll_y[tmp2] = practice_target_scroll_y[tmp3];	
			tmp2++;
			tmp3++;
		} while (tmp3 < MAX_PRACTICE_POINTS);		
		practice_player_x[tmp2] = player_x[0];
		long_temp_x = high_byte(player_x[0]);
		practice_player_x[tmp2+1] = player_x[1];
		practice_player_y[tmp2] = player_y[0];
		practice_player_y[tmp2+1] = player_y[1];
		practice_player_vel_x[tmp2] = player_vel_x[0];
		practice_player_vel_x[tmp2+1] = player_vel_x[1];
		practice_player_vel_y[tmp2] = player_vel_y[0];
		practice_player_vel_y[tmp2+1] = player_vel_y[1];
		practice_player_gravity[tmp2] = player_gravity[0];
		practice_player_gravity[tmp2+1] = player_gravity[1];
		practice_cube_rotate[tmp2] = cube_rotate[0];
		practice_cube_rotate[tmp2+1] = cube_rotate[1];
		practice_player_gamemode[tmp2] = gamemode;
		practice_mini[tmp2] = mini[0];
		practice_mini[tmp2+1] = mini[1];
		practice_dual[tmp2] = dual;
		practice_speed[tmp2] = speed;
		practice_parallax_scroll_x[tmp2] = parallax_scroll_x;
		practice_scroll_x[tmp2] = scroll_x;
		practice_scroll_y[tmp2] = scroll_y;
		practice_bg_color_type[tmp2] = lastbgcolortype;
		practice_g_color_type[tmp2] = lastgcolortype;
		practice_orbactive[tmp2] = orbactive;		
		practice_target_scroll_y[tmp2] = target_scroll_y;		
		
	}
}


void restore_practice_state() {
	tmp2 = practice_point_count - 1;
	player_x[0] = practice_player_x[tmp2];
	long_temp_x = high_byte(practice_player_x[tmp2]);
	player_x[1] = practice_player_x[tmp2+1];
	player_y[0] = practice_player_y[tmp2];
	player_y[1] = practice_player_y[tmp2+1];
	player_vel_x[0] = practice_player_vel_x[tmp2];
	player_vel_x[1] = practice_player_vel_x[tmp2+1];
	player_vel_y[0] = practice_player_vel_y[tmp2];
	player_vel_y[1] = practice_player_vel_y[tmp2+1];
	player_gravity[0] = practice_player_gravity[tmp2];
	player_gravity[1] = practice_player_gravity[tmp2+1];
	cube_rotate[0] = practice_cube_rotate[tmp2];
	cube_rotate[1] = practice_cube_rotate[tmp2+1];
	mini[0] = practice_mini[tmp2];
	mini[1] = practice_mini[tmp2+1];
	gamemode = practice_player_gamemode[tmp2];
	mini[0] = practice_mini[tmp2];
	mini[1] = practice_mini[tmp2+1];
	dual = practice_dual[tmp2];
	speed = practice_speed[tmp2];
	parallax_scroll_x = practice_parallax_scroll_x[tmp2];
	scroll_x = practice_scroll_x[tmp2] - (256 + 16);
	old_trail_scroll_y = scroll_y = practice_scroll_y[tmp2];
//	tmp2 = 0;
//	do {
//		idx8_store(trail_sprites_visible, tmp2, practice_trail_sprites_visible[tmp2]);
//		idx8_store(player_old_posy, tmp2, practice_player_old_posy[tmp2]);
//	} while (++tmp2 < 9);
	orbactive = practice_orbactive[tmp2];
	target_scroll_y = practice_target_scroll_y[tmp2];

	__A__ = currplayer<<1;
	__asm__("tay");
	#define quick_ld(to, from) __asm__("lda %v,y\n sta %v\n lda %v+1,y\n sta %v+1", from, to, from, to)
	
	quick_ld(currplayer_x, player_x);
	quick_ld(currplayer_y, player_y);
	quick_ld(currplayer_vel_x, player_vel_x);
	quick_ld(currplayer_vel_y, player_vel_y);

	#undef quick_ld
	currplayer_gravity = player_gravity[currplayer];
}

CODE_BANK_POP()
