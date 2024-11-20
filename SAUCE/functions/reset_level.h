extern unsigned char drawing_frame;
extern unsigned char* PARALLAX_CHR;

void reset_level(void) {
	// unsigned char i;
	if (!practice_point_count) famistudio_music_stop();


	// slope stuff
	was_on_slope_counter = 0;
	slope_frames = 0;
	jumps = 0;
	ufo_orbed = 0;
	slope_type = SLOPE_NONE;
	last_slope_type = SLOPE_NONE;
	curr_practice_point = practice_point_count;
	robotjumpframe[0] = 0;
	tmp1 = 30;
	if (!DEBUG_MODE && (cube_data[0] & 1)) {
		update_level_completeness();
		sfx_play(sfx_death, 0);
		while (tmp1 != 0){
			ppu_wait_nmi();
			music_update();
			dual == 1 ? oam_clear_two_players() : oam_clear_player();
			
			if (robotjumpframe[0] < 20) {
				if (!retro_mode) oam_meta_spr(high_byte(player_x[0])-2, high_byte(player_y[0])-2, Explode_Sprites[robotjumpframe[0] & 0x7F]);
				else oam_meta_spr(high_byte(player_x[0])-2, high_byte(player_y[0])-2, ExplodeR_Sprites[robotjumpframe[0] & 0x7F]);
				++robotjumpframe[0];
			}
//			pad_poll(0);
			if (joypad1.press_select && practice_point_count > 1) { practice_point_count--; curr_practice_point = 0; }				
			if (!mouse.connected && joypad2.press_select && practice_point_count > 1) { practice_point_count--; curr_practice_point = 0; }				

			--tmp1;
		}
	}
	else if (!DEBUG_MODE && (cube_data[1] & 1)) {
		update_level_completeness();
		sfx_play(sfx_death, 0);
		while (tmp1 != 0){
			ppu_wait_nmi();
			music_update();
			dual == 1 ? oam_clear_two_players() : oam_clear_player();
			if (robotjumpframe[0] < 20) {
				if (!retro_mode) oam_meta_spr(high_byte(player_x[1])-2, high_byte(player_y[1])-2, Explode_Sprites2[robotjumpframe[0] & 0x7F]);
				else oam_meta_spr(high_byte(player_x[1])-2, high_byte(player_y[1])-2, ExplodeR_Sprites2[robotjumpframe[0] & 0x7F]);
				
				++robotjumpframe[0];
			}
			if (joypad1.press_select && practice_point_count > 1) { practice_point_count--; curr_practice_point = 0; }				
			if (joypad2.press_select && practice_point_count > 1) { practice_point_count--; curr_practice_point = 0; }				
			--tmp1;
		}
	}
	pal_fade_to_withmusic(4,0);
	oam_clear();
	ppu_off(); // reset the level when you get to this point, and change this later

	scroll_y = 0x2EF;
	seam_scroll_y = (0x2EF - 0x78); // [temp]
	set_scroll_x(scroll_x);
	set_scroll_y(scroll_y);
	init_rld(level);

	if (!(options & platformer)) {
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

	player_gravity[1] = twoplayer ? 0x00 : 0x01;

	currplayer_gravity = 0;

	tmp1 = 0;
	do {
		activesprites_active[tmp1] = 0;
	} while (++tmp1 < max_loaded_sprites);

	dual = twoplayer ? 1 : 0x00;
	player_gravity[0] = 0x00;
	scroll_x = 0;
	drawing_frame = 0;
	gravity_mod = 0;
	disco_sprites = 0;
	currplayer_mini = 0x00;
	mini[0] = 0;
	mini[1] = 0;
	currplayer_vel_x = 0;
	currplayer_vel_y = 0;
	forced_trails = 0;
	player_vel_x[0] = 0;
	player_vel_y[0] = 0;
	player_vel_x[1] = 0;
	player_vel_y[1] = 0;
	cube_rotate[0] = 0;
	cube_rotate[1] = 0;
	coins = 0;
	orbactive = 0;
	coin1_timer = 0;
	coin2_timer = 0;
	coin3_timer = 0;	
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

	unrle_first_screen();

	if (practice_point_count) {
		tmp3 = practice_bg_color_type[practice_point_count-1];
			tmp2 = (tmp3 & 0x3F);                        
			pal_col(0, tmp2);
			pal_col(1, oneShadeDarker(tmp2)); 
			pal_col(9, oneShadeDarker(tmp2)); 

		tmp3 = practice_g_color_type[practice_point_count-1];
			tmp2 = (tmp3 & 0x3F);                        
	    pal_col(6, tmp2);

	    pal_set_update();
	}
	if (!no_parallax) mmc3_set_1kb_chr_bank_2(parallax_scroll_x + GET_BANK(PARALLAX_CHR));
	ppu_on_all();
	pal_fade_to_withmusic(0,4);
	if (!practice_point_count) {
	music_play(song);
	}

}