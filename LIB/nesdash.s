; Custom routines implemented specifically for famidash (some are totally not stolen from famitower)

.export _oam_meta_spr_vflipped

;void __fastcall__ oam_meta_spr_vflipped(unsigned char x,unsigned char y,const unsigned char *data);

_oam_meta_spr_vflipped:

    sta <PTR
    stx <PTR+1

    ldy #1      ;2 popa calls replacement, performed in reversed order
    lda (sp),y
    dey
    sta <SCRX
    lda (sp),y
    SEC
    SBC #$08        ; Offset everything by 8 pixels
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