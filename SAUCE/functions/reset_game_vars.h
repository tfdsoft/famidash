
CODE_BANK_PUSH("XCD_BANK_00")

void reset_game_vars(){
	if (!has_practice_point) music_play(song_practice);
	practice_player_x[0] = player_x[0];
	long_temp_x = high_byte(player_x[0]);
	practice_player_x[1] = player_x[1];
	practice_player_y[0] = player_y[0];
	practice_player_y[1] = player_y[1];
	practice_player_vel_x[0] = player_vel_x[0];
	practice_player_vel_x[1] = player_vel_x[1];
	practice_player_vel_y[0] = player_vel_y[0];
	practice_player_vel_y[1] = player_vel_y[1];
	practice_player_gravity[0] = player_gravity[0];
	practice_player_gravity[1] = player_gravity[1];
	practice_cube_rotate[0] = cube_rotate[0];
	practice_cube_rotate[1] = cube_rotate[1];
	practice_player_gamemode[0] = gamemode;
	practice_mini[0] = mini;
	practice_dual[0] = dual;
	practice_speed[0] = speed;
	practice_parallax_scroll_x[0] = parallax_scroll_x;
	practice_scroll_x[0] = scroll_x;
	practice_scroll_y[0] = scroll_y;
	practice_bg_color_type[0] = lastbgcolortype;
	practice_g_color_type[0] = lastgcolortype;
//	gnd_palette_transition_timer = 0;		//palete fade code
//	bg_palette_transition_timer = 0;		//palette fade code
	tmp2 = 0;
//	do {
//		idx8_store(practice_trail_sprites_visible, tmp2, trail_sprites_visible[tmp2]);
//		idx8_store(practice_player_old_posy, tmp2, player_old_posy[tmp2]);
//	} while (++tmp2 < 9);
	practice_orbactive[0] = orbactive;
}


void restore_practice_state() {
	player_x[0] = practice_player_x[0];
	long_temp_x = high_byte(practice_player_x[0]);
	player_x[1] = practice_player_x[1];
	player_y[0] = practice_player_y[0];
	player_y[1] = practice_player_y[1];
	player_vel_x[0] = practice_player_vel_x[0];
	player_vel_x[1] = practice_player_vel_x[1];
	player_vel_y[0] = practice_player_vel_y[0];
	player_vel_y[1] = practice_player_vel_y[1];
	player_gravity[0] = practice_player_gravity[0];
	player_gravity[1] = practice_player_gravity[1];
	cube_rotate[0] = practice_cube_rotate[0];
	cube_rotate[1] = practice_cube_rotate[1];
	gamemode = practice_player_gamemode[0];
	mini = practice_mini[0];
	dual = practice_dual[0];
	speed = practice_speed[0];
	parallax_scroll_x = practice_parallax_scroll_x[0];
	scroll_x = practice_scroll_x[0] - (256 + 16);
	old_trail_scroll_y = scroll_y = practice_scroll_y[0];
	tmp2 = 0;
//	do {
//		idx8_store(trail_sprites_visible, tmp2, practice_trail_sprites_visible[tmp2]);
//		idx8_store(player_old_posy, tmp2, practice_player_old_posy[tmp2]);
//	} while (++tmp2 < 9);
	orbactive = practice_orbactive[0];

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
