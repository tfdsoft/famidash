.extern se_irq_table, se_irq_table_position


.section .text.custom_irq_that_updates_scroll,"ax",@progbits
.global custom_irq_that_updates_scroll
custom_irq_that_updates_scroll:
    ; +3 = X (lo)
    ; +4 = X (hi)
    ; +5 = Y (lo)
    ; +6 = Y (hi)
    
    tya
    pha

    ldy se_irq_table_position

    ; The first two PPU writes can come anytime during the scanline:
    ; Nametable number << 2 to $2006.
    lda se_irq_table + 4, y ; hi byte of new X value
    lsr 
    lda se_irq_table + 6, y
    rol 
    asl 
    asl 
    sta $2006

    ; Y position to $2005
    lda se_irq_table + 5, y
    sta $2005

    ; Prepare for the 2 later writes:
    ; We reuse new_x to hold (Y & $F8) << 2.
    and #%11111000
    asl
    asl
    ldx se_irq_table + 3, y
    sta se_irq_table + 3, y

    ; ((Y & $F8) << 2) | (X >> 3) in A for $2006 later.
    txa
    lsr
    lsr
    lsr
    ora se_irq_table + 3, y

    php
    plp
    php
    plp

    ; The last two PPU writes must happen during hblank:
    stx $2005
    sta $2006

    ; Restore new_x.
    txa
    sta se_irq_table + 3, y

    
    
    ; increment irq table position
    lda se_irq_table_position
    clc
    adc #7
    sta se_irq_table_position

    ; restore Y
    pla
    tay
    rts

.section .text.custom_irq_that_updates_chr_bank,"ax",@progbits
.global custom_irq_that_updates_chr_bank
custom_irq_that_updates_chr_bank:
    ; +3 = register (0-5)
    ; +4 = bank number
    tya
    pha

    ldy se_irq_table_position

    lda se_irq_table + 3, y
    ldx se_irq_table + 4, y
    
    ora __bank_select_hi
    
    ldy #4
    1:
        php
        plp
        dey
        bne 1b
    
    sta $8000
    stx $8001

    ; reset the bank select register so our
    ; hard work doesn't get undone once we
    ; exit the interrupt
    lda #7
    ora __bank_select_hi
    sta $8000

    ; increment table index
    lda se_irq_table_position
    clc
    adc #5
    sta se_irq_table_position

    pla
    tay
    rts


.section .text.custom_irq_that_updates_chr_and_x_scroll,"ax",@progbits
.global custom_irq_that_updates_chr_and_x_scroll
custom_irq_that_updates_chr_and_x_scroll:
    ; +3 = register (0-5)
    ; +4 = bank number
    ; +5 = new x scroll value

    tya
    pha

    ldy se_irq_table_position

    lda se_irq_table+3,y
    pha ; push chr bank for faster access later
    ldx se_irq_table+4,y

    lda se_irq_table+5,y

    ldy #3

    1:
        php
        plp
        dey
        bne 1b
    nop
    
    sta $2005 ; PPU_SCROLL
    sta $2005 ; PPU_SCROLL

    pla
    ora __bank_select_hi
    sta $8000
    stx $8001

    ; reset bank select register
    lda #7
    ora __bank_select_hi
    sta $8000

    ; increment table
    lda se_irq_table_position
    clc
    adc #6
    sta se_irq_table_position

    ;inc irq_count
    pla
    tay
    rts