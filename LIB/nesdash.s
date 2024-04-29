; Custom routines implemented specifically for famidash (some are totally not stolen from famitower)

.global _level_list_lo, _level_list_hi, _level_list_bank, _sprite_list_lo, _sprite_list_hi, _sprite_list_bank
.import _rld_column, _collisionMap0, _collisionMap1 ; used by C code
.import _scroll_x, _level_data_bank, _sprite_data_bank
.import _song, _level, _gravity, _speed
.import _cube_movement, _ship_movement, _ball_movement, _ufo_movement, _robot_movement, _spider_movement, _wave_movement
.importzp _gamemode
.importzp _tmp1, _tmp2, _tmp3, _tmp4  ; C-safe temp storage
.import _DATA_PTR
.import pusha, pushax
.import _level1text, _level2text, _level3text, _level4text, _level5text, _level6text, _level7text, _level8text, _level9text, _levelAtext
.import _increase_parallax_scroll_column
.import FIRST_MUSIC_BANK
.import _auto_fs_updates

.global metatiles_top_left, metatiles_top_right, metatiles_bot_left, metatiles_bot_right, metatiles_attr

.macpack longbranch

.export _oam_meta_spr_vflipped
.export _init_rld, _unrle_next_column, _draw_screen_R
; .export _refreshmenu
.export _movement
.export _music_play, _sfx_play, _music_update

.importzp _level_data, _sprite_data
level_data = _level_data
sprite_data = _sprite_data

.define CUBE_GRAVITY $6B
.define MINI_CUBE_GRAVITY $6F

;void __fastcall__ oam_meta_spr_vflipped(unsigned char x,unsigned char y,const unsigned char *data);

.segment "ZEROPAGE"
    rld_value:      .res 1
    rld_run:        .res 1

.segment "BSS"
    ; column buffer, to be pushed to the collision map
    ; 16 metatiles in the top screen 
    ; 11 metatiles in the bot screen
    columnBuffer:   .res 16 + 11

    current_song_bank: .res 1
    scroll_count:   .res 1

.export _scroll_count := scroll_count

.export _parallax_scroll_column := parallax_scroll_column
.export _parallax_scroll_column_start := parallax_scroll_column_start
    parallax_scroll_column: .res 1
    parallax_scroll_column_start: .res 1

.segment "CODE"

_oam_meta_spr_vflipped:

    sta <PTR
    stx <PTR+1

    ldy #1      ;2 popa calls replacement, performed in reversed order
    lda (sp),y
    dey
    sta <SCRX
    lda (sp),y
    sta <SCRY
    
oam_meta_spr_vflipped_params_set: ; Put &data into PTR, X and Y into SCRX and SCRY respectively

    ldx SPRID

@1:

    lda (PTR),y     ;x offset
    cmp #$80
    beq @2
    iny
    clc
    adc <SCRX
    sta OAM_BUF+3,x
    lda (PTR),y     ;y offset
    iny
    eor #$FF
    clc
    adc <SCRY
    sta OAM_BUF+0,x
    lda (PTR),y     ;tile
    iny
    sta OAM_BUF+1,x
    lda (PTR),y     ;attribute
    iny
    EOR #$80        ; invert Y flip
    sta OAM_BUF+2,x
    inx
    inx
    inx
    inx
    jmp @1

@2:

    lda <sp
    adc #1          ;carry is always set here, so it adds 2
    sta <sp
    bcc @3
    inc <sp+1

@3:

    stx SPRID
    rts

.macro INCW addr
    INC addr
    BNE :+
        INC addr+1
:
.endmacro

.macro incw addr
    INCW addr
.endmacro

.macro incw_check addr
    INC addr
    BNE :+
        jsr incwlvl_checkC000
:
.endmacro

.segment "CODE_2"

.export _one_vram_buffer_horz_repeat
.proc _one_vram_buffer_horz_repeat
.import popptr1
	ldy VRAM_INDEX
	sta VRAM_BUF+1, y
	txa
    ora #$40
WriteHiByte:
	sta VRAM_BUF, y
		sty TEMP ;popa uses y
	jsr popptr1 ; pop two bytes from c stack into ptr1
		ldy TEMP
    ; ptr1 lo byte is len, hi byte is character to repeat
    lda ptr1
    ora #$80 ; set length + repeat byte
	sta VRAM_BUF+2, y
    lda ptr1+1
	sta VRAM_BUF+3, y
	lda #$ff ;=NT_UPD_EOF
	sta VRAM_BUF+4, y
    tya
    clc
    adc #4
    sta VRAM_INDEX
	rts
.endproc
.export _one_vram_buffer_vert_repeat
.proc _one_vram_buffer_vert_repeat
	ldy VRAM_INDEX
	sta VRAM_BUF+1, y
	txa
    ora #$80 ; vertical update
    jmp _one_vram_buffer_horz_repeat::WriteHiByte
.endproc

_init_rld:
    ; The C code being ported:
        ;
        ; void init_rld(unsigned char level){ // reset run-length decoder back to zero
        ;     rld_column = 0;
        ; 	level_data = (unsigned char *) level_list[level];
        ;     rld_value = level_data[0]; // set the value and run to the first tile type and length
        ;     rld_run = level_data[1];
        ; 	++level_data; ++level_data; 
        ; }

    ; A has the level ID

    ; Get pointers:
    TAY		                ;__ Load pointer to tables
	LDA _sprite_list_lo,y	;
	STA _sprite_data+0		;__	Get low pointer to sprite data 
	LDA _sprite_list_hi,y	;
	STA _sprite_data+1		;__	Get high pointer to sprite data 
    LDA _sprite_list_bank,y ;   Get sprite data bank
    ; CLC                     ;
    ; ADC #<FIRST_SPRITE_BANK ;
    STA _sprite_data_bank   ;__
	LDA _level_list_lo,y	;
	STA _level_data+0		;__	Get low pointer to level data 
	LDA _level_list_hi,y	;
	STA _level_data+1		;__	Get high pointer to level data 
    LDA _level_list_bank,y  ;   Get level data bank
    STA _level_data_bank    ;__
    
    JSR mmc3_set_prg_bank_1

    LDY #$00            ;-  For both (zp),y addressing and rld_column
    STY _rld_column     ;__ Reset scrolling

    ; Read header
    LDA (level_data),y  ;
    STA _song           ;   Song number
    incw_check level_data

    LDA (level_data),y  ;
    STA _gamemode       ;   Starting level number
    incw_check level_data

    LDA (level_data),y  ;
    STA _speed          ;   Starting speed
    incw_check level_data

    LDA (level_data),y  ;	Starting BG color
	AND #$3F			;	Store normal color (pal_col(0, tmp2))
    STA PAL_BUF+0       ;__ 
    SEC                 ;	A = faded OG color (A - 10)
    SBC #$10            ;__
	BPL :+				;
		LDA #$0F		;	if (faded color invalid) color = $0F (canonical black)
	:					;__
	STA PAL_BUF+1		;__	Store faded color (pal_col(1, tmp2-0x10 or 0x0F))
    incw_check level_data

	LDA (level_data),y  ;	Starting ground color
	AND #$3F			;	Store normal color (pal_col(6, tmp2))
    STA PAL_BUF+6       ;__ 
    SEC                 ;	A = faded OG color (A - 10)
    SBC #$10            ;__
	BPL :+				;
		LDA #$0F		;	if (faded color invalid) color = $0F (canonical black)
	:					;__
	STA PAL_BUF+5		;__	Store faded color (pal_col(5, tmp2-0x10 or 0x0F))
    incw_check level_data

	INC <PAL_UPDATE		;__ Yes, we do need to update the palette

SetupNextRLEByte:
    LDA (level_data),y  ;
    bmi single_rle_byte
    STA rld_run         ;__ Load rld_run, ++level_data
    incw_check level_data     ;__

    LDA (level_data),y  ;
    STA rld_value       ;   Load rld_value, ++level_data
    ; JMP incwlvl_checkC000

    INC level_data
    BNE :+
incwlvl_checkC000:  ; clobbers A
        INC level_data+1
        bit level_data+1
        ; since the high byte will only be $Ax or $Bx, when bit 6 is set then its rolled over to $c0
        bvc :+
        pha 
            ; switch banks
            LDA #$A0            ;   Reset memory-mapped ptr
            STA level_data+1    ;__
            INC _level_data_bank ;_ Increment bank
            LDA _level_data_bank
            jsr mmc3_set_prg_bank_1 ;__ Switch the bank
        pla
    :   
    RTS
single_rle_byte:
    and #$7f
    sta rld_value
    lda #0
    sta rld_run
    incw_check level_data
    rts


_unrle_next_column:

    ; Count up to zero to remove a cmp instruction
    ldx #<-27
    ldy #$00
    lda rld_value

    @FirstLoop:
        sta columnBuffer - ($100 - 27), x
        dec rld_run
        bmi @UpdateValueRun
        inx 
        bmi @FirstLoop
        bpl @WriteSetup ; Guaranteed jump
    
    @UpdateValueRun:
        ; if bit 7 of the byte is set, then its a run of length 1
        ; otherwise this is a length < 127 byte and we need to read another
        lda (level_data), y
        bmi @SingleByteRun
        sta rld_run               ;__ Load rld_run, ++level_data
        incw_check level_data     ;__

        lda (level_data), y       ;
        sta rld_value             ;   Load rld_value, ++level_data
        incw_check level_data

        lda rld_value
        inx 
        bmi @FirstLoop
        bpl @WriteSetup ; Unconditional
    
    @SingleByteRun:
        and #$7f
        sta rld_value
        ; y = 0
        sty rld_run
        incw_check level_data
        inx 
        bmi @FirstLoop
        ; and then fallthrough to copying to the collision map

    @WriteSetup:

    ; We have 27 writes to make to the collision map, thats 27 * 6 bytes for an unrolled loop.
    ; roughly twice the size for much more perf. We'll want this function to be fast when we
    ; do practice mode so we can quickly reload to the middle of levels
    ldx _rld_column
    .repeat 16, I
    lda columnBuffer + I
    sta _collisionMap0 + I * 16, x
    .endrepeat
    .repeat 11, I
    lda columnBuffer+16 + I
    sta _collisionMap0+$100 + I * 16, x
    .endrepeat

    inx
    txa
    and #$0F
    sta _rld_column
    rts

shiftBy4table:
.byte $00, $10, $20, $30
.byte $40, $50, $60, $70
.byte $80, $90, $A0, $B0
.byte $C0, $D0, $E0, $F0

TileSizeHi  = (15*2)+2+1
TileSizeLo  = (12*2)+2+1

TileOff0    = 0
TileOff1    = 0+TileSizeHi
TileEnd     = 0+TileSizeHi+TileSizeLo


AttrSizeHi  = 8*3
AttrSizeLo  = 6*3

AttrOff0    = 0
AttrOff1    = 0+AttrSizeHi
AttrEnd     = 0+AttrSizeHi+AttrSizeLo

.proc _draw_screen_R

CurrentRow = tmp1
LoopCount = tmp2

.export _draw_screen_R_frame0 := frame0
.export _draw_screen_R_frame1 := frame1
.export _draw_screen_R_frame2 := frame2
    ; Write architecture:

    ; Frame 0:
    ;   Write 0 updates the upper nametable's left tiles
    ;   Write 1 updates the lower nametable's left tiles
    ; Frame 1:
    ;   Write 0 updates the upper nametable's right tiles
    ;   Write 1 updates the lower nametable's right tiles
    ; Frame 2:
    ;   Attributes 
    
    LDA _scroll_x           ;__ Highbyte of scroll_x
    LSR                     ;
    LSR                     ;   >> 4
    LSR                     ;
    LSR                     ;__
    STA tmp4

    LDX scroll_count
    BNE frame2

    LDA tmp4
    CMP _rld_column         ;   If X == rld column, decompress shit
    BEQ frame0
    RTS
    
frame2:
        CPX #$01
        BEQ frame1
        JMP attributes

frame0:
        ; Switch banks
        LDA _level_data_bank
        JSR mmc3_set_prg_bank_1

        JSR _unrle_next_column

frame1:

        ; Writing to nesdoug's VRAM buffer starts here
        LDX VRAM_INDEX

        ; In-house replacement of get_ppu_addr, only counts X
        ; Address is big-endian
        LDY _rld_column ;   000xxxx0 - the left tiles of the metatiles
        DEY
        TYA
        AND #$0F
        ASL         ;__
        LDY scroll_count
        BEQ :+
            ORA #$01    ;   000xxxx1 - the right tiles of the metatiles
        :
        STA VRAM_BUF+TileOff0+1,X
        STA VRAM_BUF+TileOff1+1,X

        lda _scroll_x + 1 ; high byte
        and #%00000001
        eor #%00000001
        asl
        asl
        ora #($20+$80)  ; 0th nametable + NT_UPDATE_VERT
        STA VRAM_BUF+TileOff0,X
        ORA #$08        ; 2nd nametable
        STA VRAM_BUF+TileOff1,X


        ; First part of the update: the tiles
        ; Amount of data in the sequence - 27*2 tiles (8x8 tiles, left sides of the metatiles)
        LDA #(15*2)
        STA VRAM_BUF+TileOff0+2,X
        LDA #(12*2)
        STA VRAM_BUF+TileOff1+2,X

        ; The sequence itself:
        
        ; Load Y value
        LDY #$00
        sty CurrentRow
        ; Load max value
        LDA #15 - 1
        STA LoopCount
        ; Check if doing a left or right hand write
        LDA scroll_count
        AND #1
        beq @LeftWrite
            ; Right side write
            ; Call for upper tiles
            JSR right_tilewriteloop
            jmp @WriteBottomHalf
@LeftWrite:
            JSR left_tilewriteloop
@WriteBottomHalf:
        ; Load new max
        LDA #12 - 1
        STA LoopCount
        ; Add offset to X
        TXA
        CLC
        ADC #(TileSizeHi-(15*2))
        TAX
        
        LDA scroll_count
        AND #1
        beq @LeftWrite2
            JSR right_tilewriteloop
            jmp @RenderParallax
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

        ldx #TileOff0 + TileSizeHi - 1 - (2+1)
        stx LoopCount
        ldx #TileOff0
        jsr RenderParallaxLoop

        ldx #TileSizeLo - 1 - (2+1)
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
        TXA
        CLC
        ADC #TileEnd
        STA VRAM_INDEX

        INC scroll_count

        RTS

    attributes:
NametableAddrHi = tmp1
        ; Attribute write architecture:

        ; | Ad|dr |dat|
        ;   0   1   2
        ; Addr = VRAM address

        ; 1 byte can theoretically be saved by using a vertical
        ; sequence of 2 bytes, but this comes at a cost of 23
        ; cycles per 2 bytes in vblank (80 vs 103), and vlank
        ; time is not to be wasted

        ; Decremented rld_column, very useful
        LDX _rld_column
        DEX
        TXA
        AND #$0F
        STA ptr3

        ; Get the ptr (I am not bothering with 2 separate loops)
        LDA #>_collisionMap0
        STA ptr1+1
        LDA ptr3
        AND #$0E
        ADC #(<_collisionMap0-1)    ; The carry is set by the CMP used to jump into this routine
        STA ptr1
        BCC :+
            INC ptr1+1
        :

        LDA #8 - 1
        STA LoopCount

        ldx #0
        JSR attributeLoop1

        ; Last byte has no bottom tiles
        LDA columnBuffer+7
        AND #$0F
        STA columnBuffer+7

        ; Update new maximum
        LDA #8+6 - 1
        STA LoopCount

        ; Update pointer (collisionMap0 is 240 bytes, not 256)
        LDA ptr1
        SEC
        SBC #$10
        STA ptr1
        BCS :+
            DEC ptr1+1
        :

        JSR attributeLoop1

        ; Get address hi byte (either left or right side)
        lda _scroll_x + 1 ; high byte
        and #%00000001
        eor #%00000001
        asl
        asl
        ora #$23
        sta NametableAddrHi
        
        LDA ptr3
        LSR
        ORA #$C0
        
        ; Store address
        LDX VRAM_INDEX
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

            CLC
            ADC #$08
            BCC addressLoop
        
        LDY #14

        LDA VRAM_INDEX
        ADC #AttrEnd-1  ; Carry is set by the ADC : BCC
        STA VRAM_INDEX  ; State that the block is now occupied
        TAX

        dataLoop:
            LDA columnBuffer-1,Y
            STA VRAM_BUF-3+2,X

            DEX
            DEX
            DEX
            DEY
            BNE dataLoop
        
        ; Finish off the routine
        ; X has VRAM_INDEX, mark this block as taken
        LDA #$FF
        STA VRAM_BUF+AttrEnd,X
        ; Reset frame counter
        LDA #$00
        STA scroll_count
        RTS

    attributeLoop1:
            ; Read upper left metatile
            LDY #$00
            LDA (ptr1),Y
            tay
            lda metatiles_attr,y
            STA ptr2

            ; Read lower left metatile (higher chance of being the same, due to RLE)
            LDY #$10
            LDA (ptr1),Y
            tay
            lda metatiles_attr,y
            STA ptr2+1

            ; Read upper right metatile
            LDY #$01
            LDA (ptr1),Y
            tay
            lda metatiles_attr,y
            ASL
            ASL
            ORA ptr2
            STA ptr2

            ; Read lower right metatile
            LDY #$11
            LDA (ptr1),Y
            tay
            lda metatiles_attr,y
            ASL
            ASL
            ORA ptr2+1
            TAY
            LDA ptr2
            ORA shiftBy4table,Y
            STA columnBuffer,X

            ; Increment pointer
            LDA ptr1
            ; Last thing affecting carry is the ASL, which
            ; always shifts 0 into it if the metatile data
            ; is valid
            ADC #$20
            STA ptr1
            BCC :+
                INC ptr1+1
            :

            INX
            DEC LoopCount
            BPL attributeLoop1
        RTS

    right_tilewriteloop:
            ldy CurrentRow
            LDA columnBuffer,Y
            tay
            ; y is the metatile id
            lda metatiles_top_right, y
            STA VRAM_BUF+TileOff0+3,X
            lda metatiles_bot_right, y
            STA VRAM_BUF+TileOff0+4,X
            
            INX
            INX
            inc CurrentRow
            DEC LoopCount
            BPL right_tilewriteloop
        rts
    left_tilewriteloop:
            ldy CurrentRow
            LDA columnBuffer,Y
            tay
            ; y is the metatile id
            lda metatiles_top_left, y
            STA VRAM_BUF+TileOff0+3,X
            lda metatiles_bot_left, y
            STA VRAM_BUF+TileOff0+4,X
            
            INX
            INX
            inc CurrentRow
            DEC LoopCount
            BPL left_tilewriteloop
        rts
        
    RenderParallaxLoop:
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
        rts
    ; Before returning, loop again through the vram buffer and write the parallax
    ; parallax_bg_write:
    ;     ldx #27 - 1

    ;     ; based on the current scroll value.
    ;     ; y is the metatile current row, x is the current VRAM_BUF offset
    ;     ; tmp4 is the parallax_scroll_column_start value
    ;     ; which is where in the parallax buffer we are rendering from

    ;     ldy ParallaxColumnStart
    ;     cpy #9 - 1
    ;     bne :+
    ;         ; annoyingly when we are drawing the last row we have to do it differently
    ;         jsr render_last_tile
    ;         bne write_tile1
    ;     :
    ;     lda ParallaxBuffer, y
    ;     clc
    ;     adc parallax_scroll_column
    ; write_tile1:
    ;     sta VRAM_BUF+TileOff0+3,X
    ;     iny 
    ;     cpy #9
    ;     bcc :+
    ;         ldy #0
    ;     :
    ;     ; Render the second tile
    ;     cpy #9 - 1
    ;     bne :+
    ;         jsr render_last_tile
    ;         bne write_tile2
    ;     :
    ;     lda ParallaxBuffer, y
    ;     clc
    ;     adc parallax_scroll_column
    ; write_tile2:
    ;     sta VRAM_BUF+TileOff0+4,X
    ;     iny 
    ;     cpy #9
    ;     bcc :+
    ;         ldy #0
    ;     :
    ;     sty ParallaxColumnStart

    ;     jmp NextMetatile
    ;     RTS

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

.endproc

; _refreshmenu:
; 	; The C code being "ported":
; 		; one_vram_buffer(0xD1+level, NTADR_A(29,24));
; 		; ppu_off();
; 		; vram_adr(NTADR_A(2,25));	
; 		; switch (level){
; 		; 	case 0x0N:  N = 1..7
; 		; 		for(tmp1=0;levelKtext[tmp1];++tmp1){
; 		; 			vram_put(0xA0+levelNtext[tmp1]);
; 		; 		};
; 		; 		break;
; 		; }		
; 		; ppu_on_all();
; 		; return;
; 	; Instead of ppu_off/on i do it with the VRAM buffer
; 	; like a civilised person
; 	LDY VRAM_INDEX
; 	;! THE ADDRESS CORRESPONDING TO NTADR_A(29,24) IS
; 	;! $231D. THIS IS HARDCODED, CHANGE THESE LINES IF
; 	;! YOU WANT TO CHANGE THE POSITION OF IT
; ;	LDA #$23			;
; ;	STA VRAM_BUF, Y		;
; ;	LDA #$1D			;
; ;	STA VRAM_BUF+1, Y	;	one_vram_buffer(0xD1+level, NTADR_A(29,24));
; ;	LDA _level			;	(Displays the level number)
; ;	CLC					;
; ;	ADC #$D1			;
; ;	STA VRAM_BUF+2, Y	;__

; 	;! THE ADDRESS CORRESPONDING TO NTADR_A(2,25) IS
; 	;! $20A2, AND OR'D WITH THE HORIZONTAL UPDATE FLAG
; 	;! IT BECOMES $64A2. THIS IS HARDCODED, CHANGE THESE
; 	;! LINES IF YOU WANT TO CHANGE THE POSITION OF IT
; 	LDA #$65			;
; 	STA VRAM_BUF, Y	;   ~ vram_adr(NTADR_A(2,25));
; 	LDA #$CE			;
; 	STA VRAM_BUF+1, Y	;__
; 	LDA #15				;	Const length of 15
; 	STA VRAM_BUF+2, Y	;__

; 	LDX _level					;
; 	LDA @string_ptrs_lo, X	    ;   Load low byte of lvl name pointer
; 	STA <PTR					;__
; 	LDA @string_ptrs_hi, X	    ;   Load high byte of lvl name pointer
; 	STA <PTR+1					;__
; 	LDA @padding, X			    ;
; 	LSR							;	Get left offset
; 	TAX							;__
; 	ADC #$00					;	Get right offset
; 	STA <TEMP+3					;__

; 	CPX #$00	; Had to do this, very sorry
; 	BEQ @main_data

; 	LDA #$C0	; Space char

; 	@pad_loop_left:
; 		STA VRAM_BUF+3, Y
; 		INY
; 		DEX
; 		BNE @pad_loop_left
	
; 	@main_data:
; 	; No need to LDX #$00, as it's either 0 from the prev loop or 0 left padding
; 		LDA (<PTR, X)	; Load byte

; 	@main_data_loop:
; 		CLC
; 		ADC #$A0
; 		STA VRAM_BUF+3, Y
; 		INY
; 		INCW <PTR
; 		LDA (<PTR, X)			;	Load byte
; 		BNE @main_data_loop		;__ Continue if not 0
	
; 	LDX <TEMP+3
; 	BEQ @end

; 	LDA #$C0

; 	@pad_loop_right:
; 		STA VRAM_BUF+3, Y
; 		INY
; 		DEX
; 		BNE @pad_loop_right
	
; 	@end:
; 	LDA #$FF			;	Finish off the write
; 	STA VRAM_BUF+3, Y	;__

; 	TYA				;
; 	CLC				;	Adjust vram index
; 	ADC #$06		;
; 	STA VRAM_INDEX	;__



; 	RTS

; @string_ptrs_lo:
;     .byte <_level1text, <_level2text, <_level3text, <_level4text, <_level5text, <_level6text, <_level7text, <_level8text, <_level9text, <_levelAtext, <_levelBtext, <_levelCtext, <_levelDtext, <_levelEtext, <_levelFtext
; @string_ptrs_hi:
;     .byte >_level1text, >_level2text, >_level3text, >_level4text, >_level5text, >_level6text, >_level7text, >_level8text, >_level9text, >_levelAtext, >_levelBtext, >_levelCtext, >_levelDtext, >_levelEtext, >_levelFtext
; @padding:
;     ; Calculation: 15 - length of string
;     .byte 1, 2, 5, 8, 0, 4, 9, 3, 9, 10, 3, 11, 10, 10, 10

;void __fastcall__ movement(void);
.pushseg
.segment "XCD_BANK_01"

.proc _movement
    ; The C code being "ported":
        ; switch (gamemode) {
        ;     case 0x00: cube_movement(); break;
        ;     case 0x01: ship_movement(); break;
        ;     case 0x02: ball_movement(); break;
        ;     case 0x03: break;
        ;     default: break;
        ; } 

        LDX _gamemode
        CPX #$07
        BPL end    
        LDA jump_table_lo, X
        STA <PTR
        LDA jump_table_hi, X
        STA <PTR+1
        JMP (PTR)

        end:
            RTS     ; break;

        jump_table_lo:
            .byte <_cube_movement, <_ship_movement, <_ball_movement, <_ufo_movement, <_cube_movement, <_spider_movement, <_wave_movement
        jump_table_hi:
            .byte >_cube_movement, >_ship_movement, >_ball_movement, >_ufo_movement, >_cube_movement, >_spider_movement, >_wave_movement

.endproc
.popseg

;void __fastcall__ music_play(unsigned char song);
.import _musicoff
.proc _music_play
    ldx	_musicoff
    beq	start
    rts
start:
    LDY #$00
    TSX
bank_loop:
    PHA
    SEC
    SBC music_counts, Y
    BCC found_bank
    INY
    TXS ;Act as if no PHA happened
    BCS bank_loop  ; BRA
    
found_bank:
    TYA
    PHA
    ; No CLC needed as we jumped here with a BCC
    ADC #<FIRST_MUSIC_BANK
    JSR mmc3_tmp_prg_bank_1
    PLA
    CMP current_song_bank
    BEQ :+
    ;If different bank than before reinitalize FS
        STA current_song_bank
        TAY
        LDX music_data_locations_lo, Y
        LDA music_data_locations_hi, Y
        TAY
        LDA #$01
        JSR famistudio_init
    :
    PLA
    JSR famistudio_music_play
    
    JMP _mmc3_pop_prg_bank_1

; Tables currently generated manually

music_data_locations_lo:
.byte <music_data_famidash_music1, <music_data_famidash_music2, <music_data_famidash_music3
music_data_locations_hi:
.byte >music_data_famidash_music1, >music_data_famidash_music2, >music_data_famidash_music3
music_counts:
.byte 5, 7, $FF  ;last bank is marked with an FF to always stop bank picking
.endproc

; void __fastcall__ sfx_play(unsigned char sfx_index, unsigned char channel);
.import _sfxoff
.proc _sfx_play
        tax
        jsr popa
        ldy	_sfxoff
        bne end
        jmp famistudio_sfx_play

    end:
        rts
.endproc

; void __fastcall__ music_update (void);
.proc _music_update
    LDA current_song_bank
    CLC
    ADC #<FIRST_MUSIC_BANK
    JSR mmc3_tmp_prg_bank_1

    JSR famistudio_update
    JMP _mmc3_pop_prg_bank_1
.endproc
; Because i JMPed, the routine is over


;void load_next_sprite(void){
;    mmc3_tmp_prg_bank_1(SPR_BANK_00);
;    if (sprite_data[spr_index<<3] == TURN_OFF) return;
;    tmp3 = sprite_data[(spr_index<<3)+0];  low_byte(activesprites_x[spr_index % max_loaded_sprites]) = tmp3; 
;    tmp3 = sprite_data[(spr_index<<3)+1]; high_byte(activesprites_x[spr_index % max_loaded_sprites]) = tmp3; 
;    tmp3 = sprite_data[(spr_index<<3)+2];  low_byte(activesprites_y[spr_index % max_loaded_sprites]) = tmp3;
;    tmp3 = sprite_data[(spr_index<<3)+3]; high_byte(activesprites_y[spr_index % max_loaded_sprites]) = tmp3;
;    tmp3 = sprite_data[(spr_index<<3)+4]; activesprites_type[spr_index % max_loaded_sprites] = tmp3;
;    // unused byte 5
;    // unused byte 6 
;    // unused byte 7
;
;
;    tmp3 = activesprites_x[spr_index]; activesprites_realx[spr_index % max_loaded_sprites] = tmp3;
;    tmp3 = activesprites_y[spr_index]; activesprites_realy[spr_index % max_loaded_sprites] = tmp3;
;
;    //gray_line();
;    mmc3_pop_prg_bank_1();
;    ++spr_index;
;}

.import _activesprites_x, _activesprites_y, _activesprites_type
.import _activesprites_realx, _activesprites_realy

.export _load_next_sprite := load_next_sprite
.proc load_next_sprite
.import _spr_index
SpriteData = ptr1
SpriteOffset = ptr2

    lda mmc3PRG1Bank
    pha

    lda _sprite_data_bank
    jsr mmc3_set_prg_bank_1

    ; And also keep the "max sprite id" number in x
    ; This is premultiplied by two for the word sized x/y fields which come first
    lda _spr_index
    asl
    tax

    ; Now read the data into the sprite
    
    ldy #0
    lda (_sprite_data),y
    cmp #$ff
    beq @Exit
    iny
    
    ; X - 2 bytes
    sta _activesprites_x,x
    lda (_sprite_data),y
    iny
    sta _activesprites_x+1,x

    ; Y - 2 bytes
    lda (_sprite_data),y
    iny
    sta _activesprites_y,x
    lda (_sprite_data),y
    iny
    sta _activesprites_y+1,x

    ; id - 1 byte
    ; Since its 1 byte, we want to divide the "pre multiplied" offset by 2
    txa
    lsr
    tax
    lda (_sprite_data),y
    ;   no iny, as we ain't using y anymore
    sta _activesprites_type,x

    ; Increment to the next sprite index - 
    ; Add the 5 back to the pointer
    LDA #$05
    CLC
    ADC _sprite_data
    STA _sprite_data
    BCC :+
        INC _sprite_data+1
    :

    ; Copy the low bytes for the active sprite here as well.
    ; Note we couldn't write this eariler when x was multiplied by 2
    txa
    asl
    tay
    lda _activesprites_x,y
    sta _activesprites_realx,x
    lda _activesprites_y,y
    sta _activesprites_realy,x

    ; Increment the _spr_index and and it with #$0F
    INX
    TXA
    AND #$0F
    STA _spr_index

@Exit:
    pla
    jmp mmc3_set_prg_bank_1
.endproc



; char get_position(void){
;     tmp5 -= scroll_x;
;     if (high_byte(tmp5) == 0xff) {
;         load_next_sprite();
;         return 0;
;     }
;     tmp6 -= scroll_y;
;     temp_x = tmp5 & 0x00ff;
;     temp_y = tmp6 & 0x00ff;
;     if (high_byte(tmp5)) return 0;
;     if (high_byte(tmp6)) return 0;
;     return 1;
; }
; void check_spr_objects(void){
;     for (index = 0; index < max_loaded_sprites; ++index){
;         activesprites_active[index] = 0;
;         low_byte(tmp5) = low_byte(activesprites_x[index]);
;         high_byte(tmp5) = high_byte(activesprites_x[index]);
;         low_byte(tmp6) = low_byte(activesprites_y[index]);
;         high_byte(tmp6) = high_byte(activesprites_y[index]);
;         activesprites_active[index] = get_position();
;         activesprites_realx[index] = temp_x;
;         activesprites_realy[index] = temp_y;
;     }
; }

.import _activesprites_active, _scroll_x, _scroll_y
.export _check_spr_objects := check_spr_objects
.proc check_spr_objects
    ; for each sprite we want to check to see if its active
    ; if it is, update its realx/y position
    ; if its not, attempt to load another sprite
    ldx #16 - 1

check_sprite_loop:
        ; X is the current sprite object, y is the premultiplied index for two byte fields
        txa
        asl
        tay
        ; Load two byte X coord to see if we went offscreen
        lda _activesprites_x, y
        sec
        sbc _scroll_x
        lda _activesprites_x+1, y
        sbc _scroll_x+1
        bpl sprite_alive
            txa
            pha
                jsr load_next_sprite
            pla
            tax
            lda #0
            jmp write_active
    sprite_alive:
        ; Sprite is still alive, so check to see if its on screen
        bne sprite_offscreen
        ; sprite is alive AND onscreen x, so now check the Y position
        lda _activesprites_y, y
        clc ; NOTICE: intentionally subtract 1 extra to position them on the screen better
        sbc _scroll_y
        sta _activesprites_realy, x
        lda _activesprites_y+1, y
        sbc _scroll_y+1
        bne sprite_offscreen

        ; totally onscreen so finish updating its scroll position
        lda _activesprites_x, y
        sec
        sbc _scroll_x
        sta _activesprites_realx, x

        lda #1
        bne write_active ; unconditional
sprite_offscreen:
        lda #0
write_active:
        sta _activesprites_active, x
        dex
        bpl check_sprite_loop
    rts
.endproc

.pushseg
.segment "XCD_BANK_00"

.import _player_x, _player_y, _player_gravity, _player_vel_y
.import _ballframe, _robotframe, _robotjumpframe, _spiderframe
.importzp _cube_rotate, _mini
.import _CUBE, _SHIP, _BALL, _ROBOT, _UFO, _SPIDER, _WAVE
.import _MINI_CUBE, _MINI_SHIP, _MINI_BALL, _MINI_ROBOT, _MINI_UFO, _MINI_SPIDER, _MINI_WAVE
.export _drawplayerone

.proc _drawplayerone
    ; C code to be ported:
		; temp_x = high_byte(player_x[0]);
		; if(temp_x > 0xfc) temp_x = 1;
		; if(temp_x == 0) temp_x = 1;
		; switch (gamemode){
		; 	default:

		; 		cube_rotate[0] += CUBE_GRAVITY;
		; 		if (player_vel_y[0] == 0 || player_vel_y[0] == CUBE_GRAVITY || player_vel_y[0] == -CUBE_GRAVITY) cube_rotate[0]= 0;
		; 		if (high_byte(cube_rotate[0]) > 0x05) high_byte(cube_rotate[0]) -= 0x06;

		; 		if (!mini) {
		; 			if (!player_gravity[0]) oam_meta_spr(temp_x, high_byte(player_y[0])-1, CUBE[high_byte(cube_rotate)]);
		; 			else oam_meta_spr_vflipped(temp_x, high_byte(player_y[0])-1, CUBE[high_byte(cube_rotate)]);
		; 		}
		; 		else {
		; 			if (!player_gravity[0]) oam_meta_spr(temp_x, high_byte(player_y[0])-1, MINI_CUBE[high_byte(cube_rotate)]);
		; 			else oam_meta_spr_vflipped(temp_x, high_byte(player_y[0])-1, MINI_CUBE[high_byte(cube_rotate)]);				
		; 		}
		; 		break;
		; 	case 0x01:
		; 		cube_rotate[0] = 0x0400 - player_vel_y[0];
		; 		if (high_byte(cube_rotate) >= 0x08) {
		; 			cube_rotate[0]= high_byte(cube_rotate) >= 0x80 ? 0x0000 : 0x07FF;
		; 		}

		; 		if (!mini) {
		; 			if (!player_gravity[0]) oam_meta_spr(temp_x, high_byte(player_y[0])-1, SHIP[high_byte(cube_rotate)]);
		; 			else oam_meta_spr_vflipped(temp_x, high_byte(player_y[0])-1, SHIP[7-high_byte(cube_rotate)]);
		; 		}
		; 		else {
		; 			if (!player_gravity[0]) oam_meta_spr(temp_x, high_byte(player_y[0])-1, MINI_SHIP[high_byte(cube_rotate)]);
		; 			else oam_meta_spr_vflipped(temp_x, high_byte(player_y[0])-1, MINI_SHIP[7-high_byte(cube_rotate)]);
		; 		}
		; 		break;
				
		; 	case 0x02:
		; 		if (!mini) {
		; 			if (!player_gravity[0]) oam_meta_spr(temp_x, high_byte(player_y[0])-1, BALL[ballframe]);
		; 			else oam_meta_spr_vflipped(temp_x, high_byte(player_y[0])-1, BALL[ballframe]);
		; 			ballframe++;
		; 			if (ballframe > 7) { ballframe = 0; }
		; 		}
		; 		else   {
		; 			if (!player_gravity[0]) oam_meta_spr(temp_x, high_byte(player_y[0])-1, MINI_BALL[ballframe]);
		; 			else oam_meta_spr_vflipped(temp_x, high_byte(player_y[0])-1, MINI_BALL[ballframe]);
		; 		}
		; 		break;

		; 	case 0x03:
		; 		if (!player_gravity[0]) {
		; 			if (player_vel_y[0] == 0 || player_vel_y[0] == CUBE_GRAVITY || player_vel_y[0] == MINICUBE_GRAVITY) kandotemp3[0] = 0;
		; 			else if (player_vel_y[0] > 0) kandotemp3[0] = 1;
		; 			else if (player_vel_y[0] < 0) kandotemp3[0] = 2;
		; 			if (!mini) oam_meta_spr(temp_x, high_byte(player_y[0])-1, UFO[kandotemp3[0]]);
		; 			else oam_meta_spr(temp_x, high_byte(player_y[0])-1, MINI_UFO[kandotemp3[0]]);
		; 		}
		; 		else {
		; 			if (player_vel_y[0] == 0 || player_vel_y[0] == -CUBE_GRAVITY || player_vel_y[0] == -MINICUBE_GRAVITY) kandotemp3[0] = 0;
		; 			else if (player_vel_y[0] > 0) kandotemp3[0] = 1;
		; 			else if (player_vel_y[0] < 0) kandotemp3[0] = 2;
			
		; 			if (!mini) oam_meta_spr_vflipped(temp_x, high_byte(player_y[0])-1, UFO[kandotemp3[0]]);
		; 			else oam_meta_spr_vflipped(temp_x, high_byte(player_y[0])-1, MINI_UFO[kandotemp3[0]]);
		; 		}
		; 		break;
				
		; 	case 0x04:
		; 		if (player_vel_y[0] == 0 || player_vel_y[0] == CUBE_GRAVITY) {
		; 			if (!mini) {
		; 				if (!player_gravity[0]) oam_meta_spr(temp_x, high_byte(player_y[0])-1, ROBOT[robotframe[0]]);
		; 				else oam_meta_spr_vflipped(temp_x, high_byte(player_y[0])-1, ROBOT[robotframe[0]]);
		; 			}
		; 			else {
		; 				if (!player_gravity[0]) oam_meta_spr(temp_x, high_byte(player_y[0])-1, MINI_ROBOT[robotframe[0]]);
		; 				else oam_meta_spr_vflipped(temp_x, high_byte(player_y[0])-1, MINI_ROBOT[robotframe[0]]);					
		; 			}
		; 			robotframe[0]++;
		; 			if (robotframe[0] > 19) { robotframe[0] = 0; }
		; 			break;
		; 		}
		; 		else {
		; 			if (!mini) {
		; 				if (!player_gravity[0]) oam_meta_spr(temp_x, high_byte(player_y[0])-1, ROBOT_JUMP[robotjumpframe[0]]);
		; 				else oam_meta_spr_vflipped(temp_x, high_byte(player_y[0])-1, ROBOT_JUMP[robotjumpframe[0]]);
		; 			}
		; 			else {
		; 				if (!player_gravity[0]) oam_meta_spr(temp_x, high_byte(player_y[0])-1, MINI_ROBOT_JUMP[robotjumpframe[0]]);
		; 				else oam_meta_spr_vflipped(temp_x, high_byte(player_y[0])-1, MINI_ROBOT_JUMP[robotjumpframe[0]]);
		; 			}
		; 			break;
		; 		}
		; 	case 0x05:
		; 		if (player_vel_y[0] == 0 || player_vel_y[0] == CUBE_GRAVITY) {
		; 			if (!mini) {
		; 				if (!player_gravity[0]) oam_meta_spr(temp_x, high_byte(player_y[0])-1, SPIDER[spiderframe[0]]);
		; 				else oam_meta_spr_vflipped(temp_x, high_byte(player_y[0])-1, SPIDER[spiderframe[0]]);
		; 			}
		; 			else {
		; 				if (!player_gravity[0]) oam_meta_spr(temp_x, high_byte(player_y[0])-1, MINI_SPIDER[spiderframe[0]]);
		; 				else oam_meta_spr_vflipped(temp_x, high_byte(player_y[0])-1, MINI_SPIDER[spiderframe[0]]);					
		; 			}
		; 			spiderframe[0]++;
		; 			if (spiderframe[0] > 15) spiderframe[0] = 0;
		; 		}
		; 		else {
		; 			if (!mini) {
		; 				if (!player_gravity[0]) oam_meta_spr(temp_x, high_byte(player_y[0])-1, SPIDER_JUMP[0]);
		; 				else oam_meta_spr_vflipped(temp_x, high_byte(player_y[0])-1, SPIDER_JUMP[0]);
		; 			}
		; 			else {
		; 				if (!player_gravity[0]) oam_meta_spr(temp_x, high_byte(player_y[0])-1, MINI_SPIDER_JUMP[0]);
		; 				else oam_meta_spr_vflipped(temp_x, high_byte(player_y[0])-1, MINI_SPIDER_JUMP[0]);
		; 			}						
		; 		}	
		; 		break;	
	    ; }

	LDX _player_y+1		;
	DEX					;	The Y of oam_meta_spr is high_byte(player_y[0])-1
	STX <SCRY			;__

    LDA _player_x+1     ;__ temp_x = high_byte(player_x[0]);
    BNE :+              ;
        LDA #$01        ;   if(temp_x == 0) temp_x = 1;
		BNE :++			;= BRA
    :                   ;__
    CMP #$FD            ;
    BCC :+              ;	if(temp_x > 0xfc) temp_x = 1;
        LDA #$01        ;
    :                   ;__
    STA <SCRX			;__ The X of oam_meta_spr is temp_x

    ; Set up base pointer for jump tables
    LDA _mini       ;
    BEQ :+          ;   Add 6 if mini mode 
        LDA #$07    ;   ! Increment this value when new gamemodes added
    :               ;__
    CLC             ;   Actual gamemode itself
    ADC _gamemode   ;__
    TAX             ;   Get low byte of table ptr
    LDA sprite_table_table_lo, X
    STA ptr1        ;__
    LDA sprite_table_table_hi, X
    STA ptr1+1      ;__ Get high byte of table ptr

    ; The switch 
    LDX _gamemode
    DEX         ;   case 0x01: ship shit
    jeq ship   ;__
    DEX         ;   case 0x02: ball shit
    jeq ball   ;__
    DEX         ;   case 0x03: ufo shit
    jeq ufo    ;__
    DEX         ;   case 0x04: robot shit
    jeq robot  ;__
    DEX         ;   case 0x05: spider shit
    jeq spider ;__
    dex
    jeq	wave
    
    ; default: cube
    cube:
		; C code:
			; 		cube_rotate[0] += CUBE_GRAVITY;
			; 		if (player_vel_y[0] == 0 || player_vel_y[0] == CUBE_GRAVITY || player_vel_y[0] == -CUBE_GRAVITY) cube_rotate[0]= 0;
			; 		if (high_byte(cube_rotate[0]) > 0x05) high_byte(cube_rotate[0]) -= 0x06;

        LDA #<CUBE_GRAVITY		;
        CLC                     ;
        ADC _cube_rotate        ;
        STA _cube_rotate        ;   cube_rotate[0] += CUBE_GRAVITY;
        BCC :+                  ;
            INC _cube_rotate+1  ;
        :                       ;__

        LDX _player_vel_y+1		;	if highbyte(player_vel_y) == 0 it's possible that
		BEQ :+					;__ PVY == 0 or CUBE_GRAVITY
		INX						;	if highbyte == 0xFF it's possible that
		BNE @cond_no		    ;__	PVY == -CUBE_GRAVITY
			LDA _player_vel_y	;	if lowbyte == -CUBE_GRAVITY
			CMP #<($100 - <CUBE_GRAVITY)
			BNE @cond_no	    ;__
			BEQ @cond_yes	    ;__ This is a fucking mess
		:						;__
		LDA _player_vel_y		;
		BEQ @cond_yes_nold	    ;	if highbyte == 0x00 and lowbyte == CUBE_GRAVITY or 0x00
		CMP #<CUBE_GRAVITY		;
		BNE @cond_no		    ;__
		@cond_yes:			    ;
			LDA #$00			;
		@cond_yes_nold:	        ;	cube_rotate[1] = 0
			STA _cube_rotate+0	;
			STA _cube_rotate+1	;__
		@cond_no:

		LDA _cube_rotate+1		;
		SEC						;
		SBC #$06				;	if (high_byte(cube_rotate[0]) > 0x05) high_byte(cube_rotate[0]) -= 0x06;
		BCC :+					;
			STA _cube_rotate+1	;
		:						;__
		LDY _cube_rotate+1		;__	Y is the index into the table
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
		LDA _ballframe	;	Load index
		TAY				;__
		CLC				;	ballframe++;
		ADC #$01		;__
		AND #$07		;__	if (ballframe > 7) { ballframe = 0; }
		STA _ballframe	;__
		JMP fin

	ufo:
		; Real C code:
			; 		if (!player_gravity[0]) {
			; 			if (player_vel_y[0] == 0 || player_vel_y[0] == CUBE_GRAVITY || player_vel_y[0] == MINICUBE_GRAVITY) kandotemp3[0] = 0;
			; 			else if (player_vel_y[0] > 0) kandotemp3[0] = 1;
			; 			else if (player_vel_y[0] < 0) kandotemp3[0] = 2;
			; 		}
			; 		else {
			; 			if (player_vel_y[0] == 0 || player_vel_y[0] == -CUBE_GRAVITY || player_vel_y[0] == -MINICUBE_GRAVITY) kandotemp3[0] = 0;
			; 			else if (player_vel_y[0] > 0) kandotemp3[0] = 1;
			; 			else if (player_vel_y[0] < 0) kandotemp3[0] = 2;
			; 		}
			;	kandotemp3[0] used as index
		; Modified pseudo C code:
			;	cmptmp = mini ? MINICUBE_GRAVITY : CUBE_GRAVITY;
			;	kandotemp3[0] = 1;
			;	if (0 < highbyte < $80) {}	// do nothing with it
			;	else if ($80 ≤ highbyte ≤ $FF) {
			;		kandotemp3[0] = 2;
			;		if (highbyte == $FF) {
			;			if (player_gravity[0] != $00) {	
			;				if (lowbyte == -cmptmp) kandotemp3[0] = 0;
			;			}
			;		}
			;	} else if (highbyte == $00) {
			;		if (player_gravity[0] == $00) {
			;			if (lowbyte == cmptmp || lowbyte == 0) kandotemp3[0] = 0;
			;		}
			; 	}
		LDA #<CUBE_GRAVITY	;
		LDX _mini			;
		BEQ :+				;	cmptmp = mini ? MINICUBE_GRAVITY : CUBE_GRAVITY;
			LDA #<MINI_CUBE_GRAVITY
		: STA tmp1			;__

		LDY #$1				;__	kandotemp3[0] = 1;
		LDA _player_vel_y+1	;__
		BEQ :+				;__	else if (highbyte == $00) { // later }
		BPL @fin	    	;__	if (0 < highbyte < $80) {}	// do nothing with it
			INY				;__	else if ($80 ≤ highbyte ≤ $FF) { kandotemp3[0] = 2;
			CMP #$FF		;	if (highbyte == $FF) {
			BNE	@fin	    ;__
			LDA _player_gravity
			BEQ @fin	    ;__	if (player_gravity[0] != $00) {	
			LDA _player_vel_y
			CLC				;	if (lowbyte = -cmptmp)
			ADC tmp1		;
			BNE	@fin	    ;__
			TAY				;	kandotemp3[0] = 0;
			JMP fin		;__
		:
		LDX _player_vel_y	;	if (lowbyte == 0) kandotemp3[0] = 0;
		BEQ :+				;__
		ORA _player_gravity+0
		BNE @fin	    	;__	if (player_gravity[0] == $00) {
		CPX tmp1			;__	if (lowbyte == cmptmp)
		BNE @fin	    	;
		:	DEY				;	kandotemp3[0] = 0;
		@fin:   			;
			JMP fin		;__
	robot:
		; C code:
			;	if (player_vel_y[0] == 0 || player_vel_y[0] == CUBE_GRAVITY) {
			;		[index from ROBOT/MINI_ROBOT using robotframe[0]]
			; 		robotframe[0]++;
			; 		if (robotframe[0] > 19) { robotframe[0] = 0; }	
			;	} else {
			;		[index from ROBOT_JUMP/MINI_ROBOT_JUMP using robotjumpframe[0]]
			; 	}
		LDA _player_vel_y+1	;
		BNE :+++			;
		LDA _player_vel_y	;	if (player_vel_y[0] == 0 || player_vel_y[0] == CUBE_GRAVITY) {
		BEQ :+				;
		CMP #<CUBE_GRAVITY	;
		BNE :+++			;__
		:					;
			LDA _robotframe	;	[load robotframe[0] into Y]
			TAY				;__
			CLC				;	robotframe[0]++;
			ADC #$01		;__
			CMP #20			;
			BCC :+			;	if (robotframe[0] > 19) { robotframe[0] = 0; }	
				LDA #$00	;__
			:				;
			STA _robotframe	;__
			JMP fin
		:					;	} else {
			LDA #20			; ! This is the sizeof ROBOT / MINI_ROBOT, change it as needed
			CLC				;	ROBOT_JUMP[X] = ROBOT[X+20]
			ADC _robotjumpframe
			TAY				;__
			JMP fin
	spider:
		; C code:
			;	if (player_vel_y[0] == 0 || player_vel_y[0] == CUBE_GRAVITY) {
			;		[index from SPIDER/MINI_SPIDER using spiderframe[0]]
			; 		spiderframe[0]++;
			; 		if (spiderframe[0] > 15) { spiderframe[0] = 0; }	
			;	} else {
			;		[use SPIDER_JUMP/MINI_SPIDER_JUMP[0]]
			; 	}
		LDA _player_vel_y+1	;
		BNE :++		    	;
		LDA _player_vel_y	;	if (player_vel_y[0] == 0 || player_vel_y[0] == CUBE_GRAVITY) {
		BEQ :+				;
		CMP #<CUBE_GRAVITY	;
		BNE :++		    	;__
		:					;
			LDA _spiderframe	;	[load spiderframe[0] into Y]
			TAY				;__
			CLC				;	spiderframe[0]++;
			ADC #$01		;__
			AND #$0F        ;   if (spiderframe[0] > 15) spiderframe[0] = 0;
			STA _spiderframe;__
			JMP fin
		:					;	} else { SPIDER_JUMP[0] = SPIDER[8]
			LDY #8			; ! This is the sizeof SPIDER / MINI_SPIDER, change it as needed
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
        LDX #$00
    common:
		TYA					;
		ASL					;	Double da index cuz it's a table of shorts
		TAY					;__
        lda     sp          ;
        sec                 ;
        sbc     #2          ;
        sta     sp          ;   sp -= 2
        bcs     :+          ;
        dec     sp+1        ;__
        :
		LDA (ptr1), Y		;	Load low byte
		STA <PTR			;__
		INY					;
		LDA (ptr1), Y		;	Load high byte
		STA <PTR+1			;__
		LDY #$00			;__	THIS IS A MUST
		LDA _player_gravity, X	;	if (!player_gravity[0])
		BNE :+				;__	oam_meta_spr(temp_x, high_byte(player_y[0])-1, [whatever the fuck we set here]);
			JMP oam_meta_spr_params_set
		: JMP oam_meta_spr_vflipped_params_set

    sprite_table_table_lo:
        .byte <_CUBE, <_SHIP, <_BALL, <_UFO, <_ROBOT, <_SPIDER, <_WAVE
        .byte <_MINI_CUBE, <_MINI_SHIP, <_MINI_BALL, <_MINI_UFO, <_MINI_ROBOT, <_MINI_SPIDER, <_MINI_WAVE
    sprite_table_table_hi:
        .byte >_CUBE, >_SHIP, >_BALL, >_UFO, >_ROBOT, >_SPIDER, >_WAVE
        .byte >_MINI_CUBE, >_MINI_SHIP, >_MINI_BALL, >_MINI_UFO, >_MINI_ROBOT, >_MINI_SPIDER, >_MINI_WAVE
.endproc
drawplayer_common := _drawplayerone::common

.import _CUBE2, _SHIP2, _BALL2, _ROBOT2, _UFO2, _SPIDER2, _WAVE2
.import _MINI_CUBE2, _MINI_SHIP2, _MINI_BALL2, _MINI_ROBOT2, _MINI_UFO2, _MINI_SPIDER2, _MINI_WAVE2
.export _drawplayertwo

.proc _drawplayertwo
    ; C code:
        ; temp_x = high_byte(player_x[1]);
        ; if(temp_x > 0xfc) temp_x = 1;
        ; if(temp_x == 0) temp_x = 1;
        ; switch (gamemode){
        ;     default:

        ;         cube_rotate[1] += CUBE_GRAVITY;
        ;         if (player_vel_y[1] == 0 || player_vel_y[1] == CUBE_GRAVITY || player_vel_y[1] == -CUBE_GRAVITY) cube_rotate[1] = 0;
        ;         if (high_byte(cube_rotate[1]) > 0x05) high_byte(cube_rotate[1]) -= 0x06;

        ;         if (!mini) {
        ;             if (!player_gravity[1]) oam_meta_spr(temp_x, high_byte(player_y[1])-1, CUBE2[high_byte(cube_rotate[1])]);
        ;             else oam_meta_spr_vflipped(temp_x, high_byte(player_y[1])-1, CUBE2[high_byte(cube_rotate[1])]);
        ;         }
        ;         else {
        ;             if (!player_gravity[1]) oam_meta_spr(temp_x, high_byte(player_y[1])-1, MINI_CUBE2[high_byte(cube_rotate[1])]);
        ;             else oam_meta_spr_vflipped(temp_x, high_byte(player_y[1])-1, MINI_CUBE2[high_byte(cube_rotate[1])]);				
        ;         }
        ;         break;
        ;     case 0x01:
        ;         cube_rotate[1] = 0x0400 - player_vel_y[1];
        ;         if (high_byte(cube_rotate[1]) >= 0x08) {
        ;             cube_rotate[1] = high_byte(cube_rotate[1]) >= 0x80 ? 0x0000 : 0x07FF;
        ;         }

        ;         if (!mini) {
        ;             if (!player_gravity[1]) oam_meta_spr(temp_x, high_byte(player_y[1])-1, SHIP2[high_byte(cube_rotate[1])]);
        ;             else oam_meta_spr_vflipped(temp_x, high_byte(player_y[1])-1, SHIP2[7-high_byte(cube_rotate[1])]);
        ;         }
        ;         else {
        ;             if (!player_gravity[1]) oam_meta_spr(temp_x, high_byte(player_y[1])-1, MINI_SHIP2[high_byte(cube_rotate[1])]);
        ;             else oam_meta_spr_vflipped(temp_x, high_byte(player_y[1])-1, MINI_SHIP2[7-high_byte(cube_rotate[1])]);
        ;         }
        ;         break;
                
        ;     case 0x02:
        ;         if (!mini) {
        ;             if (!player_gravity[1]) oam_meta_spr(temp_x, high_byte(player_y[1])-1, BALL2[ballframe]);
        ;             else oam_meta_spr_vflipped(temp_x, high_byte(player_y[1])-1, BALL2[ballframe]);
        ;         //	ballframe++;
        ;         //	if (ballframe > 7) { ballframe = 0; }
        ;         }
        ;         else   {
        ;             if (!player_gravity[1]) oam_meta_spr(temp_x, high_byte(player_y[1])-1, MINI_BALL2[ballframe]);
        ;             else oam_meta_spr_vflipped(temp_x, high_byte(player_y[1])-1, MINI_BALL2[ballframe]);
        ;         }
        ;         break;

        ;     case 0x03:
        ;         if (!player_gravity[1]) {
        ;             if (player_vel_y[1] == 0 || player_vel_y[1] == CUBE_GRAVITY || player_vel_y[1] == MINI_CUBE_GRAVITY) kandotemp3[1] = 0;
        ;             else if (player_vel_y[1] > 0) kandotemp3[1] = 1;
        ;             else if (player_vel_y[1] < 0) kandotemp3[1] = 2;
        ;             if (!mini) oam_meta_spr(temp_x, high_byte(player_y[1])-1, UFO2[kandotemp3[1]]);
        ;             else oam_meta_spr(temp_x, high_byte(player_y[1])-1, MINI_UFO2[kandotemp3[1]]);
        ;         }
        ;         else {
        ;             if (player_vel_y[1] == 0 || player_vel_y[1] == -CUBE_GRAVITY || player_vel_y[1] == -MINI_CUBE_GRAVITY) kandotemp3[1] = 0;
        ;             else if (player_vel_y[1] > 0) kandotemp3[1] = 1;
        ;             else if (player_vel_y[1] < 0) kandotemp3[1] = 2;
            
        ;             if (!mini) oam_meta_spr_vflipped(temp_x, high_byte(player_y[1])-1, UFO2[kandotemp3[1]]);
        ;             else oam_meta_spr_vflipped(temp_x, high_byte(player_y[1])-1, MINI_UFO2[kandotemp3[1]]);
        ;         }
        ;         break;
                
        ;     case 0x04:
        ;         if (player_vel_y[1] == 0 || player_vel_y[1] == CUBE_GRAVITY) {
        ;             if (!mini) {
        ;                 if (!player_gravity[1]) oam_meta_spr(temp_x, high_byte(player_y[1])-1, ROBOT2[robotframe[1]]);
        ;                 else oam_meta_spr_vflipped(temp_x, high_byte(player_y[1])-1, ROBOT2[robotframe[1]]);
        ;             }
        ;             else {
        ;                 if (!player_gravity[1]) oam_meta_spr(temp_x, high_byte(player_y[1])-1, MINI_ROBOT2[robotframe[1]]);
        ;                 else oam_meta_spr_vflipped(temp_x, high_byte(player_y[1])-1, MINI_ROBOT2[robotframe[1]]);					
        ;             }
        ;             robotframe[1]++;
        ;             if (robotframe[1] > 19) { robotframe[1] = 0; }
        ;             break;
        ;         }
        ;         else {
        ;             if (!mini) {
        ;                 if (!player_gravity[1]) oam_meta_spr(temp_x, high_byte(player_y[1])-1, ROBOT_JUMP2[robotjumpframe[1]]);
        ;                 else oam_meta_spr_vflipped(temp_x, high_byte(player_y[1])-1, ROBOT_JUMP2[robotjumpframe[1]]);
        ;             }
        ;             else {
        ;                 if (!player_gravity[1]) oam_meta_spr(temp_x, high_byte(player_y[1])-1, MINI_ROBOT_JUMP2[robotjumpframe[1]]);
        ;                 else oam_meta_spr_vflipped(temp_x, high_byte(player_y[1])-1, MINI_ROBOT_JUMP2[robotjumpframe[1]]);
        ;             }
        ;             break;
        ;         }

        ;     case 0x05:
        ;         if (player_vel_y[1] == 0 || player_vel_y[1] == CUBE_GRAVITY) {
        ;             if (!mini) {
        ;                 if (!player_gravity[1]) oam_meta_spr(temp_x, high_byte(player_y[1])-1, SPIDER2[spiderframe[1]]);
        ;                 else oam_meta_spr_vflipped(temp_x, high_byte(player_y[1])-1, SPIDER2[spiderframe[1]]);
        ;             }
        ;             else {
        ;                 if (!player_gravity[1]) oam_meta_spr(temp_x, high_byte(player_y[1])-1, MINI_SPIDER2[spiderframe[1]]);
        ;                 else oam_meta_spr_vflipped(temp_x, high_byte(player_y[1])-1, MINI_SPIDER2[spiderframe[1]]);					
        ;             }
        ;             spiderframe[1]++;
        ;             if (spiderframe[1] > 15) spiderframe[1] = 0;
        ;         }
        ;         else {
        ;             if (!mini) {
        ;                 if (!player_gravity[1]) oam_meta_spr(temp_x, high_byte(player_y[1])-1, SPIDER_JUMP2[0]);
        ;                 else oam_meta_spr_vflipped(temp_x, high_byte(player_y[1])-1, SPIDER_JUMP2[0]);
        ;             }
        ;             else {
        ;                 if (!player_gravity[1]) oam_meta_spr(temp_x, high_byte(player_y[1])-1, MINI_SPIDER_JUMP2[0]);
        ;                 else oam_meta_spr_vflipped(temp_x, high_byte(player_y[1])-1, MINI_SPIDER_JUMP2[0]);
        ;             }						
        ;         }	
        ;         break;	
        ; }
    LDX _player_y+3		;
	DEX					;	The Y of oam_meta_spr is high_byte(player_y[1])-1
	STX <SCRY			;__

    LDA _player_x+3     ;__ temp_x = high_byte(player_x[1]);
    BNE :+              ;
        LDA #$01        ;   if(temp_x == 0) temp_x = 1;
		BNE :++			;= BRA
    :                   ;__
    CMP #$FD            ;
    BCC :+              ;	if(temp_x > 0xfc) temp_x = 1;
        LDA #$01        ;
    :                   ;__
    STA <SCRX			;__ The X of oam_meta_spr is temp_x

    ; Set up base pointer for jump tables
    LDA _mini       ;
    BEQ :+          ;   Add 6 if mini mode 
        LDA #$07    ;   ! Increment this value when new gamemodes added
    :               ;__
    CLC             ;   Actual gamemode itself
    ADC _gamemode   ;__
    TAX             ;   Get low byte of table ptr
    LDA sprite_table_table_lo, X
    STA ptr1        ;__
    LDA sprite_table_table_hi, X
    STA ptr1+1      ;__ Get high byte of table ptr

    ; The switch 
    LDX _gamemode
    DEX         ;   case 0x01: ship shit
    jeq ship   ;__
    DEX         ;   case 0x02: ball shit
    jeq ball   ;__
    DEX         ;   case 0x03: ufo shit
    jeq ufo    ;__
    DEX         ;   case 0x04: robot shit
    jeq robot  ;__
    DEX         ;   case 0x05: spider shit
    jeq spider ;__
    DEX         ;   case 0x05: spider shit
    jeq wave ;__
    
    ; default: cube
    cube:
		; C code:
			; 		cube_rotate[1] += CUBE_GRAVITY;
			; 		if (player_vel_y[1] == 0 || player_vel_y[1] == CUBE_GRAVITY || player_vel_y[1] == -CUBE_GRAVITY) cube_rotate[1]= 0;
			; 		if (high_byte(cube_rotate[1]) > 0x05) high_byte(cube_rotate[1]) -= 0x06;

        LDA #<CUBE_GRAVITY		;
        CLC                     ;
        ADC _cube_rotate+2      ;
        STA _cube_rotate+2      ;   cube_rotate[1] += CUBE_GRAVITY;
        BCC :+                  ;
            INC _cube_rotate+3  ;
        :                       ;__

        LDX _player_vel_y+3		;	if highbyte(player_vel_y) == 0 it's possible that
		BEQ :+					;__ PVY == 0 or CUBE_GRAVITY
		INX						;	if highbyte == 0xFF it's possible that
		BNE @cond_no		    ;__	PVY == -CUBE_GRAVITY
			LDA _player_vel_y+2	;	if lowbyte == -CUBE_GRAVITY
			CMP #<($100 - <CUBE_GRAVITY)
			BNE @cond_no	    ;__
			BEQ @cond_yes   	;__ This is a fucking mess
		:						;__
		LDA _player_vel_y+2		;
		BEQ @cond_yes_nold	    ;	if highbyte == 0x00 and lowbyte == CUBE_GRAVITY or 0x00
		CMP #<CUBE_GRAVITY		;
		BNE @cond_no		    ;__
		@cond_yes:		    	;
			LDA #$00			;
		@cond_yes_nold:	        ;	cube_rotate[1] = 0
			STA _cube_rotate+2	;
			STA _cube_rotate+3	;__
		@cond_no:

		LDA _cube_rotate+3		;
		SEC						;
		SBC #$06				;	if (high_byte(cube_rotate[1]) > 0x05) high_byte(cube_rotate[1]) -= 0x06;
		BCC :+					;
			STA _cube_rotate+3	;
		:						;__
		LDY _cube_rotate+3		;__	Y is the index into the table
		JMP fin
	
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
		JMP fin

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
		; ADC #$01		;__
		; AND #$07		;__	if (ballframe > 7) { ballframe = 0; }
		; STA _ballframe	;__
		LDY _ballframe
		JMP fin

	ufo:
		; Real C code:
			; 		if (!player_gravity[1]) {
			; 			if (player_vel_y[1] == 0 || player_vel_y[1] == CUBE_GRAVITY || player_vel_y[1] == MINICUBE_GRAVITY) kandotemp3[1] = 0;
			; 			else if (player_vel_y[1] > 0) kandotemp3[1] = 1;
			; 			else if (player_vel_y[1] < 0) kandotemp3[1] = 2;
			; 		}
			; 		else {
			; 			if (player_vel_y[1] == 0 || player_vel_y[1] == -CUBE_GRAVITY || player_vel_y[1] == -MINICUBE_GRAVITY) kandotemp3[1] = 0;
			; 			else if (player_vel_y[1] > 0) kandotemp3[1] = 1;
			; 			else if (player_vel_y[1] < 0) kandotemp3[1] = 2;
			; 		}
			;	kandotemp3[1] used as index
		; Modified pseudo C code:
			;	cmptmp = mini ? MINICUBE_GRAVITY : CUBE_GRAVITY;
			;	kandotemp3[1] = 1;
			;	if (0 < highbyte < $80) {}	// do nothing with it
			;	else if ($80 ≤ highbyte ≤ $FF) {
			;		kandotemp3[1] = 2;
			;		if (highbyte == $FF) {
			;			if (player_gravity[1] != $00) {	
			;				if (lowbyte == -cmptmp) kandotemp3[1] = 0;
			;			}
			;		}
			;	} else if (highbyte == $00) {
			;		if (player_gravity[1] == $00) {
			;			if (lowbyte == cmptmp || lowbyte == 0) kandotemp3[1] = 0;
			;		}
			; 	}
		LDA #<CUBE_GRAVITY	;
		LDX _mini			;
		BEQ :+				;	cmptmp = mini ? MINICUBE_GRAVITY : CUBE_GRAVITY;
			LDA #<MINI_CUBE_GRAVITY
		: STA tmp1			;__

		LDY #$1				;__	kandotemp3[1] = 1;
		LDA _player_vel_y+3	;__
		BEQ :+				;__	else if (highbyte == $00) { // later }
		BPL @fin		    ;__	if (0 < highbyte < $80) {}	// do nothing with it
			INY				;__	else if ($80 ≤ highbyte ≤ $FF) { kandotemp3[1] = 2;
			CMP #$FF		;	if (highbyte == $FF) {
			BNE	@fin    	;__
			LDA _player_gravity+1
			BEQ @fin    	;__	if (player_gravity[1] != $00) {	
			LDA _player_vel_y+2
			CLC				;	if (lowbyte = -cmptmp)
			ADC tmp1		;
			BNE	@fin	    ;__
			TAY				;	kandotemp3[1] = 0;
			JMP fin		    ;__
		:
		LDX _player_vel_y+2	;	if (lowbyte == 0) kandotemp3[1] = 0;
		BEQ :+				;__
		ORA _player_gravity+1
		BNE @fin		    ;__	if (player_gravity[1] == $00) {
		CPX tmp1			;__	if (lowbyte == cmptmp)
		BNE @fin		    ;
		:	DEY				;	kandotemp3[1] = 0;
		@fin:		    	;
			JMP fin	    	;__
	robot:
		; C code:
			;	if (player_vel_y[1] == 0 || player_vel_y[1] == CUBE_GRAVITY) {
			;		[index from ROBOT/MINI_ROBOT using robotframe[1]]
			; 		robotframe[1]++;
			; 		if (robotframe[1] > 19) { robotframe[1] = 0; }	
			;	} else {
			;		[index from ROBOT_JUMP/MINI_ROBOT_JUMP using robotjumpframe[1]]
			; 	}
		LDA _player_vel_y+3	;
		BNE :+++			;
		LDA _player_vel_y+2	;	if (player_vel_y[1] == 0 || player_vel_y[1] == CUBE_GRAVITY) {
		BEQ :+				;
		CMP #<CUBE_GRAVITY	;
		BNE :+++			;__
		:					;
			LDA _robotframe+1;	[load robotframe[1] into Y]
			TAY				;__
			CLC				;	robotframe[1]++;
			ADC #$01		;__
			CMP #20			;
			BCC :+			;	if (robotframe[1] > 19) { robotframe[1] = 0; }	
				LDA #$00	;__
			:				;
			STA _robotframe+1;__
			JMP fin
		:					;	} else {
			LDA #20			; ! This is the sizeof ROBOT / MINI_ROBOT, change it as needed
			CLC				;	ROBOT_JUMP[X] = ROBOT[X+20]
			ADC _robotjumpframe+1
			TAY				;__
			JMP fin
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
		BNE :++		    	;
		LDA _player_vel_y+2	;	if (player_vel_y[1] == 0 || player_vel_y[1] == CUBE_GRAVITY) {
		BEQ :+				;
		CMP #<CUBE_GRAVITY	;
		BNE :++		    	;__
		:					;
			LDA _spiderframe+1;	[load spiderframe[1] into Y]
			TAY				;__
			CLC				;	spiderframe[1]++;
			ADC #$01		;__
			AND #$0F        ;   if (spiderframe[1] > 15) spiderframe[1] = 0;
			STA _spiderframe+1;__
			JMP fin
		:					;	} else { SPIDER_JUMP[0] = SPIDER[8]
			LDY #8			; ! This is the sizeof SPIDER / MINI_SPIDER, change it as needed
			JMP fin
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
		; JMP fin



	fin:
        LDX #$01
		JMP drawplayer_common
	sprite_table_table_lo:
		.byte <_CUBE2, <_SHIP2, <_BALL2, <_UFO2, <_ROBOT2, <_SPIDER2, <_WAVE2
		.byte <_MINI_CUBE2, <_MINI_SHIP2, <_MINI_BALL2, <_MINI_UFO2, <_MINI_ROBOT2, <_MINI_SPIDER2, <_MINI_WAVE2
	sprite_table_table_hi:
		.byte >_CUBE2, >_SHIP2, >_BALL2, >_UFO2, >_ROBOT2, >_SPIDER2, >_WAVE2
		.byte >_MINI_CUBE2, >_MINI_SHIP2, >_MINI_BALL2, >_MINI_UFO2, >_MINI_ROBOT2, >_MINI_SPIDER2, >_MINI_WAVE2

.endproc
.popseg

.pushseg 
.segment "CODE"

.importzp _temp_x, _temp_y, _temp_room, _collision
.export _bg_collision_sub
.proc _bg_collision_sub
    ; C code:
        ; if(temp_y >= 0xf0) return 0;
        ; coordinates = (temp_x >> 4) + ((temp_y) & 0xf0);
        ; // we just need 4 bits each from x and y
        ; tmp3 = temp_room&1; //high byte
        ; if (tmp3 && coordinates >= 0xc0) return COL_ALL;
        ; if (tmp3 == 0)
        ;     collision = collisionMap0[coordinates];
        ; else
        ;     collision = collisionMap1[coordinates];
        ; return is_solid[collision];
    LDA _temp_y     ;
    CMP #$F0        ;   if(temp_y >= 0xf0) return 0;
    BCS Return0	;__
    AND #$F0        ;	temp_y & 0xF0
    STA tmp1        ;__
	LDA _temp_x		;
	LSR				;
	LSR				;	temp_x >> 4
	LSR				;
	LSR				;__
	ORA tmp1		;	coordinates = (temp_x >> 4) + ((temp_y) & 0xf0);
	TAX				;__

	LDA _temp_room	;	tmp3 = temp_room&1;
	AND #$01		;__
	BNE Room1		;__
	LDA _collisionMap0,X	; collision = collisionMap0[coordinates];
	JMP BothRooms

	Room1:
	; "tmp3" is 1, check for coordinates >= $C0
	CPX #$C0			;	if (tmp3 && coordinates >= 0xc0) return COL_ALL;
	BCS ReturnColAll	;__
	LDA _collisionMap1,X	; collision = collisionMap0[coordinates];
	BothRooms:
	STA _collision	;
	TAX				;__
	LDA _is_solid,X	;	return is_solid[collision];
	RTS				;__

	Return0:
	LDA #$00
	RTS

	ReturnColAll:
	LDA #$40
	RTS

.endproc

.popseg