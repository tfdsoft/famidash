;MMC3 IRQ LIBRARY BY NESDOUG
;SOME FUNCTIONS ARE REMOVED HERE SINCE WE DON'T NEED THEM


;version Feb 2023
;credit to Matt Hughson for help


.define A12_INVERT $80
;values 0 or $80, for the $8000 register
;(changes in tileset mapping)

;if invert bit is 0 
;mode 0 changes $0000-$07FF
;mode 1 changes $0800-$0FFF
;mode 2 changes $1000-$13FF
;mode 3 changes $1400-$17FF
;mode 4 changes $1800-$1BFF
;mode 5 changes $1C00-$1FFF

;if invert bit is $80
;mode 0 changes $1000-$17FF
;mode 1 changes $1800-$1FFF
;mode 2 changes $0000-$03FF
;mode 3 changes $0400-$07FF
;mode 4 changes $0800-$0BFF
;mode 5 changes $0C00-$0FFF



.segment "ZEROPAGE"
;    BP_BANK_8000: .res 1
;    mmc3_8000_PRG:    .res 1
;    mmc3_8001_PRG:    .res 1
;    mmc3_8000_CHR:    .res 1
;    mmc3_8001_CHR:    .res 1
    mmc3_8000: .res 1 ; backup, just in case interrupt
    mmc3_ptr:        .res 2 ; array for the irq parser
    mmc3_index:        .res 1 ; index to this array
    irq_done:        .res 1

    
;   .exportzp mmc3_8000_PRG, mmc3_8001_PRG, mmc3_8000_CHR, mmc3_8001_CHR
;    .exportzp BP_BANK_8000, 
    .exportzp mmc3_8000
    .exportzp mmc3_ptr, mmc3_index, irq_done
    

.segment "STARTUP"
;needs to be mapped to the fixed bank

;.export _set_prg_8000, _get_prg_8000, _set_prg_a000
;.export _set_chr_mode_0, _set_chr_mode_1, _set_chr_mode_2, _set_chr_mode_3
;.export _set_chr_mode_4, _set_chr_mode_5

;.export _set_mirroring, _set_wram_mode, 
.export _disable_irq
.export _set_irq_ptr, _is_irq_done


; most of these functions only use the A register
; because some of the music code needs X unchanged


; sets the bank at $8000-9fff
;_set_prg_8000:
;    sta BP_BANK_8000
;    pha
;    lda #(6 | A12_INVERT)
;    bne bank_swap_common

;    sta mmc3_8000 ;backup, in case of interrupt
;    sta $8000
;    pla
;    sta $8001
;    rts


; returns the current bank at $8000-9fff    
;_get_prg_8000:
;    lda BP_BANK_8000
;    ldx #0
;    rts
    
    
; sets the bank at $a000-bfff
;_set_prg_a000:
;    pha
;    lda #(7 | A12_INVERT)
;    bne bank_swap_common
    
;    sta mmc3_8000 ;backup, in case of interrupt
;    sta $8000
;    pla
;    sta $8001
;    rts



; see chart in above for what these do
;_set_chr_mode_0:
;    pha
;    lda #(0 | A12_INVERT)
;bank_swap_common:    
;    sta mmc3_8000 ;backup, in case of interrupt
;    sta $8000   
;    pla
;    sta $8001
;    rts

    
;_set_chr_mode_1:
;    pha
;    lda #(1 | A12_INVERT)
;    bne bank_swap_common
    
;    sta mmc3_8000 ;backup, in case of interrupt
;    sta $8000   
;    pla
;    sta $8001
;    rts

    
;_set_chr_mode_2:
;    pha
;    lda #(2 | A12_INVERT)
;    bne bank_swap_common
    
;    sta mmc3_8000 ;backup, in case of interrupt
;    sta $8000   
;    pla
;    sta $8001
;    rts

    
;_set_chr_mode_3:
;    pha
;    lda #(3 | A12_INVERT)
;    bne bank_swap_common
    
;    sta mmc3_8000 ;backup, in case of interrupt
;    sta $8000   
;    pla
;    sta $8001
;    rts

    
;_set_chr_mode_4:
;    pha
;    lda #(4 | A12_INVERT)
;    bne bank_swap_common
    
;    sta mmc3_8000 ;backup, in case of interrupt
;    sta $8000   
;    pla
;    sta $8001
;    rts

    
;_set_chr_mode_5:
;    pha
;    lda #(5 | A12_INVERT)
;    bne bank_swap_common
    
;    sta mmc3_8000 ;backup, in case of interrupt
;    sta $8000   
;    pla
;    sta $8001
;    rts

 
    
; MIRROR_VERTICAL 0
; MIRROR_HORIZONTAL 1    
;_set_mirroring:
;    sta $a000
;    rts
    
    
; WRAM_OFF $40
; WRAM_ON $80
; WRAM_READ_ONLY $C0
;_set_wram_mode:
;    sta $a001
;    rts
    

_disable_irq:
    sta $e000 ;any value
    lda #<default_array
    ldx #>default_array
    ;jmp _set_irq_ptr ; fall through
    
    
_set_irq_ptr:
;ax = pointer
    sta mmc3_ptr
    stx mmc3_ptr+1
    rts    
    
    
_is_irq_done:
    lda irq_done
    ldx #0
    rts

    
default_array: ;just an eof terminator
.byte $ff



    
irq:
    rti

    ;; temporarily disable irq
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
    ldy mmc3_index
;    ldx #0
@loop:
    lda (mmc3_ptr), y ; get value from array
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
    lda (mmc3_ptr), y ; get value from array
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
    lda (mmc3_ptr), y ; get 2nd value from array
    iny    
    sta $2006
    jmp @loop
    
@wait: ; fe-ff wait or exit
    cmp #$ff
    beq @exit    
    lda (mmc3_ptr), y ; get value from array
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
    ora #A12_INVERT
    sta $8000
    lda (mmc3_ptr), y ; get next value
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
    sty mmc3_index
    rts
    
@exit:
    sta irq_done ;value 0xff
    dey ; undo the previous iny, keep it pointed to ff
    sty mmc3_index
    rts
    
    
set_scanline_count:
; any value will do for most of these registers
    sta $e000 ; disable mmc3 irq
    sta $c000 ; set the irq counter reload value
    sta $c001 ; reload the reload value
    sta $e001 ; enable the mmc3 irq
    cli ;make sure irqs are enabled
    rts

