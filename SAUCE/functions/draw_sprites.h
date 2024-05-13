#pragma code-name(push, "XCD_BANK_00")
#pragma data-name(push, "XCD_BANK_00")
#pragma rodata-name(push, "XCD_BANK_00")

void reset_level(void);

/*
	Draws the first player sprite
	Implemented in asm
*/
void __fastcall__ drawplayerone();
void __fastcall__ drawplayertwo();

void draw_sprites(void){
//	dual = 1;
//	twoplayer = 1;
	// draw player

	if (!invisible) {
		if (dual) {
			if (kandoframecnt & 0x01) { drawplayertwo(); drawplayerone(); }
			else { drawplayerone(); drawplayertwo(); }
		}
		else drawplayerone();
	}
	// the level sprites

	//	for (index = 0; index < max_loaded_sprites; ++index){		//no flicker

	if (has_practice_point) {
		
		if (long_temp_x > 10) { 
				long_temp_x--;
				long_temp_x--;
				oam_meta_spr(long_temp_x, high_byte(practice_player_y[currplayer])-1, Practice_Sprites[0]);
		}
		else if (long_temp_x < 10) { }
	}

	if (trails) {
		oam_meta_spr(player_old_posx[7], player_old_posy[7], Trail_Circle[0]);
		oam_meta_spr(player_old_posx[6], player_old_posy[6], Trail_Circle[0]);
		oam_meta_spr(player_old_posx[5], player_old_posy[5], Trail_Circle[0]);
		oam_meta_spr(player_old_posx[4], player_old_posy[4], Trail_Circle[0]);
		oam_meta_spr(player_old_posx[3], player_old_posy[3], Trail_Circle[0]);
		oam_meta_spr(player_old_posx[2], player_old_posy[2], Trail_Circle[0]);
		oam_meta_spr(player_old_posx[1], player_old_posy[1], Trail_Circle[0]);
		oam_meta_spr(player_old_posx[0], player_old_posy[0], Trail_Circle[0]);
	}

        shuffle_offset += 11;								//-----------|
        if (shuffle_offset >= max_loaded_sprites) {					//           |
          shuffle_offset -= max_loaded_sprites;						//           |
        }										//           |
        // the level sprites								//           |
        for (count = 0; count < max_loaded_sprites; ++count){				//   FLICKER |
          // and every sprite add another number thats also coprime with 16 AND 11	//           |
          shuffle_offset += 9;								//           |
          if (shuffle_offset >= max_loaded_sprites) {					//           |	
            shuffle_offset -= max_loaded_sprites;					//           |
          }										//           |
          index = shuffle_offset;							//-----------|

		if (index < 0xF0) {
			if (activesprites_type[index] & 0x80) continue;
		}
		temp_y = low_byte(activesprites_realy[index]);
		if (!activesprites_active[index]) continue; 
		temp_x = low_byte(activesprites_realx[index]);
		if (temp_x == 0) temp_x = 1;
		if (temp_x > 0xf0) continue;
#define animation_frame_count tmp1
#define animation_frame tmp2
#define spr_type tmp3
#define needs_reload tmp4
#define animation_ptr tmpptr1
#define animation_data_ptr tmpptr2
		if (activesprites_type[index] > 0x80) {}
		else {
			if (temp_y < 0xf0) {
			needs_reload = 0;
			spr_type = activesprites_type[index];
			animation_ptr = (unsigned char*)animation_frame_list[spr_type];
			// If this sprite has animations, then this pointer will not be null
			if (animation_ptr) {
				// Reduce the frame counter by one to see if we need to move to the next frame
				// If this frame has expired, then move to the next animation frame
				animation_frame_count = --activesprites_anim_frame_count[index];
				if (animation_frame_count >= 0x80) {
					animation_frame = ++activesprites_anim_frame[index];
					// if the animation frame is past the length, wrap it around back to zero
					if (animation_frame >= animation_frame_length[spr_type]) {
						activesprites_anim_frame[index] = animation_frame = 0;
					}
					// and then set the animation_frame_count to be reloaded
					needs_reload = 1;
				} else {
					animation_frame = activesprites_anim_frame[index];
				}
				
				// Now load the data for this frame of animation
				// The fastest way to convince cc65 to read all of the data is to force
				// it to read all the bytes at once
				tmplong = ((unsigned long int*)animation_ptr)[animation_frame];
				if (needs_reload) {
					activesprites_anim_frame_count[index] = low_byte(tmplong);
				}
				// And finally, load the pointer for this animation
				animation_data_ptr = (unsigned char*)high_word(tmplong);
			} else {
				animation_data_ptr =  (unsigned char*)Metasprites[spr_type];
			}
			oam_meta_spr(temp_x, temp_y, animation_data_ptr);
			}
		}
		
	}
#undef spr_type
#undef animation_ptr
}



#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)
