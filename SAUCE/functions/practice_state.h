CODE_BANK_PUSH("XCD_BANK_04")

#if !__VS_SYSTEM
const uint8_t multBufLookup[] = {0, 11, 22, 33, 44, 55, 66, 77};

const uint8_t multStateLookup_lo[] = {
	LSB(0*FAMISTUDIO_STATE_SIZE),	LSB(1*FAMISTUDIO_STATE_SIZE),	LSB(2*FAMISTUDIO_STATE_SIZE),	LSB(3*FAMISTUDIO_STATE_SIZE),
	LSB(4*FAMISTUDIO_STATE_SIZE),	LSB(5*FAMISTUDIO_STATE_SIZE),	LSB(6*FAMISTUDIO_STATE_SIZE),	LSB(7*FAMISTUDIO_STATE_SIZE),
};
const uint8_t multStateLookup_hi[] = {
	MSB(0*FAMISTUDIO_STATE_SIZE),	MSB(1*FAMISTUDIO_STATE_SIZE),	MSB(2*FAMISTUDIO_STATE_SIZE),	MSB(3*FAMISTUDIO_STATE_SIZE),
	MSB(4*FAMISTUDIO_STATE_SIZE),	MSB(5*FAMISTUDIO_STATE_SIZE),	MSB(6*FAMISTUDIO_STATE_SIZE),	MSB(7*FAMISTUDIO_STATE_SIZE),
};

extern uint16_t old_draw_scroll_y;

extern uint8_t famistudio_state[FAMISTUDIO_STATE_SIZE];
extern uint8_t famistudio_output_buf[FAMISTUDIO_OUTPUT_BUF_SIZE];
#endif

void store_practice_state(){
#if !__VS_SYSTEM
	if (!practice_point_count) {
		if (!practice_music_sync)
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
	lohi_arr16_store(practice_player_2_x, get_Y, player_x[1]);
	lohi_arr16_store(practice_player_1_y, get_Y, player_y[0]);
	lohi_arr16_store(practice_player_2_y, get_Y, player_y[1]);
	lohi_arr16_store(practice_player_1_vel_x, get_Y, player_vel_x[0]);
	lohi_arr16_store(practice_player_2_vel_x, get_Y, player_vel_x[1]);
	lohi_arr16_store(practice_player_1_vel_y, get_Y, player_vel_y[0]);
	lohi_arr16_store(practice_player_2_vel_y, get_Y, player_vel_y[1]);
	lohi_arr16_store(practice_cube_1_rotate, get_Y, cube_rotate[0]);
	lohi_arr16_store(practice_cube_2_rotate, get_Y, cube_rotate[1]);
	
	idx8_store(practice_nocamlockforced, get_Y, nocamlockforced);
	idx8_store(practice_song, get_Y, song);
	idx8_store(practice_player_1_gravity, get_Y, player_gravity[0]);
	idx8_store(practice_player_2_gravity, get_Y, player_gravity[1]);
	idx8_store(practice_player_1_mini, get_Y, mini[0]);
	idx8_store(practice_player_2_mini, get_Y, mini[1]);
	idx8_store(practice_player_1_slope_frames, get_Y, slope_frames[0]);
	idx8_store(practice_player_2_slope_frames, get_Y, slope_frames[1]);
	idx8_store(practice_player_1_was_on_slope_counter, get_Y, was_on_slope_counter[0]);
	idx8_store(practice_player_2_was_on_slope_counter, get_Y, was_on_slope_counter[1]);
	idx8_store(practice_player_1_slope_type, get_Y, slope_type[0]);
	idx8_store(practice_player_2_slope_type, get_Y, slope_type[1]);
	idx8_store(practice_player_1_last_slope_type, get_Y, last_slope_type[0]);
	idx8_store(practice_player_2_last_slope_type, get_Y, last_slope_type[1]);

	lohi_arr32_store_from(practice_scroll_x, get_Y, scroll_x);
	lohi_arr16_store(practice_scroll_y, get_Y, scroll_y);
	lohi_arr16_store(practice_seam_scroll_y, get_Y, seam_scroll_y);
	lohi_arr16_store(practice_old_draw_scroll_y, get_Y, old_draw_scroll_y);
	lohi_arr16_store(practice_target_scroll_y, get_Y, target_scroll_y);
	lohi_arr16_store(practice_min_scroll_y, get_Y, min_scroll_y);

	idx8_store(practice_player_invis, get_Y, player_invis);
	idx8_store(practice_player_gamemode, get_Y, gamemode);
	idx8_store(practice_dual, get_Y, dual);
	idx8_store(practice_speed, get_Y, speed);
	idx8_store(practice_parallax_scroll_x, get_Y, parallax_scroll_x);
	idx8_store(practice_bg_color_type, get_Y, lastbgcolortype);
	idx8_store(practice_g_color_type, get_Y, lastgcolortype);
	idx8_store(practice_outline_color, get_Y, outline_color);
	idx8_store(practice_orbactive, get_Y, orbactive);
	idx8_store(practice_disco_sprites, get_Y, disco_sprites);
	idx8_store(practice_slowmode, get_Y, slowmode);
	idx8_store(practice_forced_trails, get_Y, forced_trails);
	idx8_store(practice_gravity_mod, get_Y, gravity_mod);

	if (practice_music_sync) {
		memcpy(practice_famistudio_state + lohi_arr16_load(multStateLookup, tmp1), famistudio_state, FAMISTUDIO_STATE_SIZE);
		memcpy(practice_famistudio_registers + multBufLookup[tmp1], famistudio_output_buf, FAMISTUDIO_OUTPUT_BUF_SIZE);
    }
	practice_sprite_x_pos = high_byte(player_x[0]);
	auto_practicepoint_timer = 200;
#endif
}


void load_practice_state() {
#if !__VS_SYSTEM
	tmp2 = curr_practice_point;
	player_x[0] = lohi_arr16_load(practice_player_1_x, tmp2);
	player_x[1] = lohi_arr16_load(practice_player_2_x, get_Y);
	player_y[0] = lohi_arr16_load(practice_player_1_y, get_Y);
	player_y[1] = lohi_arr16_load(practice_player_2_y, get_Y);
	player_vel_x[0] = lohi_arr16_load(practice_player_1_vel_x, get_Y);
	player_vel_x[1] = lohi_arr16_load(practice_player_2_vel_x, get_Y);
	player_vel_y[0] = lohi_arr16_load(practice_player_1_vel_y, get_Y);
	player_vel_y[1] = lohi_arr16_load(practice_player_2_vel_y, get_Y);
	cube_rotate[0] = lohi_arr16_load(practice_cube_1_rotate, get_Y);
	cube_rotate[1] = lohi_arr16_load(practice_cube_2_rotate, get_Y);

	currplayer_gravity = player_gravity[0] = \
		idx8_load(practice_player_1_gravity, get_Y);
	player_gravity[1] = idx8_load(practice_player_2_gravity, get_Y);

	currplayer_mini = mini[0] = idx8_load(practice_player_1_mini, get_Y);
	mini[1] = idx8_load(practice_player_2_mini, get_Y);

	currplayer_slope_frames = slope_frames[0] = idx8_load(practice_player_1_slope_frames, get_Y);
	slope_frames[1] = idx8_load(practice_player_2_slope_frames, get_Y);

	currplayer_was_on_slope_counter = was_on_slope_counter[0] = \
		idx8_load(practice_player_1_was_on_slope_counter, get_Y);
	was_on_slope_counter[1] = idx8_load(practice_player_2_was_on_slope_counter, get_Y);
	
	currplayer_slope_type = slope_type[0] = \
		idx8_load(practice_player_1_slope_type, get_Y);
	slope_type[1] = idx8_load(practice_player_2_slope_type, get_Y);
	
	nocamlockforced = idx8_load(practice_nocamlockforced, get_Y);
	song = idx8_load(practice_song, get_Y);
	disco_sprites = idx8_load(practice_disco_sprites, get_Y);
	slowmode = idx8_load(practice_slowmode, get_Y);
	forced_trails = idx8_load(practice_forced_trails, get_Y);
	gravity_mod = idx8_load(practice_gravity_mod, get_Y);
	
	currplayer_last_slope_type = last_slope_type[0] = \
		idx8_load(practice_player_1_last_slope_type, get_Y);
	last_slope_type[1] = idx8_load(practice_player_2_last_slope_type, get_Y);

	lohi_arr32_load_to(practice_scroll_x, get_Y, scroll_x);
	old_trail_scroll_y = scroll_y =	lohi_arr16_load(practice_scroll_y, get_Y);
	old_draw_scroll_y = lohi_arr16_load(practice_old_draw_scroll_y, get_Y);
	seam_scroll_y = lohi_arr16_load(practice_seam_scroll_y, get_Y);
	target_scroll_y = lohi_arr16_load(practice_target_scroll_y, get_Y);
	min_scroll_y = lohi_arr16_load(practice_min_scroll_y, get_Y);

	player_invis = idx8_load(practice_player_invis, get_Y);
	gamemode = idx8_load(practice_player_gamemode, get_Y);
	dual = idx8_load(practice_dual, get_Y);
	speed = idx8_load(practice_speed, get_Y);
	parallax_scroll_x = idx8_load(practice_parallax_scroll_x, get_Y);
//	tmp2 = 0;
//	do {
//		idx8_store(trail_sprites_visible, tmp2, practice_trail_sprites_visible[tmp2]);
//		idx8_store(player_old_posy, tmp2, practice_player_old_posy[tmp2]);
//	} while (++tmp2 < 9);
	orbactive = idx8_load(practice_orbactive, get_Y);
	practice_sprite_x_pos = idx8_load(practice_player_1_x_hi, get_Y);

	outline_color = idx8_load(practice_outline_color, get_Y);

	lastgcolortype = idx8_load(practice_g_color_type, get_Y);
	lastbgcolortype = idx8_load(practice_bg_color_type, get_Y);

	scroll_x -= (256 + 16);

	tmp3 = (lastbgcolortype & 0x3F);
	pal_col(0, tmp3);
	tmp3 = oneShadeDarker(tmp3);
	pal_col(1, tmp3);
	pal_col(9, tmp3);

	tmp3 = (lastgcolortype & 0x3F);
	pal_col(6, tmp3);
	pal_col(5, oneShadeDarker(tmp3));

	tmp3 = (outline_color & 0x3F);
	pal_col(3, tmp3);
	pal_col(7, tmp3);

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
	auto_practicepoint_timer = 200;
#endif

}

void music_restore() {
	#if !__VS_SYSTEM
		famistudio_music_stop();
		
		// Copy famistudio music state
		memcpy(famistudio_state, practice_famistudio_state + lohi_arr16_load(multStateLookup, tmp2), FAMISTUDIO_STATE_SIZE);

		// Copy the registers
		memcpy(famistudio_output_buf, practice_famistudio_registers + multBufLookup[tmp2], FAMISTUDIO_OUTPUT_BUF_SIZE);

		// Clear all sfx (only 1 stream is enabled, that's all we need to clear)
		famistudio_sfx_clear_channel(FAMISTUDIO_SFX_CH0);
		// famistudio_sfx_clear_channel(FAMISTUDIO_SFX_CH1);
		// famistudio_sfx_clear_channel(FAMISTUDIO_SFX_CH2);
		// famistudio_sfx_clear_channel(FAMISTUDIO_SFX_CH3);

		// Output to APU
		POKE(0x4000, famistudio_output_buf[0]);
		POKE(0x4001, 0x08);
		POKE(0x4002, famistudio_output_buf[1]);
		POKE(0x4003, famistudio_output_buf[2]);
		POKE(0x4004, famistudio_output_buf[3]);
		POKE(0x4005, 0x08);
		POKE(0x4006, famistudio_output_buf[4]);
		POKE(0x4007, famistudio_output_buf[5]);
		POKE(0x4008, famistudio_output_buf[6]);
		POKE(0x400a, famistudio_output_buf[7]);
		POKE(0x400b, famistudio_output_buf[8]);
		POKE(0x400c, famistudio_output_buf[9]);
		POKE(0x400e, famistudio_output_buf[10]);
	#endif
}	

CODE_BANK_POP()
