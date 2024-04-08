; Custom routines implemented specifically for famidash (some are totally not stolen from famitower)

.import _level_list, _sprite_list, _bank_list
.import _rld_column, _collisionMap0, _collisionMap1 ; used by C code
.import _scroll_x, _level_data_bank
.import _song, _level
.import _cube_movement, _ship_movement, _ball_movement, _ufo_movement
.importzp _gamemode
.importzp _tmp1, _tmp2, _tmp3, _tmp4  ; C-safe temp storage
.import _DATA_PTR
.import pusha, pushax
.import _level1text, _level2text, _level3text, _level4text, _level5text, _level6text, _level7text, _level8text, _level9text, _levelAtext
.import _increase_parallax_scroll_column
.import FIRST_MUSIC_BANK

.global metatiles_top_left, metatiles_top_right, metatiles_bot_left, metatiles_bot_right, metatiles_attr

.macpack longbranch

.export _oam_meta_spr_vflipped
.export _init_rld, _unrle_next_column, _draw_screen_R
; .export _refreshmenu
.export _movement
.export _music_play, _music_update

.importzp _level_data
level_data = _level_data

;void __fastcall__ oam_meta_spr_vflipped(unsigned char x,unsigned char y,const unsigned char *data);

.segment "ZEROPAGE"
    rld_value:      .res 1
    rld_run:        .res 1

.segment "BSS"
    columnBuffer:   .res 15 * 2 ; column buffer, to be pushed to the collision map

    current_song_bank: .res 1
    scroll_count:   .res 1

.export _scroll_count := scroll_count

.export _parallax_scroll_column := parallax_scroll_column
.export _parallax_scroll_column_start := parallax_scroll_column_start
    parallax_scroll_column: .res 1
    parallax_scroll_column_start: .res 1

.segment "CODE_2"

_oam_meta_spr_vflipped:

    sta <PTR
    stx <PTR+1

    ldy #1      ;2 popa calls replacement, performed in reversed order
    lda (sp),y
    dey
    sta <SCRX
    lda (sp),y
    sta <SCRY
    
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
.export _one_vram_buffer_horz_repeat
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
    STA tmp1            ;__ Store pointer for bank table

    LDY #>_level_list   ;   Get high byte of level_list ptr
    STY ptr1+1          ;__
    ;!S LDY #>_sprite_list  ;   Get high byte of sprite_list ptr
    ASL                 ;
    BCC :+              ;
        INC ptr1+1      ;   Adjust high bytes if level num >= $80
        ;!S INY             ;__
    : 
    ;!S STY ptr2+1        ;__ Store high byte of sprite_list ptr
    LDY #<_level_list   ;
    STY ptr1            ;
    ;!S LDY #<_sprite_list  ;   Get and store low bytes
    ;!S STY ptr2            ;

    TAY                 ;__ Get the pointer

    LDA (ptr1),y        ;   Load low byte of level data pointer
    STA level_data      ;__
    ;!S LDA (ptr2),y        ;   Load low byte of sprite data pointer
    ;!S STA insert_var_here ;__

    INY                 ;   Now do high bytes

    LDA (ptr1),y        ;
    STA level_data+1    ;__ Load high byte of level data pointer
    ;!S LDA (ptr2),y        ;   Load low byte of sprite data pointer
    ;!S STA insert_var_here+1;__

    LDY tmp1            ;__ Load pointer to bank table
    LDA _bank_list,y    ;   Get level data bank
    STA _level_data_bank;__
    
    JSR mmc3_set_prg_bank_1

    LDY #$00            ;-  For both (zp),y addressing and rld_column
    STY _rld_column     ;__ Reset scrolling

    ; Read header
    LDA (level_data),y  ;
    STA _song           ;   Song number
    INCW level_data     ;__

    LDA (level_data),y  ;
    STA _gamemode       ;   Starting level number
    ; JSR incwlvl_checkC000

    ; ; LDA (level_data),y  ;
    ; ; STA ???             ;   Starting speed
    ; INCW level_data     ;__

    ; ; LDA (level_data),y  ;
    ; ; STA ???             ;   Starting BG color
    ; JSR incwlvl_checkC000

    ; ; LDA (level_data),y  ;
    ; ; STA ???             ;   Starting ground color

    ; ;3 unused bytes + 1 increment
    ; ; Code for that is just as below, just replace the 6 with 3

    ;ill do 6 unused bytes intead + 1 increment, is faster
    LDA level_data
    CLC
    ADC #6+1
    STA level_data
    BCC :++
        LDX level_data+1
        INX
        CPX #$C0
        BMI :+
            INC _level_data_bank
            LDA _level_data_bank
            JSR mmc3_set_prg_bank_1
            LDX #$C0
        : STX level_data+1
    :

    LDA (level_data),y  ;
    STA rld_value       ;   Load rld_value, ++level_data
    INCW level_data     ;__

    LDA (level_data),y  ;
    STA rld_run         ;__ Load rld_run, ++level_data
    ; JMP incwlvl_checkC000

incwlvl_checkC000:  ; clobbers A, and clobbers X with Y if banks are switched
    INC level_data
    BNE :+
        INC level_data+1
        LDA level_data+1
        CMP #$C0
        BNE :+
        ; switch banks
        LDA #$A0            ;   Reset memory-mapped ptr
        STA level_data+1    ;__
        INC _level_data_bank ;_ Increment bank
        LDA _level_data_bank
        JMP mmc3_set_prg_bank_1 ;__ Switch the bank
    :   
    RTS

_unrle_next_column:
    ; The C code being ported:
        ; void unrle_next_column(void){ // this should explain itself
        ;     y = 0;
        ;     while (y < 27) { // level is 27 tiles high, so run for 27 tiles
        ;         columnBuffer[y] = rld_value; // write a value to the column buffer
        ;         ++y; // increment column buffer write location
        ;         --rld_run; // decrement run by 1
        ;         if (rld_run == 0){
        ;             rld_value = *level_data; // go to the next rle index in the level data
        ; 			++level_data;
        ; 			rld_run = *level_data; // go to the next rle index in the level data
        ; 			++level_data;
        ;         }
        ;     }
        ;     y = 0;
        ;     while (y < 27) { // write the column buffer to the collision map
        ;         collisionMap0[(y<<4)+rld_column] = columnBuffer[y];
        ;         // NEVER use two pointers on the same line.
        ;         // it will compile to 55 instructions whereas doing the above compiles to just 10
        ;         ++y;
        ;     }
        ;     ++rld_column;
        ; 	rld_column &= 0x0F;
        ; }

    LDY #$00
    LDX #$00
    LDA rld_value

    @FirstLoop:
        STA columnBuffer, Y
        DEC rld_run
        BEQ @UpdateValueRun
        INY
        CPY #27
        BNE @FirstLoop
        BEQ @WriteSetup ; Guaranteed jump
    
    @UpdateValueRun:
        LDA (level_data, X) ;
        STA rld_value       ;   Load rld_value, ++level_data
        INCW level_data     ;__

        LDA (level_data, X) ;
        STA rld_run         ;__ Load rld_run, ++level_data
        JSR incwlvl_checkC000

        LDA rld_value

        INY
        CPY #27
        BNE @FirstLoop
    
    @WriteSetup:
        ; Set Y to 26-16, which is the maximum index
        LDY #(26-16)

        ; Y<<4+rld_column is handled through X
        LDA _rld_column
        ; The last opcode affecting the carry is the CPY, which cleared the carry when
        ; Y reached 27. Therefore the carry is set, needing a -1       
        ADC #<(26<<4)-1  ; The low byte due to 26<<4 being $1A0
        TAX

        ; The ADC clears the carry, and it needs to be set for the subtraction in the
        ; loop to work (i found no way around this, even with SBC)
        SEC

    @FirstWriteLoop:
        LDA columnBuffer+16, Y        ; Get columnBuffer[y]
        STA _collisionMap0+$100, X ; Store into collisionMap[(y<<4)+rld_column]

        ; None of the opcodes in this loop affect carry, except for the SBC,
        ; and the SBC always leaves the carry set unless it underflows below 0,
        ; at which point you exit the loop
        TXA
        SBC #$10
        TAX

        DEY
        BCS @FirstWriteLoop ; If the carry is clear, a borrow occured in the SBC, indicating an underflow
    
    ; Set Y to 15
    LDY #15

    ; X is already at the correct value, but the carry isn't
    SEC
    
    @SecondWriteLoop:
        LDA columnBuffer, Y
        STA _collisionMap0, X

        ; Check first loop for why no SEC
        TXA
        SBC #$10
        TAX

        DEY
        BCS @SecondWriteLoop

    ; X contains rld_column in the low nybble, so just increment it
    INX
    TXA
    AND #$0F
    STA _rld_column
    RTS

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
;     .byte <_level1text, <_level2text, <_level3text, <_level4text, <_level5text, <_level6text, <_level7text, <_level8text, <_level9text, <_levelAtext, <_levelBtext, <_levelCtext
; @string_ptrs_hi:
;     .byte >_level1text, >_level2text, >_level3text, >_level4text, >_level5text, >_level6text, >_level7text, >_level8text, >_level9text, >_levelAtext, >_levelBtext, >_levelCtext
; @padding:
;     ; Calculation: 15 - length of string
;     .byte 1, 2, 5, 8, 0, 4, 9, 3, 9, 10, 11, 10

;void __fastcall__ movement(void);
_movement:
    ; The C code being "ported":
        ; switch (gamemode) {
        ;     case 0x00: cube_movement(); break;
        ;     case 0x01: ship_movement(); break;
        ;     case 0x02: ball_movement(); break;
        ;     case 0x03: break;
        ;     default: break;
        ; } 

    ; !WHEN THE AMOUNT OF IMPLEMENTED GAMEMODES EXCEEDS 6 UNCOMMENT THE FOLLOWING CODE:
    ; !==== CODE START
        ; LDX _gamemode
        ; CPX #$03
        ; BPL @end    
        ; LDA @jump_table_lo, X
        ; STA <PTR
        ; LDA @jump_table_hi, X
        ; STA <PTR+1
        ; JMP (PTR)

        ; @end:
        ;     RTS     ; break;

        ; @jump_table_lo:
        ;     .byte <_cube_movement, <_ship_movement, <_ball_movement, <_ufo_movement
        ; @jump_table_hi:
        ;     .byte >_cube_movement, >_ship_movement, >_ball_movement, >_ufo_movement
    ; !==== CODE END
    ; !Currently it takes less cycles to just do the following:
    LDX _gamemode		; switch (gamemode)
    jeq _cube_movement	; case 0x00: cube_movement(); break;
    DEX					; case 0x01:
    jeq _ship_movement	;	ship_movement(); break;
    DEX					; case 0x02:
    jeq _ball_movement	;	ball_movement(); break;
    DEX					; case 0x03:
    jeq _ufo_movement	;	ufo_movement(); break;
    RTS					; case 0x04: default: break;

;void __fastcall__ music_play(unsigned char song);
_music_play:
    LDY #$00
    TSX
@bank_loop:
    PHA
    SEC
    SBC @music_counts, Y
    BCC @found_bank
    INY
    TXS ;Act as if no PHA happened
    BCS @bank_loop  ; BRA
    
@found_bank:
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
        LDX @music_data_locations_lo, Y
        LDA @music_data_locations_hi, Y
        TAY
        LDA #$01
        JSR famistudio_init
    :
    PLA
    JSR famistudio_music_play
    
    JMP _mmc3_pop_prg_bank_1

; Tables currently generated manually

@music_data_locations_lo:
.byte <music_data_1, <music_data_2, <music_data_3
@music_data_locations_hi:
.byte >music_data_1, >music_data_2, >music_data_3
@music_counts:
.byte 6, 18, $FF  ;last bank is marked with an FF to always stop bank picking

; void __fastcall__ music_update (void);
_music_update:
    LDA current_song_bank
    CLC
    ADC #<FIRST_MUSIC_BANK
    JSR mmc3_tmp_prg_bank_1

    JSR famistudio_update
    JMP _mmc3_pop_prg_bank_1

; Because i JMPed, the routine is over

SPR_BANK_00 = $1c


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
.importzp _sprite_data
.import _spr_index
SpriteData = ptr1
SpriteOffset = ptr2

    lda _spr_index
    cmp #$ff
    bne :+
        ; Maximum sprites reached?
        rts
    :

    lda #$1c
    jsr _mmc3_tmp_prg_bank_1


    lda #0
    sta SpriteOffset+1

    ; Sprite data is 8 bytes, so multiply by 8 (16 bit)
    lda _spr_index
    asl
    rol SpriteOffset+1
    asl
    rol SpriteOffset+1
    asl
    rol SpriteOffset+1
    sta SpriteOffset
    ; And also keep the "max sprite id" number in x
    ; This is premultiplied by two for the word sized x/y fields which come first
    lda _spr_index
    and #$0f
    asl
    tax
    
    ; Copy the pointer used for the sprite data to ZP so we can use (zp), y addressing
    lda _sprite_data
    clc
    adc SpriteOffset
    sta SpriteData
    lda _sprite_data+1
    adc SpriteOffset+1
    sta SpriteData+1

    ; Now read the data into the sprite
    
    ldy #0
    lda (SpriteData),y
    iny
    cmp #$ff ; If we've reached the end of the sprite data exit
    beq @EarlyExit
    
    ; X - 2 bytes
    sta _activesprites_x,x
    lda (SpriteData),y
    iny
    sta _activesprites_x+1,x

    ; Y - 2 bytes
    lda (SpriteData),y
    iny
    sta _activesprites_y,x
    lda (SpriteData),y
    iny
    sta _activesprites_y+1,x

    ; id - 1 byte
    ; Since its 1 byte, we want to divide the "pre multiplied" offset by 2
    txa
    lsr
    tax
    lda (SpriteData),y
    iny
    sta _activesprites_type,x

    ; Copy the low bytes for the active sprite here as well.
    ; Note we couldn't write this eariler when x was multiplied by 2
    txa
    asl
    tay
    lda _activesprites_x,y
    sta _activesprites_realx,x
    lda _activesprites_y,y
    sta _activesprites_realy,x

    ; Increment to the next sprite index
    inc _spr_index
    bne @Exit

@EarlyExit:
    lda #$ff
    sta _spr_index
@Exit:
    jmp _mmc3_pop_prg_bank_1
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