.if .not(useConstInitPtr)
music_data_locations_lo:
	.byte <music_data_famidash_music1, <music_data_famidash_music2, <music_data_famidash_music3, <music_data_famidash_music4, <music_data_famidash_music5, <music_data_famidash_music6, <music_data_famidash_music7, <music_data_famidash_music8, <music_data_famidash_music9, <music_data_famidash_music10, <music_data_famidash_music11, <music_data_famidash_music12
music_data_locations_hi:
	.byte >music_data_famidash_music1,>music_data_famidash_music2,>music_data_famidash_music3,>music_data_famidash_music4,>music_data_famidash_music5,>music_data_famidash_music6,>music_data_famidash_music7,>music_data_famidash_music8,>music_data_famidash_music9,>music_data_famidash_music10,>music_data_famidash_music11,>music_data_famidash_music12
.endif

music_counts:
	.byte 1, 2, 2, 2, 2, 3, 3, 2, 3, 4, 5, $FF ;last bank is marked with an FF to always stop bank picking