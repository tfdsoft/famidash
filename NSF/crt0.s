; Startup code for cc65 and Shiru's NES library
; based on code by Groepaz/Hitmen <groepaz@gmx.net>, Ullrich von Bassewitz <uz@cc65.org>

;REMOVED initlib
;this called the CONDES function
; Linker generated symbols
	.import VERSION, TOTAL_SONGS, START_SONG, NTSC_RATE, PAL_RATE, REGION, SOUND_EXP, NSF2_FEATURES
	
	.import START_BANK_0, START_BANK_1, START_BANK_2, START_BANK_3, START_BANK_4, START_BANK_5, START_BANK_6, START_BANK_7
	.import FIRST_MUSIC_BANK, FIRST_DMC_BANK
	.import PRGDATASIZE

.include "zeropage.inc"




PPU_CTRL	=$2000
PPU_MASK	=$2001
PPU_STATUS	=$2002
PPU_OAM_ADDR=$2003
PPU_OAM_DATA=$2004
PPU_SCROLL	=$2005
PPU_ADDR	=$2006
PPU_DATA	=$2007
PPU_OAM_DMA	=$4014
PPU_FRAMECNT=$4017
DMC_FREQ	=$4010
CTRL_PORT1	=$4016
CTRL_PORT2	=$4017



.segment "ZEROPAGE"

NTSC_MODE: 			.res 1
FRAME_CNT1: 		.res 1
FRAME_CNT2: 		.res 1
VRAM_UPDATE: 		.res 1
; NAME_UPD_ADR: 		.res 2
NAME_UPD_ENABLE: 	.res 1
PAL_UPDATE: 		.res 1
; PAL_BG_PTR: 		.res 2
; PAL_SPR_PTR: 		.res 2
PAL_PTR:            .res 2
SCROLL_X: 			.res 1
SCROLL_Y: 			.res 1
SCROLL_X1: 			.res 1
SCROLL_Y1: 			.res 1
; PAD_STATE: 			.res 2		;one byte per controller
; PAD_STATE2: 		.res 2		;one byte per controller
; PAD_STATEP: 		.res 2
; PAD_STATEP2: 		.res 2
; PAD_STATET: 		.res 2
; PAD_STATET2: 		.res 2
PPU_CTRL_VAR: 		.res 1
PPU_CTRL_VAR1: 		.res 1
PPU_MASK_VAR: 		.res 1
RAND_SEED: 			.res 4

TEMP: 				.res 11
SPRID:				.res 1

; variables for nesdoug's metatile system
; META_PTR:			.res 2
; META_PTR2:		.res 2
; DATA_PTR:			.res 2
; META_VAR:			.res 1

xargs:				.res 4

 
;
; NES 2.0 header
;
.segment "HEADER"

	LOAD_ADDR = 0	; In case of bankswitching, indicates amount of padding
	INIT_ADDR = start
	PLAY_ADDR = music_update

	.byte 'N', 'E', 'S', 'M', $1A ; ID
	.byte <VERSION
	.byte <TOTAL_SONGS
	.byte <START_SONG
	.word .loword(LOAD_ADDR)
	.word .loword(INIT_ADDR)
	.word .loword(PLAY_ADDR)
	.asciiz "Famidash Music                 "
	.asciiz "7 Musicians at / with TFDSoft  "
	.asciiz "(c) TFDSoft 2023-2024          "
	.word .loword(NTSC_RATE)
	.byte <START_BANK_0, <START_BANK_1, <START_BANK_2, <START_BANK_3, <START_BANK_4, <START_BANK_5, <START_BANK_6, <START_BANK_7
	.word .loword(PAL_RATE)
	.byte <REGION
	.byte <SOUND_EXP
	.byte <NSF2_FEATURES
	.byte <PRGDATASIZE, >PRGDATASIZE, ^PRGDATASIZE

; .segment "STARTUP"

start:
music_update:

mmc3_tmp_prg_bank_1:
famistudio_dpcm_bank_callback:
; _exit:

	; lda PPU_STATUS
	; and #$80
	; sta <NTSC_MODE

	; jsr initialize_mapper

    ; ; jsr	zerobss	; Unnecessary, we already zeroed out the entire memory
	; jsr	copydata	; Sets all the initial values of variables

    ; lda #<(__C_STACK_START__+__C_STACK_SIZE__) ;changed
    ; sta	sp
    ; lda	#>(__C_STACK_START__+__C_STACK_SIZE__)
    ; sta	sp+1            ; Set argument stack ptr

	; ; jsr	initlib	; removed. this called the CONDES function

	; lda #%10100000
	; sta <PPU_CTRL_VAR
	; sta PPU_CTRL		;enable NMI
	; lda #%00000110
	; sta <PPU_MASK_VAR

; waitSync3:
	; lda <FRAME_CNT1
; @1:
	; cmp <FRAME_CNT1
	; beq @1

; detectNTSC:



	; jsr _ppu_off

	; ; lda #0
	; ; ldx #0
	; ; jsr _set_vram_update

	; LDA #<-1			;   Do famistudio_init
    ; JSR _music_play		;__

    ; LDA #<.bank(sounds)
    ; JSR mmc3_tmp_prg_bank_1
    
	; ldx #<sounds
	; ldy #>sounds
	; jsr famistudio_sfx_init


	
	; .include "nsfmapper.s"
	; .include "nsfdash.s"
		
.segment "DMC_BANK_00"
	.incbin "MUSIC/EXPORTS/music_bank0.dmc"
.segment "DMC_BANK_01"
	.incbin "MUSIC/EXPORTS/music_bank1.dmc"

.include "famistudio_ca65.s"
	

.segment "PCM_BANK"
GeometryDashPCMA:
	.incbin "MUSIC/PCM/geometry-dash2.pcm"
	.byte $00

.segment "PCM_BANK_B"
GeometryDashPCMB:
	.incbin "MUSIC/PCM/fire2.pcm"
	.byte $00


; Store music a switchable PRG bank
; .s files, as generated by FamiStudio through the export menu
.segment "MUS_BANK_00"
	.include "MUSIC/EXPORTS/music_1.s"
.segment "MUS_BANK_01"
	.include "MUSIC/EXPORTS/music_2.s"
.segment "MUS_BANK_02"
	.include "MUSIC/EXPORTS/music_3.s"
.segment "MUS_BANK_03"
	.include "MUSIC/EXPORTS/music_4.s"
.segment "MUS_BANK_04"
	.include "MUSIC/EXPORTS/music_5.s"

.segment "SFX_BANK"
	.include "MUSIC/EXPORTS/sfx.s"
