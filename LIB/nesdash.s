; Custom routines implemented specifically for famidash (some are totally not stolen from famitower)

.import _level_list, _sprite_list, _bank_list
.import _rld_column, _collisionMap0, _collisionMap1 ; used by C code
.import _scroll_x, _level_data_bank
.import _song, _level
.importzp _gamemode
.importzp _tmp1, _tmp2, _tmp3, _tmp4  ; C-safe temp storage
.import _DATA_PTR
.import pusha, pushax
.import _level1text, _level2text, _level3text, _level4text, _level5text, _level6text, _level7text

.import FIRST_MUSIC_BANK
.macpack longbranch

.export _oam_meta_spr_vflipped
.export _init_rld, _unrle_next_column, _draw_screen_R
.export _refreshmenu
.export _music_play, _music_update

;void __fastcall__ oam_meta_spr_vflipped(unsigned char x,unsigned char y,const unsigned char *data);

.segment "ZEROPAGE"
    level_data:     .res 2
    rld_value:      .res 1
    rld_run:        .res 1

.segment "BSS"
    columnBuffer:   .res 27; column buffer, to be pushed to the collision map

    current_song_bank: .res 1
    scroll_count:   .res 1

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

_draw_screen_R:

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
    CLC
    ADC #$FC
    LSR                     ;
    LSR                     ;   >> 4
    LSR                     ;
    LSR                     ;__
    STA tmp4

    LDX scroll_count
    BNE @framenot0

    LDA tmp4
    CMP _rld_column         ;   If X == rld column, decompress shit
    BEQ @frame0
    RTS
    
    @framenot0:
        CPX #$01
        BEQ @frame1
        JMP @attributes

    @frame0:
        ; Switch banks
        LDA _level_data_bank
        JSR mmc3_set_prg_bank_1

        JSR _unrle_next_column

    @frame1:

        

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

        LDA #($20+$80)  ; 0th nametable + NT_UPDATE_VERT
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
        
        LDA columnBuffer    ;
        EOR #$FF            ;   Force update pointer
        STA META_VAR        ;__
        ; Load max
        LDA #15
        STA tmp2
        ; Load Y value
        LDA scroll_count
        AND #1
        STA tmp3
        ; Call for upper tiles
        LDY #$00
        JSR @tilewriteloop

        ; Load new max
        LDA #27
        STA tmp2
        ; Add offset to X
        TXA
        CLC
        ADC #(TileSizeHi-(15*2))
        TAX
        ; Call for lower tiles
        JSR @tilewriteloop

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

    @attributes:
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

        LDA #8
        STA tmp1

        LDX #$00
        
        ; Force metatile update
        LDA (ptr1,X)
        EOR #$FF
        STA META_VAR

        JSR @attributeLoop1

        ; Last byte has no bottom tiles
        LDA columnBuffer+7
        AND #$0F
        STA columnBuffer+7

        ; Update new maximum
        LDA #8+6
        STA tmp1

        ; Update pointer (collisionMap0 is 240 bytes, not 256)
        LDA ptr1
        ; The carry is set by the CPX at the end of the loop
        SBC #$10
        STA ptr1
        BCS :+
            DEC ptr1+1
        :

        JSR @attributeLoop1

        ; Get address i
        
        LDA ptr3
        LSR
        ORA #$C0
        
        ; Store address
        LDX VRAM_INDEX
        @addressLoop:
            ; Low byte
            STA VRAM_BUF+AttrOff0+1,X
            STA VRAM_BUF+AttrOff1+1,X
            TAY
            ; High byte
            LDA #$23
            STA VRAM_BUF+AttrOff0,X
            ORA #$08
            STA VRAM_BUF+AttrOff1,X
            TYA

            INX 
            INX
            INX

            CLC
            ADC #$08
            BCC @addressLoop
        
        LDY #14

        LDA VRAM_INDEX
        ADC #AttrEnd-1  ; Carry is set by the ADC : BCC
        STA VRAM_INDEX  ; State that the block is now occupied
        TAX

        @dataLoop:
            LDA columnBuffer-1,Y
            STA VRAM_BUF-3+2,X

            DEX
            DEX
            DEX
            DEY
            BNE @dataLoop
        
        ; Finish off the routine
        ; X has VRAM_INDEX, mark this block as taken
        LDA #$FF
        STA VRAM_BUF+AttrEnd,X
        ; Reset frame counter
        LDA #$00
        STA scroll_count
        RTS

    @attributeLoop1:
            ; Read upper left metatile
            LDY #$00
            JSR @getAttr
            STA ptr2

            ; Read lower left metatile (higher chance of being the same, due to RLE)
            LDY #$10
            JSR @getAttr
            STA ptr2+1

            ; Read upper right metatile
            LDY #$01
            JSR @getAttr
            ASL
            ASL
            ORA ptr2
            STA ptr2

            ; Read lower right metatile
            LDY #$11
            JSR @getAttr
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
            CPX tmp1
            BNE @attributeLoop1
        RTS

    @getAttr:
        ; Read metatile
        LDA (ptr1),Y
        CMP META_VAR
        BEQ :+
            STA META_VAR
            JSR MT_MULT5
        :
        LDY #$04

        ; Read its attributes
        LDA (META_PTR2),Y
        RTS


    @tilewriteloop:
            ;Fetch metatile pointer
            STY tmp1

            LDA columnBuffer,Y  ;
            CMP META_VAR        ;   No need to get metatile pointer for the same metatile
            BEQ :+              ;__
                STA META_VAR    ;   Get new metatile pointer
                JSR MT_MULT5    ;__
            :
            LDY tmp3

            ;Fetch data, write to buffer

            ;Tile:
            ; 1 | 2 
            ;---+---
            ; 3 | 4 

            LDA (META_PTR2),Y   ;   Tile 1
            STA VRAM_BUF+TileOff0+3,X
            INY                 ;__
            INY                 ;__ Tile 2
            LDA (META_PTR2),Y   ;   Tile 3
            STA VRAM_BUF+TileOff0+4,X


            ;Buffer the attributes in column buffer

            INX
            INX

            LDY tmp1
            INY
            CPY tmp2
            BNE @tilewriteloop
        RTS


_refreshmenu:
	; The C code being "ported":
		; ppu_off();
		; vram_adr(NTADR_A(2,25));	
		; switch (level){
		; 	case 0x0N:  N = 1..7
		; 		for(tmp1=0;levelKtext[tmp1];++tmp1){
		; 			vram_put(0xA0+levelNtext[tmp1]);
		; 		};
		; 		break;
		; }		
		; ppu_on_all();
		; return;
	; Instead of ppu_off/on i do it with the VRAM buffer
	; like a civilised person
	LDY VRAM_INDEX
	;! THE ADDRESS CORRESPONDING TO NTADR_A(2,25) IS
	;! $24A2, AND OR'D WITH THE HORIZONTAL UPDATE FLAG
	;! IT BECOMES $64A2. THIS IS HARDCODED, CHANGE THESE
	;! LINES IF YOU WANT TO CHANGE THE POSITION OF IT
	LDA #$64			;
	STA VRAM_BUF, Y		;   ~ vram_adr(NTADR_A(2,25));
	LDA #$A2			;
	STA VRAM_BUF+1, Y	;__
	LDA #15				;	Const length of 15
	STA VRAM_BUF+2, Y	;__

	LDX _level					;
	LDA @string_ptrs_lo-1, X	;   Load low byte of lvl name pointer
	STA <PTR					;__
	LDA @string_ptrs_hi-1, X	;   Load high byte of lvl name pointer
	STA <PTR+1					;__
	LDA @padding-1, X			;
	LSR							;	Get left offset
	TAX							;__
	ADC #$00					;	Get right offset
	STA <TEMP+3					;__

	CPX #$00	; Had to do this, very sorry
	BEQ @main_data

	LDA #$C0	; Space char

	@pad_loop_left:
		STA VRAM_BUF+3, Y
		INY
		DEX
		BNE @pad_loop_left
	
	@main_data:
	; No need to LDX #$00, as it's either 0 from the prev loop or 0 left padding
		LDA (<PTR, X)	; Load byte

	@main_data_loop:
		CLC
		ADC #$A0
		STA VRAM_BUF+3, Y
		INY
		INCW <PTR
		LDA (<PTR, X)			;	Load byte
		BNE @main_data_loop		;__ Continue if not 0
	
	LDX <TEMP+3
	BEQ @end

	LDA #$C0

	@pad_loop_right:
		STA VRAM_BUF+3, Y
		INY
		DEX
		BNE @pad_loop_right
	
	@end:
	LDA #$FF			;	Finish off the write
	STA VRAM_BUF+3, Y	;__

	TYA				;
	CLC				;	Adjust vram index
	ADC #$03		;
	STA VRAM_INDEX	;__

	RTS

@string_ptrs_lo:
    .byte <_level1text, <_level2text, <_level3text, <_level4text, <_level5text, <_level6text, <_level7text
@string_ptrs_hi:
    .byte >_level1text, >_level2text, >_level3text, >_level4text, >_level5text, >_level6text, >_level7text
@padding:
    ; Calculation: 15 - length of string
    .byte 1, 2, 5, 8, 0, 4, 9

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
