CODE_BANK_PUSH("XCD_BANK_04")

void reset_level(void);
void minus15y();
void minus15x();
void plus15y();
void plus15x();
void trail_loop();
/*
	Draws the first player sprite
	Implemented in asm
*/
void __fastcall__ drawplayerone();
void __fastcall__ drawplayertwo();

void draw_sprites(void){
	// dual = 1;
	// twoplayer = 1;
	
	// draw player
	if (!invisible) {
		if (dual) {
			if (kandoframecnt & 0x01) { crossPRGBankJump0(drawplayertwo); crossPRGBankJump0(drawplayerone); }
			else { crossPRGBankJump0(drawplayerone); crossPRGBankJump0(drawplayertwo); }
		}
#ifdef FLAG_KANDO_FUN_STUFF
		else if (bigboi) { crossPRGBankJump0(drawplayerone); plus15x(); crossPRGBankJump0(drawplayerone); minus15x(); minus15y(); crossPRGBankJump0(drawplayerone); plus15x(); crossPRGBankJump0(drawplayerone); minus15x(); plus15y(); }
		else if (longmode && !tallmode) { crossPRGBankJump0(drawplayerone); plus15x(); crossPRGBankJump0(drawplayerone); minus15x(); }
		else if (tallmode && !longmode) { crossPRGBankJump0(drawplayerone); minus15y(); crossPRGBankJump0(drawplayerone); plus15y(); }
		else if (tallmode && longmode) { crossPRGBankJump0(drawplayerone); minus15y(); crossPRGBankJump0(drawplayerone); plus15y(); plus15x(); crossPRGBankJump0(drawplayerone); minus15x(); }
#endif
		else crossPRGBankJump0(drawplayerone);
	}
	// the level sprites

	//	for (index = 0; index < max_loaded_sprites; ++index){		//no flicker
	if (invisblocks) return;

	if (practice_point_count) {
		tmp3 = practice_player_1_y_hi[curr_practice_point];
		if (long_temp_x > 10) { 
			long_temp_x -= 3;
			oam_meta_spr(long_temp_x, tmp3 - 1, Practice_Sprites[0]);
		}
		// else if (long_temp_x < 10) {}
	}

	if (retro_mode) {
		tmp9 = 0;
		do {
			if (jimsheatballalive[tmp9]) {
				oam_meta_spr(jimsheatballx[tmp9 & 0x7F], idx16_load_hi_NOC(jimsheatbally, tmp9), Heat_Ball_Sprites[jimsheatballframe[tmp9] & 0x7F]);		
				jimsheatballframe[tmp9] == 20 ? jimsheatballframe[tmp9] = 0 : idx8_inc(jimsheatballframe, tmp9);
				jimsheatballx[tmp9 & 0x7F] >= 0xF8 ? jimsheatballalive[tmp9] = 0 : idx16_inc_NOC(jimsheatballx, tmp9);
			}
		} while (++tmp9 < MAX_FIREBALLS);
	}

	


	

	// The flickering motherfucker, by jrowe
	shuffle_offset = (shuffle_offset + 11) & 0x0F;
	// the level sprites
	count = 0;
	do {
		// and every sprite add another number thats also coprime with 16 AND 11
		shuffle_offset = (shuffle_offset + 9) & 0x0F;	// !!! If max_loaded_sprites changes change this
		index = shuffle_offset;
		
		if ((int8_t)(idx8_load(activesprites_type, index)) < 0) continue;
		if (!activesprites_active[index]) continue; 

		temp_x = activesprites_realx[index];
		if (temp_x > 0xf0) continue;
		if (temp_x == 0) temp_x = 1;

		temp_y = activesprites_realy[index];
		if (temp_y > 0xf0) continue;

		#define animation_frame_count tmp1
		#define animation_frame tmp2
		#define spr_type tmp3
		#define needs_reload tmp4
		#define animation_ptr tmpptr1
		#define animation_data_ptr tmpptr2
		
		needs_reload = 0;
		spr_type = activesprites_type[index];
		animation_ptr = (unsigned char *)animation_frame_list[spr_type & 0x7F];
		// If this sprite has animations, then this pointer will not be null
		if (high_byte(animation_ptr)) {
			// Reduce the frame counter by one to see if we need to move to the next frame
			// If this frame has expired, then move to the next animation frame
			animation_frame_count = idx8_dec(activesprites_anim_frame_count, index);
			if ((int8_t)animation_frame_count < 0) {
				animation_frame = idx8_inc(activesprites_anim_frame, index);
				// if the animation frame is past the length, wrap it around back to zero
				if (animation_frame >= animation_frame_length[spr_type]) {
					activesprites_anim_frame[index] = 0;
					animation_frame = 0;
				}
				// and then set the animation_frame_count to be reloaded
				needs_reload = 1;
			} else {
				animation_frame = activesprites_anim_frame[index];
			}
			
			// Now load the data for this frame of animation
			// The fastest way to convince cc65 to read all of the data is to force
			// it to read all the bytes at once
			__AX__ = animation_frame << 1;
			__AX__ += animation_frame;
			animation_ptr += __AX__;

			__asm__ ("ldy #2 \n lda (%v), y \n sta %v+1 \n dey \n lda (%v), y \n sta %v", animation_ptr, animation_data_ptr, animation_ptr, animation_data_ptr);

			if (needs_reload) {
				__A__ = *(uint8_t*)animation_ptr;
				__asm__ ("ldy %v \n sta %v, y", index, activesprites_anim_frame_count);
			}
			
			// And load the pointer for this animation
		} else {
			animation_data_ptr = (unsigned char*)Metasprites[spr_type & 0x7F];
		}
		oam_meta_spr(temp_x, temp_y, animation_data_ptr);
		
	} while (++count < max_loaded_sprites);
	if (!dual) {
	if (kandoframecnt & 0x01) {
		
		tmp2 = 0;
		do {
			__A__ = idx8_load(trail_sprites_visible, tmp2 + 1); __asm__("pha");	
			idx8_store(trail_sprites_visible, tmp2, (__asm__("pla"), __A__));	// TODO: idx8_X or idxY_load_store macros, this is insane 
		} while (++tmp2 < sizeof(trail_sprites_visible) - 1);

		if (orbactive || trails == 1) {
			trail_sprites_visible[tmp2] = 1;
		} else {
			trail_sprites_visible[tmp2] = 0;
		}
	}
	if ((trails == 1) || (trails != 2) && forced_trails != 2 && !invisible && viseffects) {
		trail_loop();
	}
	else if ((forced_trails == 2 || trails == 2) && !dual && viseffects) {
		temptemp5++;
		tmp6 = currplayer_vel_x << 1;
		
		tmpA = player_x[0];
		tmpB = player_y[0];

		high_byte(player_x[0]) -= high_byte(tmp6);
		high_byte(player_y[0]) = player_old_posy[1];

		if (!(kandoframecnt & 1)) crossPRGBankJump0(drawplayerone);
		
		high_byte(player_x[0]) -= high_byte(tmp6);
		high_byte(player_y[0]) = player_old_posy[2];

		if (kandoframecnt & 1) crossPRGBankJump0(drawplayerone);

		high_byte(player_x[0]) -= high_byte(tmp6);
		high_byte(player_y[0]) = player_old_posy[3];

		if (gamemode == 0) {
			tmp9 = currplayer_mini;
			currplayer_mini = 1;
		}

		if (!(kandoframecnt & 1)) crossPRGBankJump0(drawplayerone);
		
		if (gamemode == 0) {
			currplayer_mini = tmp9;
		}
		
		player_x[0] = tmpA;
		player_y[0] = tmpB;
		temptemp5--;		
	}
	}
#undef spr_type
#undef animation_ptr
}

void trail_loop() {
	tmp6 = currplayer_vel_x << 1;

	if (kandoframecnt & 1) {
		tmp1 = 8;
		tmp5 = currplayer_x - tmp6;
		do {
			if (trail_sprites_visible[tmp1 - 1]) {	
				oam_meta_spr(high_byte(tmp5), idx8_load(player_old_posy, (uint8_t)(9 - tmp1)), Trail_Circ);
			}
			
			tmp5 = tmp5 - tmp6;
			tmp1--;
		} while (tmp1 > 1);
	} else {
		tmp1 = 2;
		tmp5 = currplayer_x - tmp6 - tmp6 - tmp6 - tmp6 - tmp6 - tmp6 - tmp6;
		do {
			if (trail_sprites_visible[tmp1 - 1]) {
				oam_meta_spr(high_byte(tmp5), idx8_load(player_old_posy, (uint8_t)(9 - tmp1)), Trail_Circ);
			}
			
			tmp5 = tmp5 + tmp6;
			tmp1++;
		} while (tmp1 < 9);
	}	
}

void put_progress_bar_sprite() {
	oam_meta_spr(tmp1, tmp2, Number_Sprites[22 + tmp3]);
}

void put_number() {
	oam_meta_spr(tmp1, tmp2, Number_Sprites[high_byte(tmp6) + tmp3]);
}

void minus15y() {
	high_byte(player_y[0]) -= 15;
}

void minus15x() {
	high_byte(player_x[0]) -= 15;
}

void plus15y() {
	high_byte(player_y[0]) += 15;
}

void plus15x() {
	high_byte(player_x[0]) += 15;
}

CODE_BANK_POP()
