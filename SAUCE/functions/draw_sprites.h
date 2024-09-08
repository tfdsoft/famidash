#pragma code-name(push, "XCD_BANK_04")
#pragma data-name(push, "XCD_BANK_04")
#pragma rodata-name(push, "XCD_BANK_04")

void reset_level(void);

/*
	Draws the first player sprite
	Implemented in asm
*/
void __fastcall__ drawplayerone();
void __fastcall__ drawplayertwo();

uint8_t plus9_tbl [] = {
	(0x0 + 9)&0xF,	(0x1 + 9)&0xF,	(0x2 + 9)&0xF,	(0x3 + 9)&0xF,
	(0x4 + 9)&0xF,	(0x5 + 9)&0xF,	(0x6 + 9)&0xF,	(0x7 + 9)&0xF,
	(0x8 + 9)&0xF,	(0x9 + 9)&0xF,	(0xA + 9)&0xF,	(0xB + 9)&0xF,
	(0xC + 9)&0xF,	(0xD + 9)&0xF,	(0xE + 9)&0xF,	(0xF + 9)&0xF,
};

void draw_sprites(void){
	// dual = 1;
	// twoplayer = 1;
	
	// draw player

	if (!invisible) {
		if (dual) {
			if (kandoframecnt & 0x01) { drawplayertwo(); drawplayerone(); }
			else { drawplayerone(); drawplayertwo(); }
		}
#ifdef FLAG_KANDO_FUN_STUFF
		else if (bigboi) { drawplayerone(); high_byte(player_x[0]) += 15; drawplayerone(); high_byte(player_x[0]) -= 15; high_byte(player_y[0]) -= 15; drawplayerone(); high_byte(player_x[0]) += 15; drawplayerone(); high_byte(player_x[0]) -= 15; high_byte(player_y[0]) += 15; }
		else if (longmode && !tallmode) { drawplayerone(); high_byte(player_x[0]) += 15; drawplayerone(); high_byte(player_x[0]) -= 15; }
		else if (tallmode && !longmode) { drawplayerone(); high_byte(player_y[0]) -= 15; drawplayerone(); high_byte(player_y[0]) += 15; }
		else if (tallmode && longmode) { drawplayerone(); high_byte(player_y[0]) -= 15; drawplayerone(); high_byte(player_y[0]) += 15; high_byte(player_x[0]) += 15; drawplayerone(); high_byte(player_x[0]) -= 15; }
#endif
		else drawplayerone();
	}
	// the level sprites

	//	for (index = 0; index < max_loaded_sprites; ++index){		//no flicker
	if (invisblocks) return;

	if (has_practice_point) {
		
		if (long_temp_x > 10) { 
			long_temp_x -= 2;
			oam_meta_spr(long_temp_x, idx16_hi_NOC(practice_player_y, currplayer)-1, Practice_Sprites[0]);
		}
		// else if (long_temp_x < 10) {}
	}

	if (retro_mode) {
		tmp9 = 0;
		do {
			if (jimsheatballalive[tmp9]) {
				oam_meta_spr(jimsheatballx[tmp9 & 0x7F], idx16_hi_NOC(jimsheatbally, tmp9), Heat_Ball_Sprites[jimsheatballframe[tmp9] & 0x7F]);		
				jimsheatballframe[tmp9] == 20 ? jimsheatballframe[tmp9] = 0 : uint8_inc(jimsheatballframe, tmp9);
				jimsheatballx[tmp9 & 0x7F] == 0xFF ? jimsheatballalive[tmp9] = 0 : uint8_inc(jimsheatballx, tmp9);
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
		
		if ((int8_t)(uint8_load(activesprites_type, index)) < 0) continue;
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
			animation_frame_count = uint8_dec(activesprites_anim_frame_count, index);
			if ((int8_t)animation_frame_count < 0) {
				animation_frame = uint8_inc(activesprites_anim_frame, index);
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
	if (forced_trails == 1 || trails == 1 || (gamemode == 6 && trails != 2)) {
		tmp6 = currplayer_vel_x << 1;
		tmp5 = player_x[0] - tmp6;

		tmp1 = 8;

		do {
			oam_meta_spr(high_byte(tmp5), uint8_load(player_old_posy, (uint8_t)(9 - tmp1)), Trail_Circ);
			tmp5 = tmp5 - tmp6;
			tmp1--;
		} while (tmp1 > 0);

	}
	if ((forced_trails == 2 || trails == 2) && !dual && !twoplayer) {

		tmp6 = currplayer_vel_x << 2;
		
		tmpA = player_x[0];
		tmpB = player_y[0];

		high_byte(player_x[0]) -= high_byte(tmp6);
		high_byte(player_y[0]) = player_old_posy[3];

		drawplayerone();
		
		high_byte(player_x[0]) -= high_byte(tmp6);
		high_byte(player_y[0]) = player_old_posy[6];

		drawplayerone();
		
		player_x[0] = tmpA;
		player_y[0] = tmpB;
	}
#undef spr_type
#undef animation_ptr
}



#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)
