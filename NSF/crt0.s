; Startup code for cc65 and Shiru's NES library
; based on code by Groepaz/Hitmen <groepaz@gmx.net>, Ullrich von Bassewitz <uz@cc65.org>
.include "LIB/asm/crt0.s"


; Linker generated symbols
	.import VERSION, TOTAL_SONGS, START_SONG, NTSC_RATE, PAL_RATE, SOUND_EXP, NSF2_FEATURES
	
	.import START_BANK_0, START_BANK_1, START_BANK_2, START_BANK_3, START_BANK_4, START_BANK_5, START_BANK_6, START_BANK_7
	.import FIRST_MUSIC_BANK, FIRST_DMC_BANK
	.import PRGDATASIZE


; .include "zeropage.inc"
; .include "music_songlist.inc"
; .include "sfx_sfxlist.inc"

REGION := 1

;
; NSF2 header
;
.segment "NSF_HEADER"

	LOAD_ADDR = $8000	; In case of bankswitching, indicates amount of padding from the start of the ROM
	INIT_ADDR = init
	PLAY_ADDR = play

	.byte 'N', 'E', 'S', 'M', $1A ; ID
	.byte <VERSION
	.byte <TOTAL_SONGS
	.byte <START_SONG
	.word .loword(LOAD_ADDR)
	.word .loword(INIT_ADDR)
	.word .loword(PLAY_ADDR)
	.asciiz "Famidash"
	.repeat 31 - 8
		.byte $00
	.endrepeat
	.asciiz "OG by 9 ppl, covers by 7 ppl"
	.repeat 31 - 28
		.byte $00
	.endrepeat
	.byte "TFDSoft 23-24,GD producers 08-14"
	.word .loword(NTSC_RATE)
	.byte <START_BANK_0, <START_BANK_1, <START_BANK_2, <START_BANK_3, <START_BANK_4, <START_BANK_5, <START_BANK_6, <START_BANK_7
	.word .loword(PAL_RATE)
	.byte <REGION
	.byte <SOUND_EXP
	.byte <NSF2_FEATURES
	.byte <PRGDATASIZE, >PRGDATASIZE, ^PRGDATASIZE

; .importzp NTSC_MODE
; .import current_song_bank

PLAYBACK_MODE = tmp1
sampleID = tmp2

; routines
; .import famistudio_init, famistudio_sfx_init, famistudio_sfx_play
; .import sounds
; .import _music_play, _music_update, _playPCM
; .import mmc3_set_prg_bank_0, mmc3_tmp_prg_bank_1, _mmc3_pop_prg_bank_1

.segment "NSF_CODE"

init:
	; lda PPU_STATUS
	; and #$80
	; sta <NTSC_MODE
	dex
	stx <NTSC_MODE
	
	cmp #(song_max+sfx_max)
	bcs pcm_init
	
	ldy #0
	sty PLAYBACK_MODE
	
	cmp #song_max
	bcs sfx_init
	tax
	lda song_tbl, X
    JMP _music_play	

song_tbl:
.byte song_menu_theme, song_stereo_madness, song_back_on_track, song_polargeist
.byte song_dry_out, song_base_after_base, song_cant_let_go, song_jumper
.byte song_time_machine, song_cycles, song_xstep, song_clutterfunk
.byte song_theory_of_everything, song_electroman_adventures, song_custom_endgame, song_practice

sfx_init:
	; The carry is set
	SBC #song_max
	pha
	JSR famistudio_init_for_sfx
	
    LDA #<.bank(sounds)
    JSR mmc3_tmp_prg_bank_1
    
	ldx #<sounds
	ldy #>sounds
	JSR famistudio_sfx_init
	
	PLA
	LDX #0
	JMP famistudio_sfx_play

pcm_init:
	; The carry is set
	sbc #(song_max+sfx_max)
	sta sampleID
	lda #$80
	sta PLAYBACK_MODE
play_return:
	rts

play:
	BIT PLAYBACK_MODE
	bvs play_return
	bmi pcm_play
	jmp _music_update
pcm_play:
	lda #<.bank(_playPCM)
	jsr	mmc3_set_prg_bank_1
	LDA sampleID
	DEC PLAYBACK_MODE
	JMP _playPCM

.proc famistudio_init_for_sfx
	; CONFIGURATION:
	; If the following value is set and valid, it will be used
	; as the pointer to famistudio_init in all banks. If it
	; isn't, then music_pointers_lo, hi and song count tables
	; are needed for proper operation.
	constInitPtr = $A000

	.ifndef constInitPtr
		constInitPtr = 0
	.endif
	useConstInitPtr = (constInitPtr >= $6000)
	
	
	LDA #<FIRST_MUSIC_BANK
	JSR mmc3_tmp_prg_bank_1
	
	.if useConstInitPtr
		LDX #<constInitPtr
		LDY #>constInitPtr
	.else
		LDX #<music_data_famidash_music1
		LDY #>music_data_famidash_music1
	.endif
	LDA NTSC_MODE
	JSR famistudio_init
	
	JMP _mmc3_pop_prg_bank_1
.endproc
	
.include "nsfmapper.s"

.segment "METADATA"
	.include "metadata.s"
