; Custom routines implemented specifically for famidash (some are totally not stolen from famitower)

.import _rld_column, _level_list, _columnBuffer, _collisionMap0 ; used by C code

.export _oam_meta_spr_vflipped
.export _init_rld, _unrle_next_column

;void __fastcall__ oam_meta_spr_vflipped(unsigned char x,unsigned char y,const unsigned char *data);

.segment "ZEROPAGE"
    level_data:     .res 2
    rld_value:      .res 1
    rld_run:        .res 1

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

    ; Get level_data pointer:
    LDY #>_level_list   ;
    ASL                 ;   Get high byte,
    BCC :+              ;   Adjust if level num >= $80
        INY             ;
    : STY ptr1+1        ;__ Store high byte
    LDY #<_level_list   ;   Get and store low byte
    STY ptr1            ;__

    TAY                 ;__ Get the pointer

    LDA (ptr1),y        ;
    STA level_data      ;   Load low byte of level data pointer
    INY                 ;__
    LDA (ptr1),y        ;
    STA level_data+1    ;__ Load high byte of level data pointer
    

    LDY #$00            ;-  For both (zp),y addressing and rld_column
    STY _rld_column     ;__ Reset scrolling
    

    LDA (level_data),y  ;
    STA rld_value       ;   Load rld_value, ++level_data
    INCW level_data     ;__

    LDA (level_data),y  ;
    STA rld_run         ;   Load rld_run, ++level_data
    INCW level_data     ;__

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
        STA _columnBuffer, Y
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
        STA rld_run         ;   Load rld_run, ++level_data
        INCW level_data     ;__

        LDA rld_value

        INY
        CPY #27
        BNE @FirstLoop
    
    @WriteSetup:
        ; Set Y to 26-16-1, which is the maximum index
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
        LDA _columnBuffer+16, Y        ; Get columnBuffer[y]
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
        LDA _columnBuffer, Y
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