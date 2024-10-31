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

REGION = 0

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
	.asciiz "(c) TFDSoft 2023-2024"
	.repeat 31 - 21
		.byte $00
	.endrepeat
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

.byte "NSF:init"

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
    JMP _music_play	

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

.byte "NSF:play"

play:
	BIT PLAYBACK_MODE
	bvs play_return
	bmi pcm_play
	jmp _music_update
pcm_play:
	LDA sampleID
	DEC PLAYBACK_MODE
	JMP _playPCM
	
.byte "NSF:fs_init_sfx"

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
