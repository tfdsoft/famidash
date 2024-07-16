#pragma code-name(push, "XCD_BANK_00")
#pragma data-name(push, "XCD_BANK_00")
#pragma rodata-name(push, "XCD_BANK_00")

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
	practice_player_gamemode = gamemode;
	practice_mini = mini;
	practice_dual = dual;
	practice_speed = speed;
	practice_scroll_x = scroll_x;
	practice_scroll_y = scroll_y;
	practice_bg_color_type = lastbgcolortype;
	practice_g_color_type = lastgcolortype;
	gnd_palette_transition_timer = 0;		//palete fade code
	bg_palette_transition_timer = 0;		//palette fade code
}

#pragma code-name(pop)
#pragma data-name(pop)
#pragma rodata-name(pop)