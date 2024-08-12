;
; MMC3 Mapper registers, for use with the functions below
; 
.define MMC3_REG_BANK_SELECT $8000
.define MMC3_REG_BANK_DATA $8001
MMC3_REG_MIRRORING = $a000
MMC3_REG_PRG_RAM_PROTECT = $a001
.define MMC3_REG_IRQ_LATCH $c000
.define MMC3_REG_IRQ_RELOAD $c001
.define MMC3_REG_IRQ_DISABLE $e000
.define MMC3_REG_IRQ_ENABLE $e001

; .define MMC3_MIRRORING_VERTICAL 0
; .define MMC3_MIRRORING_HORIZONTAL 1
; _MMC3_MIRRORING_VERTICAL = 0
; _MMC3_MIRRORING_HORIZONTAL = 1
; .export _MMC3_MIRRORING_VERTICAL, _MMC3_MIRRORING_HORIZONTAL, MMC3_REG_MIRRORING

.define MMC3_REG_SEL_2KB_CHR_0 %00000000
.define MMC3_REG_SEL_2KB_CHR_1 %00000001 
.define MMC3_REG_SEL_1KB_CHR_0 %00000010
.define MMC3_REG_SEL_1KB_CHR_1 %00000011
.define MMC3_REG_SEL_1KB_CHR_2 %00000100 
.define MMC3_REG_SEL_1KB_CHR_3 %00000101
.define MMC3_REG_SEL_PRG_BANK_0 %00000110
.define MMC3_REG_SEL_PRG_BANK_1 %00000111

.define MMC3_REG_SEL_CHR_MODE_A %00000000
.define MMC3_REG_SEL_CHR_MODE_B %10000000
.define MMC3_REG_SEL_PRG2_C000 %00000000
.define MMC3_REG_SEL_PRG2_8000 %01000000

.import FIRST_DMC_BANK

; Values for which banks to load
.define MMC3_REG_CONTROL_DEFAULT #%11100

.segment "ZEROPAGE"
    ; Used to track whether a register write was interrupted, so we can try again if needed.
    ; alexmush comment:
    ; not anymore, just used for the PRG mode
    mmc3ChrInversionSetting: .res 1
    mmc3IRQTablePtr:    .res 2
    mmc3IRQTableIndex:  .res 1
    mmc3IRQJoever:      .res 1
    mmc3_8000:          .res 1
.segment "BSS"
    mmc3PRG1Bank: .res 1    ;because famistudio updates


.segment "IRQ_T"
    _irqTableBuf:   .res 16
    _irqTable:   .res 16
    .export _irqTable

.segment "CODE_2"
    _mmc3_pop_prg_bank_1:
        LDA #MMC3_REG_SEL_PRG_BANK_1
        ora mmc3ChrInversionSetting
        sta MMC3_REG_BANK_SELECT
        LDA mmc3PRG1Bank
        STA MMC3_REG_BANK_DATA
        rts
    .export _mmc3_pop_prg_bank_1

    mmc3_set_prg_bank_1:
    _mmc3_set_prg_bank_1:
        STA mmc3PRG1Bank
    mmc3_tmp_prg_bank_1:    ; ONLY MEANT FOR USE WITH NMI-RELATED TEMPORARY BANKSWITCHING
        PHA
        lda #MMC3_REG_SEL_PRG_BANK_1
    mmc3_internal_set_bank:
        ora mmc3ChrInversionSetting
        sta MMC3_REG_BANK_SELECT
        PLA
        sta MMC3_REG_BANK_DATA
        rts
    .export _mmc3_set_prg_bank_1
	
    ; Store mirroring value to mmc3 register
    mmc3_set_prg_bank_0:
    _mmc3_set_prg_bank_0:
        PHA
        lda #MMC3_REG_SEL_PRG_BANK_0
        BNE mmc3_internal_set_bank  ; BRA
    .export _mmc3_set_prg_bank_0

    mmc3_set_2kb_chr_bank_0:
    _mmc3_set_2kb_chr_bank_0:
        PHA
        lda #MMC3_REG_SEL_2KB_CHR_0
        BEQ mmc3_internal_set_bank  ; BRA
    .export _mmc3_set_2kb_chr_bank_0

    mmc3_set_2kb_chr_bank_1:
    _mmc3_set_2kb_chr_bank_1:
        PHA
        lda #MMC3_REG_SEL_2KB_CHR_1
        BNE mmc3_internal_set_bank  ; BRA
    .export _mmc3_set_2kb_chr_bank_1

    mmc3_set_1kb_chr_bank_0:
    _mmc3_set_1kb_chr_bank_0:
        PHA
        lda #MMC3_REG_SEL_1KB_CHR_0
        BNE mmc3_internal_set_bank  ; BRA
    .export _mmc3_set_1kb_chr_bank_0

    mmc3_set_1kb_chr_bank_1:
    _mmc3_set_1kb_chr_bank_1:
        PHA
        lda #MMC3_REG_SEL_1KB_CHR_1
        BNE mmc3_internal_set_bank  ; BRA
    .export _mmc3_set_1kb_chr_bank_1

    mmc3_set_1kb_chr_bank_2:
    _mmc3_set_1kb_chr_bank_2:
        PHA
        lda #MMC3_REG_SEL_1KB_CHR_2
        BNE mmc3_internal_set_bank  ; BRA
    .export _mmc3_set_1kb_chr_bank_2

    mmc3_set_1kb_chr_bank_3:
    _mmc3_set_1kb_chr_bank_3:
        PHA
        lda #MMC3_REG_SEL_1KB_CHR_3
        BNE mmc3_internal_set_bank  ; BRA
    .export _mmc3_set_1kb_chr_bank_3

    .macro mmc3_set_mirroring
        sta MMC3_REG_MIRRORING
    .endmacro

    initialize_mapper:
        ; lda #(MMC3_REG_SEL_CHR_MODE_A | MMC3_REG_SEL_PRG2_8000)
        lda #(MMC3_REG_SEL_CHR_MODE_B | MMC3_REG_SEL_PRG2_8000)
        sta mmc3ChrInversionSetting

		; lda #%10000000
		; sta MMC3_REG_PRG_RAM_PROTECT

        lda #1
        sta MMC3_REG_MIRRORING  ; Set mirroring to horizontal
        jmp mmc3_set_prg_bank_1



    mmc3_disable_irq:
    _mmc3_disable_irq:
        sta $e000 ;any value
        lda #$ff
        sta _irqTable
        lda #<_irqTable
        ldx #>_irqTable
        
        ; fall through to setting the pointer
    .export _mmc3_disable_irq
    set_irq_ptr:
    _set_irq_ptr:
        ;ax = pointer
        sta mmc3IRQTablePtr
        stx mmc3IRQTablePtr+1
        ;lda #$ff    ; set the first byte of the irq table to $ff
        ;sta _irqTable; just to be on the safe side
        rts
    .export _set_irq_ptr

    is_irq_done:
    _is_irq_done:
        lda mmc3IRQJoever
        ldx #0
        rts
    .export _is_irq_done


    irq:
        pha
        txa
        pha
        tya
        pha
        
        sta $e000    ; disable mmc3 irq
                    ; any value will do
        
        jsr irq_parser
        
        pla
        tay
        pla
        tax
        pla

        rti
        
        
    ;format
    ;value < 0xf0, it's a scanline count
    ;zero is valid, it triggers an IRQ at the end of the current line

    ;if >= 0xf0...
    ;f0 = 2000 write, next byte is write value
    ;f1 = 2001 write, next byte is write value
    ;f2-f4 unused - future TODO ?
    ;f5 = 2005 write, next byte is H Scroll value
    ;f6 = 2006 write, next 2 bytes are write values


    ;f7 = change CHR mode 0, next byte is write value
    ;f8 = change CHR mode 1, next byte is write value
    ;f9 = change CHR mode 2, next byte is write value
    ;fa = change CHR mode 3, next byte is write value
    ;fb = change CHR mode 4, next byte is write value
    ;fc = change CHR mode 5, next byte is write value

    ;fd = very short wait, no following byte 
    ;fe = short wait, next byte is quick loop value
    ;(for fine tuning timing of things)

    ;ff = end of data set

        
    irq_parser:
        ldy mmc3IRQTableIndex
    ;    ldx #0
    @loop:
        lda (mmc3IRQTablePtr), y ; get value from array
        iny
        cmp #$fd ;very short wait
        beq @loop
        
        cmp #$fe ;fe-ff wait or exit
        bcs @wait
        
        cmp #$f0
        bcs @1
        jmp @scanline ;below f0
    @1:    
        
        cmp #$f7
        bcs @chr_change
    ;f0-f6    
        tax
        lda (mmc3IRQTablePtr), y ; get value from array
        iny
        cpx #$f0
        bne @2
        sta $2000 ; f0
        jmp @loop
    @2:
        cpx #$f1
        bne @3
        sta $2001 ; f1
        jmp @loop
    @3:
        cpx #$f5 
        bne @4
        ldx #4
    @better_timing: ; don't change till near the end of the line
        dex
        bne @better_timing
        
        sta $2005 ; f5
        sta $2005 ; second value doesn't matter
        jmp @loop
    @4:
        sta $2006 ; f6
        lda (mmc3IRQTablePtr), y ; get 2nd value from array
        iny    
        sta $2006
        jmp @loop
        
    @wait: ; fe-ff wait or exit
        cmp #$ff
        beq @exit    
        lda (mmc3IRQTablePtr), y ; get value from array
        iny
        tax
        beq @loop ; if zero, just exit
    @wait_loop: ; the timing of this wait could change if this crosses a page boundary
        dex
        bne @wait_loop        
        jmp @loop    

    @chr_change:
    ;f7-fc change a CHR set
        sec
        sbc #$f7 ;should result in 0-5
        ora #$80 ;A12_INVERT
        sta $8000
        lda (mmc3IRQTablePtr), y ; get next value
        iny
        sta $8001

        lda mmc3_8000 ;restore the MMC3 bank select register
        sta $8000     ;in case we interrupted something
        jmp @loop
        
    @scanline:
        nop ;trying to improve stability
        nop
        nop
        nop
        jsr set_scanline_count ;this terminates the set
        sty mmc3IRQTableIndex
        rts
        
    @exit:
        sta mmc3IRQJoever ;value 0xff
        dey ; undo the previous iny, keep it pointed to ff
        sty mmc3IRQTableIndex
        rts


    set_scanline_count:
        ; any value will do for most of these registers
        sta $e000 ; disable mmc3 irq
        sta $c000 ; set the irq counter reload value
        sta $c001 ; reload the reload value
        sta $e001 ; enable the mmc3 irq
        cli ;make sure irqs are enabled
        rts



    write_irq_table:    ; FIRST ASM ROUTINE BY USERSNIPER
    _write_irq_table:   ; how did i do
        ;ax = pointer

        ; replace mmc3IRQTablePtr temporarily
        sta mmc3IRQTablePtr
        stx mmc3IRQTablePtr+1

        ; write two bytes ahead in SRAM (unused space)
        ; as a failsafe in the event that the table is
        ; not fully written to or read from
        lda #$ff
        sta _irqTable+$10
        sta _irqTable+$11

        ldy #0
    @loop:
        lda (mmc3IRQTablePtr), y
        sta _irqTable, y
        iny

        cpy #$10
        beq @done

        cmp #$ff
        bne @loop

    @done:
        ; set mmc3IRQTablePtr back to what it was
        lda #<_irqTable
        ldx #>_irqTable
        jsr set_irq_ptr

        rts
    .export _write_irq_table



    write_irq_table_frombuffer:
    _write_irq_table_frombuffer:

        ; write two bytes ahead in SRAM (unused space)
        ; as a failsafe in the event that the table is
        ; not fully written to or read from
        lda #$ff
        sta _irqTable+$10
        sta _irqTable+$11
        
        ldy #$f0
    @loop:
        lda _irqTableBuf-$f0, y
        sta _irqTable-$f0, y
        iny

        beq @done

        cmp #$ff
        bne @loop

    @done:
        rts
    .export _write_irq_table_frombuffer



    ;write_irq_table_tobuffer:
    ;_write_irq_table_tobuffer:
    ;    ; a = byte
    ;    ; x = offset
    ;    sta _irqTable, x
    ;    rts
    ;.export _write_irq_table_tobuffer