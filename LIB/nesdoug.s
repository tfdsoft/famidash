;written by Doug Fraker
;version 1.3, 10/31/2022

.export _set_vram_buffer, _multi_vram_buffer_horz, _multi_vram_buffer_vert, _one_vram_buffer
.export _get_pad_new, _get_frame_count, _set_music_speed
.export _check_collision, _pal_fade_to, _set_scroll_x, _set_scroll_y, _add_scroll_y, _sub_scroll_y
.export  _get_ppu_addr, _get_at_addr, _set_data_pointer, _set_mt_pointer, _buffer_4_mt, _buffer_1_mt
.export _color_emphasis, _xy_split, _gray_line, _seed_rng
.export _clear_vram_buffer

.segment "CODE"




;void set_vram_buffer(void)
_set_vram_buffer:
	ldx #$ff
	stx VRAM_BUF
	inx ;x=0
	stx VRAM_INDEX
	ldx #>VRAM_BUF
	lda #<VRAM_BUF
	jmp _set_vram_update
	
	

	
;void multi_vram_buffer_horz(char * data, unsigned char len, int ppu_address);
_multi_vram_buffer_horz:
	;note PTR = TEMP and TEMP+1

	ldy VRAM_INDEX
	sta VRAM_BUF+1, y
	txa
	clc
	adc #$40 ; NT_UPD_HORZ
	sta VRAM_BUF, y
	
_multi_vram_buffer_common:
	jsr popa ;len
		sta TEMP+3 ;loop count
		ldy VRAM_INDEX
		sta VRAM_BUF+2, y
	jsr popax ;pointer to data
		sta <PTR
		stx <PTR+1
	ldx VRAM_INDEX ;need y for source, x is for dest and for vram_index
		inx
		inx
		inx
		
	ldy #0
@loop:
	lda (PTR), y
	sta VRAM_BUF, x
	inx
	iny
	cpy TEMP+3
	bne @loop
	lda #$ff ;=NT_UPD_EOF
	sta VRAM_BUF, x
	stx VRAM_INDEX
	rts
	
	
	

;void multi_vram_buffer_vert(char * data, unsigned char len, int ppu_address);
_multi_vram_buffer_vert:
	ldy VRAM_INDEX
	sta VRAM_BUF+1, y
	txa
	clc
	adc #$80 ; NT_UPD_VERT
	sta VRAM_BUF, y
	
	jmp _multi_vram_buffer_common
	
	
	

;void one_vram_buffer(unsigned char data, int ppu_address);
_one_vram_buffer:
	ldy VRAM_INDEX
	sta VRAM_BUF+1, y
	txa
	sta VRAM_BUF, y
	iny
	iny
		sty <TEMP ;popa uses y
	jsr popa
		ldy <TEMP
	sta VRAM_BUF, y
	iny
	lda #$ff ;=NT_UPD_EOF
	sta VRAM_BUF, y
	sty VRAM_INDEX
	rts
	
	
	
	
;void clear_vram_buffer(void);	
_clear_vram_buffer:
	lda #0
	sta VRAM_INDEX
	lda #$ff
	sta VRAM_BUF
	rts
	
	
	
	
;unsigned char __fastcall__ get_pad_new(unsigned char pad);	
_get_pad_new:
	tay
	lda <PAD_STATET,y
	ldx #0
	rts
	
	
	
	
;unsigned char __fastcall__ get_frame_count(void);	
_get_frame_count:
	lda <FRAME_CNT1
	ldx #0
	rts
	
	
	
	
;void __fastcall__ set_music_speed(unsigned char tempo);
_set_music_speed:
	sta FT_SONG_SPEED
	rts
	
	




PTR2 = TEMP+2 ;and TEMP+3

;unsigned char __fastcall__ check_collision(void * object1, void * object2);
_check_collision:
	; sprite object collision code
	; this would work with any size struct, as long as the first 4 bytes are...
	; x, y, width, height
	; note PTR is the same as TEMP and TEMP+1

	sta PTR
	stx PTR+1 ;set up a pointer to the first object
	jsr popax
	sta PTR2
	stx PTR2+1 ;set up a pointer to the second object
	

	ldy #0
	lda (PTR),y
	sta TEMP+4  	;X 1
	lda (PTR2), y
	sta TEMP+6		;X 2
	iny
	iny
	lda (PTR),y
	sta TEMP+5 		;width1
	lda (PTR2), y
	sta TEMP+7		;width2

	
;see if they are colliding x
	
;first check if obj1 R (obj1 x + width) < obj2 L
	
	lda TEMP+4 ;X 1
	clc
	adc TEMP+5 ;width 1
	cmp TEMP+6 ;X 2
	bcc @no
	
;now check if obj1 L > obj2 R (obj2 x + width)

	lda TEMP+6 ;X 2
	clc
	adc TEMP+7 ;width 2
	cmp TEMP+4 ;X 1
	bcc @no


;repeat process with y
	ldy #1
	lda (PTR),y
	sta TEMP+4  	;Y 1
	lda (PTR2), y
	sta TEMP+6		;Y 2
	iny
	iny
	lda (PTR),y
	sta TEMP+5 		;height1
	lda (PTR2), y
	sta TEMP+7		;height2

;see if they are colliding y
	
;first check if obj1 Bottom (obj1 y + height) < obj2 Top
	
	lda TEMP+4 ;Y 1
	clc
	adc TEMP+5 ;height 1
	cmp TEMP+6 ;Y 2
	bcc @no
	
;now check if obj1 Top > obj2 Bottom (obj2 y + height)

	lda TEMP+6 ;Y 2
	clc
	adc TEMP+7 ;height 2
	cmp TEMP+4 ;Y 1
	bcc @no


@yes:
	lda #1
	ldx #0
	rts
	
@no:
	lda #0
	tax ;ldx #0
	rts

	
	
	
;void __fastcall__ pal_fade_to(unsigned char from, unsigned char to);	
_pal_fade_to:
	sta TEMP+9 ;to
	jsr popa
	sta TEMP+10 ;from
	jmp @check_equal
	
@fade_loop:	
	lda #4
	jsr _delay ;wait 4 frames
	
	lda TEMP+10 ;from
	cmp TEMP+9 ;to
	bcs @more
	
@less:	
	clc
	adc #1
	sta TEMP+10 ;from
	jsr _pal_bright
	jmp @check_equal
	
@more:	
	sec
	sbc #1
	sta TEMP+10 ;from
	jsr _pal_bright
	
@check_equal:
	lda TEMP+10
	cmp TEMP+9
	bne @fade_loop
	
@done:	
	jsr _ppu_wait_nmi ;do 1 final, make sure the last change goes
	rts
	
	
	
	
;void __fastcall__ set_scroll_x(unsigned int x);	
_set_scroll_x:
	sta <SCROLL_X
	txa
	and #$01
	sta <TEMP
	lda <PPU_CTRL_VAR
	and #$fe
	ora <TEMP
	sta <PPU_CTRL_VAR
	rts
	
	
	
	
;void __fastcall__ set_scroll_y(unsigned int y);	
_set_scroll_y:
	sta <SCROLL_Y
	txa
	and #$01
	asl a
	sta <TEMP
	lda <PPU_CTRL_VAR
	and #$fd
	ora <TEMP
	sta <PPU_CTRL_VAR
	rts
	
	
	
	
;int __fastcall__ add_scroll_y(unsigned char add, unsigned int scroll);
_add_scroll_y:
	sta TEMP
	stx TEMP+1 ;x = high
	jsr popa
	clc
	adc TEMP
	bcs @adjust
	cmp #$f0
	bcs @adjust
	rts
	
@adjust:
	adc #15 ;carry is set, same as clc/adc #16
	inc TEMP+1 ;x = high
	ldx TEMP+1
	rts
	
	
	
	
;int __fastcall__ sub_scroll_y(unsigned char sub, unsigned int scroll);
_sub_scroll_y:
	;is a in range?
	cmp #$f0
	bcc @ok
	lda #$00
@ok:
	sta TEMP
	stx TEMP+1 ;x = high
	jsr popa
	sta TEMP+2
	lda TEMP
	sec
	sbc TEMP+2
	bcc @adjust
	rts
	
@adjust:
	sbc #15 ;carry is clear, same as sec/sbc #16
	dec TEMP+1 ;x = high
	ldx TEMP+1
	rts
	
	
	
	
;int __fastcall__ get_ppu_addr(char nt, char x, char y);	
_get_ppu_addr:	
	and #$f8 ;y bits
	ldx #0
	stx TEMP+1
	asl a
	rol TEMP+1
	asl a
	rol TEMP+1
	sta TEMP
	
	jsr popa ;x bits
	lsr a
	lsr a
	lsr a
	ora TEMP
	sta TEMP
	
	jsr popa ;nt 0-3
	and #3
	asl a
	asl a
	ora #$20
	ora TEMP+1
	tax
	lda TEMP
	rts
	
	

	
;int __fastcall__ get_at_addr(char nt, char x, char y);
_get_at_addr:
	and #$e0
	sta TEMP
	
	jsr popa
	and #$e0
	lsr a
	lsr a
	lsr a
	ora TEMP
	lsr a
	lsr a
	ora #$c0
	sta TEMP
	
	jsr popa
	and #3
	asl a
	asl a
	ora #$23
	tax
	lda TEMP
	rts
	
	
	

;void __fastcall__ set_data_pointer(const char * data);
_set_data_pointer:
	sta DATA_PTR
	stx DATA_PTR+1
	rts

	
	
	
;void __fastcall__ set_mt_pointer(const char * metatiles);	
_set_mt_pointer:
	sta META_PTR
	stx META_PTR+1
	rts
	
	
	
	
;void __fastcall__ buffer_4_mt(int ppu_address, char index);
_buffer_4_mt:
	;a is the index into the data, get 4 metatiles

	and #$ee ;sanitize, x and y should be even
	tay
	lda (DATA_PTR), y
	sta TEMP+2
	iny
	lda (DATA_PTR), y
	sta TEMP+3
		tya
		clc
		adc #15
			cmp #$f0 ;too far, data set only 240 bytes
			bcs @skip
		tay
	lda (DATA_PTR), y
	sta TEMP+4
	iny
	lda (DATA_PTR), y
	sta TEMP+5
@skip:	
;metatiles are in TEMP+2 - TEMP+5 now

	jsr popax ;ppu address
	and #$9c ;sanitize, should be top left
	sta TEMP+7
	stx TEMP+8 ;save for later, ppu_address
	
	sta TEMP
	txa
	ora #$40	;NT_UPD_HORZ
	sta TEMP+1
	
;buffer the ppu_address

	lda #0
	sta TEMP+6 ;loop count, index to the metatiles
	ldx VRAM_INDEX
@loop:	
	lda TEMP ;low byte
	sta VRAM_BUF+1, x
	lda TEMP+1 ;high byte
	sta VRAM_BUF,x
	jsr @sub1 ;adds $20 to the address for next time
	
		lda #4 ;tell the system 4 bytes in a row
		sta VRAM_BUF+2,x
		sta VRAM_BUF+9,x ;loops twice, so, it does this twice
		
	jsr @sub2 ;gets y is which metatile
	
	lda (META_PTR), y
	sta VRAM_BUF+3,x ;		buffer the 4 tiles
	iny
	lda (META_PTR), y
	sta VRAM_BUF+4,x
	iny
	lda (META_PTR), y
	sta VRAM_BUF+10,x
	iny
	lda (META_PTR), y
	sta VRAM_BUF+11,x
	jsr @sub4 ;get attrib bits, shift into place
	
;same, but for right side	
	lda TEMP ;low byte ppu address, again
	sta VRAM_BUF+8,x
	lda TEMP+1 ;high byte
	sta VRAM_BUF+7,x
	jsr @sub1
	
	inc TEMP+6 ;count and index
	jsr @sub2
	lda (META_PTR), y
	sta VRAM_BUF+5,x ;		buffer the 4 tiles
	iny
	lda (META_PTR), y
	sta VRAM_BUF+6,x
	iny
	lda (META_PTR), y
	sta VRAM_BUF+12,x
	iny
	lda (META_PTR), y
	sta VRAM_BUF+13,x
	jsr @sub4
	
	txa ;adjust the vram index to the next set
	clc
	adc #14
	tax
	
	jsr @sub3 ;check if lowest y on screen, skip the la
	bne @loop_done

	inc TEMP+6
	ldy TEMP+6
	cpy #4
	bcc @loop
	
@loop_done:	
	
	
	
;now push 1 attribute byte to the vram buffer
;first, shift the bits to get an attribute address
;we stored the original at TEMP+7,8, 8 is high byte
;a bunch of bit shifting to get 3 bits from x and 3 y
	lsr TEMP+8 ;high byte
	ror TEMP+7
	lsr TEMP+8
	ror TEMP+7
	lda TEMP+7
	pha ;save
	and #7 ;just the x bits
	sta TEMP
	pla
	lsr a ;just the y bits
	lsr a
	and #$f8
	ora #$c0
	ora TEMP
	sta TEMP ;low byte
;now high byte	
	lda TEMP+8
	asl a
	asl a
	ora #$23
	sta TEMP+1 ;high byte, and the low byte is in TEMP

	
;finally, push it all to the vram_buffer as a single byte
	lda TEMP+1 ;high byte
	sta VRAM_BUF,x
	inx
	lda TEMP ;low byte
	sta VRAM_BUF,x
	inx
	lda TEMP+10
	sta VRAM_BUF,x
	inx
	lda #$ff ;=NT_UPD_EOF
	sta VRAM_BUF,x
	stx VRAM_INDEX
	rts

	
@sub1:	;add $20 is a 1 down on the screen
	tay ;high byte
	lda TEMP
	clc
	adc #$20
	sta TEMP
	bcc @sub1b
	iny
@sub1b:
	sty TEMP+1
	rts
	
	
@sub2:	;get the next metatile offset
	ldy TEMP+6
	lda TEMP+2, y ;metatile
;multiply by 5	
	sta TEMP+9
	asl a
	asl a ;x4 = 4 bytes per
	clc
	adc TEMP+9
	tay
	rts
	

@sub3: ;check make sure we're not at the lowest y and overflowing
	ldy #0 ;x is forbidden
	lda TEMP+8 ;high byte
	and #$03
	cmp #$03
	bne @not_overflow
	lda TEMP+7
	cmp #$80 ;last row of mt
	bcc @not_overflow
	iny
	lsr TEMP+10 ;make sure the attrib bits in correct position
	lsr TEMP+10
	lsr TEMP+10
	lsr TEMP+10
@not_overflow:
	tya ;set flag
	rts
	
	
@sub4: ;get attrib bits, roll them in place
	iny
	lda (META_PTR), y ;5th byte = attribute
	and #3 ;just need 2 bits
	ror a ;bit to carry
	ror TEMP+10 ;shift carry in
	ror a ;bit to carry
	ror TEMP+10 ;roll the a.t. bits in the high 2 bits
	rts
	
	
	
	
;void __fastcall__ buffer_1_mt(int ppu_address, char metatile);
_buffer_1_mt:
	;which metatile, in A

	sta TEMP+2
	
	jsr popax ;get ppu address
	and #$de ;sanitize, should be even x and y
	sta TEMP
	txa
	ora #$40 ;NT_UPD_HORZ
	sta TEMP+1
	
	ldx VRAM_INDEX	
	lda TEMP				;ppu address
	sta VRAM_BUF+1,x
		clc
		adc #$20 ;shouldn't be rollover
	sta VRAM_BUF+6,x	
	
	lda TEMP+1
	sta VRAM_BUF,x
	sta VRAM_BUF+5,x
	
	lda #2 ;tell the system 2 bytes in a row
	sta VRAM_BUF+2,x
	sta VRAM_BUF+7,x
	
	lda TEMP+2 ;which metatile
	asl a
	asl a
	clc
	adc TEMP+2 ;multiply 5
	tay
	lda (META_PTR), y ;tile
	sta VRAM_BUF+3,x
	iny
	lda (META_PTR), y ;tile
	sta VRAM_BUF+4,x
	iny
	lda (META_PTR), y ;tile
	sta VRAM_BUF+8,x
	iny
	lda (META_PTR), y ;tile
	sta VRAM_BUF+9,x
	
	txa
	clc
	adc #10
	sta VRAM_INDEX
	tax
	lda #$ff ;=NT_UPD_EOF
	sta VRAM_BUF,x
	rts
	
	
	
	
;void __fastcall__ color_emphasis(char color);	
_color_emphasis:
	;a = bits 1110 0000
	and #$e0 ;sanitize
	sta TEMP
	lda <PPU_MASK_VAR
	and #$1f
	ora TEMP
	sta <PPU_MASK_VAR
	rts
	
	
	
	
;void __fastcall__ xy_split(unsigned int x, unsigned int y);
_xy_split:
	;Nametable number << 2 (that is: $00, $04, $08, or $0C) to $2006
	;Y to $2005
	;X to $2005
	;Low byte of nametable address to $2006, which is ((Y & $F8) << 2) | (X >> 3)

	sta <TEMP+2 ;y low
	stx <TEMP+3
	jsr popax
	sta <TEMP ;x low
	stx <TEMP+1
	
;push to stack in reverse order	
	lda <TEMP+2 ;low y
	and #$f8
	asl a
	asl a
	sta <TEMP+4
	lda <TEMP ;low x
	lsr a
	lsr a
	lsr a
	ora <TEMP+4
	pha
	
	lda <TEMP ;low x
	pha
	
	lda <TEMP+2 ;low y
	pha

	lda <TEMP+3 ;y high
	and #$01
	asl a
	sta <TEMP+4
	lda <TEMP+1 ;x high
	and #$01
	ora <TEMP+4
	asl a
	asl a
	pha

@3:

	bit PPU_STATUS
	bvs @3

@4:

	bit PPU_STATUS
	bvc @4

	pla
	sta $2006
	pla
	sta $2005
	pla
	sta $2005
	pla
	sta $2006
	rts	
	

	
	
;void gray_line(void);
_gray_line:
	lda <PPU_MASK_VAR
	and #$1f ;no color emphasis bits
	ora #1 ;yes gray bit
	sta PPU_MASK
	
	ldx #20 ;wait
@loop:
	dex
	bne @loop
	
	lda <PPU_MASK_VAR
	and #$1e ;no gray bit
	ora #$e0 ;all color emphasis bits
	sta PPU_MASK
	
	ldx #20 ;wait
@loop2:
	dex
	bne @loop2
	
	lda <PPU_MASK_VAR ;normal
	sta PPU_MASK
	rts
	
	
	
	
;void seed_rng(void);
_seed_rng:
	lda <FRAME_CNT1
	sta <RAND_SEED
	rts
	
	
	
