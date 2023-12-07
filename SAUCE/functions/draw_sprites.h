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
		case 0x02:
			cube_rotate = 0x0400 - player.vel_y;
			if (high_byte(cube_rotate) >= 0x08) {
				cube_rotate = high_byte(cube_rotate) >= 0x80 ? 0x0000 : 0x07FF;
			}

			if (!gravity) oam_meta_spr(temp_x, high_byte(player.y)-1, SHIP[high_byte(cube_rotate)]);
			else oam_meta_spr_vflipped(temp_x, high_byte(player.y)-1, SHIP[7-high_byte(cube_rotate)]);

			break;
    }
	
	// the level sprites
	for (index = 0; index < max_loaded_sprites; ++index){
		if (activesprites_active[index] & 0x30) continue;
		temp_y = low_byte(activesprites_realy[index]);
		if (!activesprites_active[index]) continue; 
		temp_x = low_byte(activesprites_realx[index]);
		if (temp_x == 0) temp_x = 1;
		if (temp_x > 0xf0) continue;
		if (temp_y < 0xf0) {
			tmp3 = activesprites_type[index];
			oam_meta_spr(temp_x, temp_y-1, Metasprites[tmp3 & 0x0f]);
		}
	}
}