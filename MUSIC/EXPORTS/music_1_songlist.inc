song_dpcm = 0
song_menu_theme = 1
song_practice = 2
song_max = 3

.if SONG_STRINGS
song_strings:
.asciiz "dpcm"
.asciiz "Menu Theme"
.asciiz "Practice"
.endif
