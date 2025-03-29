; Custom routines implemented specifically for famidash (some are totally not stolen from famitower)
.importzp _gamemode
.importzp _tmp1, _tmp2, _tmp3, _tmp4, _tmp5, _tmp6, _tmp7, _tmp8, _tmp9, _temptemp5  ; C-safe temp storage
.import pusha, pushax, callptr4
.import _scroll_x, _cursedmusic

.if VS_SYSTEM
	.import _draw_arrow
.endif

.macpack longbranch

.importzp _sprite_data
sprite_data = _sprite_data

.define gamemode_count 9

.macro INCW addr
	INC addr
	BNE :+
		INC addr+1
:
.endmacro

.macro incw addr
	INCW addr
.endmacro

; You get your arguments back in ptr3
.macro crossPRGBankJSR inArgCount, routine, bank
	.ifblank routine
		.error "Have to supply routine and argument count for crossPRGBankJSR"
	.endif

	.ifnblank bank
		LDY bank
	.else
		LDY #.bank(routine)
	.endif

	.ifnblank inArgCount
		.if inArgCount >= 2
			STX ptr3+1
		.endif
		.if inArgCount >= 1
			STA ptr3
		.endif
	.endif

	LDA #<routine
	LDX #>routine
	jsr crossPRGBankJump
.endmacro


.segment "ZEROPAGE"
	rld_value:      	.res 1
	rld_run:        	.res 1

.segment "BSS"
	; column buffer, to be pushed to the collision map
	; 15 metatiles in the top 3 screens 
	; 12 metatiles in the bottom screen
	; 3 metatiles in the ground
	columnBuffer:		.res 15 + 15 + 15 + 12 + 3

	; variables related to the vertical seam / level height
	extceil:			.res 1
	rld_load_value:		.res 1
	min_scroll_y:		.res 2

	; variables related to both the above and below
	old_draw_scroll_y:	.res 2
	seam_scroll_y:		.res 2
	
	; variables related to draw_screen
	rld_column:			.res 1
	drawing_frame:		.res 1
	parallax_scroll_column: .res 1
	parallax_scroll_column_start: .res 1

	current_song_bank:	.res 1
	auto_fs_updates:	.res 1

	hexToDecOutputBuffer: .res 5
 

.export _extceil := extceil
.export _min_scroll_y := min_scroll_y
.export	_seam_scroll_y := seam_scroll_y
.export _old_draw_scroll_y := old_draw_scroll_y

.export _drawing_frame := drawing_frame
.export _parallax_scroll_column := parallax_scroll_column
.export _parallax_scroll_column_start := parallax_scroll_column_start

.export _auto_fs_updates := auto_fs_updates
.export _hexToDecOutputBuffer := hexToDecOutputBuffer

; .export _pad = PAD_STATEP
; .export _pad_new = PAD_STATET

; Standard for function declaration here:
; C function name
; .segment declaration
; [ <empty line>
; imports ]
; <empty line>
; .export declaration
; the function itself

; void __fastcall__ oam_meta_spr_flipped(uint8_t x,uint8_t y,const void *data);
.segment "XCD_BANK_05"

.export __oam_meta_spr_flipped
.proc __oam_meta_spr_flipped
	; AX = data
	; sreg[0] = x
	; sreg[1] = y
	; xargs[0] = flip
	sta <PTR
	stx <PTR+1

	ldx SPRID
	ldy #0

loop:

	lda (PTR),y     ;x offset
	cmp #$80
	beq end
	iny
	clc
	BIT xargs+0 ;	Check for bit 6 (HFLIP)
	BVC :+		;__
	EOR #$FF	;	If HLIPd, then two's complement
	ADC #($100 - 8)	; Carry is clear
	SEC			;__
	:			;
	adc sreg+0
	sta OAM_BUF+3,x
	lda (PTR),y     ;y offset
	INY
	clc
	BIT xargs+0	;	Check for bit 7 (VFLIP)
	BPL :+		;__
	EOR #$FF	;   If VLIPd, then two's complement
	; ADC #($100 - 16)	; Carry is clear, Y is -16'd because of us using 8x16 mode
	SEC			;__
	:			;
	adc sreg+1
	sta OAM_BUF+0,x
	lda (PTR),y     ;tile
	iny
	sta OAM_BUF+1,x
	lda (PTR),y     ;attribute
	iny
	EOR xargs+0
	sta OAM_BUF+2,x
	.if USE_ILLEGAL_OPCODES
		txa			;	aka X += 4
		axs #<-4	;__
	.else
		inx
		inx
		inx
		inx
	.endif
	jmp loop

end:

	stx SPRID
	rts
.endproc

.segment "RODATA"

.export _shiftBy4table := shiftBy4table
shiftBy4table:
	.byte $00, $10, $20, $30
	.byte $40, $50, $60, $70
	.byte $80, $90, $A0, $B0
	.byte $C0, $D0, $E0, $F0

.segment "CODE"

.export __one_vram_buffer_repeat
.proc __one_vram_buffer_repeat
	; ax = ppu_address
	; sreg[0] = data
	; sreg[1] = len
	ldy VRAM_INDEX
	sta VRAM_BUF+1, y
	txa
	sta VRAM_BUF+0, y
	; ptr1 lo byte is len, hi byte is character to repeat
	lda sreg+1
	ora #$80 ; set length + repeat byte
	sta VRAM_BUF+2, y
	lda sreg+0
	sta VRAM_BUF+3, y
	lda #$ff ;=NT_UPD_EOF
	sta VRAM_BUF+4, y
	tya
	clc
	adc #4
	sta VRAM_INDEX
	rts
.endproc

; void __fastcall__ init_rld(uint8_t level);
.segment "CODE_2"

.global _level_list_lo, _level_list_hi, _level_list_bank, _sprite_list_lo, _sprite_list_hi, _sprite_list_bank
.import _song, _speed, _lastgcolortype, _lastbgcolortype
.import _level_data_bank, _sprite_data_bank
.import _discomode

.export _init_rld
_init_rld:
	; A - the level ID

	; Get pointers:
	TAY						;__ Load pointer to tables
	LDA _sprite_list_lo,y	;
	STA _sprite_data+0		;__	Get low pointer to sprite data 
	LDA _sprite_list_hi,y	;
	STA _sprite_data+1		;__	Get high pointer to sprite data 
	LDA _sprite_list_bank,y	;
	STA _sprite_data_bank	;__	Get sprite data bank
	LDA _level_list_lo,y	;
	STA	ptr1+0				;__	Get low pointer to level data
	LDA _level_list_hi,y	;
	STA	ptr1+1				;__	Get high pointer to level data 
	LDA _level_list_bank,y	;
	STA _level_data_bank	;__	Get level data bank
	
	JSR mmc3_set_prg_bank_1

	LDY #$00			;-  For both (zp),y addressing and rld_column
	STY rld_column		;__ Reset scrolling

	; Read header
	LDA (ptr1),y		;
	STA _song			;   Song number
	INCW ptr1			;__

	LDA (ptr1),y		;
	STA _gamemode		;   Starting level number
	INCW ptr1			;__

	LDA (ptr1),y		;
	STA _speed			;   Starting speed
	INCW ptr1			;__

	LDA (ptr1),y		;	Starting BG color
;	AND #$3F			;	Store normal color (pal_col(0, tmp2))
	STA _no_parallax		;__
	INCW ptr1			;__

;	LDA _discomode
;	BNE @noset
	LDA (ptr1),y	;	Starting BG color
	AND #$3F			;	Store normal color (pal_col(0, tmp2))
	STA PAL_BUF_RAW+0		;__
	ldx _lastbgcolortype
	cpx #$ff
	bne @noset
	STA _lastbgcolortype
@noset:
	TAX
;	lda _discomode
;	bne @nostore
	LDA palBrightTable3, X
	STA PAL_BUF_RAW+1		;__	Store faded color (pal_col(1, oneShadeDarker(tmp2))
	STA PAL_BUF_RAW+9		;__	Store faded color (pal_col(1, oneShadeDarker(tmp2))
@nostore:
	txa
	incw ptr1

	LDA (ptr1),y	;	Starting ground color
	AND #$3F			;	Store normal color (pal_col(6, tmp2))
	STA PAL_BUF_RAW+6		;__
	ldx _lastgcolortype
	cpx #$ff
	bne @noset2
	STA	_lastgcolortype
@noset2:
	TAX
	LDA palBrightTable3, X
	STA PAL_BUF_RAW+5		;__	Store faded color (pal_col(5, oneShadeDarker(tmp2)))
	INC <PAL_UPDATE		;__ Yes, we do need to update the palette

	; Copy all the raw colors into the buffer for the current brightness
	ldy PAL_BUF_RAW+0
	lda (PAL_PTR),y
	sta PAL_BUF+0
	ldy PAL_BUF_RAW+1
	lda (PAL_PTR),y
	sta PAL_BUF+1
	ldy PAL_BUF_RAW+5
	lda (PAL_PTR),y
	sta PAL_BUF+5
	ldy PAL_BUF_RAW+6
	lda (PAL_PTR),y
	sta PAL_BUF+6
	ldy PAL_BUF_RAW+9
	lda (PAL_PTR),y
	sta PAL_BUF+9
	


	
	ldy #0
	incw ptr1

	.if USE_ILLEGAL_OPCODES
		lax (ptr1),y
	.else
		LDA	(ptr1),y
		TAX
	.endif
	EOR #$FF			;
	CLC					;	Level height
	ADC #$01			;
	STA rld_load_value	;__

	LDA	#$01			;- (to automatically shift out 1)
	CPX	#27+1			;	Extceil flag
	ROR					;
	STA	extceil			;__

	@min_scroll_y_calc:
		LDA	#$00			;
		STA	min_scroll_y+1	;__
		
		TXA						;
		EOR	#$FF				;	Get 57 - level height
		; SEC done by LDA #$01	;	aka the highest row
		ADC #<(1+57-1)			;__
		SEC
	@min_scroll_y_loop:
		SBC	#15				;__
		BCC	@min_scroll_y_fin
		INC	min_scroll_y+1
		TAX
		BCS	@min_scroll_y_loop	; = BRA
	@min_scroll_y_fin:
		LDA	shiftBy4table, X
		ORA #$08
		STA min_scroll_y

	incw ptr1

SetupNextRLEByte:
	ldx	ptr1+0		;	LZ data ptr
	ldy	ptr1+1		;__

	jsr	LZ_init_decomp

    jsr	LZ_get_byte		;
	cmp	#$00			;
    bmi single_rle_byte	;	Load rld_run
    STA rld_run			;__ 

    jsr	LZ_get_byte		;
    STA rld_value		;__	Load rld_value
	RTS
single_rle_byte:
	and #$7f
	sta rld_value
	lda #0
	sta rld_run
	rts

; void unrle_next_column();
.segment "CODE_2"

.export _unrle_next_column
.proc _unrle_next_column

	col_idx = tmp1

	; Count up to zero to remove a cmp instruction
	ldx rld_load_value
	lda rld_value

	@FirstLoop:
		sta columnBuffer - ($100 - (15 + 15 + 15 + 12)), x
		dec rld_run
		bmi @UpdateValueRun
		inx 
		bmi @FirstLoop
		bpl @End ; Guaranteed jump
	
	@UpdateValueRun:
		stx	col_idx

	@ReadNewVal:
		; if bit 7 of the byte is set, then its a run of length 1
		; otherwise this is a length < 127 byte and we need to read another
		jsr	LZ_get_byte			;
		cmp	#$00				;
		bmi @SingleByteRun		;	Load rld_run
		sta rld_run				;__

		jsr	LZ_get_byte			;
		cmp	rld_run				;	Load rld_value
		beq	@ParseMetaSeq		;	or meta sequence
	@noMetaSeq:					;
		sta rld_value			;__
	
		ldx	col_idx
		inx 
		bmi @FirstLoop
		bpl @End ; Unconditional

	@ParseMetaSeq:
		cmp	#$7F			;
		bne @noMetaSeq		;	Parse meta sequences
		jsr	loadLevelContinuation
		jmp	@ReadNewVal		;__

	@SingleByteRun:
		and #$7f
		sta rld_value
		ldy	#$00
		sty rld_run
		ldx col_idx
		inx 
		bmi @FirstLoop
		; and then fallthrough to copying to the collision map

	@End:
	ldx rld_column
	inx
	.if USE_ILLEGAL_OPCODES
		lda #$0F
		sax rld_column
	.else
		txa
		and #$0F
		sta rld_column
	.endif
	rts
.endproc

; Function not available in C
.segment "CODE_2"

.proc loadLevelContinuation
	; Meta sequence: load new level chunk
	jsr	LZ_get_byte			;	Get Meta Level ID
	tay						;__

	lda	_level_chunk_list_bank, y	;
	sta	_level_data_bank			;	Get new data bank
	jsr	mmc3_set_prg_bank_1			;__

	ldx	_level_chunk_list_lo, y		;__	Get new data low ptr
	lda	_level_chunk_list_hi, y		;	Get new data high ptr
	tay								;__

	jmp	LZ_init_decomp
.endproc

; void __fastcall__ dummy_unrle_columns(uint16_t columns);
.segment "CODE_2"

.import umul8x16r24m

.export _dummy_unrle_columns
.proc _dummy_unrle_columns
	lastType = tmp1	; 0 = group of bytes, FF = single byte
	mulIn0 = ptr3
	mulIn1 = ptr1
	mulRes0 = ptr1
	mulRes1 = ptr1+1
	mulRes2 = sreg
	start:
		sta mulIn0			;
		stx mulIn0+1		;	Multiply the
		and #$0F			;	amount of columns
		sta rld_column		;__
		lda rld_load_value	;
		eor #$FF			;
		sec					;	by level height
		adc #0				;
		sta mulIn1			;__
		jsr umul8x16r24m
		; result now in ptr1:sreg[0],
		; y = 0 

		inc mulRes1		;	increment for beq ending condition
		inc mulRes2		;__

		lda mulRes0
		clc				;	Subtract 1 extra, rld_run after all
		sbc rld_run		;__
		sta mulRes0
		bcs loop
		
		dec mulRes1
		bne loop
		
		dec mulRes2
		beq end_early
		
	loop:
		jsr	LZ_get_byte	; either single-run value or run
		cmp	#$00
		bmi single_byte
		sta rld_run

		jsr	LZ_get_byte			;
			cmp	rld_run			;	Load rld_value
			beq	parseMetaSeq	;	or meta sequence
		loop_noMetaSeq:			;
			tax					;__

		lda mulRes0
		clc	; subtract 1 extra
		sbc rld_run
		sta mulRes0
		bcs loop

		dec mulRes1
		bne loop
	
		dec mulRes2
		bne loop	; = BRA

	end_multi:
		stx rld_value
		; the remaining rld_run is 2's complement of (mulRes0 - 1)
	end_early:
		lda mulRes0
		eor #$FF
		sta rld_run
		rts


	single_byte:
		dec mulRes0
		ldx mulRes0
		inx	; less bytes then cpx #$ff
		bne loop
		dec mulRes1
		bne loop
		dec mulRes2
		bne loop

	end_single:
		and #$7F
		sta rld_value
		lda	#$00
		sta rld_run	; y is still 0
		rts

	parseMetaSeq:
		cmp	#$7F			;
		bne loop_noMetaSeq	;	Parse meta sequences
		jsr	loadLevelContinuation
		jmp	loop			;__
.endproc




.segment "XCD_BANK_02"	; dep of: _draw_screen

.proc writeToCollisionMap
	; We have 27 writes to make to the collision map, thats 27 * 6 bytes for an unrolled loop.
	; roughly twice the size for much more perf. ill probably make it back to loop
	ldx rld_column
	.if USE_ILLEGAL_OPCODES
		dex
		lda #$0F
		axs #0
	.else
		dex
		txa
		and #$0F
		tax
	.endif
	ldy rld_load_value
	cpy #<-(15+15+12)
	bcs write_collmap1
		.repeat 15, I
			lda columnBuffer+(15*0) + I
			sta collMap0 + I * 16, x
		.endrepeat
	write_collmap1:
	cpy #<-(15+12)
	bcs write_collmap2
		.repeat 15, I
			lda columnBuffer+(15*1) + I
			sta collMap1 + I * 16, x
		.endrepeat
	write_collmap2:
	cpy #<-(12)
	bcs write_collmap3
		.repeat 15, I
			lda columnBuffer+(15*2) + I
			sta collMap2 + I * 16, x
		.endrepeat
	write_collmap3:
		.repeat 12, I
			lda columnBuffer+(15*3) + I
			sta collMap3 + I * 16, x
		.endrepeat
	write_ground:
		.repeat 3, I
			lda ground + I * 16, x
			sta columnBuffer+(15*3)+12+I
		.endrepeat
	rts
.endproc


; [Not used in C]
.segment "XCD_BANK_02"	; dep of: _draw_screen

.import _scroll_y

.export get_seam_scroll_y
.proc get_seam_scroll_y
	; No inputs
	; Returns seam_scroll_y in AX
start:
	BIT	extceil
	BPL	noSeam

yesSeam:
	; Seam position:
	; Y ≥	| Y <	| A		| B		|
	; 	0	|  $78	|	0	|	1	|
	;  $78	| $178	|  2/0	|	1	|
	; $178	| $278	|	2	|  3/1	|
	; $278	| $2F0	|	2	|	3	|

	; Get seam position
	LDA	_scroll_y
	LDX	_scroll_y+1
	SEC
	SBC	#$78	;
	BCS	:+		;	AX = scroll_y - $78
		SBC #$10-1;	(with valid scroll_y coordinates)
		DEX		;__
	:
	STA	seam_scroll_y
	STX seam_scroll_y+1

	RTS

noSeam:
	; The level's ceiling ≤ 27 blocks, no need for a seam
	LDA	#$78
	LDX #$02
	STA	seam_scroll_y
	STX	seam_scroll_y+1
	RTS

	; Total seam system:
	; High byte	| Seam screen	| A		| B		|
	;	FF		|	There isn't	|	0	| 	1	|
	;	00		|		00		|  2/0	|	1	|
	;	01		|		01		|	2	|  3/1	|
	;	02		|	There isn't	|	2	|	3	|
	;	No seam can be distinguished by high byte >= 02 or bit 1
.endproc


; char draw_screen();
.segment "XCD_BANK_02"

.global dsrt_fr1O : zp

.export _draw_screen
.proc _draw_screen

; Write architecture:

; Frame 0:
;   Write 0 updates the upper nametable's left tiles
;   Write 1 updates the lower nametable's left tiles
; Frame 1:
;   Write 0 updates the upper nametable's right tiles
;   Write 1 updates the lower nametable's right tiles
; Frame 2:
;   Attributes

	frame_free = 0
	frame_R_tile_1 = 1
	frame_R_attr = 2
	frame_UD_tiles_separate_1 = 3
	frame_UD_attr_unified = 4
	frame_UD_attr_separate = 5

start:
	LDX drawing_frame		;	If something is being drawn, continue
	BNE switch				;__

	LDA _scroll_x			;
	LSR						;
	LSR						;	If X == rld column and we are free,
	LSR						;	start drawing the right edge
	LSR						;
	CMP rld_column			;
	BEQ draw_screen_R_tiles	;__

	;
	;	The drawing_frame is 0, but we don't have the right edge to update
	;	That means it is time to start updating the vertical scrolling seam
	;__

	LDA	extceil						;	If the ceiling is extended
	EOR	#$80						;	and blocks are visible
	ORA	_invisblocks				;	update vertical seam tiles
	BEQ	jmpto_draw_screen_UD_tiles	;__	

	LDA	#0		;
	TAX			;	Otherwise return 0
	RTS			;__

jmpto_draw_screen_UD_tiles:
	JMP draw_screen_UD_tiles_frame0

switch:
	DEX									;	if drawing_frame == 1, do frame 1
	BEQ	draw_screen_R_tiles+dsrt_fr1O	;__	of drawing the right edge (right tile halves)
	DEX									;	if drawing_frame == 2, do frame 2
	jeq	draw_screen_R_attributes		;__ of drawing the right edge (attributes)
	DEX									;	if drawing_frame == 3, do frame 1
	jeq	draw_screen_UD_tiles_frame1		;__	of drawing the up/down tiles (copy the lower tiles)


; [Subroutine]
.global metatiles_top_left, metatiles_top_right, metatiles_bot_left, metatiles_bot_right
.import _increase_parallax_scroll_column
.import _no_parallax, _invisblocks

.proc draw_screen_R_tiles

	TileWriteSize	= (15*2)+2+1

	TileOff0		= 0
	TileOff1		= 0+TileWriteSize
	TileEnd			= 0+TileWriteSize+TileWriteSize

	CurrentRow = tmp1
	LoopCount = tmp2
	SeamValue = ptr3+1

	

frame0:
	LDA #frame_free
	STA drawing_frame
	; Switch banks
	crossPRGBankJSR ,_unrle_next_column,_level_data_bank
	JSR writeToCollisionMap
frame1:

	; thanks ca65, very cool
	.if (frame1 - frame0) < 256
		.exportzp dsrt_fr1O = <(frame1 - frame0)
	.else
		.error "too far"
	.endif

calc_seam_pos:

	LDA seam_scroll_y
	LDX seam_scroll_y+1

	LDY	#15+15	;__	Load the starting nametable into Y

	CPX #$02	;	If there is a seam,
	BCS @noseam	;__	calculate its position in metatiles
	@yesseam:
		LSR					;
		LSR					;	Divide by 16, get index 
		LSR					;	inside screen in metatiles
		LSR					;__
		CLC					;	Add 0 or 15, since scroll_y is nonlinear
		ADC SeamTable, X	;__
		ADC #30				;__	If the carry was set then something got fucked
		STA SeamValue
		BCC @fin	; = BRA, unless the additions got fucked

	@noseam:		;__	If there is no seam, store an invalid value
		STX SeamValue
		CPX	#$FF	;
		BNE	@fin	;	If the starting screen is 0, load into Y
			LDY #0	;__
	@fin:
		STY	CurrentRow

write_start:
	; Writing to nesdoug's VRAM buffer starts here
	LDX VRAM_INDEX

	; In-house replacement of get_ppu_addr, only counts X
	; Address is big-endian
	LDY rld_column ;   000xxxx0 - the left tiles of the metatiles
	DEY
	TYA
	AND #$0F
	ASL         ;__
	LDY drawing_frame
	BEQ :+
		ORA #$01    ;   000xxxx1 - the right tiles of the metatiles
	:
	STA VRAM_BUF+TileOff0+1,X
	STA VRAM_BUF+TileOff1+1,X

	; Get nametable
	lda _scroll_x + 1 ; high byte
	and #%00000001
	tay
	lda	ntAddrHiTbl,y
	STA VRAM_BUF+TileOff0,X
	ORA #$08        ; 2nd nametable
	STA VRAM_BUF+TileOff1,X


	; First part of the update: the tiles
	; Amount of data in the sequence - 27*2 tiles (8x8 tiles, left sides of the metatiles)
	LDA #(15*2)
	STA VRAM_BUF+TileOff0+2,X
	STA VRAM_BUF+TileOff1+2,X

	; The sequence itself:
	
	; Load max value
	LDA #15 - 1
	STA LoopCount
	; Check if doing a left or right hand write
	LDA drawing_frame
	AND #1
	beq @LeftWrite
		; Right side write
		; Call for upper tiles
		JSR right_tilewriteloop
		BMI @WriteBottomHalf	; The loop keeps looping via a BPL, therefore a BMI = BRA
	@LeftWrite:
		JSR left_tilewriteloop
@WriteBottomHalf:
	; Load new max
	LDA #15 - 1
	STA LoopCount
	; Add offset to X
	.if USE_ILLEGAL_OPCODES
		TXA
		AXS #<-(TileWriteSize-(15*2))
	.else
		TXA
		CLC
		ADC #(TileWriteSize-(15*2))
		TAX
	.endif

	; No need to do anything for the screen, as it always increments

	LDA drawing_frame
	AND #1
	beq @LeftWrite2
		JSR right_tilewriteloop
		BMI @RenderParallax	; The loop keeps looping via a BPL, therefore a BMI = BRA
	@LeftWrite2:
		; Call for lower tiles
		JSR left_tilewriteloop
@RenderParallax:

	ParallaxBufferStart = tmp1
	ParallaxExtent = tmp3
	; Loop through the vram writes and find any $00 tiles and replace them with parallax
	; Calculate the end of the parallax column offset
	ldy parallax_scroll_column
	lda ParallaxBufferOffset, y
	sta ParallaxBufferStart
	clc
	adc #9
	sta ParallaxExtent

	lda ParallaxBufferStart
	clc
	adc parallax_scroll_column_start
	tay

	ldx #TileOff0 + TileWriteSize - 1 - (2+1)
	stx LoopCount
	ldx #TileOff0
	jsr RenderParallaxLoop

	ldx #TileWriteSize - 1 - (2+1)
	stx LoopCount
	ldx #TileOff1
	jsr RenderParallaxLoop
	
	; move to the next scroll column for next frame
	jsr _increase_parallax_scroll_column

	; Demarkate end of write
	LDX VRAM_INDEX
	LDA #$FF
	STA VRAM_BUF+TileEnd,X

	; Declare this section as taken
	.if USE_ILLEGAL_OPCODES
		; A is already #$FF
		AXS #<-TileEnd
		STX VRAM_INDEX
	.else
		TXA
		CLC
		ADC #TileEnd
		STA	VRAM_INDEX
	.endif

	INC drawing_frame

	LDA #1
	LDX #0
	RTS

right_tilewriteloop:
		ldy CurrentRow
		lda _invisblocks
		beq @norm
		lda #0
		beq @done
		@norm:
		LDA columnBuffer,Y
		@done:
		tay
		; y is the metatile id
		lda metatiles_top_right, y
		STA VRAM_BUF+TileOff0+3,X
		lda metatiles_bot_right, y
		STA VRAM_BUF+TileOff0+4,X
		
		INX
		INX
		LDA CurrentRow
		CMP SeamValue
		SEC		; Does not reset the Zero flag
		BNE :+	; If the seam doesn't match up, dont subtract
			SBC	#30	; Carry still set after this (or invalid otherwise)
		: ADC #0 ; Adds a 1
		STA CurrentRow
		DEC LoopCount
		BPL right_tilewriteloop
	rts

left_tilewriteloop:
		ldy CurrentRow
		lda _invisblocks
		beq @norm2
		lda #0
		beq @done2
		@norm2:
		LDA columnBuffer,Y
		@done2:
		tay
		; y is the metatile id
		lda metatiles_top_left, y
		STA VRAM_BUF+TileOff0+3,X
		lda metatiles_bot_left, y
		STA VRAM_BUF+TileOff0+4,X
		
		INX
		INX
		LDA CurrentRow
		CMP SeamValue
		SEC		; Does not reset the Zero flag
		BNE :+	; If the seam doesn't match up, dont subtract
			SBC	#30	; Carry still set after this (or invalid otherwise)
		: ADC #0 ; Adds a 1
		STA CurrentRow
		DEC LoopCount
		BPL left_tilewriteloop
	rts
		
RenderParallaxLoop:
	lda _no_parallax
	bne @nopar
		lda VRAM_BUF+TileOff0+3,x
		bne :+
			; empty tile, so replace it with the parallax for this
			lda ParallaxBuffer, y
			sta VRAM_BUF+TileOff0+3,x
		:
		iny
		cpy ParallaxExtent
		bne :+
			ldy ParallaxBufferStart
		:
		inx
		dec LoopCount
		bpl RenderParallaxLoop
@nopar:
		rts

; Column striped parallax data definition
; add to the tile for the next row, up to 6.
ParallaxBuffer:
	ParallaxBufferOffset:
		.byte ParallaxBufferCol0 - ParallaxBuffer
		.byte ParallaxBufferCol1 - ParallaxBuffer
		.byte ParallaxBufferCol2 - ParallaxBuffer
		.byte ParallaxBufferCol3 - ParallaxBuffer
		.byte ParallaxBufferCol4 - ParallaxBuffer
		.byte ParallaxBufferCol5 - ParallaxBuffer
	ParallaxBufferCol0:
		.byte $80, $90, $a0, $b0, $86, $96, $a6, $b6, $8c
	ParallaxBufferCol1:
		.byte $81, $91, $a1, $b1, $87, $97, $a7, $b7, $8d
	ParallaxBufferCol2:
		.byte $82, $92, $a2, $b2, $88, $98, $a8, $b8, $8e
	ParallaxBufferCol3:
		.byte $83, $93, $a3, $b3, $89, $99, $a9, $b9, $9c
	ParallaxBufferCol4:
		.byte $84, $94, $a4, $b4, $8a, $9a, $aa, $ba, $9d
	ParallaxBufferCol5:
		.byte $85, $95, $a5, $b5, $8b, $9b, $ab, $bb, $9e

SeamTable:
	.byte 0, 15

ntAddrHiTbl:
	.byte	$24|$80,	$20|$80
.endproc

; [Subroutine]
.global metatiles_attr
.import _no_parallax, _invisblocks

.proc draw_screen_R_attributes
	AttrWriteSize	= 3*8

	AttrOff0		= 0
	AttrOff1		= 0+AttrWriteSize
	AttrEnd			= 0+AttrWriteSize+AttrWriteSize

	tmp5 = ptr2
	ColumnBufferIdx = ptr2+1

	NametableAddrHi = tmp1
	LoopCount = tmp2
	SeamValue = ptr3+1
	; Attribute write architecture:

	; | Ad|dr |dat|
	;   0   1   2
	; Addr = VRAM address

	; 1 byte can theoretically be saved by using a vertical
	; sequence of 2 bytes, but this comes at a cost of 23
	; cycles per 2 bytes in vblank (80 vs 103), and vlank
	; time is not to be wasted

	; Decremented rld_column, very useful
	LDX rld_column
	DEX
	.if USE_ILLEGAL_OPCODES
		LDA #$0F
		SAX ptr3
	.else
		TXA
		AND #$0F
		STA ptr3
	.endif

	; Seam pos for attributes:
	; ( <seam_scroll_y & $E0 | >seam_scroll_y & 5) ^ column
	LDA seam_scroll_y
	AND #$E0
	STA SeamValue
	LDA seam_scroll_y+1
	AND #$03	; add bit 1 to not use if no seam
	ORA SeamValue
	STA SeamValue

	LDY	#>collMap2		;__	Get the default value
	AND #$03			;	Bits 0 and 1 are directly from >seam_scroll_y
	CMP	#$03			;	For value $FF start at screen 0, otherwise screen 2
	BNE	:+				;
		LDY	#>collMap0	;	Get high byte of starting value
	:					;	(the screen)
	STY	ptr1+1			;__

	LDA ptr3			;
	AND #$0E			;	Get column (w/o highest bit cuz attributes)
	; ADC #<(collMap0-1) ; the low byte is 0
	STA ptr1			;__
	EOR	SeamValue		;	The only overlapping bit is bit 1,
	STA	SeamValue		;__	if it's invalid the seam won't be drawn

	LDX #0
	STX ColumnBufferIdx
	JSR attributeCalc

	; Increment screen (we always increment)
	INC ptr1+1

	DEC	SeamValue

	JSR attributeCalc

	; Get address hi byte (either left or right side)
	lda _scroll_x + 1 	; high byte
	and #%00000001		;
	tay					;	5 cycles, 6 bytes
	lda	ntAddrHiTbl, Y	;__
	sta NametableAddrHi
	
	LDA ptr3
	LSR
	ORA #$C0
	
	; Store address
	LDX VRAM_INDEX
	CLC
	addressLoop:
		; Low byte
		STA VRAM_BUF+AttrOff0+1,X
		STA VRAM_BUF+AttrOff1+1,X
		TAY
		; High byte
		lda NametableAddrHi
		STA VRAM_BUF+AttrOff0,X
		ORA #$08
		STA VRAM_BUF+AttrOff1,X
		TYA

		INX 
		INX
		INX

		; C is cleared by BCC
		ADC #$08
		BCC addressLoop
	
	LDY #16

	LDA VRAM_INDEX
	ADC #AttrEnd-1  ; Carry is set by the ADC : BCC
	STA VRAM_INDEX  ; State that the block is now occupied
	TAX

	dataLoop:
		LDA columnBuffer-1,Y
		STA VRAM_BUF-3+2,X

		.if USE_ILLEGAL_OPCODES
			TXA
			AXS #3
		.else
			DEX
			DEX
			DEX
		.endif
		DEY
		BNE dataLoop
	
	; Finish off the routine
	; X has the original VRAM_INDEX, mark this block as taken
	LDA #$FF
	STA VRAM_BUF+AttrEnd,X
	; Reset frame counter
	LDX #frame_free
	STX drawing_frame

	LDA #1
	RTS

attributeCalc:
	LDA #8 - 1
	STA LoopCount

	attributeLoop:
		; Read lower right metatile
		LDY #$11
		.if USE_ILLEGAL_OPCODES
			lax (ptr1),y
		.else
			LDA	(ptr1),Y
			tax
		.endif
		; Read lower left metatile
		dey
		LDA (ptr1), Y
		tay
		; Get their attributes
		lda metatiles_attr,x	; Lower right
		ASL
		ASL
		ora metatiles_attr,y	; Lower left
		STA tmp5

		; Read upper right metatile
		LDY #$01
		.if USE_ILLEGAL_OPCODES
			lax (ptr1),y
		.else
			LDA	(ptr1),Y
			tax
		.endif
		; Read upper left metatile
		dey
		LDA (ptr1), Y
		tay
		; Get their attributes
		lda metatiles_attr,x	; Upper right
		ASL
		ASL
		ora metatiles_attr,y	; Upper left

		; Combine
		LDY tmp5	; Y has the lower metatile attrs, will shift by 4
		ORA shiftBy4table,Y
		LDX ColumnBufferIdx
		STA columnBuffer,X

		; Increment pointer
		LDA	ptr1
		CMP SeamValue
		BNE :+
			DEC ptr1+1
			DEC ptr1+1
		:
		CLC
		ADC #$20
		STA	ptr1

		INC ColumnBufferIdx
		DEC LoopCount
		BPL attributeLoop
	RTS

ntAddrHiTbl:
	.byte	$27,	$23
.endproc


; [Subroutine]
.global metatiles_top_left, metatiles_top_right, metatiles_bot_left, metatiles_bot_right
.import _no_parallax, _invisblocks
.import _scroll_y

.proc draw_screen_UD_tiles_frame0
	scroll_direction = tmp1
	column_idx = tmp2
	loop_count = tmp3

	new_seam_pos = ptr1
	this_seam_pos = ptr2
	collmap_ptr = ptr3

	UnifiedTileWriteSize = (16*4)+2+1
	Separate2WritesSize = (16*2)+((2+1)*2)	; Contains 32 tiles in total, in 2 writes
	SepWrABuf = VRAM_BUF+0
	SepWrBBuf = VRAM_BUF+3
	SepWrCBuf = VRAM_BUF+Separate2WritesSize+0
	SepWrDBuf = VRAM_BUF+Separate2WritesSize+3
	SepWriEnd = Separate2WritesSize

	start:
		LDA	_scroll_y				;
		SEC							;
		SBC	old_draw_scroll_y		;
		STA	tmp1					;	XY = scroll_y - old_draw_scroll_y
		LDA	_scroll_y+1				;
		SBC	old_draw_scroll_y+1		;
		TAY							;__

		ORA	tmp1
		BNE	calc_new_seam_pos

		TAX		;	A is 0
		RTS		;__

	calc_new_seam_pos:
		@start:
			LDA	#$10
			STA	sreg+0
			LDA	seam_scroll_y
			LDX	seam_scroll_y+1
			CPY	#$00	;	Puts carry into X
			BMI	@up		;__
		
		@down:
			JSR	__add_scroll_y		;__	Calculate new seam position
			STA	this_seam_pos+0		;	Store new seam position
			STX	this_seam_pos+1		;__
			JSR	@calc_diff			;__	Calculate difference
			CMP	#$38				;
			TXA						;	If the difference is less than
			LDX	#2					;	($78 - $40), we went too far
			SBC	#$00				;	Also load the scrolling direction offset
			BCS	@fin				;__
		
		@ret0:		;
			LDA	#0	;	Return 0
			TAX		;	(nothing was done)
			RTS		;__
		
		@calc_diff:	;__	[Subroutine]
			STA	new_seam_pos		;	Store new seam position
			STX	new_seam_pos+1		;__
			STA	sreg+0				;
			STX	sreg+1				;	Calculate the difference 
			LDX	_scroll_y			;	between scroll_y and seam position
			LDA	_scroll_y+1			;	(doesn't need to be linearized due to its indended range)
			JMP	__sub_scroll_y_ext	;__
		
		@up:
			STA	this_seam_pos+0		;	Store old seam position
			STX	this_seam_pos+1		;__
			JSR	__sub_scroll_y		;__	Calculate new seam position
			JSR	@calc_diff			;__	Calculate difference
			CMP	#$B8				;
			TXA						;	If the difference is more than
			LDX	#0					;	($78 + $40), we went too far
			SBC	#$00				;	Also load scrolling direction offset
			BCS	@ret0				;__
		
		@fin:
			STX	scroll_direction

			LDA	_scroll_y
			LDY	_scroll_y+1
			STA	old_draw_scroll_y
			STY	old_draw_scroll_y+1

			LDA	new_seam_pos
			LDY	new_seam_pos+1
			STA	seam_scroll_y
			STY	seam_scroll_y+1

			LDY	this_seam_pos+1
			CPY	#$02				;	If no seam, exit early
			BCS	@ret0				;__

	start_writing:
		@get_collmap_ptr:
			;	Y contains the >seam_scroll_y, Carry is clear
			LDA this_seam_pos	;
			AND	#$F0			;	Get low byte
			STA	collmap_ptr		;__	(none of these affect the carry)
			TYA					;
			ADC	scroll_direction;
			ORA	#>collMap0		;	Get high byte
			STA	collmap_ptr+1	;__

		@get_write_type:
			LDX	VRAM_INDEX

			; 2 scenarios: one write 64 tiles long, or 4 writes, 16-x and x tiles long each (thanks jrowe screen extension)
			LDY	rld_column
			jne write_separate

	write_unified:
		@shift_addr:
			LDA	this_seam_pos	;__	Get bits: hhll uuuu (u will be ignored)
			ASL					;	Double 8-bit left shift
			ADC	#$80			;	to shift the mm bits to the high byte
			ROL					;__	to get ll00 00hh
		@store_low:
			TAY					;__	Tmp storage
			AND	#$C0			;	Store the low byte for X=0
			STA	VRAM_BUF+1,	X	;__
		@store_high:
			LDA	_scroll_x+1		;	Thanks jroweboy
			LSR					;__
			TYA					;	These don't affect carry
			AND	#$03			;__
			BCS	:+				;	Get X of nametable
				ORA	#$04		;__
			:	ORA	#$20|$40	;__	Get valid nametable addr with horizontal seq update
			LDY	this_seam_pos+1	;
			BEQ	:+				;	Get Y of nametable
				ORA	#$08		;__
			:	STA	VRAM_BUF+0,X;__	Store the high byte of nametable addr
		@store_length:
			LDA	#64				;	Store length
			STA	VRAM_BUF+2,	X	;__
		@store_finish:
			LDA	#$FF
			STA	VRAM_BUF+UnifiedTileWriteSize,	X

	write_unified_loop:
		@start:
			LDA	#$00
			STA	column_idx
			LDA	#$10
			STA	loop_count
		@loop:
			LDY	column_idx			;
			LDA	(collmap_ptr),	Y	;	Get metatile
			TAY						;__

			LDA	metatiles_top_left,	Y	;
			STA	VRAM_BUF+3+0,	X		;
			LDA	metatiles_top_right,Y	;
			STA	VRAM_BUF+3+1,	X		;	Get and store the tiles
			LDA	metatiles_bot_left,	Y	;	into the VRAM buffer
			STA	VRAM_BUF+3+32,	X		;
			LDA	metatiles_bot_right,Y	;
			STA	VRAM_BUF+3+33,	X		;__

			INX
			INX
			INC	column_idx
			DEC	loop_count
			BNE	@loop

		LDA	VRAM_INDEX
		CLC
		ADC	#UnifiedTileWriteSize
		STA	VRAM_INDEX

		; TODO eventually: parallax

		LDA #1
		LDX	#0

		RTS

	write_separate:
		;	Write architecture:
		;	Wr:	| Wr. A (32-X)	| Wr. B (X)	| Wr. C (32-X)	| Wr. D (X)	|
		;	Loc:|		VRAM buffer			|		Column buffer		|
		;	NT:	|	NT. A/C		|	NT. B/D	|	NT. A/C		|	NT. B/D	|
		;	Tile|			Upper			|			Lower			|
		;	X:	|		X		|	  0		|		X		|	  0		|
		;		 \Combined length of 32(+6)/ \Combined length of 32(+6)/

		@shift_addr:
			LDA	this_seam_pos	;__	Get bits: hhll uuuu (u will be ignored)
			ASL					;	Double 8-bit left shift
			ADC	#$80			;	to shift the mm bits to the high byte
			ROL					;__	to get ll00 00hh
		@store_low:
			TAY					;__	Tmp storage
			AND	#$C0			;	Push the low byte for X=0
			PHA					;__	for writes B&D
			LSR					;
			ORA	rld_column		;	Add the X
			ASL					;__
			STA	SepWrABuf+1,X	;__	Store write A
			ORA	#$20			;	Get and
			STA	SepWrCBuf+1,X	;__	store write C
		@store_high:
			LDA	_scroll_x+1		;	Thanks jroweboy
			LSR					;__
			TYA					;	These don't affect carry
			AND	#$03			;__
			BCC	:+				;	Get X of nametable
				ORA	#$04		;__
			:	ORA	#$20|$40	;__	Get valid nametable addr with horizontal seq update
			LDY	this_seam_pos+1	;
			BEQ	:+				;	Get Y of nametable
				ORA	#$08		;__
			:	PHA				;__	Push high byte of nametable addr for writes B & D
			STA SepWrABuf,	X	;	Store the high byte
			STA	SepWrCBuf,	X	;__
		@store_length:
			LDA	#16				;
			SEC					;
			SBC	rld_column		;	Get length for writes A & C
			STA	loop_count		;	Store as a counter to check for writes B & D
			ASL					;__
			STA	SepWrABuf+2,X	;	Store it
			STA	SepWrCBuf+2,X	;__
	write_separate_loop:
		@setup_first_loop:
			LDA	rld_column
			STA	column_idx
		@loop_AC:
			LDY	column_idx			;
			LDA	(collmap_ptr),	Y	;	Get metatile
			TAY						;__

			LDA	metatiles_top_left,	Y	;
			STA	SepWrABuf+3+0,	X		;
			LDA	metatiles_top_right,Y	;
			STA	SepWrABuf+3+1,	X		;	Get and store the tiles
			LDA	metatiles_bot_left,	Y	;	into the VRAM buffer
			STA	SepWrCBuf+3+0,	X		;
			LDA	metatiles_bot_right,Y	;
			STA	SepWrCBuf+3+1,	X		;__

			INX
			INX
			INC	column_idx
			DEC	loop_count
			BNE	@loop_AC
		@setup_second_loop:
			LDA	column_idx
			CMP	#$10
			BNE @fin

			LDA	#$00
			STA	column_idx

			LDA	rld_column		;	Update loop count
			STA	loop_count		;__
			ASL					;
			STA	SepWrBBuf+2,X	;	Store the length
			STA	SepWrDBuf+2,X	;__

			PLA					;	Invert the high byte's
			EOR	#$04			;__	X of the nametable
			STA	SepWrBBuf+0,X	;	Store the high nametable byte
			STA	SepWrDBuf+0,X	;__

			PLA					;
			STA	SepWrBBuf+1,X	;	Store the low nametable byte
			ORA	#$20			;
			STA	SepWrDBuf+1,X	;__

			INX
			INX
			INX

			BCC	@loop_AC	;__	Last carry instruction was ASL rld_column, which shifted out a 0

		@fin:
			LDA	#frame_UD_tiles_separate_1
			STA	drawing_frame

			; Current X is pointing at the last element - 3
			INX
			INX
			INX
			STX	VRAM_INDEX
			LDY	#Separate2WritesSize
		@transfer_loop:
			DEX
			LDA	SepWrCBuf,	X
			STA	columnBuffer-1,	Y
			DEY
			BNE	@transfer_loop

			LDA	#$FF
			STA	VRAM_BUF+Separate2WritesSize,	X

			LDA	#1
			LDX	#0
			RTS


.endproc


.proc draw_screen_UD_tiles_frame1
	Separate2WritesSize = (16*2)+((2+1)*2)	; Contains 32 tiles in total, in 2 writes
	@start:
		LDA	VRAM_INDEX
		CLC
		ADC	#Separate2WritesSize
		STA	VRAM_INDEX
		TAX

		LDY	#Separate2WritesSize
	@loop:
		DEX
		LDA	columnBuffer-1,	Y
		STA	VRAM_BUF,	X
		DEY
		BNE	@loop
	@fin:
		LDA	#$FF
		STA	VRAM_BUF+Separate2WritesSize, X

		LDA	#1
		LDX	#frame_free
		STX	drawing_frame
		RTS
.endproc

.endproc


; void __fastcall__ load_ground(uint8_t id);
.segment "XCD_BANK_06"

.import _ground

.export _load_ground
.proc _load_ground
	;A = ground num
	ASL						;
	TAX						;
	LDA _ground, X			;	ptr1 = ground[id]
	STA ptr1				;	(we're already within the correct bank)
	LDA _ground+1, X		;
	STA ptr1+1				;__
	LDX #<-48				;__	X = idx @ collmap data, count up to 0
	LDY	#$00				;__	Y = 0

	ground_ptr = ground-($100-48)

	; there's a max of 48 bytes of data to fill, 
	; the rle worst case is 96 bytes long,
	; therefore not needing to check for an overflow

	loop:
		LDA (ptr1),y		;
		bmi single_rle_byte	;	Run
		STA tmp1			;
		iny					;__

		LDA (ptr1),y		;	Value
		iny					;__

		STY tmp2
		LDY tmp1
	mult_loop:
		STA ground_ptr, X
		INX
		BEQ fin
		DEY
		BPL mult_loop
		LDY tmp2
		BNE loop	; Physically cannot be not 0

	single_rle_byte:
		AND #$7F
		STA ground_ptr, X
		INY
		INX
		BNE loop

	fin:
		RTS

.endproc

; void __fastcall__ draw_padded_text(const void * data, uint8_t len, uint8_t total_len, uintptr_t ppu_address)
.segment "CODE_2"

.export __draw_padded_text
.proc __draw_padded_text
	; AX = ppu_address
	; sreg[0] = total_len
	; sreg[1] = len
	; xargs[0:1] = data

	spaceChr = $FE
	data = xargs+0
	total_len = sreg+0
	len = sreg+1

	LDY VRAM_INDEX
	STA VRAM_BUF+1, Y	;
	TXA					;	vram pointer
	STA VRAM_BUF+0, Y	;__
	LDA total_len		;	total length
	STA VRAM_BUF+2, Y	;__

	SEC					;	Total padding
	SBC len				;__
	LSR					;	Get left offset
	STA tmp1			;__
	ADC #$00			;	Get right offset
	TAY					;__

	LDA total_len
	ADC	VRAM_INDEX		;	Carry is guaranteed to be clear by LSR : ADC #$00
	; If carry is still set, we have big problems
	; BCS some shit to do
	TAX
	ADC #$03
	STA VRAM_INDEX

	LDA #$FF			;	Finish off the write
	STA VRAM_BUF+3, X	;__

	CPY #$00	; Had to do this, very sorry
	BEQ main_data

	LDA #spaceChr

	pad_loop_right:
		STA VRAM_BUF+2, X
		DEX
		DEY
		BNE pad_loop_right
		
	main_data:
		LDY len
		DEY

	main_data_loop:
		LDA (<data), Y
		STA VRAM_BUF+2, X
		DEX
		DEY
		BPL main_data_loop

	LDY tmp1	;	Pad left amount
	BEQ fin		;__

	LDA #spaceChr

	pad_loop_left:
		STA VRAM_BUF+2, X
		DEX
		DEY
		BNE pad_loop_left

	fin:
		RTS

.endproc

; void movement();
.segment "XCD_BANK_01"

.import _cube_movement, _ship_movement, _ball_movement, _ufo_movement, _robot_movement, _spider_movement, _wave_movement
.import _retro_mode

.export _movement
.proc _movement
	LDX _gamemode
	CPX #<gamemode_count
	BCS end
	lda _retro_mode
	beq @no1
	lda _gamemode
	cmp #1
	bne	@no1
		; LDA #<_ufo_movement
		; STA <PTR
		; LDA #>_ufo_movement
		; STA <PTR+1
		; JMP (PTR)	
		JMP _ufo_movement
	
	@no1:
		LDA jump_table_hi, X
		PHA
		LDA jump_table_lo, X
		PHA

	end:
		RTS     ; break or use the RTS trick

	jump_table_lo:
		.byte <(_cube_movement-1), <(_ship_movement-1), <(_ball_movement-1), <(_ufo_movement-1), <(_cube_movement-1), <(_spider_movement-1), <(_wave_movement-1), <(_ball_movement-1), <(_cube_movement-1)
	jump_table_hi:
		.byte >(_cube_movement-1), >(_ship_movement-1), >(_ball_movement-1), >(_ufo_movement-1), >(_cube_movement-1), >(_spider_movement-1), >(_wave_movement-1), >(_ball_movement-1), >(_cube_movement-1)

.endproc

; void __fastcall__ music_play(uint8_t song);
.segment "CODE_2"

.import _options

.export _music_play
.proc _music_play  

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

    bit _options ; sets N flag to bit 7 of _options without affecting A  
    bpl musicon
    rts  
musicon:  
    LDY #<FIRST_MUSIC_BANK
    tsx
bank_loop:
    PHA
    SEC
    SBC music_counts-FIRST_MUSIC_BANK, Y
    BCC found_bank
    INY
    TXS ;Act as if no PHA happened
    BCS bank_loop  ; BRA
found_bank:
    TYA
    JSR mmc3_tmp_prg_bank_1
    CPY current_song_bank
    BEQ :+
    ;If different bank than before reinitalize FS
        STY	current_song_bank
		.if useConstInitPtr
			LDX #<constInitPtr
			LDY #>constInitPtr
		.else
			LDX music_data_locations_lo-FIRST_MUSIC_BANK, Y
			LDA	music_data_locations_hi-FIRST_MUSIC_BANK, Y
			TAY
		.endif
        LDA NTSC_MODE
        JSR famistudio_init
    :
    PLA
    JSR famistudio_music_play
    
    JMP _mmc3_pop_prg_bank_1

; Tables generated by export.py
.include "MUSIC/EXPORTS/musicPlayRoutines.s"
.endproc

.segment "CODE_2"

.proc famistudio_dpcm_bank_callback
	clc
	adc #<FIRST_DMC_BANK
	jmp mmc3_set_prg_bank_0
.endproc


; void __fastcall__ sfx_play(uint8_t sfx_index, uint8_t channel);
.segment "CODE_2"

.import _options

.export __sfx_play
.proc __sfx_play  
    ; a = sfx
	; x = channel

    bit _options ; bit 6 is copied to the overflow flag  
    bvc play  
    rts  
play:    
	tay

	lda	mmc3PRG1Bank
	pha
	lda #<.bank(sounds)
    jsr mmc3_set_prg_bank_1

	tya
    jsr famistudio_sfx_play

	pla
	jmp mmc3_set_prg_bank_1
.endproc

; void music_update();
.segment "CODE_2"

.export _music_update
.proc _music_update
    LDA current_song_bank
    JSR mmc3_tmp_prg_bank_1
    JSR famistudio_update
    JMP _mmc3_pop_prg_bank_1
.endproc
; Because i JMPed, the routine is over


; void load_next_sprite(uint8_t slot);
.segment "CODE_2"

.import _activesprites_x_lo, _activesprites_x_hi
.import _activesprites_y_lo, _activesprites_y_hi
.import _activesprites_type, _activesprites_activated
.import _activesprites_realx, _activesprites_realy

.export _load_next_sprite := load_next_sprite
.proc load_next_sprite

	; Check that the pointer is valid
	ldy _sprite_data+1
	beq early_exit

    ; Paste current free sprite slot into X
   	tax

    ; Now read the data into the sprite
    ldy #0
    lda (_sprite_data),y
    cmp #$ff
    beq exit
    iny
    
    ; X - 2 bytes
    sta _activesprites_x_lo,x
	sta _activesprites_realx,x
    lda (_sprite_data),y
    iny
    sta _activesprites_x_hi,x

    ; Y - 2 bytes
    lda (_sprite_data),y
    iny
    sta _activesprites_y_lo,x
	sta _activesprites_realy,x
    lda (_sprite_data),y
    iny
    sta _activesprites_y_hi,x

    ; id - 1 byte
    lda (_sprite_data),y
    ;   no iny, as we ain't using y anymore
    sta _activesprites_type,x
    
    lda #0
    sta _activesprites_activated,x

    ; Increment to the next sprite index - 
    ; Add the 5 back to the pointer
    lda	#$05
    clc
    adc	_sprite_data
    sta	_sprite_data
	ldy _sprite_data+1
    bcc	:+
        iny
    :

exit:
	;	Y is currently 0
	sty _sprite_data+1	;__	invalidate the sprite pointer
early_exit:
	rts
.endproc

; uint16_t calculate_linear_scroll_y(uint16_t nonlinearScroll);
.segment "CODE_2"

.export _calculate_linear_scroll_y
.proc _calculate_linear_scroll_y
	; AX = input, AX = output
	; clobbers tmp1
	STX tmp1
	LDY	tmp1
	INY	; for the BEQ ending condition
	LDX #0
	CLC
	loop:
		DEY
		BEQ end
		ADC #$F0
		BCC loop
			INX
			CLC
			BCC loop
	end:
	RTS
.endproc

; void cap_scroll_y_at_top();
.segment "CODE_2"

.importzp _currplayer_y
.import _scroll_y

.export _cap_scroll_y_at_top
.proc _cap_scroll_y_at_top
check:
	lda     _scroll_y		;
	cmp     _min_scroll_y	;	if (scroll_y < min_scroll_y)
	lda     _scroll_y+1		;
	sbc     _min_scroll_y+1	;__
	bcc     doit
	rts

doit:
	; compensate currplayer_y
	lda     _scroll_y
	ldx     _scroll_y+1
	sta     sreg
	stx     sreg+1
	ldx     _min_scroll_y	;
	lda     _min_scroll_y+1	;	scroll_y = min_scroll_y
	stx     _scroll_y		;
	sta     _scroll_y+1		;__
	jsr     __sub_scroll_y_ext
	jsr     _calculate_linear_scroll_y
	eor     #$FF
	sec
	adc     _currplayer_y+1
	sta     _currplayer_y+1
	; we can't do anything with the high byte of the diff anyway

	rts
.endproc


; void check_spr_objects();
.segment "CODE_2"

.import _activesprites_active, _scroll_x, _scroll_y, _animating

.export _check_spr_objects := check_spr_objects
.proc check_spr_objects
	realScrollY = ptr1
	; save current bank
    lda mmc3PRG1Bank
    pha

	; load sprite data bank
    lda _sprite_data_bank
    jsr mmc3_set_prg_bank_1

	lda	_scroll_y
	ldx	_scroll_y+1
	jsr _calculate_linear_scroll_y
	sta realScrollY
	stx realScrollY+1

    ; for each sprite we want to check to see if its active
    ; if it is, update its realx/y position
    ; if its not, attempt to load another sprite
    ldx #16 - 1

check_sprite_loop:
        ; X is the current sprite object
		lda _activesprites_type, x	;	If the sprite (e.g. color triggers)
		cmp #$ff					;	has been marked as "complete",
		beq sprite_dead				;__
		
        lda _activesprites_x_lo, x	;
        sec							;	Or the sprite has
        sbc _scroll_x				;	went offscreen,
        lda _activesprites_x_hi, x	;
        sbc _scroll_x+1				;__
        bpl sprite_alive

		lda _activesprites_type, x
		cmp #$07
		beq coin_dead
		cmp #$1A
		beq coin_dead
		cmp #$1B
		bne sprite_dead
	coin_dead:
		lda #0
		sta _animating
	sprite_dead:					;__	Load a new one in its place
            txa						;	Takes the "slot" argument in A
			jsr load_next_sprite	;__	But also preserves the X
            lda #0
            jmp write_active
    sprite_alive:
        ; Sprite is still alive, so check to see if its on screen
        bne sprite_offscreen2
        ; sprite is alive AND onscreen x, so now check the Y position
        lda _activesprites_y_lo, x
        clc ; NOTICE: intentionally subtract 1 extra to position them on the screen better
        sbc realScrollY
        sta _activesprites_realy, x
        lda _activesprites_y_hi, x
        sbc realScrollY+1
        bne sprite_offscreen
	finish:
        ; totally onscreen so finish updating its scroll position
        lda _activesprites_x_lo, x
        sec
        sbc _scroll_x
        sta _activesprites_realx, x

        lda #1
        bne write_active ; unconditional
	sprite_offscreen:
		lda _animating
		beq sprite_offscreen2
		lda _activesprites_type, x
		cmp #$07
		beq finish
		cmp #$1A
		beq finish
		cmp #$1B
		beq finish
	sprite_offscreen2:
        lda #0
	write_active:
        sta _activesprites_active, x
        dex
        bpl check_sprite_loop
end:
	pla
	jmp mmc3_set_prg_bank_1
.endproc

.segment "XCD_BANK_05"

.define CUBE_GRAVITY ::_CUBE_GRAVITY
.define MINI_CUBE_GRAVITY ::_MINI_CUBE_GRAVITY

.import _player_x, _player_y, _player_gravity, _player_vel_x, _player_vel_y
.import _ballframe, _robotframe, _robotjumpframe, _spiderframe, _retro_mode, _icon, _gameState, _titleicon
.importzp _cube_rotate, _mini, _was_on_slope_counter
.import _CUBE, _SHIP, _BALL, _ROBOT, _ROBOT_ALT, _UFO, _SPIDER, _WAVE, _SWING, _ROBOT_ALT2, _SPIDER_ALT, _SPIDER_ALT2
.import _MINI_CUBE, _MINI_SHIP, _MINI_BALL, _MINI_BALL_ALT, _MINI_ROBOT, _MINI_ROBOT_ALT, _MINI_UFO, _MINI_SPIDER, _MINI_SPIDER_ALT, _MINI_WAVE, _MINI_SWING, _MINI_SWING_ALT
.importzp _cube_data, _slope_frames, _slope_type
drawcube_rounding_table:
	.byte 0, <-1, <-2, 3, 2, 1
	.byte 0, <-1, <-2, 3, 2, 1	; doubling it simplifies the routine
	.byte <-24

drawcube_sprite_table:
	; Bits 6-7: FLIP
	; Bits 0-2: actual idx
	.define NOFLIP $00
	.define H_FLIP $40
	.define V_FLIP $80
	.define HVFLIP $C0
	.byte NOFLIP|0, NOFLIP|1, NOFLIP|2, NOFLIP|3, NOFLIP|4, NOFLIP|5
	.byte NOFLIP|6, V_FLIP|5, V_FLIP|4, V_FLIP|3, V_FLIP|2, V_FLIP|1
	.byte HVFLIP|0, HVFLIP|1, HVFLIP|2, HVFLIP|3, HVFLIP|4, HVFLIP|5
	.byte HVFLIP|6, H_FLIP|5, H_FLIP|4, H_FLIP|3, H_FLIP|2, H_FLIP|1
	.undef NOFLIP
	.undef H_FLIP
	.undef V_FLIP
	.undef HVFLIP

drawcube_sprite_way:
	; Bits 6-7: FLIP
	; Bits 0-2: actual idx
	.define NOFLIP $00
	.define H_FLIP $40
	.define V_FLIP $80
	.define HVFLIP $C0
	.byte NOFLIP|0, NOFLIP|1, NOFLIP|2, NOFLIP|3, NOFLIP|4, NOFLIP|5
	.byte NOFLIP|6, H_FLIP|5, H_FLIP|4, H_FLIP|3, H_FLIP|2, H_FLIP|1
	.byte H_FLIP|0, HVFLIP|1, HVFLIP|2, HVFLIP|3, HVFLIP|4, HVFLIP|5
	.byte V_FLIP|6, V_FLIP|5, V_FLIP|4, V_FLIP|3, V_FLIP|2, V_FLIP|1
	.undef NOFLIP
	.undef H_FLIP
	.undef V_FLIP
	.undef HVFLIP

drawcube_sprite_none:
	; Bits 6-7: FLIP
	; Bits 0-2: actual idx
	.define NOFLIP $00
	.define H_FLIP $40
	.define V_FLIP $80
	.define HVFLIP $C0
	.byte NOFLIP|0, NOFLIP|1, NOFLIP|2, NOFLIP|3, NOFLIP|4, NOFLIP|5
	.byte NOFLIP|6, NOFLIP|1, NOFLIP|2, NOFLIP|3, NOFLIP|4, NOFLIP|5
	.byte NOFLIP|6, NOFLIP|1, NOFLIP|2, NOFLIP|3, NOFLIP|4, NOFLIP|5
	.byte NOFLIP|6, NOFLIP|1, NOFLIP|2, NOFLIP|3, NOFLIP|4, NOFLIP|5
	.undef NOFLIP
	.undef H_FLIP
	.undef V_FLIP
	.undef HVFLIP


drawplayer_center_offsets:
	;		Cub	Shp Bal	UFO	RBT	SPI	Wav
	.byte	8,	8,	8,	8,	4,	4,	8,	8,	8; normal size
	.byte	4,	4,	4,	4,	4,	4,	4,	4,	4; mini 

; void drawplayerone();
.segment "XCD_BANK_05"

.export _drawplayerone
.proc _drawplayerone

    LDX _cube_data
    LDA _slope_frames+0
    ORA _slope_type+0
    BEQ :+
        TXA
        ORA #%10000000
        BNE @skipClearBit
    :
        TXA
        AND #%01111111
    @skipClearBit:
    sta _cube_data

	LDA _player_gravity+0
	BEQ :+
		LDA #$80
	: STA xargs+0

	LDX _player_y+1		;
	DEX					;	The Y of oam_meta_spr is high_byte(player_y[0])-1
	STX sreg+1			;__

	; Set up base pointer for jump tables
	LDA _mini       ;
	BEQ :+          ;   Add 8 if mini mode 
		LDA #gamemode_count
	:               ;__
	CLC             ;   Actual gamemode itself
	ADC _gamemode   ;__
	PHA
	LDX _retro_mode
	BEQ :+
		ADC #gamemode_count*2	; ain't no way the last one overflowed
	:
	TAX
	LDA sprite_table_table_lo, X
	STA ptr1		;__	Get low byte of table ptr
	LDA sprite_table_table_hi, X
	STA ptr1+1		;__ Get high byte of table ptr
	PLA				;	Get pure gamemode number
	TAX				;__

	LDY _player_x+1     ;__ temp_x = high_byte(player_x[0]);
	; The condition if is temp_x == 0 or is > 0xfc,
	; this can be expressed as (temp_x - 1) > 0xfb
	DEY					;
	CPY #$FC            ;
	BCC :+              ;	if(temp_x-1 > 0xfb) temp_x = 1;
		LDY #$00        ;
	:                   ;__
	TYA
	SEC		; I decremented the Y, this is getting back at it
	ADC drawplayer_center_offsets, X
	STA sreg+0			;__ The X of oam_meta_spr is temp_x

	; The switch 
	LDX _gamemode
	DEX			;	case 0x01: ship shit
	jeq ship	;__
	DEX			;	case 0x02: ball shit
	jeq ball	;__
	DEX			;	case 0x03: ufo shit
	jeq ufo		;__
	DEX			;	case 0x04: robot shit
	jeq robot	;__
	DEX			;	case 0x05: spider shit
	jeq spider	;__
	dex			;	case 0x06: wave shit
	jeq	wave	;__	
	dex			;	case 0x07: swing shit
	jeq	ship	;__
	dex			;	case 0x08: NINJA
	jeq	cube	;__
	
	; default: cube
    cube:
		; C code:
			; 		if (player_vel_y[0] == 0) cube_rotate[0] = round to the nearest 90°;
			; 		else cube_rotate[0] += player_gravity[0] ? -CUBE_GRAVITY : CUBE_GRAVITY;
			; 		cap the mf at 0..23
		@rounding_table = drawcube_rounding_table

        BIT _cube_data
        BMI @round
		ldx _temptemp5			;player trails?
		bne	@fin			;if so, get out of here
		LDA _player_vel_y+1		;	if player_vel_y == 0
		ORA _player_vel_y+0		;
		BNE @no_round		    ;__
        @round:	    
			STA	_cube_rotate+0	;__ low_byte = 0
			.if USE_ILLEGAL_OPCODES
				LAX _cube_rotate+1	;	LAX abs is apparently stable
			.else
				LDA _cube_rotate+1
				TAX
			.endif
			SEC					;
			SBC #12				;
			BCC :+				;	Limit table idx to 0..12
				TAX				;	
				CLC				;
			:					;__
			LDA _cube_rotate+1	;	Round the cube rotation
			ADC @rounding_table, X
            STA _cube_rotate+1
			BIT _cube_data
            BPL :+
                LDY _slope_type
                CLC
                ADC rounding_slope_table-1, y
            : 
            TAX
            JMP @fin_nold

		@no_round:
		LDA _cube_rotate
		CLC

		LDX _player_gravity+0
		BNE @subtract

			ADC #<CUBE_GRAVITY      ;
			STA _cube_rotate        ;
			BCC @fin				;   cube_rotate[0] += CUBE_GRAVITY;
				LDX _cube_rotate+1	;
				INX					;__
				CPX #24				;
				BCC :+				;	Cap at 24
					LDX #00			;
				: STX _cube_rotate+1;__
				JMP @fin_nold

		@subtract:
			SBC #<CUBE_GRAVITY-1	; 	
			STA _cube_rotate		;
			BCS @fin				;	cube_rotate[0] -= CUBE_GRAVITY;
				DEC _cube_rotate+1	;
				BPL @fin			;__
				LDA #23				;	Cap at 0
				STA _cube_rotate+1	;__

		@fin:
			LDX _cube_rotate+1
        @fin_nold:
			LDA _gamemode
			cmp #8
			beq @noflip

			LDA _gameState
			cmp #1
			bne @normalicon
			LDA _titleicon
			jmp @domore
			
		@normalicon:
			LDA _icon

		@domore:
			cmp #$12
			beq @noflip
			cmp #$16
			beq @noflip
   			cmp #$0F
			beq @noflip
			cmp #2
			bne	@norm
			LDA drawcube_sprite_way, X
			jmp @don
		@norm:
			LDA drawcube_sprite_table, X
			jmp @don
		@noflip:
			LDA drawcube_sprite_none, X
			;jmp @don
			
		@don:
			TAX
			AND #$C0
			PHA
			lda _gameState
			cmp #1
			bne @continue
			pla
			ora #$20
			bne @resume
		@continue:
			PLA
		@resume:
			STA xargs+0	; flip setting
			TXA
			AND #$07
			TAY
			JMP fin

	ship:
		; C code:
			; 		cube_rotate[0] = 0x0400 - player_vel_y[0];
			; 		if (high_byte(cube_rotate) >= 0x08) {
			; 			cube_rotate[0]= high_byte(cube_rotate) >= 0x80 ? 0x0000 : 0x07FF;
			; 		}
		TXA						;(X = 0 as per JEQ)
		TAY						;
		sec						;
		sbc _player_vel_y		;	cube_rotate[0] = 0x0400 - player_vel_y[0];
		sta _cube_rotate		;	(Mostly generated by cc65 lmao)
		lda #$04				;
		sbc _player_vel_y+1		;
		; A has high byte of _cube_rotate
		CMP	#$08				;	if (high_byte(cube_rotate) >= 0x08) {
		BCC :++					;__
			CMP #$80			;	if (high_byte(cube_rotate) < 0x80)
			BCC	:+				;__
				LDY #$07		;	cube_rotate[0] = 0x07FF
				DEX				;__
			:					;__	else 0x0000 (Y and X still remain at 0)
			STX _cube_rotate	;__	Store low byte
			TYA					;
		:						;	Store high byte
		STA	_cube_rotate+1		;__
		
		; Frame index is high byte of _cube_rotate if gravity is 0, 
		;* and 7-high byte if gravity isn't 0
		LDX _player_gravity+0
		BEQ :+
			; 7 - A = -A + 7
			; -A = (A ^ 0xFF) + 1
			; 7 - A = (A ^ 0xFF) + 8
			EOR #$FF
			CLC
			ADC #$08
		:
		TAY
		JMP fin

	ball:
		; C code:
			; if (!mini) {
			;	[calls to oam] 
			; 			ballframe++;
			; 			if (ballframe > 7) { ballframe = 0; }
			;	}
		LDA _options
		and #$04  ;platformer
		beq	@ball2
		lda _player_vel_x
		bne @ball2
		lda #0
		ldy #0
		beq @donball
	@ball2:
		LDA _ballframe	;	Load index
		TAY				;__
		CLC				;	ballframe++;
		ADC #$01		;__
		AND #$07		;__	if (ballframe > 7) { ballframe = 0; }
		STA _ballframe	;__
	@donball:
		JMP fin

	ufo:
		; Real C code:
			; 		if (!player_gravity[0]) {
			; 			if (player_vel_y[0] == 0) kandotemp3[0] = 0;
			; 			else if (player_vel_y[0] > 0) kandotemp3[0] = 1;
			; 			else if (player_vel_y[0] < 0) kandotemp3[0] = 2;
			; 		}
			; 		else {
			; 			if (player_vel_y[0] == 0) kandotemp3[0] = 0;
			; 			else if (player_vel_y[0] > 0) kandotemp3[0] = 1;
			; 			else if (player_vel_y[0] < 0) kandotemp3[0] = 2;
			; 		}
			;	kandotemp3[0] used as index
		; Modified pseudo C code:
			;	kandotemp3[0] = 1;
			;	if (0 < highbyte < $80) {}	// do nothing with it
			;	else if ($80 ≤ highbyte ≤ $FF) {
			;		kandotemp3[0] = 2;
			;	} else if (highbyte == $00) {
			;		if (lowbyte == 0) kandotemp3[0] = 0;
			; 	}
		LDY #$1				;__	kandotemp3[0] = 1;
		LDA _player_vel_y+1	;__
		BEQ :+				;__	else if (highbyte == $00) { // later }
		BPL @go	    		;__	if (0 < highbyte < $80) {}	// do nothing with it
			INY				;__	else if ($80 ≤ highbyte ≤ $FF) { kandotemp3[0] = 2; }
			JMP fin			;__
		:
		ORA _player_vel_y	;	if (player_vel_y == 0)
		BNE @go				;__
		DEY					;	kandotemp3[0] = 0;
	@go:
		JMP fin				;__
	robot:
		; C code:
			;	if (player_vel_y[0] == 0) {
			;		[index from ROBOT/MINI_ROBOT using robotframe[0]]
			; 		robotframe[0]++;
			; 		if (robotframe[0] > 19) { robotframe[0] = 0; }	
			;	} else {
			;		[index from ROBOT_JUMP/MINI_ROBOT_JUMP using robotjumpframe[0]]
			; 	}
			LDA _was_on_slope_counter
			BNE @ignoreJump
			LDA _player_vel_y+1	;
			ORA _player_vel_y	;	if (player_vel_y[0] == 0) {
			BNE @jump			;__
		@ignoreJump:
			LDA _retro_mode
			BNE @jim
			LDA _options
			and #$04
			beq	@cont1
			LDA _player_vel_x
			bne @cont1
			lda #0
			sta _robotframe
			ldy #0
			jmp @fini
			
		@cont1:
			LDA #0
			LDY _robotframe	;	[load robotframe[0] into Y]
			SEC				;	robotframe[0]++; (A is 0, so set the carry and bam)
			ADC _robotframe	;__
			CMP #20			;
			BCC @hur			;	if (robotframe[0] > 19) { robotframe[0] = 0; }	
				LDA #$00	;__
			@hur:				;
			STA _robotframe	;__
		@fini:
			JMP fin
		@jump:				;	} else {
			LDA #21			; ! This is the sizeof ROBOT / MINI_ROBOT, change it as needed
			CLC				;	ROBOT_JUMP[X] = ROBOT[X+20]
			ADC _robotjumpframe
			TAY				;__
			JMP fin
		@jim:
			LDA #0
			LDY _robotframe	;	[load robotframe[0] into Y]
			SEC				;	robotframe[0]++; (A is 0, so set the carry and bam)
			ADC _robotframe	;__
			CMP #15			;
			BCC @JIMMOMENT	;	if (robotframe[0] > 14) { robotframe[0] = 0; }	
				LDA #$00	;__
			@JIMMOMENT:		;
			STA _robotframe	;__
			JMP fin

	spider:
		; C code:
			;	if (player_vel_y[0] == 0 ) {
			;		[index from SPIDER/MINI_SPIDER using spiderframe[0]]
			; 		spiderframe[0]++;
			; 		if (spiderframe[0] > 15) { spiderframe[0] = 0; }	
			;	} else {
			;		[use SPIDER_JUMP/MINI_SPIDER_JUMP[0]]
			; 	}
		LDA _player_vel_y+1	;
		ORA _player_vel_y	;	if (player_vel_y[0] == 0) {
		BNE @jump			;
			LDA _options
			and #$04
			beq	@cont1
			LDA _player_vel_x
			bne @cont1
			lda #0
			sta _spiderframe
			ldy #0
			jmp fin
			
		@cont1:
			LDA #0
			LDY _spiderframe	;	[load spiderframe[0] into Y]
			SEC				;	spiderframe[0]++; (A is 0, so set the carry and bam)
			ADC _spiderframe ;__
			AND #$0F        ;   if (spiderframe[0] > 15) spiderframe[0] = 0;
			STA _spiderframe;__
			JMP fin
		@jump:				;	} else { SPIDER_JUMP[0] = SPIDER[8]
			LDA #16			; ! This is the sizeof ROBOT / MINI_ROBOT, change it as needed
			CLC				;	ROBOT_JUMP[X] = ROBOT[X+20]
			ADC _robotjumpframe
			TAY				;__

			JMP fin

	wave:
		; C code:
			; 		cube_rotate[0] = 0x0400 - player_vel_y[0];
			; 		if (high_byte(cube_rotate) >= 0x08) {
			; 			cube_rotate[0]= high_byte(cube_rotate) >= 0x80 ? 0x0000 : 0x07FF;
			; 		}
		TXA						;(X = 0 as per JEQ)
		TAY						;
		sec						;
		sbc _player_vel_y		;	cube_rotate[0] = 0x0400 - player_vel_y[0];
		sta _cube_rotate		;	(Mostly generated by cc65 lmao)
		lda #$04				;
		sbc _player_vel_y+1		;
		; A has high byte of _cube_rotate
		CMP	#$08				;	if (high_byte(cube_rotate) >= 0x08) {
		BCC :++					;__
			CMP #$80			;	if (high_byte(cube_rotate) < 0x80)
			BCC	:+				;__
				LDY #$07		;	cube_rotate[0] = 0x07FF
				DEX				;__
			:					;__	else 0x0000 (Y and X still remain at 0)
			STX _cube_rotate	;__	Store low byte
			TYA					;
		:						;	Store high byte
		STA	_cube_rotate+1		;__
		
        ; Fix for speed greater than x3 being mirrored
        LDY _player_vel_x+1
        CPY #$04
        BCC :+
            ; 7 - A = -A + 7
			; -A = (A ^ 0xFF) + 1
			; 7 - A = (A ^ 0xFF) + 8
            LDY _mini
            BNE :+
			EOR #$FF
			CLC
			ADC #$08
        :

        ; Frame index is high byte of _cube_rotate if gravity is 0, 
		;* and 7-high byte if gravity isn't 0
		LDX _player_gravity+0
		BEQ :+
			; 7 - A = -A + 7
			; -A = (A ^ 0xFF) + 1
			; 7 - A = (A ^ 0xFF) + 8
			EOR #$FF
			CLC
			ADC #$08
		:
		TAY
		JMP fin



	fin:
    common:
		TYA					;
		ASL					;	Double da index cuz it's a table of shorts
		TAY					;__

		; ; CENTERING DEBUGGING ONLY
		; lda <FRAME_CNT1
		; and #$01
		; beq :+
		; 	lda #$40
		; : eor xargs+0
		; sta xargs+0


		LDA (ptr1), Y		;	Load low byte
		PHA					;__
		INY					;
		LDA (ptr1), Y		;	Load high byte
		TAX					;__
		PLA
		JMP __oam_meta_spr_flipped ;__	oam_meta_spr(temp_x, high_byte(player_y[0])-1, [whatever the fuck we set here]);

    sprite_table_table_lo:
        .byte <_CUBE, <_SHIP, <_BALL, <_UFO, <_ROBOT, <_SPIDER, <_WAVE, <_SWING, <_CUBE
        .byte <_MINI_CUBE, <_MINI_SHIP, <_MINI_BALL, <_MINI_UFO, <_MINI_ROBOT, <_MINI_SPIDER, <_MINI_WAVE, <_MINI_SWING, <_MINI_CUBE
    sprite_table_table_lo2:
        .byte <_CUBE, <_SHIP, <_BALL, <_UFO, <_ROBOT_ALT, <_SPIDER_ALT, <_WAVE, <_SWING, <_CUBE
        .byte <_MINI_CUBE, <_MINI_SHIP, <_MINI_BALL_ALT, <_MINI_UFO, <_MINI_ROBOT_ALT, <_MINI_SPIDER_ALT, <_MINI_WAVE, <_MINI_SWING_ALT, <_MINI_CUBE
    sprite_table_table_hi:
        .byte >_CUBE, >_SHIP, >_BALL, >_UFO, >_ROBOT, >_SPIDER, >_WAVE, >_SWING, >_CUBE
        .byte >_MINI_CUBE, >_MINI_SHIP, >_MINI_BALL, >_MINI_UFO, >_MINI_ROBOT, >_MINI_SPIDER, >_MINI_WAVE, >_MINI_SWING, >_MINI_CUBE
    sprite_table_table_hi2:
        .byte >_CUBE, >_SHIP, >_BALL, >_UFO, >_ROBOT_ALT, >_SPIDER_ALT, >_WAVE, >_SWING, >_CUBE
        .byte >_MINI_CUBE, >_MINI_SHIP, >_MINI_BALL_ALT, >_MINI_UFO, >_MINI_ROBOT_ALT, >_MINI_SPIDER_ALT, >_MINI_WAVE, >_MINI_SWING_ALT, >_MINI_CUBE

    rounding_slope_table:
		;     45v  22v  66v  45^  22^  66^  nothing
        .byte $09, $08, $09, $00, $03, $04, $08, $00
		.byte $09, $16, $1a, $00, $03, $1a, $17		;upsidedown
.endproc
drawplayer_common := _drawplayerone::common

; void drawplayertwo();
.segment "XCD_BANK_05"

.import _CUBE2, _SHIP2, _BALL2, _ROBOT2, _UFO2, _SPIDER2, _WAVE2, _SWING2
.import _MINI_CUBE2, _MINI_SHIP2, _MINI_BALL2, _MINI_ROBOT2, _MINI_UFO2, _MINI_SPIDER2, _MINI_WAVE2, _MINI_SWING2

.export _drawplayertwo
.proc _drawplayertwo


    LDX _cube_data+1
    LDA _slope_frames+1
    ORA _slope_type+1
    BEQ :+
        TXA
        ORA #%10000000
        BNE @skipClearBit
    :
        TXA
        AND #%01111111
    @skipClearBit:
    sta _cube_data+1
    
	LDA _player_gravity+1
	BEQ :+
		LDA #$80
	: STA xargs+0	; flip

	LDX _player_y+3		;
	DEX					;	The Y of oam_meta_spr is high_byte(player_y[1])-1
	STX sreg+1			;__

	; Set up base pointer for jump tables
	LDA _mini+1       ;
	BEQ :+          ;   Add 8 if mini mode 
		LDA #gamemode_count
	:               ;__
	CLC             ;   Actual gamemode itself
	ADC _gamemode   ;__
	PHA
	LDX _retro_mode
	BEQ :+
		ADC #gamemode_count*2	; ain't no way the last one overflowed
	:
	TAX
	LDA sprite_table_table_lo, X
	STA ptr1		;__	Get low byte of table ptr
	LDA sprite_table_table_hi, X
	STA ptr1+1		;__ Get high byte of table ptr
	PLA				;	Get pure gamemode number
	TAX				;__

	LDY _player_x+3     ;__ temp_x = high_byte(player_x[1]);
	; The condition if is temp_x == 0 or is > 0xfc,
	; this can be expressed as (temp_x - 1) > 0xfb
	DEY					;
	CPY #$FC            ;
	BCC :+              ;	if(temp_x-1 > 0xfb) temp_x = 1;
		LDY #$00        ;
	:                   ;__
	TYA
	SEC		; I decremented the Y, this is getting back at it
	ADC drawplayer_center_offsets, X
	STA sreg+0			;__ The X of oam_meta_spr is temp_x

	; The switch 
	LDX _gamemode
	DEX			;	case 0x01: ship shit
	jeq ship	;__
	DEX			;	case 0x02: ball shit
	jeq ball	;__
	DEX			;	case 0x03: ufo shit
	jeq ufo		;__
	DEX			;	case 0x04: robot shit
	jeq robot	;__
	DEX			;	case 0x05: spider shit
	jeq spider	;__
	dex			;	case 0x06: wave shit
	jeq	wave	;__	
	dex			;	case 0x07: swing shit
	jeq	ship	;__
	dex			;	case 0x08: NINJA
	jeq	cube	;__

    ; default: cube
    cube:
        ; C code:
			; 		if (player_vel_y[1] == 0) cube_rotate[1] = round to the nearest 90°;
			; 		else cube_rotate[1] += player_gravity[1] ? -CUBE_GRAVITY : CUBE_GRAVITY;
			; 		cap the mf at 0..23
		@rounding_table = drawcube_rounding_table

        BIT _cube_data+1
        BMI @round
	;	ldx _temptemp5		;PLAYER TRAILS are disabled for 2 player mode anyway
	;	bne	@fin		

		LDA _player_vel_y+3		;	if player_vel_y == 0
		ORA _player_vel_y+2		;
		BNE @no_round			;__
		@round:
			STA	_cube_rotate+2	;__ low_byte = 0
			.if USE_ILLEGAL_OPCODES
				LAX _cube_rotate+3	;	LAX abs is apparently stable
			.else
				LDA _cube_rotate+3	;
				TAX
			.endif
			SEC					;
			SBC #12				;
			BCC :+				;	Limit table idx to 0..12
				TAX				;	
				CLC				;
			:					;__
			LDA _cube_rotate+3	;	Round the cube rotation
			ADC @rounding_table, X
			STA _cube_rotate+3	;
			BIT _cube_data+1
			BPL :+
				LDY _slope_type+1
				CLC
				ADC rounding_slope_table-1, y
			: 
			TAX					;__
			JMP @fin_nold

		@no_round:
		LDA _cube_rotate+2
		CLC

		LDX _player_gravity+1
		BNE @subtract

			ADC #<CUBE_GRAVITY      ;
			STA _cube_rotate+2		;
			BCC @fin				;   cube_rotate[0] += CUBE_GRAVITY;
				LDX _cube_rotate+3	;
				INX					;__
				CPX #24				;
				BCC :+				;	Cap at 24
					LDX #00			;
				: STX _cube_rotate+3;__
				JMP @fin_nold

		@subtract:
			SBC #<CUBE_GRAVITY-1	; 	
			STA _cube_rotate+2		;
			BCS @fin				;	cube_rotate[0] -= CUBE_GRAVITY;
				DEC _cube_rotate+3	;
				BPL @fin			;__
				LDA #23				;	Cap at 0
				STA _cube_rotate+3	;__

		@fin:
			LDX _cube_rotate+3
        @fin_nold:
			LDA _gamemode
			cmp #8
			beq @noflip	
			LDA _icon
			cmp #$12
			beq @noflip
			cmp #$16
			beq @noflip
   			cmp #$0F
			beq @noflip
			cmp #2
			bne	@norm
			LDA drawcube_sprite_way, X
			jmp @don
		@norm:
			LDA drawcube_sprite_table, X
			jmp @don
		@noflip:
			LDA drawcube_sprite_none, X
			;jmp @don
			
		@don:
			TAX
			AND #$C0
			STA xargs+0
			TXA
			AND #$07
			TAY
			JMP drawplayer_common

	ship:
		; C code:
			; 		cube_rotate[1] = 0x0400 - player_vel_y[1];
			; 		if (high_byte(cube_rotate) >= 0x08) {
			; 			cube_rotate[1]= high_byte(cube_rotate) >= 0x80 ? 0x0000 : 0x07FF;
			; 		}
		TXA						;(X = 0 as per JEQ)
		TAY						;
		sec						;
		sbc _player_vel_y+2		;	cube_rotate[1] = 0x0400 - player_vel_y[1];
		sta _cube_rotate+2		;	(Mostly generated by cc65 lmao)
		lda #$04				;
		sbc _player_vel_y+3		;
		; A has high byte of _cube_rotate
		CMP	#$08				;	if (high_byte(cube_rotate) >= 0x08) {
		BCC :++					;__
			CMP #$80			;	if (high_byte(cube_rotate) < 0x80)
			BCC	:+				;__
				LDY #$07		;	cube_rotate[1] = 0x07FF
				DEX				;__
			:					;__	else 0x0000 (Y and X still remain at 0)
			STX _cube_rotate+2	;__	Store low byte
			TYA					;
		:						;	Store high byte
		STA	_cube_rotate+3		;__
		
		; Frame index is high byte of _cube_rotate if gravity is 0, 
		;* and 7-high byte if gravity isn't 0
		LDX _player_gravity+1
		BEQ :+
			; 7 - A = -A + 7
			; -A = (A ^ 0xFF) + 1
			; 7 - A = (A ^ 0xFF) + 8
			EOR #$FF
			CLC
			ADC #$08
		:
		TAY
		JMP drawplayer_common
	ball:
		; C code:
			; if (!mini) {
			;	[calls to oam] 
			; 			ballframe++;
			; 			if (ballframe > 7) { ballframe = 0; }
			;	}
		; LDA _ballframe	;	Load index
		; TAY				;__
		; CLC				;	ballframe++;
		; ADC #$01			;__
		; AND #$07			;__	if (ballframe > 7) { ballframe = 0; }
		; STA _ballframe	;__
		lda _options
		and #$04
		beq	@continue
		lda _player_vel_x
		bne @continue
		lda #0
		ldy #0
		jmp drawplayer_common
	@continue:
		LDY _ballframe
		JMP drawplayer_common
	ufo:
		; Real C code:
			; 		if (!player_gravity[1]) {
			; 			if (player_vel_y[1] == 0) kandotemp3[1] = 0;
			; 			else if (player_vel_y[1] > 0) kandotemp3[1] = 1;
			; 			else if (player_vel_y[1] < 0) kandotemp3[1] = 2;
			; 		}
			; 		else {
			; 			if (player_vel_y[1] == 0) kandotemp3[1] = 0;
			; 			else if (player_vel_y[1] > 0) kandotemp3[1] = 1;
			; 			else if (player_vel_y[1] < 0) kandotemp3[1] = 2;
			; 		}
			;	kandotemp3[1] used as index
		; Modified pseudo C code:
			;	kandotemp3[1] = 1;
			;	if (0 < highbyte < $80) {}	// do nothing with it
			;	else if ($80 ≤ highbyte ≤ $FF) {
			;		kandotemp3[1] = 2;
			;	} else if (highbyte == $00) {
			;		if (lowbyte == 0) kandotemp3[1] = 0;
			; 	}

		LDY #$1				;__	kandotemp3[1] = 1;
		LDA _player_vel_y+3	;__
		BEQ :+				;__	else if (highbyte == $00) { // later }
		BPL @fin		    ;__	if (0 < highbyte < $80) {}	// do nothing with it
			INY				;__	else if ($80 ≤ highbyte ≤ $FF) { kandotemp3[1] = 2; }
			JMP drawplayer_common	    ;__
		:
		ORA _player_vel_y+2	;	if (lowbyte == 0) kandotemp3[1] = 0;
		BNE @fin			;
			DEY				;	kandotemp3[1] = 0;
		@fin:
			JMP drawplayer_common    	;__
	robot:
		; C code:
			;	if (player_vel_y[1] == 0 || player_vel_y[1] == CUBE_GRAVITY) {
			;		[index from ROBOT/MINI_ROBOT using robotframe[1]]
			; 		robotframe[1]++;
			; 		if (robotframe[1] > 19) { robotframe[1] = 0; }	
			;	} else {
			;		[index from ROBOT_JUMP/MINI_ROBOT_JUMP using robotjumpframe[1]]
			; 	}
			LDA _was_on_slope_counter+1
			BNE @ignoreJump
			LDA _player_vel_y+3	;
			ORA _player_vel_y+2	;	if (player_vel_y[1] == 0 || player_vel_y[1] == CUBE_GRAVITY) {
			BNE @jump
		@ignoreJump:
			LDA _options
			and #$04
			beq	@cont1
			LDA _player_vel_x+2
			bne @cont1
			lda #0
			sta _robotframe
			ldy #0
			jmp @fini
			
		@cont1:
			LDA #0
			LDY _robotframe	;	[load robotframe[0] into Y]
			SEC				;	robotframe[0]++; (A is 0, so set the carry and bam)
			ADC _robotframe	;__
			CMP #20			;
			BCC @hur			;	if (robotframe[0] > 19) { robotframe[0] = 0; }	
				LDA #$00	;__
			@hur:				;
			STA _robotframe	;__
		@fini:
			JMP drawplayer_common
		@jump:				;	} else {
			LDA #21			; ! This is the sizeof ROBOT / MINI_ROBOT, change it as needed
			CLC				;	ROBOT_JUMP[X] = ROBOT[X+20]
			ADC _robotjumpframe
			TAY				;__
			JMP drawplayer_common
	spider:
		; C code:
			;	if (player_vel_y[1] == 0 || player_vel_y[1] == CUBE_GRAVITY) {
			;		[index from SPIDER/MINI_SPIDER using spiderframe[1]]
			; 		spiderframe[1]++;
			; 		if (spiderframe[1] > 15) { spiderframe[1] = 0; }	
			;	} else {
			;		[use SPIDER_JUMP/MINI_SPIDER_JUMP[0]]
			; 	}
		LDA _player_vel_y+3	;
		ORA _player_vel_y+2	;	if (player_vel_y[1] == 0 || player_vel_y[1] == CUBE_GRAVITY) {
		BNE @jump	    	;__
			LDA _options
			and #$04
			beq	@cont1
			LDA _player_vel_x
			bne @cont1
			lda #0
			sta _spiderframe
			ldy #0
			jmp drawplayer_common
			
		@cont1:
			LDA #0
			LDY _spiderframe+1;	[load spiderframe[1] into Y] 
			SEC				;	spiderframe[1]++; (A is 0, so set the carry and bam)
			ADC _spiderframe+1;__
			AND #$0F        ;   if (spiderframe[1] > 15) spiderframe[1] = 0;
			STA _spiderframe+1;__
			JMP drawplayer_common
		@jump:				;	} else { SPIDER_JUMP[0] = SPIDER[8]
			LDA #16			; ! This is the sizeof ROBOT / MINI_ROBOT, change it as needed
			CLC				;	ROBOT_JUMP[X] = ROBOT[X+20]
			ADC _robotjumpframe
			TAY				;__

			JMP drawplayer_common
	wave:
		; C code:
			; 		cube_rotate[1] = 0x0400 - player_vel_y[1];
			; 		if (high_byte(cube_rotate) >= 0x08) {
			; 			cube_rotate[1]= high_byte(cube_rotate) >= 0x80 ? 0x0000 : 0x07FF;
			; 		}
		TXA						;(X = 0 as per JEQ)
		TAY						;
		sec						;
		sbc _player_vel_y+2		;	cube_rotate[1] = 0x0400 - player_vel_y[1];
		sta _cube_rotate+2		;	(Mostly generated by cc65 lmao)
		lda #$04				;
		sbc _player_vel_y+3		;
		; A has high byte of _cube_rotate
		CMP	#$08				;	if (high_byte(cube_rotate) >= 0x08) {
		BCC :++					;__
			CMP #$80			;	if (high_byte(cube_rotate) < 0x80)
			BCC	:+				;__
				LDY #$07		;	cube_rotate[1] = 0x07FF
				DEX				;__
			:					;__	else 0x0000 (Y and X still remain at 0)
			STX _cube_rotate+2	;__	Store low byte
			TYA					;
		:						;	Store high byte
		STA	_cube_rotate+3		;__
		
        ; Fix for speed greater than x3 being mirrored
        LDY _player_vel_x+1
        CPY #$04
        BCC :+
            ; 7 - A = -A + 7
			; -A = (A ^ 0xFF) + 1
			; 7 - A = (A ^ 0xFF) + 8
            LDY _mini+1
            BNE :+
			EOR #$FF
			CLC
			ADC #$08
        :
		; Frame index is high byte of _cube_rotate if gravity is 0, 
		;* and 7-high byte if gravity isn't 0
		LDX _player_gravity+1
		BEQ :+
			; 7 - A = -A + 7
			; -A = (A ^ 0xFF) + 1
			; 7 - A = (A ^ 0xFF) + 8
			EOR #$FF
			CLC
			ADC #$08
		:
		TAY
		JMP drawplayer_common
	sprite_table_table_lo:
		.byte <_CUBE2, <_SHIP2, <_BALL2, <_UFO2, <_ROBOT2, <_SPIDER2, <_WAVE2, <_SWING2, <_CUBE2
		.byte <_MINI_CUBE2, <_MINI_SHIP2, <_MINI_BALL2, <_MINI_UFO2, <_MINI_ROBOT2, <_MINI_SPIDER2, <_MINI_WAVE2, <_MINI_SWING2, <_MINI_CUBE2
    sprite_table_table_lo2:
        .byte <_CUBE2, <_SHIP2, <_BALL2, <_UFO2, <_ROBOT_ALT2, <_SPIDER_ALT2, <_WAVE2, <_SWING2, <_CUBE2
        .byte <_MINI_CUBE2, <_MINI_SHIP2, <_MINI_BALL_ALT, <_MINI_UFO2, <_MINI_ROBOT_ALT, <_MINI_SPIDER_ALT, <_MINI_WAVE2, <_MINI_SWING_ALT, <_MINI_CUBE2
	sprite_table_table_hi:
		.byte >_CUBE2, >_SHIP2, >_BALL2, >_UFO2, >_ROBOT2, >_SPIDER2, >_WAVE2, >_SWING2, <_CUBE2
		.byte >_MINI_CUBE2, >_MINI_SHIP2, >_MINI_BALL2, >_MINI_UFO2, >_MINI_ROBOT2, >_MINI_SPIDER2, >_MINI_WAVE2, >_MINI_SWING2, <_MINI_CUBE2
    sprite_table_table_hi2:
        .byte >_CUBE2, >_SHIP2, >_BALL2, >_UFO2, >_ROBOT_ALT2, >_SPIDER_ALT2, >_WAVE2, >_SWING2, <_CUBE2
        .byte >_MINI_CUBE2, >_MINI_SHIP2, >_MINI_BALL_ALT, >_MINI_UFO2, >_MINI_ROBOT_ALT, >_MINI_SPIDER_ALT, >_MINI_WAVE2, >_MINI_SWING_ALT, <_MINI_CUBE2
    rounding_slope_table:
		;     45v  22v  66v  45^  22^  66^  nothing
        .byte $09, $08, $09, $00, $03, $04, $08, $00
		.byte $09, $16, $1a, $00, $03, $1a, $17		;upsidedown


.endproc

; char bg_collision_sub();
.segment "CODE_2"

.importzp _temp_x, _temp_y, _temp_room, _collision

.export _bg_collision_sub
.proc _bg_collision_sub
    ; Returns collision block indexed by
	; temp_x for X
	; temp_room and y for Y
    LDA _temp_y     ;
    CMP #$F0        ;   if(temp_y >= 0xf0) return 0;
    BCS Return0		;__
    AND #$F0        ;	temp_y & 0xF0
    STA tmp1        ;__
	LDA _temp_x		;
	LSR				;
	LSR				;	temp_x >> 4
	LSR				;
	LSR				;__
	ORA tmp1		;	coordinates = (temp_x >> 4) + ((temp_y) & 0xf0);
	TAY				;__

	LDA _temp_room	;	tmp3 = temp_room&3;
	AND #$03		;__
	ORA #>collMap0
	STA ptr1+1
	LDA #$00
	STA ptr1

	.if USE_ILLEGAL_OPCODES
		LAX (ptr1),Y
	.else
		LDA (ptr1),Y
		TAX
	.endif
	LDA metatiles_coll,X	;	return is_solid[collision];
	STA _collision	;
	RTS				;__

	Return0:
	LDA #$00
	sta _collision
	RTS

.endproc

.segment "CODE_2"

.export crossPRGBankJump
.proc crossPRGBankJump
	; AX = address of function
	; Y = bank of function
	STA ptr4
	STX ptr4+1
	LDA mmc3PRG1Bank
	PHA
	TYA
	JSR mmc3_set_prg_bank_1
	LDA ptr3
	LDX ptr3+1
	JSR callptr4
	STA ptr3
	STX ptr3+1
	PLA
	JMP mmc3_set_prg_bank_1
.endproc

; void __fastcall__ playPCM(uint8_t sample);
.segment "XCD_BANK_00"
SSDPCM_ptr = ptr1
SSDPCM_bank_num = tmp1
SSDPCM_amp = tmp2
SSDPCM_wait = tmp3
SSDPCM_delta_add = ptr2

SSDPCM_luts:
.repeat 256, I
	.byte ((I>>6)&3)
.endrepeat 
.repeat 256, I
	.byte ((I>>4)&3)
.endrepeat 
.repeat 256, I
	.byte ((I>>2)&3)
.endrepeat 
.repeat 256, I
	.byte ((I>>0)&3)
.endrepeat 

SSDPCM_amps:
.repeat 64, I
	.byte (-1*I)&$ff
	.byte (0*I)&$ff
	.byte (1*I)&$ff
	.byte (2*I)&$ff
.endrepeat

SSDPCM_amplo:
.repeat 64, I
	.lobytes SSDPCM_amps+(I*4) 
.endrepeat
SSDPCM_amphi:
.repeat 64, I
	.hibytes SSDPCM_amps+(I*4) 
.endrepeat

.export _playPCM
.proc _playPCM
    ; A = Sample
	tay
	ldx	NTSC_MODE
	bne :+
		clc
		adc #(SampleRate_PAL-SampleRate_NTSC)
	:
	tax
	lda SampleRate_NTSC, x
    sta SSDPCM_wait
	ldx Bank, y

    lda #128
    sta SSDPCM_amp
    ;enable DMC but disable DPCM
    lda #%00000000
    sta FAMISTUDIO_APU_DMC_FREQ
    lda #%00001011
    sta FAMISTUDIO_APU_SND_CHN
    lda #0
	sta SSDPCM_ptr
    sta FAMISTUDIO_APU_DMC_LEN
    lda #%00011011
    sta FAMISTUDIO_APU_SND_CHN
    ; mute sqs+noi
    lda #$30
    sta FAMISTUDIO_APU_NOISE_VOL
    lda #%00110000
    sta FAMISTUDIO_APU_PL1_VOL
    sta FAMISTUDIO_APU_PL2_VOL
    ;init pcm
 	ldy #0

    lda #>$BFFF		;	2
    sta SSDPCM_ptr+1	;__	3
    lda #<$BFFF		;	2
    sta SSDPCM_ptr	;__	3

    txa		;__	2
    jsr mmc3_set_prg_bank_0	;__	35

    ;play pcm
@RestartPtr:
	jsr SSDPCM_getbyte
	tax
	lda SSDPCM_amplo, x
	sta SSDPCM_delta_add
	lda SSDPCM_amphi, x
	sta SSDPCM_delta_add+1
	cpx #$ff
	bne :+
    jmp @DoneWithPCM
:
.repeat 128/4
	jsr SSDPCM_dobyte
.endrepeat
	jmp @RestartPtr


@DoneWithPCM:
    lda #%00011111
    sta FAMISTUDIO_APU_SND_CHN
    lda #<FIRST_DMC_BANK
	jmp mmc3_set_prg_bank_0


SSDPCM_dobyte:
    jsr SSDPCM_getbyte
	tax
	ldy SSDPCM_luts, x ; 4
	lda SSDPCM_amp ; 2
	clc ; 2
	adc (SSDPCM_delta_add), y ; 5
	sta SSDPCM_amp ; 3
	lsr ; 2
	jsr SSDPCM_store_pcm ; 6

	ldy SSDPCM_luts+256, x
	lda SSDPCM_amp
	clc
	adc (SSDPCM_delta_add), y
	sta SSDPCM_amp
	lsr
	jsr SSDPCM_store_pcm

	ldy SSDPCM_luts+512, x
	lda SSDPCM_amp
	clc
	adc (SSDPCM_delta_add), y
	sta SSDPCM_amp
	lsr
	jsr SSDPCM_store_pcm

	ldy SSDPCM_luts+768, x
	lda SSDPCM_amp
	clc
	adc (SSDPCM_delta_add), y
	sta SSDPCM_amp
	lsr
	jsr SSDPCM_store_pcm
	rts


SSDPCM_store_pcm:
    ; 4+2+5+2+3+2+6 = 24 cycles
    sta $4011 ; 4
    nop
    nop
    nop
    lda SSDPCM_wait	; 3 
    sec
@Delay:
	sbc #1		;	5n cycles
	bcs @Delay	;__
    rts

SSDPCM_getbyte:
 inc SSDPCM_ptr
 bne @g1
 inc SSDPCM_ptr+1
@g1:
 lda SSDPCM_ptr
 cmp #$00
 bne @g2
 lda SSDPCM_ptr+1
 cmp #$C0+$20
 bne @g2

 lda #$80
 sta SSDPCM_ptr+1
 lda SSDPCM_getbyte
 pha
 inc SSDPCM_getbyte
 pla
 jsr mmc3_set_prg_bank_0

@g2:
 ldy #0
 lda (SSDPCM_ptr), y
 rts

; BurnCycles:	; 6 for JSR
;     php	;	7
;     plp	;__
;     php	;	7
;     plp	;__
;     rts	;	6

; Sample rate calculations go per this formula:
; ((Region Clock / Sample Rate)-Sample Load Time)/5
; Sample Load Time is:
; 58 cycles?
; A reverse calculation is:
; Region Clock / ((Ans)*5+Sample Load Time)
; The target sample speed is specified after each value,
; Real playback speed and deviation percentage are specified in parentheses
; TODO: get proper sample calculations for SSDPCM2
.include "MUSIC/EXPORTS/pcm_metadata.s"

.endproc

; uint16_t hexToDec (uint16_t input)
.segment "CODE_2"

.export _hexToDec
.proc _hexToDec
	; AX = input
	; hexToDecOutputBuffer = output
	; AX = duplicate output

	; Step 1. loop over X and add 256
	start:
		INX			; for BEQ ending condition
		STX tmp1
		LDY #0		; for storing when overflows
		STY hexToDecOutputBuffer+2
		STY hexToDecOutputBuffer+3
		STY hexToDecOutputBuffer+4
	
	clr_x_loop:
		LDX #0
	loop:
		SEC
		SBC #10
		BCS :+
			DEC tmp1
			BEQ end
		:
		INX
		CPX #10
		BNE loop	; carry is always clear

		INC hexToDecOutputBuffer+2
		CPX hexToDecOutputBuffer+2	; if 10 == out[2]
		BNE clr_x_loop
		STY hexToDecOutputBuffer+2

		INC hexToDecOutputBuffer+3
		CPX hexToDecOutputBuffer+3	; if 10 == out[3]
		BNE clr_x_loop
		STY hexToDecOutputBuffer+3

		INC hexToDecOutputBuffer+4
		BNE clr_x_loop	; BRA

	end:
		; Carry is clear
		ADC #10
		STA hexToDecOutputBuffer+0
		STX hexToDecOutputBuffer+1
		RTS
.endproc



; void printDecimal (uintptr_t ppu_address, uint16_t value, uint8_t digits, uint8_t zeroChr, uint8_t spaceChr)
.segment "CODE_2"

.export __printDecimal
.proc __printDecimal
	; AX = ppu_address
	; sreg = value
	; xargs[0] = digits
	; xargs[1] = zeroChr
	; xargs[2] = spaceChr
	value = sreg
	digits = xargs+0
	zeroChr = xargs+1
	spaceChr = xargs+2

	start:
		LDY VRAM_INDEX
		STA VRAM_BUF+1, Y	;
		TXA					;	VRAM pointer
		STA VRAM_BUF+0, Y	;__
		LDA digits			;	Length
		STA VRAM_BUF+2, Y	;__
		CLC					;
		ADC VRAM_INDEX		;	Update VRAM index
		ADC #3				;__
		PHA					;
		TAY					;
		LDA #$FF			;	Mark section as taken
		STA VRAM_BUF, Y		;__

		LDA value			;
		LDX value+1			;	Convert to decimal
		JSR _hexToDec		;__

		LDY VRAM_INDEX

		LDX digits
		DEX
		BEQ numberLoop

	spaceLoop:
		LDA hexToDecOutputBuffer, X
		BNE numberStart
		LDA spaceChr
		STA VRAM_BUF+3, Y
		INY
		DEX
		BNE spaceLoop

		; Fallthrough on the last digit
	numberLoop:
		LDA hexToDecOutputBuffer, X
	numberStart:
		CLC
		ADC zeroChr
		STA VRAM_BUF+3, Y
		INY
		DEX
		BPL numberLoop

	end:
		PLA
		STA VRAM_INDEX
		RTS

.endproc

.segment "CODE_2"

; void update_level_completeness();
.segment "CODE_2"

.import _level, _practice_point_count
.import _level_completeness_normal

.export _update_level_completeness
.proc _update_level_completeness
	levelsInTable = ::_MAX_LEVEL_COMPLETE

	levelLengthLo = ptr1+0
	levelLengthMd = ptr1+1
	levelLengthHi = tmp1

	percentage = tmp2

	start:
		LDY	_level
		LDA	_level_lengths_lo, Y
		STA levelLengthLo
		.if MID_LEVEL_LENGTHS_ENABLED
			LDA _level_lengths_md, Y
			STA levelLengthMd
		.endif
		.if HIGH_LEVEL_LENGTHS_ENABLED
			LDA _level_lengths_hi, Y
			STA levelLengthHi
		.endif

		LDY #$FF
		.if MID_LEVEL_LENGTHS_ENABLED
			STY percentage
		.endif

		LDA _scroll_x+3
		STA sreg+1
		LDA _scroll_x+2
		STA sreg+0
		LDX _scroll_x+1
		.if MID_LEVEL_LENGTHS_ENABLED
			LDY _scroll_x+0
		.else
			LDA _scroll_x+0
		.endif

		; Adjust for BEQ ending condition
		INC sreg+1
		.if !HIGH_LEVEL_LENGTHS_ENABLED
			INC sreg+0
		.endif
		.if !MID_LEVEL_LENGTHS_ENABLED
			INX
		.endif

	loop_sec:
		.if MID_LEVEL_LENGTHS_ENABLED
			TYA
		.endif
		SEC
	loop:
		.if MID_LEVEL_LENGTHS_ENABLED
			INC percentage
		.else
			INY
		.endif
		SBC	levelLengthLo
		BCS loop

		.if MID_LEVEL_LENGTHS_ENABLED
			TAY
			TXA
			SBC levelLengthMd
			TAX
			BCS loop_sec
		.else
			DEX
			BNE loop_sec
		.endif

		.if HIGH_LEVEL_LENGTHS_ENABLED
			LDA sreg+0
			SBC levelLengthHi
			STA sreg+0
			BCS loop_sec
		.else
			DEC	sreg+0
			BNE loop_sec
		.endif

		DEC sreg+1
		BNE loop_sec

	fin:

		.if MID_LEVEL_LENGTHS_ENABLED
			LDY percentage
		.endif

		CPY #99			;
		BCC :+			;	Cap at 99
			LDY #99		;	100% is reserved for complete levels only
		:				;__

		LDA _practice_point_count	;
		BEQ :+					;
			LDA #levelsInTable	;	Calculate whether to store 
		:						;	the new completeness in the
		CLC						;	normal or practice table
		ADC _level				;
		TAX						;__

		TYA						;
		CMP _level_completeness_normal, X
		BCC :+					;	Update value if bigger than last one
			STA _level_completeness_normal, X
		:						;__
		RTS

.endproc

; [Not used in C]
.segment "CODE"

.import	__DATA_LOAD__,	__DATA_RUN__,	__DATA_SIZE__,	__DATA_LOAD_BANK__

.global copydata
.proc copydata

	seg_count = 1

	current_area = tmp1
	current_bank = tmp2

	src = sreg
	dest = xargs+0

	start:
		lda	#0
		sta	current_bank
		ldy	#<seg_count

	loop:
		lda	load_lo-1,	y
		sta	src+0
		lda	load_hi-1,	y
		sta	src+1
		
		lda	run_lo-1,	y
		sta	dest+0
		lda	run_hi-1,	y
		sta	dest+1

		lda	bank-1,	y
		beq	@no_bankswitch
			cmp	current_bank
			beq	@no_bankswitch
				jsr	mmc3_tmp_prg_bank_1	; only allowed because this is run on init
				sta	current_bank
		@no_bankswitch:

		lda	size_lo-1,	y
		ldx	size_hi-1,	y
		sty	current_area
		jsr	__memcpy

		ldy	current_area
		dey
		bne	loop

	rts

load_lo:
	.byte	<__DATA_LOAD__
load_hi:
	.byte	>__DATA_LOAD__

run_lo:
	.byte	<__DATA_RUN__
run_hi:
	.byte	>__DATA_RUN__

size_lo:
	.byte	<__DATA_SIZE__
size_hi:
	.byte	>__DATA_SIZE__

bank:
	.byte	<__DATA_LOAD_BANK__

.endproc


; void increment_attempt_count();
.segment "XCD_BANK_00"

.import _attemptCounter

.export _increment_attempt_count
.proc _increment_attempt_count
	; This can be totally made into a generic routine, just ping @alexmush (but itll be less optimized)
	ldy #10	; the number limit
	lda #0	; store if overflows
		
	inc _attemptCounter+0	;	attemptCounter[0]++;
	cpy _attemptCounter+0	;	if (10 == attemptCounter[0]) {
	bne finish				;		(Note the Yoda notation, sorta reflects the cpy)
	sta _attemptCounter+0	;__		attemptCounter[0] = 0;

	inc _attemptCounter+1	;		attemptCounter[1]++;
	cpy _attemptCounter+1	;		if (10 == attemptCounter[1]) {
	bne finish				;			attemptCounter[2] = 0;
	sta _attemptCounter+1	;__	and so on until digit 7

	inc _attemptCounter+2
	cpy _attemptCounter+2
	bne finish
	sta _attemptCounter+2
	
	inc _attemptCounter+3
	cpy _attemptCounter+3
	bne finish
	sta _attemptCounter+3

	inc _attemptCounter+4
	cpy _attemptCounter+4
	bne finish
	sta _attemptCounter+4

	inc _attemptCounter+5
	cpy _attemptCounter+5
	bne finish
	sta _attemptCounter+5

	inc _attemptCounter+6	; No checks here lmao (can be added tho)
	
	finish:
	rts
.endproc


; void display_attempt_counter (uint8_t zeroChr, uintptr_t ppu_address);
.segment "XCD_BANK_06"	; Same as state_lvldone	

.import _attemptCounter

.export __display_attempt_counter
.proc __display_attempt_counter
	; AX = ppu_address
	; sreg[0] = zeroChr
	zeroChr = sreg

	start:
		pha		; temp storage
		ldy #7	; size of _attemptCounter

	numsize_loop:
		dey
		beq	use_one_vram_buffer	; If Y decrements to 0, we are just printing the last digit
		lda	_attemptCounter, y
		beq	numsize_loop

		; now we have the (amount of digits to print - 1) in Y
	vram_write_header:
		sty	tmp1

		txa					;
		ora	#$40			;	NT_UPD_HORZ
		ldx	VRAM_INDEX		;
		sta	VRAM_BUF+0,	x	;	Calculate the vram address of the leftmost digit
		pla					;	and store in the buffer
		sec					;
		sbc	tmp1			;
		sta	VRAM_BUF+1,	x	;__
		iny					;
		tya					;	The amount of bytes needs to be incremented
		sta	VRAM_BUF+2,	x	;__

		clc
	vram_write_main:
		lda	_attemptCounter-1, y
		; clc should not be needed as the writes SHOULD NOT overflow
		adc	zeroChr
		sta	VRAM_BUF+3,	x
		inx
		dey
		bne vram_write_main

	vram_write_finish:
		lda	#$FF
		sta	VRAM_BUF+3,	x
		txa
		clc
		adc	#3
		sta	VRAM_INDEX
		rts

	use_one_vram_buffer:
		lda	_attemptCounter+0

		clc
		adc	zeroChr
		sta	sreg	; doesn't matter, it's not used anymore anyway

		; X has remained the same high byte of PPU address
		; A has to be recovered rq
		pla

		jmp	__one_vram_buffer
.endproc


; void draw_dialog_box(const char * data);
.segment "XCD_BANK_02"

.import popax	; Unfortunately
.import _paletteSettings
.import _DialogBox

.export _draw_dialog_box
.proc _draw_dialog_box
	dataPtr = ptr1
	vramPtr = ptr2

start:
	sta	dataPtr			;	Store the data pointer
	stx	dataPtr+1		;__

	ldy	#$20						;
	sty	PPU_ADDR					;
	ldy	#$00						;
	sty	PPU_ADDR					;	Unrle the base dialog box to nametable A
	lda	#<_DialogBox				;
	ldx	#>_DialogBox				;
	jsr	_vram_unrle					;__

	lda	#<_paletteSettings	;
	ldx	#>_paletteSettings	;	Load the correct palette
	jsr	_pal_bg				;__

	lda	#$20			;
	sta	vramPtr+1		;
	sta	PPU_ADDR		;	Store the upper left corner
	lda	#$C5			;	as the VRAM address
	sta	vramPtr			;
	sta	PPU_ADDR		;__

	ldy	dataPtr			;
	lda	#$00			;	Index with Y
	sta	dataPtr			;__

get_symbol:
	lda	(dataPtr),	y	;__	Load symbol
	iny					;
	bne :+				;	Increment data pointer
		inc	dataPtr+1	;
	:					;__
	cmp	#$10			;	If the symbol < $10,
	bcc	control_code	;__	it's a control code
regular_symbol:			;	If it is not, store
	sta	PPU_DATA		;__	the symbol to the PPU
	inc	vramPtr			;
	bne	get_symbol		;	Increment the VRAM ptr
	inc	vramPtr+1		;
	bne	get_symbol		;__ = BRA

control_code:
	sbc	#$0B-1		;__	Subtract maximum real control code, carry is clear
	jeq	vert_skip	;__	\v - skip some lines down
	tax				;
	inx				;	\n - newline
	beq	newline		;__
	inx				;	\t - skip some chars forward
	beq	space		;__
	inx				;	\b - fill line with black space
	beq	black_line	;__
	inx				;	\a - include a substring
	beq	recurse		;__
	rts				;__	Any other control code terminates the routine

newline:
	lda	vramPtr
	ldx	vramPtr+1
	adc	#$20-1		;__	Carry is set
	and	#$E0
	ora	#$05
	sta	vramPtr
	bcc	:+
		inx
		stx	vramPtr+1
	:
	stx	PPU_ADDR
	sta	PPU_ADDR
	bne	get_symbol

space:
	lda	(dataPtr), y	;
	iny
	bne	:+
		inc	dataPtr+1
	:
	
	ldx	vramPtr+1

	clc
	adc	vramPtr
	bcc	:+
		inx
		stx	vramPtr+1
	:
	stx	PPU_ADDR
	sta	vramPtr
	sta	PPU_ADDR
	jmp	get_symbol

black_line:
	ldx	vramPtr+1
	lda	vramPtr
	and	#$E0
	ora	#$05
	sta	vramPtr

	stx	PPU_ADDR
	sta	PPU_ADDR

	ldx	#22
	lda	#$FE

	@loop:
		sta	PPU_DATA
		dex
		bne	@loop

	ldx	vramPtr+1
	lda	vramPtr
	stx	PPU_ADDR
	sta	PPU_ADDR
	jmp	get_symbol

recurse:
	lda	dataPtr+1	;
	pha				;	Push the old data
	tya				;	to hardware stack
	pha				;__

	jsr	popax		;	Pop the new
	tay				;	data from
	stx	dataPtr+1	;__	software stack

	jsr	get_symbol

	pla				;
	tay				;	Pop the old data
	pla				;	from hardware stack
	sta	dataPtr+1	;__

	jmp	get_symbol

vert_skip:
	lda	(dataPtr), y	;
	iny					;
	bne	:+				;	Load amount of lines to skip
		inc	dataPtr+1	;
	:					;__

	and	#$1F			;
	cmp	#$10			;	Put bit 4 into tmp memory
	rol	dataPtr			;__
	and	#$0F			;
	cmp	#$08			;	Put bit 3 into tmp memory
	rol	dataPtr			;__
	asl					;
	tax					;	A <<= 5
	lda	shiftBy4table,x	;__
	
	adc	vramPtr			;__	Carry is clear by the ASL
	and	#$E0			;	Rewind to beginning of line
	ora	#$05			;__	(does not affect carry)
	tax					;__	Temp mem
	lda	dataPtr			;	Add high byte
	adc	vramPtr+1		;__
	sta	PPU_ADDR		;	Store high byte
	sta	vramPtr+1		;__	
	stx	PPU_ADDR		;	Store low byte
	stx	vramPtr			;__

	ldx	#$00			;	Reset temp mem back to 0
	stx	dataPtr			;__

	jmp	get_symbol
	
.endproc


; Standard for function declaration here:
; void init_sprites();
.segment "CODE"

.importzp _sprite_data	
.import _sprite_data_bank
.import _activesprites_type, _activesprites_x_hi, _activesprites_x_lo, _activesprites_active

.export _init_sprites
.proc _init_sprites
	; No arguments, at all
	
	x_counter = tmp1
	
	; Pointers are already set up by init_rld (at X=0)
	
	LDA	mmc3PRG1Bank			;
	PHA							;
	LDA	_sprite_data_bank		;	Switch to the correct bank
	JSR	mmc3_set_prg_bank_1		;__
	
	LDX	#::_max_loaded_sprites
	LDA	#$FF		;
	clear_spritetype_loop:				;
		STA	_activesprites_type-1,	X	;	Clear sprites to load them
		DEX								;
		BNE	clear_spritetype_loop		;__
		
	; Everything is init'd at X=0, so skip some sprite data if X != 0
	
	
	LDY	#1					;__	Offset of high X byte, move inside block if opened
	.if 0	; Feature is currently disabled due to no levels exceeding 4096 blocks (256*256px)
	; First loop, for non-zero 3/4 bytes of scroll_x
	; Flies thru sprite data till they overflow enough
	; Note: may skip shit if there's too little sprites
	; AND MAY NOT ACTUALLY WORK PROPERLY
	old_hi_byte = tmp2
	
	highest_bytes_setup:
		LDA	_scroll_x+2			;
		ORA	_scroll_x+3			;	Skip this altogether if the scroll_x isn't ass big
		BEQ	high_byte_setup		;__
		
		LDX	_scroll_x+3			;
		INX						;	Store highest byte, inc for BEQ ending condition
		STX	x_counter			;__
		
		LDX	_scroll_x+2			;
		INX						;__
		
		JMP	highest_bytes_loop_entrypoint
		
	highest_bytes_loop:
		LDA	#5-1				;
		ADC	sprite_data			;	Relies on set carry
		STA	sprite_data			;__
		BCC	:+					;
			INC	sprite_data+1	;	Overflow
		:						;__
		
		@entrypoint:
		
		LDA	(sprite_data),y		;
		CMP	old_hi_byte			;	If no overflow just
		STA	old_hi_byte			;	increment the pointer
		BCS	highest_bytes_loop	;__
		
		; An overflow of x_hi happened, decrement the counters
		
		SEC						;__	Set for the addition at the beginning
		DEX						;	Decrement the 3rd byte counter
		BNE	highest_bytes_loop	;__
		DEC	x_counter			;	Decrement the 4th byte counter
		BNE	highest_bytes_loop	;__
		
		highest_bytes_loop_entrypoint := @entrypoint
	
	.endif
	
	high_byte_setup:
		LDX	_scroll_x+1
		BEQ	low_byte_setup
		BNE @entrypoint	; BRA
			@data_comparison_loop:
				LDA	#5-1				;
				ADC	sprite_data			;	Relies on set carry
				STA	sprite_data			;__
				BCC	@entrypoint			;	Overflow
					INC	sprite_data+1	;__
		
			@entrypoint:
				TXA						;
				CMP	(sprite_data),	y	;	return if scroll_x <= sprite x
				BEQ	@return				;
				BCS	@data_comparison_loop;__
			
			@return:
	low_byte_setup:	
		STX	x_counter
		LDX	_scroll_x
		BEQ @skip
		BNE @entrypoint
			@data_comparison_loop:
				LDA	#5-1				;
				ADC	sprite_data			;	Relies on set carry
				STA	sprite_data			;__
				BCC	@entrypoint			;	Overflow
					INC	sprite_data+1	;__
		
			@entrypoint:
				DEY
				TXA						;
				CMP	(sprite_data),	y	;	return if scroll_x <= sprite x
				INY						;
				LDA	x_counter			;
				SBC	(sprite_data),	y	;
				BEQ	@return				;
				BCS	@data_comparison_loop;__
			
			@return:
		@skip:
		

	; BAM, the pointer is adjusted
	; Load the sprites now
	
	DEY	; Y is 1
	
	LDX	#::_max_loaded_sprites
	loading_loop:
		;__	Y is 0
		LDA	(sprite_data),	y	;
		CMP	#$FF				;	If sprite data ended, stfu
		BEQ	return				;__
		
		DEX						;
		TXA						;	Load next sprite
		JSR	_load_next_sprite	;
		LDY	#0					;__ Reset Y
		
		; Part where it was writing to activesprites_active
		; is ommited as it is done in load_next_sprite
		
		CPX	#0					;	Repeat for all sprite slots
		BNE	loading_loop		;__
	
	return:
	
	PLA
	JMP mmc3_set_prg_bank_1
		
.endproc


; void set_tile_banks();
; 
;	if (!no_parallax) {
;		mmc3_set_1kb_chr_bank_0(spike_set[level] + (parallax_scroll_x & 1));
;		mmc3_set_1kb_chr_bank_1(block_set[level] + (parallax_scroll_x & 1));	//tile graphics
;		mmc3_set_1kb_chr_bank_2(parallax_scroll_x + GET_BANK(PARALLAX_CHR));
;		mmc3_set_1kb_chr_bank_3(saw_set[level] + (parallax_scroll_x & 1));
;	}
;	else {
;		mmc3_set_1kb_chr_bank_0(spike_set[level]);
;		mmc3_set_1kb_chr_bank_1(block_set[level]);	//tile graphics
;		mmc3_set_1kb_chr_bank_2(SLOPESA);
;		mmc3_set_1kb_chr_bank_3(saw_set[level]);
;	}
