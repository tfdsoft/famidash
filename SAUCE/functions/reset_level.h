extern unsigned char drawing_frame;
extern unsigned char* PARALLAX_CHR;

void music_restore();

void death_animation() {
	nmi_fs_updates_on();
	if (!practice_point_count || practice_music_sync) famistudio_music_stop();

	tmp1 = 30;
	if (!DEBUG_MODE) {
		if (cube_data[0] & 1) tmp2 = 0;
		else if (cube_data[1] & 1) tmp2 = 1;

		#if __VS_SYSTEM
		coins_inserted--;
		#endif
		update_level_completeness();
		sfx_play(sfx_death, 0);
		while (tmp1 != 0){
			ppu_wait_nmi();
			dual == 1 ? oam_clear_two_players() : oam_clear_player();
			
			if (robotjumpframe[0] < 20) {
				if (!retro_mode) oam_meta_spr(high_byte(player_x[tmp2])-2, high_byte(player_y[tmp2])-2, Explode_Sprites[robotjumpframe[0] & 0x7F]);
				else oam_meta_spr(high_byte(player_x[tmp2])-2, high_byte(player_y[tmp2])-2, ExplodeR_Sprites[robotjumpframe[0] & 0x7F]);
				++robotjumpframe[0];
			}
//			pad_poll(0);
			if (practice_point_count > 1 && (((mouse.connected ? 0 : joypad2.press) | joypad1.press) & PAD_SELECT)) {
				curr_practice_point--;
				if (curr_practice_point >= practice_point_count)
					curr_practice_point = practice_point_count - 1;
			}	

			--tmp1;
		}					
	}

	pal_fade_out();
	oam_clear();
	ppu_off(); // reset the level when you get to this point, and change this later
	nmi_fs_updates_off();
}

void reset_level() {
	nmi_fs_updates_on();

	#if !__VS_SYSTEM
	gameState = STATE_GAME; //fix for dying as the end trigger triggers
	#endif
	// slope stuff
	currplayer_was_on_slope_counter = 0;
	was_on_slope_counter[0] = 0;
	was_on_slope_counter[1] = 0;
	jumps = 0;
	ufo_orbed = 0;
	slowmode = 0;
	force_platformer = 0;
	player_invis = 0;
	slope_type[0] = SLOPE_NONE;
	slope_type[1] = SLOPE_NONE;
	currplayer_slope_type = SLOPE_NONE;
	last_slope_type[0] = SLOPE_NONE;
	last_slope_type[1] = SLOPE_NONE;
	currplayer_last_slope_type = SLOPE_NONE;
	curr_practice_point = latest_practice_point;
	robotjumpframe[0] = 0;
	slope_frames[0] = 0;
	slope_frames[1] = 0;
	nocamlockforced = 0;
	minicoins = 0;
	currplayer_slope_frames = 0;
	make_cube_jump_higher = 0;

	#if __VS_SYSTEM
	if (!coins_inserted) return;
	#endif

	scroll_y = 0x2EF;
	seam_scroll_y = (0x2EF - 0x78); // [temp]
	set_scroll_x(scroll_x);
	set_scroll_y(scroll_y);
	init_rld(level);

	if (!(options & platformer) && !force_platformer) {
	player_x[0] = 0x0000;
	player_x[1] = 0x0000;
	currplayer_x = 0x0000;
	} else {
	player_x[0] = 0x1110;
	player_x[1] = 0x1110;
	currplayer_x = 0x1110;
	}

	player_y[0] = 0xb000;
	player_y[1] = 0xb000;
	currplayer_y = 0xb000;

	memfill(jimsheatballalive, 0, MAX_FIREBALLS);

	for (tmp1 = 0; tmp1 < max_loaded_sprites; tmp1++) {
		activesprites_anim_frame[tmp1] = 0;
	}

	player_gravity[1] = twoplayer ? GRAVITY_DOWN : GRAVITY_UP;

	currplayer_gravity = GRAVITY_DOWN;
	update_currplayer_table_idx();

	tmp1 = 0;
	do {
		activesprites_active[tmp1] = 0;
	} while (++tmp1 < max_loaded_sprites);

	dual = twoplayer ? 1 : 0;
	player_gravity[0] = GRAVITY_DOWN;
	scroll_x = 0;
	drawing_frame = 0;
	gravity_mod = 0;
	disco_sprites = 0;
	player_mini[0] = player_mini[1] = currplayer_mini = 0;
	player_vel_x[0] = player_vel_x[1] = currplayer_vel_x = 0;
	player_vel_y[0] = player_vel_y[1] = currplayer_vel_y = 0;
	forced_trails = 0;
	cube_rotate[0] = 0;
	cube_rotate[1] = 0;
	coins = 0;
	orbactive = 0;
	coin1_timer = coin2_timer = coin3_timer = 0;
//	cube_data[0] = 0;
//	cube_data[1] = 0;   this resets in level_loading/unrle_first_screen
#ifdef FLAG_KANDO_FUN_STUFF
	tallmode = 0;
	longmode = 0;
	bigboi = 0;
#endif
	target_scroll_y = 0x0180;
	curr_x_scroll_stop = 0x5000;
	target_x_scroll_stop = 0x5000;
	discoframe = 0;
	if (!practice_point_count) {
		memfill(player_old_posy, 0, sizeof(player_old_posy));
		memfill(trail_sprites_visible, 0, sizeof(trail_sprites_visible));
		invincible_counter = 8;
	}
	update_currplayer_table_idx();

	unrle_first_screen();

	if (!no_parallax) mmc3_set_1kb_chr_bank_2(parallax_scroll_x + GET_BANK(PARALLAX_CHR));
	ppu_on_all();
	pal_fade_in();
	if (!practice_point_count) {
		music_play(song);
	} else if (practice_music_sync) {
		crossPRGBankJump0(music_restore);
	}		
	nmi_fs_updates_off();
}