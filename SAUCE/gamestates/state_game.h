void state_game(){
	ppu_off();

	init_rld(0);
    unrle_first_screen();

	famistudio_music_play(song_stereo_madness_foreverbound);

    while (1){
        famistudio_update();

    }
}