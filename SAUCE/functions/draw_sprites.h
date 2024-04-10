void reset_level(void);

#pragma code-name(push, "LVL_BANK_00")
#pragma data-name(push, "LVL_BANK_00")
#pragma rodata-name(push, "LVL_BANK_00")


void draw_sprites(void){
	// draw player
    temp_x = high_byte(player.x);
	if(temp_x > 0xfc) temp_x = 1;
	if(temp_x == 0) temp_x = 1;
	switch (gamemode){
		default:

			cube_rotate += CUBE_GRAVITY;
			if (player.vel_y == 0) cube_rotate = 0;
			if (cube_rotate > 0x05FF) cube_rotate -= 0x0600;

			if (!mini) {
				if (!gravity) oam_meta_spr(temp_x, high_byte(player.y)-1, CUBE[high_byte(cube_rotate)]);
				else oam_meta_spr_vflipped(temp_x, high_byte(player.y)-1, CUBE[high_byte(cube_rotate)]);
			}
			else {
				if (!gravity) oam_meta_spr(temp_x, high_byte(player.y)-1, MINI_CUBE[high_byte(cube_rotate)]);
				else oam_meta_spr_vflipped(temp_x, high_byte(player.y)-1, MINI_CUBE[high_byte(cube_rotate)]);				
			}
			break;
		case 0x01:
			cube_rotate = 0x0400 - player.vel_y;
			if (high_byte(cube_rotate) >= 0x08) {
				cube_rotate = high_byte(cube_rotate) >= 0x80 ? 0x0000 : 0x07FF;
			}

			if (!mini) {
				if (!gravity) oam_meta_spr(temp_x, high_byte(player.y)-1, SHIP[high_byte(cube_rotate)]);
				else oam_meta_spr_vflipped(temp_x, high_byte(player.y)-1, SHIP[7-high_byte(cube_rotate)]);
			}
			else {
				if (!gravity) oam_meta_spr(temp_x, high_byte(player.y)-1, MINI_SHIP[high_byte(cube_rotate)]);
				else oam_meta_spr_vflipped(temp_x, high_byte(player.y)-1, MINI_SHIP[7-high_byte(cube_rotate)]);
			}
			break;
			
		case 0x02:
			if (!mini) {
				if (!gravity) oam_meta_spr(temp_x, high_byte(player.y)-1, BALL[ballframe]);
				else oam_meta_spr_vflipped(temp_x, high_byte(player.y)-1, BALL[ballframe]);
				ballframe++;
				if (ballframe > 7) { ballframe = 0; }
			}
			else   {
				if (!gravity) oam_meta_spr(temp_x, high_byte(player.y)-1, MINI_BALL[ballframe]);
				else oam_meta_spr_vflipped(temp_x, high_byte(player.y)-1, MINI_BALL[ballframe]);
			}
			break;

		case 0x03:
			if (!gravity) {
				if (player.vel_y == 0 || player.vel_y == 0x6B) kandotemp3 = 0;
				else if (player.vel_y > 0) kandotemp3 = 1;
				else if (player.vel_y < 0) kandotemp3 = 2;
				if (!mini) oam_meta_spr(temp_x, high_byte(player.y)-1, UFO[kandotemp3]);
				else oam_meta_spr(temp_x, high_byte(player.y)-1, MINI_UFO[kandotemp3]);
			}
			else {
				if (player.vel_y == 0 || player.vel_y == -0x6B) kandotemp3 = 0;
				else if (player.vel_y > 0) kandotemp3 = 1;
				else if (player.vel_y < 0) kandotemp3 = 2;
		
				if (!mini) oam_meta_spr_vflipped(temp_x, high_byte(player.y)-1, UFO[kandotemp3]);
				else oam_meta_spr_vflipped(temp_x, high_byte(player.y)-1, MINI_UFO[kandotemp3]);
			}
			break;
			
		case 0x04:
			if (player.vel_y == 0 || player.vel_y == CUBE_GRAVITY) {
				if (!mini) {
					if (!gravity) oam_meta_spr(temp_x, high_byte(player.y)-1, ROBOT[robotframe]);
					else oam_meta_spr_vflipped(temp_x, high_byte(player.y)-1, ROBOT[robotframe]);
				}
				else {
					if (!gravity) oam_meta_spr(temp_x, high_byte(player.y)-1, MINI_ROBOT[robotframe]);
					else oam_meta_spr_vflipped(temp_x, high_byte(player.y)-1, MINI_ROBOT[robotframe]);					
				}
				robotframe++;
				if (robotframe > 19) { robotframe = 0; }
				break;
			}
			else {
				if (!mini) {
					if (!gravity) oam_meta_spr(temp_x, high_byte(player.y)-1, ROBOT_JUMP[robotjumpframe]);
					else oam_meta_spr_vflipped(temp_x, high_byte(player.y)-1, ROBOT_JUMP[robotjumpframe]);
				}
				else {
					if (!gravity) oam_meta_spr(temp_x, high_byte(player.y)-1, MINI_ROBOT_JUMP[robotjumpframe]);
					else oam_meta_spr_vflipped(temp_x, high_byte(player.y)-1, MINI_ROBOT_JUMP[robotjumpframe]);
				}
				break;
			}
    }
	
	// the level sprites

	//	for (index = 0; index < max_loaded_sprites; ++index){		//no flicker

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
				animation_data_ptr = (unsigned char*)high2bytes(tmplong);
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
