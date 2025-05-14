void mouse_and_cursor();

extern uint8_t famistudio_song_speed;
const uint8_t xbgmlookuptable[];

void dec_mouse_timer() {
	kandoframecnt++;
	if (kandoframecnt & 1 && mouse_timer) mouse_timer--;	
}		

void check_if_music_stopped() {
	#if __VS_SYSTEM
		tmp2 = (newrand() & 31) + 1;
		if (famistudio_song_speed == 0x80) { music_play(xbgmlookuptable[tmp2]); }
	#else
		if (songplaying && famistudio_song_speed == 0x80) { music_play(xbgmlookuptable[song]); }
		else if (famistudio_song_speed == 0x80) { music_play(xbgmlookuptable[menu_music]); }
	#endif
}

void loop_routine_update() {
	newrand();
	ppu_wait_nmi();
	#if __VS_SYSTEM
	check_if_music_stopped();
	#endif
	music_update();
	oam_clear();
	mouse_and_cursor();
}		
