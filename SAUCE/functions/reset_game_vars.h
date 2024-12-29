CODE_BANK_PUSH("XCD_BANK_04")

void reset_game_vars(){
	if (!practice_point_count) {
		music_play(song_practice);
		latest_practice_point = 0;
	} else {
		latest_practice_point++;
		latest_practice_point &= 7;
	}

	if (practice_point_count < MAX_PRACTICE_POINTS)
		practice_point_count++;

	tmp1 = latest_practice_point;

	curr_practice_point = latest_practice_point;
	lohi_arr16_store(practice_player_1_x, tmp1, player_x[0]);
	lohi_arr16_store(practice_player_2_x, tmp1, player_x[1]);
	lohi_arr16_store(practice_player_1_y, tmp1, player_y[0]);
	lohi_arr16_store(practice_player_2_y, tmp1, player_y[1]);
	lohi_arr16_store(practice_player_1_vel_x, tmp1, player_vel_x[0]);
	lohi_arr16_store(practice_player_2_vel_x, tmp1, player_vel_x[1]);
	lohi_arr16_store(practice_player_1_vel_y, tmp1, player_vel_y[0]);
	lohi_arr16_store(practice_player_2_vel_y, tmp1, player_vel_y[1]);
	lohi_arr16_store(practice_cube_1_rotate, tmp1, cube_rotate[0]);
	lohi_arr16_store(practice_cube_2_rotate, tmp1, cube_rotate[1]);
	
	practice_player_1_gravity[tmp1] = player_gravity[0];
	practice_player_2_gravity[tmp1] = player_gravity[1];
	practice_player_1_mini[tmp1] = mini[0];
	practice_player_2_mini[tmp1] = mini[1];
	practice_player_1_slope_frames[tmp1] = slope_frames[0];
	practice_player_2_slope_frames[tmp1] = slope_frames[1];
	practice_player_1_was_on_slope_counter[tmp1] = was_on_slope_counter[0];
	practice_player_2_was_on_slope_counter[tmp1] = was_on_slope_counter[1];
	practice_player_1_slope_type[tmp1] = slope_type[0];
	practice_player_2_slope_type[tmp1] = slope_type[1];
	practice_player_1_last_slope_type[tmp1] = last_slope_type[0];
	practice_player_2_last_slope_type[tmp1] = last_slope_type[1];

	lohi_arr32_store(practice_scroll_x, tmp1, scroll_x);
	lohi_arr16_store(practice_scroll_y, tmp1, scroll_y);
	lohi_arr16_store(practice_target_scroll_y, tmp1, target_scroll_y);

	practice_player_gamemode[tmp1] = gamemode;
	practice_dual[tmp1] = dual;
	practice_speed[tmp1] = speed;
	practice_parallax_scroll_x[tmp1] = parallax_scroll_x;
	practice_bg_color_type[tmp1] = lastbgcolortype;
	practice_g_color_type[tmp1] = lastgcolortype;
	practice_orbactive[tmp1] = orbactive;

	long_temp_x = high_byte(player_x[0]);
}


void restore_practice_state() {
	tmp2 = curr_practice_point;
	player_x[0] = lohi_arr16_load(practice_player_1_x, tmp2);
	player_x[1] = lohi_arr16_load(practice_player_2_x, tmp2);
	player_y[0] = lohi_arr16_load(practice_player_1_y, tmp2);
	player_y[1] = lohi_arr16_load(practice_player_2_y, tmp2);
	player_vel_x[0] = lohi_arr16_load(practice_player_1_vel_x, tmp2);
	player_vel_x[1] = lohi_arr16_load(practice_player_2_vel_x, tmp2);
	player_vel_y[0] = lohi_arr16_load(practice_player_1_vel_y, tmp2);
	player_vel_y[1] = lohi_arr16_load(practice_player_2_vel_y, tmp2);
	cube_rotate[0] = lohi_arr16_load(practice_cube_1_rotate, tmp2);
	cube_rotate[1] = lohi_arr16_load(practice_cube_2_rotate, tmp2);

	player_gravity[0] = practice_player_1_gravity[tmp2];
	player_gravity[1] = practice_player_2_gravity[tmp2];
	currplayer_gravity = player_gravity[0];

	mini[0] = practice_player_1_mini[tmp2];
	mini[1] = practice_player_2_mini[tmp2];
	currplayer_mini = mini[0];

	slope_frames[0] = practice_player_1_slope_frames[tmp2];
	slope_frames[1] = practice_player_2_slope_frames[tmp2];
	currplayer_slope_frames = slope_frames[0];

	was_on_slope_counter[0] = practice_player_1_was_on_slope_counter[tmp2];
	was_on_slope_counter[1] = practice_player_2_was_on_slope_counter[tmp2];
	currplayer_was_on_slope_counter = was_on_slope_counter[0];
	
	slope_type[0] = practice_player_1_slope_type[tmp2];
	slope_type[1] = practice_player_2_slope_type[tmp2];
	currplayer_slope_type = slope_type[0];
	
	last_slope_type[0] = practice_player_1_last_slope_type[tmp2];
	last_slope_type[1] = practice_player_2_last_slope_type[tmp2];
	currplayer_last_slope_type = last_slope_type[0];

	scroll_x = lohi_arr32_load(practice_scroll_x, tmp2) - (256 + 16);
	old_trail_scroll_y = scroll_y = lohi_arr16_load(practice_scroll_y, tmp2);
	target_scroll_y = lohi_arr16_load(practice_target_scroll_y, tmp2);

	gamemode = practice_player_gamemode[tmp2];
	dual = practice_dual[tmp2];
	speed = practice_speed[tmp2];
	parallax_scroll_x = practice_parallax_scroll_x[tmp2];
//	tmp2 = 0;
//	do {
//		idx8_store(trail_sprites_visible, tmp2, practice_trail_sprites_visible[tmp2]);
//		idx8_store(player_old_posy, tmp2, practice_player_old_posy[tmp2]);
//	} while (++tmp2 < 9);
	orbactive = practice_orbactive[tmp2];
	long_temp_x = practice_player_1_x_hi[tmp2];

	lastgcolortype = practice_g_color_type[tmp2];
	
	lastbgcolortype = practice_bg_color_type[tmp2];
	tmp3 = (lastbgcolortype & 0x3F);
	pal_col(0, tmp3);
	tmp3 = oneShadeDarker(tmp3);
	pal_col(1, tmp3);
	pal_col(9, tmp3);

	tmp3 = (lastgcolortype & 0x3F);
	pal_col(6, tmp3);
	pal_col(5, oneShadeDarker(tmp3));

	pal_set_update();

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
