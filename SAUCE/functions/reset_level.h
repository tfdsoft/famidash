void reset_level(void) {

	famistudio_music_stop();
	famistudio_sfx_play(sfx_death, 0);

	
	tmp1 = 0;
	while (tmp1 < 60){
		ppu_wait_nmi();
		famistudio_update();
		++tmp1;
		gray_line();
	}

	ppu_off(); // reset the level when you get to this point, and change this later
	scroll_x = 0;
    scroll_y = 0xEF;
    init_rld(level);
	unrle_first_screen();
	player.x = 0x0000;
	player.y = 0xb000;
	gravity = 0x00;
	gamemode = 0x01;
	player.vel_x = 0;
    player.vel_y = 0;
	cube_data = 0;
	ppu_on_all();
	famistudio_music_play(level);

}