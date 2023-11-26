void reset_level(void);

void draw_sprites(void){

	// the level sprites
	for (index = 0; index < max_loaded_sprites; ++index){
		temp_y = low_byte(activesprites_y[index]);
		if (!activesprites_active[index]) continue; 
		temp_x = activesprites_x[index];
		if (temp_x == 0) temp_x = 1;
		if (temp_x > 0xf0) continue;
		if (temp_y < 0xf0) oam_meta_spr(temp_x, temp_y, Portal_Gravity_Up);
	}

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
			cube_rotate = 0x047F - player.vel_y;

			if (!gravity) oam_meta_spr(temp_x, high_byte(player.y)-1, SHIP[high_byte(cube_rotate)]);
			else oam_meta_spr_vflipped(temp_x, high_byte(player.y)-1, SHIP[8-high_byte(cube_rotate)]);

			break;
    }




	
}