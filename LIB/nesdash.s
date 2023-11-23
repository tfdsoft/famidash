; Custom routines implemented specifically for famidash (some are totally not stolen from famitower)

.import _level_list, _sprite_list, _bank_list
.import _rld_column, _collisionMap0, _collisionMap1 ; used by C code
.import _scroll_count, _scroll_x, _level_data_bank
.import _song
.importzp _gamemode
.importzp _tmp1, _tmp2, _tmp3, _tmp4  ; C-safe temp storage
.import _DATA_PTR
.import pusha, pushax

.import FIRST_MUSIC_BANK

.export _oam_meta_spr_vflipped
.export _init_rld, _unrle_next_column, _draw_screen_R
.export _music_play, _music_update

;void __fastcall__ oam_meta_spr_vflipped(unsigned char x,unsigned char y,const unsigned char *data);

.segment "ZEROPAGE"
    level_data:     .res 2
    rld_value:      .res 1
    rld_run:        .res 1

.segment "BSS"
    columnBuffer:   .res 27; column buffer, to be pushed to the collision map

    current_song_bank: .res 1

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
            LDX _level_data_bank+1 ;
            INX                 ;   1 cycle faster than INC zp : LDA zp
            TXA                 ;__
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

shiftBy6Table:
    .byte $00, $40, $80, $C0

_draw_screen_R:
    ; C code to be ported:
        ; void draw_screen_R(void){
        ;     //scrolling to the right, draw metatiles as we go
        ;     pseudo_scroll_x = high_byte(scroll_x) + 0x100;
        ;     x = pseudo_scroll_x;
        ;     tmp4 = x >> 4;
        ;     wait_hang_on_should_i_write_to_the_collision_map();
        ;     tmp1 = (scroll_count&3)<<6;
        ;     if (!(scroll_count & 4)){
        ;         set_data_pointer(active_level[0]);
        ;         address = get_ppu_addr(0, x, tmp1);
        ;     } else {
        ;         set_data_pointer(active_level[1]);
        ;         if (scroll_count == 7) {scroll_count = 0; return;}
        ;         address = get_ppu_addr(2, x, tmp1);
        ;     }
        ;     index = tmp1 + tmp4;
        ;     buffer_4_mt(address, index); // ppu_address, index to the data
        ;     address += 0x80;
        ;     index += 0x20;
        ;     buffer_4_mt(address, index); // ppu_address, index to the data

        ; }


    LDA _level_data_bank
    JSR mmc3_set_prg_bank_1
    
    LDA _scroll_x           ;__ Highbyte of scroll_x
    CLC
    ADC #$F8
    LSR                     ;
    LSR                     ;   >> 4
    LSR                     ;
    LSR                     ;__
    STA _tmp4               ;= _tmp4 = tmp4
    STA tmp4
    ; wait_hang_on_should_i_write_to_the_collision_map();
        ; The C code being ported:
            ; if ((rld_column == X)){	// assume the X	has already been bitshifted
            ; 	unrle_next_column();
            ; 	unrle_next_column();
            ; }
            ;
        CMP _rld_column
        BEQ :+
        RTS

    :
    JSR _unrle_next_column
    LDA _scroll_count       ;   
    AND #3                  ;   Get index for fast <<6 shift
    TAX                     ;__
    LDA shiftBy6Table, x    ;   tmp1 = tmp1
    STA tmp1                ;__
    CLC                     ;
    ADC _tmp4               ;   _tmp4 = index
    STA _tmp4               ;__

    Size0 = (15*2)+2+1
    Size1 = Size0
    Size2 = (12*2)+2+1
    Size3 = Size2

    Offset0 = 0
    Offset1 = Size0
    Offset2 = Size0+Size1
    Offset3 = Size0+Size2+Size3
    

    ; Writing to nesdoug's VRAM buffer starts here
    LDX VRAM_INDEX

    ; In-house replacement of get_ppu_addr, only counts X
    ; Address is big-endian
    LDA tmp4    ;   000xxxx0 - the left tiles of the metatiles
    ASL         ;__
    STA VRAM_BUF+Offset0+1,X
    STA VRAM_BUF+Offset2+1,X

    ORA #$01    ;   000xxxx1 - the right tiles of the metatiles
    STA VRAM_BUF+Offset1+1,X
    STA VRAM_BUF+Offset3+1,X

    LDA #($20+$80)  ; 0th nametable + NT_UPDATE_VERT
    STA VRAM_BUF+Offset0,X
    STA VRAM_BUF+Offset1,X
    ORA #$08
    STA VRAM_BUF+Offset2,X
    STA VRAM_BUF+Offset3,X


    ; First part of the update: the tiles
    ; Amount of data in the sequence - 27*2 tiles (8x8 tiles, left sides of the metatiles)
    LDA #(15*2)
    STA VRAM_BUF+Offset0+2,X
    STA VRAM_BUF+Offset1+2,X
    LDA #(12*2)
    STA VRAM_BUF+Offset2+2,X
    STA VRAM_BUF+Offset3+2,X

    ; The sequence itself:

    ;TODO Use columnBuffer to get the data
    LDY #$00

    @tilewriteloop1:
        ;Fetch metatile pointer
        STY tmp1

        LDA columnBuffer,Y  ;
        STA META_VAR        ;   Get metatile pointer
        JSR MT_MULT5        ;__

        ;Fetch data, write to buffer

        ;Tile:
        ; 1 | 2 
        ;---+---
        ; 3 | 4 

        LDA (META_PTR2),Y   ;   Tile 1
        STA VRAM_BUF+Offset0+3,X
        INY                 ;__
        LDA (META_PTR2),Y   ;   Tile 2
        STA VRAM_BUF+Offset1+3,X
        INY                 ;__
        LDA (META_PTR2),Y   ;   Tile 3
        STA VRAM_BUF+Offset0+4,X
        INY                 ;__
        LDA (META_PTR2),Y   ;   Tile 4
        STA VRAM_BUF+Offset1+4,X
        INY                 ;__

        ;Buffer the attributes in column buffer
        LDA #$01
        BIT _rld_column
        BEQ :+
        ; MATH
        :
            LDA (META_PTR2),Y
            LDY tmp1
            STA columnBuffer,Y
        INX
        INX

        INY
        CPY #15
        BNE @tilewriteloop1

    LDA #$FF
    STA VRAM_BUF+Offset2

    ;TODO new block for the attributes

    RTS
        




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
