; Startup code for cc65 and Shiru's NES library
; based on code by Groepaz/Hitmen <groepaz@gmx.net>, Ullrich von Bassewitz <uz@cc65.org>

;REMOVED initlib
;this called the CONDES function
.include "BUILD_FLAGS.s"
.include "C_defines.s"

.exportzp _VRAM_UPDATE := VRAM_UPDATE

    .export _exit,__STARTUP__:absolute=1
	.export _PAL_BUF := PAL_BUF, _PAL_UPDATE := PAL_UPDATE, _xargs := xargs
	.export _PAL_BUF_RAW := PAL_BUF_RAW, _PAL_PTR := PAL_PTR
	.import push0,popa,popax,_main

; Linker generated symbols
	.import __C_STACK_START__, __C_STACK_SIZE__
	.import __PAL_BUF_START__, __OAM_BUF_START__, __VRAM_BUF_START__
	.import	__CODE_LOAD__   ,__CODE_RUN__   ,__CODE_SIZE__
	.import	__RODATA_LOAD__ ,__RODATA_RUN__ ,__RODATA_SIZE__

	.import MAPPER, SUBMAPPER, MIRRORING, PRG_BANK_COUNT, CHR_BANK_COUNT, SRAM, TRAINER, CONSOLE_TYPE, PRG_RAM_COUNT, PRG_NVRAM_COUNT, CHR_RAM_COUNT, CHR_NVRAM_COUNT, CPU_PPU_TIMING, HARDWARE_TYPE, MISC_ROMS, DEF_EXP_DEVICE
	.import FIRST_MUSIC_BANK, FIRST_DMC_BANK, _SRAM_VALIDATE

VRAM_BUF=__VRAM_BUF_START__
OAM_BUF=__OAM_BUF_START__
PAL_BUF_RAW=__PAL_BUF_START__
PAL_BUF=PAL_BUF_RAW+$20

SFX_STRINGS = 0

; .importzp _PAD_STATE, _PAD_STATET ;added
.include "zeropage.inc"

.include "music_songlist.inc"
.include "sfx_sfxlist.inc"



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
PAD_STATE: 			.res 2		;one byte per controller
PAD_STATE2: 		.res 2		;one byte per controller
PAD_STATEP: 		.res 2
PAD_STATEP2: 		.res 2
PAD_STATET: 		.res 2
PAD_STATET2: 		.res 2
PPU_CTRL_VAR: 		.res 1
PPU_CTRL_VAR1: 		.res 1
PPU_MASK_VAR: 		.res 1
RAND_SEED: 			.res 4

TEMP: 				.res 11
SPRID:				.res 1

PAD_BUF		=TEMP+1

PTR			=TEMP	;word
LEN			=TEMP+2	;word
NEXTSPR		=TEMP+4
SCRX		=TEMP+5
SCRY		=TEMP+6
SRC			=TEMP+7	;word
DST			=TEMP+9	;word

SP_TEMP     =TEMP+7
CHRBANK_TEMP=TEMP+8

RLE_LOW		=TEMP
RLE_HIGH	=TEMP+1
RLE_TAG		=TEMP+2
RLE_BYTE	=TEMP+3

VRAM_INDEX:			.res 1
; variables for nesdoug's metatile system
; META_PTR:			.res 2
; META_PTR2:		.res 2
; DATA_PTR:			.res 2
; META_VAR:			.res 1

xargs:				.res 4
noMouse:			.res 1

 
;
; NES 2.0 header
;
.segment "HEADER"

    NES2_0_IDENTIFIER = %00001000

    .byte 'N', 'E', 'S', $1A ; ID
    .byte <PRG_BANK_COUNT
    .byte <CHR_BANK_COUNT
    .byte <(MIRRORING | (SRAM << 1) | (TRAINER << 2) | ((MAPPER & $00F) << 4))
    .byte <((MAPPER & $0F0) | CONSOLE_TYPE | NES2_0_IDENTIFIER)
    .byte <(((MAPPER & $F00) >> 8) | SUBMAPPER << 4)
    .byte <(((PRG_BANK_COUNT & $F00) >> 8) | ((CHR_BANK_COUNT & $F00) >> 4))
    .byte <(PRG_RAM_COUNT | (PRG_NVRAM_COUNT << 4))
    .byte <(CHR_RAM_COUNT | (CHR_NVRAM_COUNT << 4))
    .byte <CPU_PPU_TIMING, <HARDWARE_TYPE, <MISC_ROMS, <DEF_EXP_DEVICE

.segment "STARTUP"

start:
_exit:
	lda #%10000000					;	Stolen from initialize_mapper
	sta MMC3_REG_PRG_RAM_PROTECT	;__
    lda $00
    sta $7FFE
    lda $01
    sta $7FFF


    sei
	cld
	ldx #$40
	stx CTRL_PORT2
    ldx #$ff
    txs
    inx
    stx PPU_MASK
    stx DMC_FREQ
    stx PPU_CTRL		;no NMI

initPPU:
    bit PPU_STATUS
@1:
    bit PPU_STATUS
    bpl @1
@2:
    bit PPU_STATUS
    bpl @2

clearPalette:
	lda #$3f
	sta PPU_ADDR
	stx PPU_ADDR
	lda #$0f
	ldx #$20
@1:
	sta PPU_DATA
	dex
	bne @1

clearVRAM:
	txa
	ldy #$20
	sty PPU_ADDR
	sta PPU_ADDR
	ldy #$10
@1:
	sta PPU_DATA
	inx
	bne @1
	dey
	bne @1

	lda $FC
	bne @cont1
@fallback1:
	lda #$FD
@cont1:
	sta aart_lz_buffer
	lda $FD
	bne @cont2
@fallback2:
	lda #$FD
@cont2:
	sta aart_lz_buffer+1
	lda $FE
	bne @cont3
@fallback3:
	lda #$FD
@cont3:
	sta aart_lz_buffer+2
	lda $FF
    bne @cont4
@fallback4:
	lda #$FD
@cont4:
	sta aart_lz_buffer+3

clearRAM:
    txa
@1:
    sta $00,x   ;
    sta $0100,x ;
    sta $0200,x ;
    sta $0300,x ;   Clear regular NES RAM
    sta $0400,x ;
    sta $0500,x ;
    sta $0600,x ;
    sta $0700,x ;__
	sta $6000,x ;
	sta $6100,x ;   Clear the collision map space
    sta $6200,x ;
	sta $6300,x ;__
    inx
    bne @1


	lda aart_lz_buffer
	sta RAND_SEED
	lda aart_lz_buffer+1
	sta RAND_SEED+1
	lda aart_lz_buffer+2
	sta RAND_SEED+2
	lda aart_lz_buffer+3
	sta RAND_SEED+3

	lda #4
	jsr _pal_bright
	jsr _pal_clear
	jsr _oam_clear

	jsr initialize_mapper

    ; jsr	zerobss	; Unnecessary, we already zeroed out the entire memory
	jsr	copydata	; Sets all the initial values of variables

    lda #<(__C_STACK_START__+__C_STACK_SIZE__) ;changed
    sta	sp
    lda	#>(__C_STACK_START__+__C_STACK_SIZE__)
    sta	sp+1            ; Set argument stack ptr

	; jsr	initlib	; removed. this called the CONDES function

	lda #%10100000
	sta <PPU_CTRL_VAR
	sta PPU_CTRL		;enable NMI
	lda #%00000110
	sta <PPU_MASK_VAR

waitSync3:
	lda <FRAME_CNT1
@1:
	cmp <FRAME_CNT1
	beq @1

detectNTSC:
	ldx #52				;blargg's code
	ldy #24
@1:
	dex
	bne @1
	dey
	bne @1

	lda PPU_STATUS
	and #$80
	sta <NTSC_MODE

	jsr _ppu_off

	; lda #0
	; ldx #0
	; jsr _set_vram_update

	LDA #<-1			;   Do famistudio_init
    JSR _music_play		;__

    LDA #<.bank(sounds)
    JSR mmc3_tmp_prg_bank_1
    
	ldx #<sounds
	ldy #>sounds
	jsr famistudio_sfx_init

	lda #0
	sta PPU_SCROLL
	sta PPU_SCROLL

    cli

	jmp _main			;no parameters

	.include "METATILES/metatiles.s"

	.include "LEVELS/all_level_data.s"
	.include "LEVELS/all_sprite_data.s"
	.include "LEVELS/level_header.s"
	.include "LEVELS/all_level_table.s"
	
	.include "mapper.s"
	.include "neslib.s"
	.include "nesdash.s"
	.include "nesdoug.s"
	.include "lz.s"
    
.segment "DMC_BANK_00"
	.incbin "MUSIC/EXPORTS/music_bank0.dmc"
.segment "DMC_BANK_01"
	.incbin "MUSIC/EXPORTS/music_bank1.dmc"
.segment "DMC_BANK_02"
	.incbin "MUSIC/EXPORTS/music_bank2.dmc"
.segment "DMC_BANK_03"
	.incbin "MUSIC/EXPORTS/music_bank3.dmc"
.segment "DMC_BANK_04"
	.incbin "MUSIC/EXPORTS/music_bank4.dmc"
.segment "DMC_BANK_05"
	.incbin "MUSIC/EXPORTS/music_bank5.dmc"
.segment "DMC_BANK_06"
	.incbin "MUSIC/EXPORTS/music_bank6.dmc"
.segment "DMC_BANK_07"
	.incbin "MUSIC/EXPORTS/music_bank7.dmc"
.segment "DMC_BANK_08"
	.incbin "MUSIC/EXPORTS/music_bank8.dmc"
.segment "DMC_BANK_09"
;	.incbin "MUSIC/EXPORTS/music_bank9.dmc"
.segment "DMC_BANK_0A"
;	.incbin "MUSIC/EXPORTS/music_bankA.dmc"
.segment "DMC_BANK_0B"
;	.incbin "MUSIC/EXPORTS/music_bankB.dmc"

CURSED_MUSIC_ENABLE = 1
.segment "BSS"
.export _famistudio_state
_famistudio_state = *
.include "famistudio_ca65.s"

	


; Store music in switchable PRG banks
; .s files, as generated by export.py
.segment "MUS_BANK_00"
	.include "MUSIC/EXPORTS/music_0.s"
.segment "MUS_BANK_01"
	.include "MUSIC/EXPORTS/music_1.s"
.segment "MUS_BANK_02"
	.include "MUSIC/EXPORTS/music_2.s"
.segment "MUS_BANK_03"
	.include "MUSIC/EXPORTS/music_3.s"
.segment "MUS_BANK_04"
	.include "MUSIC/EXPORTS/music_4.s"
.segment "MUS_BANK_05"
	.include "MUSIC/EXPORTS/music_5.s"
.segment "MUS_BANK_06"
	.include "MUSIC/EXPORTS/music_6.s"
.segment "MUS_BANK_07"
	.include "MUSIC/EXPORTS/music_7.s"
.segment "MUS_BANK_08"
	.include "MUSIC/EXPORTS/music_8.s"
.segment "MUS_BANK_09"
	.include "MUSIC/EXPORTS/music_9.s"
.segment "MUS_BANK_0A"
	.include "MUSIC/EXPORTS/music_10.s"
.segment "MUS_BANK_0B"
	.include "MUSIC/EXPORTS/music_11.s"
.segment "MUS_BANK_0C"
	.include "MUSIC/EXPORTS/music_12.s"
.segment "MUS_BANK_0D"
	.include "MUSIC/EXPORTS/music_13.s"
.segment "MUS_BANK_0E"
	.include "MUSIC/EXPORTS/music_14.s"
.segment "MUS_BANK_0F"
	.include "MUSIC/EXPORTS/music_15.s"
.segment "MUS_BANK_10"
	.include "MUSIC/EXPORTS/music_16.s"
.segment "MUS_BANK_11"
	.include "MUSIC/EXPORTS/music_17.s"
.segment "MUS_BANK_12"
	.include "MUSIC/EXPORTS/music_18.s"
.segment "MUS_BANK_13"
	.include "MUSIC/EXPORTS/music_19.s"
.segment "MUS_BANK_14"
	.include "MUSIC/EXPORTS/music_20.s"
.segment "MUS_BANK_15"
	.include "MUSIC/EXPORTS/music_21.s"
.segment "MUS_BANK_16"
	.include "MUSIC/EXPORTS/music_22.s"
.segment "MUS_BANK_17"
	.include "MUSIC/EXPORTS/music_23.s"
.segment "MUS_BANK_18"
	.include "MUSIC/EXPORTS/music_24.s"
.segment "MUS_BANK_19"
	.include "MUSIC/EXPORTS/music_25.s"
.segment "MUS_BANK_1A"
	.include "MUSIC/EXPORTS/music_26.s"
.segment "MUS_BANK_1B"
	.include "MUSIC/EXPORTS/music_27.s"
.segment "MUS_BANK_1C"
	.include "MUSIC/EXPORTS/music_28.s"
.segment "MUS_BANK_1D"
	.include "MUSIC/EXPORTS/music_29.s"
.segment "MUS_BANK_1E"
	.include "MUSIC/EXPORTS/music_30.s"
.segment "MUS_BANK_1F"
	.include "MUSIC/EXPORTS/music_31.s"
.segment "MUS_BANK_20"
;	.include "MUSIC/EXPORTS/music_32.s"
.segment "MUS_BANK_21"
;	.include "MUSIC/EXPORTS/music_33.s"
.segment "MUS_BANK_22"
;	.include "MUSIC/EXPORTS/music_34.s"
.segment "MUS_BANK_23"
;	.include "MUSIC/EXPORTS/music_35.s"
.segment "MUS_BANK_24"
;	.include "MUSIC/EXPORTS/music_36.s"
.segment "MUS_BANK_25"
;	.include "MUSIC/EXPORTS/music_37.s"
.segment "MUS_BANK_26"
;	.include "MUSIC/EXPORTS/music_38.s"
.segment "MUS_BANK_27"
;	.include "MUSIC/EXPORTS/music_39.s"
.segment "MUS_BANK_28"
;	.include "MUSIC/EXPORTS/music_40.s"

.segment "SFX_BANK"
	.include "MUSIC/EXPORTS/sfx.s"

.segment "COLLMAP0"
	collMap0:		.res 16*15
.segment "COLLMAP1"
	collMap1:		.res 16*15
.segment "COLLMAP2"
    collMap2:       .res 16*15
.segment "COLLMAP3"
    collMap3:       .res 16*12
	ground:			.res 16*3

.segment "SRAM"
	.align 256
	aart_lz_buffer:	.res 512

.segment "VECTORS"

    .word nmi	;$fffa vblank nmi
    .word start	;$fffc reset
   	.word irq	;$fffe irq / brk



.segment "GAMECHR"
.export _GAME_CHR
_GAME_CHR:
 ;   .incbin "GRAPHICS/famidash.chr" ; 8kb		//default (0)
 ;   .incbin "GRAPHICS/famidash-parallax.chr" ; 4kb	//default (8)
 ;   .incbin "GRAPHICS/famidash2.chr" ; 8kb		//theory of everything (12)
 ;   .incbin "GRAPHICS/famidash-parallax2.chr" ; 4kb	//theory of everything (20)
   
    .incbin "GRAPHICS/Level Tiles/SpikesA.chr" ; (0)
    .incbin "GRAPHICS/Level Tiles/SpikesB.chr" ; (2)
    .incbin "GRAPHICS/Level Tiles/SpikesC.chr" ; (4)
    .incbin "GRAPHICS/Level Tiles/BlocksA.chr" ; (6)
    .incbin "GRAPHICS/Level Tiles/BlocksB.chr" ; (8)
    .incbin "GRAPHICS/Level Tiles/BlocksC.chr" ; (10)
    .incbin "GRAPHICS/Level Tiles/BlocksD.chr" ; (12)
    .incbin "GRAPHICS/Level Tiles/SawbladesA.chr" ; (14)
    .incbin "GRAPHICS/Level Tiles/slopesA.chr" ; (16)

    .incbin "GRAPHICS/Gamemode/so_retro_v2.chr" ; 1kb (18) 
    .incbin "GRAPHICS/Level Sprites/bankportals.chr" ; 1kb

    .incbin "GRAPHICS/Gamemode/bankgamemodesA.chr" ; 1kb (20)
    .incbin "GRAPHICS/Level Sprites/bankportals.chr" ; 1kb
    .incbin "GRAPHICS/Gamemode/bankgamemodesAretro.chr" ; 1kb (22)
    .incbin "GRAPHICS/Level Sprites/bankportals.chr" ; 1kb
    .incbin "GRAPHICS/Gamemode/bankgamemodesB.chr" ; 1kb (24)
    .incbin "GRAPHICS/Level Sprites/bankportals.chr" ; 1kb
    .incbin "GRAPHICS/Gamemode/bankgamemodesBretro.chr" ; 1kb (26)
    .incbin "GRAPHICS/Level Sprites/bankportals.chr" ; 1kb

    .incbin "GRAPHICS/Level Sprites/bankmain.chr" ; 1kb (28) 
    .incbin "GRAPHICS/Level Sprites/bankblank.chr" ; 1kb
    .incbin "GRAPHICS/Level Sprites/bankmain.chr" ; 1kb (30) 
    .incbin "GRAPHICS/Level Sprites/bankblank2.chr" ; 1kb

    .incbin "GRAPHICS/Level Sprites/bankmain.chr" ; 1kb (32) 
    .incbin "GRAPHICS/Level Sprites/bankblankcloud.chr" ; 1kb
    .incbin "GRAPHICS/Level Sprites/bankmain.chr" ; 1kb (34) 
    .incbin "GRAPHICS/Level Sprites/bankblankcloud2.chr" ; 1kb

    .incbin "GRAPHICS/Level Sprites/bankmain.chr" ; 1kb (36) 
    .incbin "GRAPHICS/Level Sprites/bankblankfingerdash.chr" ; 1kb
    .incbin "GRAPHICS/Level Sprites/bankmain.chr" ; 1kb (38) 
    .incbin "GRAPHICS/Level Sprites/bankblankfingerdash2.chr" ; 1kb

    .repeat 15, I   ; banks 40 - 69
        .incbin .sprintf("GRAPHICS/Icons/bankicon%02X.chr", I)  ; 1kb
        .incbin "GRAPHICS/Level Sprites/bankportals.chr" ; 1kb
    .endrepeat

    .repeat 11, I   ; banks 70 - 91
        .incbin .sprintf("fan icon collection/CONTEST WINNERS/contest%1X.chr", I+1) ; 1kb
        .incbin "GRAPHICS/Level Sprites/bankportals.chr" ; 1kb
    .endrepeat

        .incbin "fan icon collection/starfox.chr" ; 1kb (92)
        .incbin "GRAPHICS/Level Sprites/bankportals.chr" ; 1kb

    .incbin "GRAPHICS/Gamemode/banktriangle.chr" ; 1kb (94)
    .incbin "GRAPHICS/Level Sprites/bankportals.chr" ; 1kb
    
    .incbin "GRAPHICS/Menus/cursors.chr" ; 2kb (96)

    .incbin "GRAPHICS/Menus/menus.chr"    ; 4kb (98)
    .incbin "GRAPHICS/Menus/menuicons.chr"    ; 4kb (102)
    .incbin "GRAPHICS/Menus/levelcomplete.chr"    ; 4kb (106)
    .incbin "GRAPHICS/Menus/practicecomplete.chr"    ; 1kb (110)
   .incbin "GRAPHICS/Level Tiles/SawbladesNone.chr" ; 1kb (111)

 ;   .incbin "GRAPHICS/Menus/practicecomplete.chr"    ; 1kb (112)

.segment "PARALLAXCHR"  ; banks 112 - 255
.export _PARALLAX_CHR
_PARALLAX_CHR:
	.incbin "GRAPHICS/parallax.chr" ; 144kb
