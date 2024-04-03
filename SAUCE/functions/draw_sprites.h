void reset_level(void);

void draw_sprites(void){


	// draw player
    temp_x = high_byte(player.x);
	if(temp_x > 0xfc) temp_x = 1;
	if(temp_x == 0) temp_x = 1;
	switch (gamemode){
		default:
			cube_rotate += CUBE_GRAVITY;
			if (cube_rotate > 0x05FF) cube_rotate -= 0x0600;

			if (!gravity) oam_meta_spr(temp_x, high_byte(player.y)-1, CUBE[high_byte(cube_rotate)]);
			else oam_meta_spr_vflipped(temp_x, high_byte(player.y)-1, CUBE[high_byte(cube_rotate)]);

			break;
		case 0x01:
			cube_rotate = 0x0400 - player.vel_y;
			if (high_byte(cube_rotate) >= 0x08) {
				cube_rotate = high_byte(cube_rotate) >= 0x80 ? 0x0000 : 0x07FF;
			}

			if (!gravity) oam_meta_spr(temp_x, high_byte(player.y)-1, SHIP[high_byte(cube_rotate)]);
			else oam_meta_spr_vflipped(temp_x, high_byte(player.y)-1, SHIP[7-high_byte(cube_rotate)]);

			break;
		case 0x02:

			cube_rotate ^= 0x0100;
			oam_meta_spr(temp_x, high_byte(player.y)-1, BALL[ballframe]);
			ballframe++;
			if (ballframe > 5) { ballframe = 0; }
			break;
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

		if (activesprites_type[index] & 0x30) continue;
		temp_y = low_byte(activesprites_realy[index]);
		if (!activesprites_active[index]) continue; 
		temp_x = low_byte(activesprites_realx[index]);
		if (temp_x == 0) temp_x = 1;
		if (temp_x > 0xf0) continue;
		if (temp_y < 0xf0) {
			tmp3 = activesprites_type[index];
			if (tmp3 == 7) {			//coin
				oam_meta_spr(temp_x, temp_y-1, COIN_SPRITES[coinframe]);
				coinframe++;
				if (coinframe > 19) {coinframe = 0;}
			}
			else if (tmp3 == 0x0A) {			//yellow pad
				oam_meta_spr(temp_x, temp_y-1, YELLOW_PAD_FRAMES[padframe]);
			}
			else {
				oam_meta_spr(temp_x, temp_y-1, Metasprites[tmp3 & 0x0f]);
			}
				padframe++;
				if (padframe > 7) {padframe = 0;}
		}
	}
}
