; welcome to the world's worst IRQ function ever :sob:

; you can't use ANY function in here that uses the
; imaginary registers (rc0-rc31). have fun!

IRQ_LATCH   = $c000
IRQ_RELOAD  = $c001
IRQ_DISABLE = $e000
IRQ_ENABLE  = $e001

.global irq_ptr
.global irq_count
.global irq_table, irq_table_offset

.section .zp.bss
    irq_count:          .fill 1     ; how many IRQs have
                                    ; been executed this
                                    ; frame
    irq_ptr:            .fill 2     ; pointer to next IRQ function

.section .bss
    irq_table_offset:   .fill 1     ; offset in below table
    irq_table:          .fill 64    ; 64 bytes should be enough.
    irq_lastbyte:       .fill 1     ; 8 bytes * 8 interrupts 
    irq_tmp:            .fill 1     ; = 64 bytes total. have the
                                    ; extra byte to catch the
                                    ; end of the table.

; yes, i am fully aware that there is a better way to do this:
; - only increment the offset by the amount of arguments
; - bake the function pointers into the reload value,
;   using a lookup table

.section .prg_rom_fixed_lo.text.irq,"a",@progbits
.globl irq
    irq:

        pha     ; store A
        txa
        pha     ; store X
        tya
        pha     ; store Y

        sta IRQ_DISABLE ; disable mmc3 irq

        ldy irq_table_offset

        ldx irq_table+0,y
        inx 
        beq exitirq     ; if the reload value is 255,
                        ; don't bother

        ; RUN THIS INTERRUPT
        ; setup new pointer
        lda irq_table+1,y
        ldx irq_table+2,y
        sta irq_ptr+0
        stx irq_ptr+1

        jsr 1f              ; jsr here first since the
                            ; OG 6502 doesn't have an 
                            ; indirect JSR opcode

        ; SETUP NEXT INTERRUPT
        ; code will return here after an rts

        ; increment table offset
        lda irq_table_offset
        clc
        adc #$8
        sta irq_table_offset
        tay

        lda irq_table,y
        sta IRQ_LATCH
        sta IRQ_RELOAD
        sta IRQ_ENABLE

    
        ; EXIT IRQ
    exitirq:
        pla     ; get Y
        tay
        pla     ; get X
        tax
        pla     ; get A
        
        rti
    1:
        jmp (irq_ptr)
    2:
        sta IRQ_LATCH
        sta IRQ_RELOAD
        beq exitirq ; bra




stall:
    1:          ; stall for a bit so that the
        dey     ; register updates are outside
        bne 1b  ; the active display
        rts

    
.globl irq_basic
    irq_basic:
        ;inc irq_count
        rts



.globl irq_set_x_scroll
    ; ptr+3 = new X scroll value
    irq_set_x_scroll:
        ldy #$7
        jsr stall
        
        ldy irq_table_offset

        lda irq_table+3,y
        sta $2005 ;PPU_SCROLL
        sta $2005 ;PPU_SCROLL
        
        ;inc irq_count
        rts



.globl irq_set_chr
    ; ptr+3 = chr bank ID
    ; ptr+4 = chr bank value
    irq_set_chr:
        ldy #$2
        jsr stall

        ldy irq_table_offset

        lda irq_table+3,y
        ldx irq_table+4,y
        
        jsr set_chr_bank    ; args were loaded
                            ; at the start
        ;inc irq_count
        rts

.globl irq_set_4k_chr_0
    ; ptr+3 = chr bank value
    ; set 2kb chr 0 and 2kb chr 1
    irq_set_4k_chr_0:
        ldy #$3
        jsr stall
        
        ldy irq_table_offset

        lda #0
        ldx irq_table+3,y

        ora __bank_select_hi
        sta $8000
        stx $8001
        ora #1
        inx
        inx
        sta $8000
        stx $8001
        sta __in_progress

        rts

;.globl irq_set_4k_chr_1
    ; ptr+3 = chr bank value
    ; set 2kb chr 0 and 2kb chr 1
;    irq_set_4k_chr_1:
;        ldy #$3
;        jsr stall
        
;        ldy irq_table_offset

;        lda #2
;        ldx irq_table+3,y

;        ora __bank_select_hi
;        tay
;        sty $8000
;        stx $8001
;        inx
;        iny
;        sty $8000
;        stx $8001
;        inx
;        iny
;        sty $8000
;        stx $8001
;        inx
;        iny
;        sty $8000
;        stx $8001
;        sta __in_progress

;        rts

.globl irq_set_chr_and_scroll
    ; ptr+3 = chr bank ID
    ; ptr+4 = chr bank value
    ; ptr+5 = new X scroll value
    irq_set_chr_and_scroll:

        ; inline'd the stall(in) here because it took too long to jsr
        ldy #3
    1:          ; stall for a bit so that the
        dey     ; register updates are outside
        bne 1b  ; the active display

        ldy irq_table_offset

        lda irq_table+3,y
        pha ; push chr bank for faster access later
        ldx irq_table+4,y

        lda irq_table+5,y
        
        sta $2005 ; PPU_SCROLL
        sta $2005 ; PPU_SCROLL

        pla
        ora __bank_select_hi
        sta $8000
        stx $8001

        ;inc irq_count
        rts



.balign 128
.globl irq_update_bg_palette
    
    irq_update_bg_palette:
        ; re-use the irq pointer for the
        ; palette data
        ldy irq_table_offset

        lda irq_table+3,y
        ldx irq_table+4,y
    

        sta irq_ptr+0
        stx irq_ptr+1

        ldx #16

    1:  ; calculate the brightness of the new palette set
        ; UNROLLED FOR SPEED!
        dex
        txa
        tay
        lda (irq_ptr),y
        tay
        lda (PAL_BG_PTR_OLD),y
        pha
        dex

        txa
        tay
        lda (irq_ptr),y
        tay
        lda (PAL_BG_PTR_OLD),y
        pha
        dex

        txa
        tay
        lda (irq_ptr),y
        tay
        lda (PAL_BG_PTR_OLD),y
        pha
        dex

        txa
        tay
        lda (irq_ptr),y
        tay
        lda (PAL_BG_PTR_OLD),y
        pha
        dex
        
        inx
        bne 1b

        ldy #1
        jsr stall
        nop

        ; turn off ppu
        lda PPU_MASK_VAR
        and #$E7    ;disable rendering
        sta $2001   ;PPU_MASK

        ; set ppu address
        lda #$3f
        sta $2006
        stx $2006

        ; set 4kb chr 0 to the 0th bank
        lda #0
        tax
        ora __bank_select_hi
        sta __in_progress
        sta $8000
        stx $8001
        ora #1
        inx
        inx
        sta $8000
        stx $8001

        ldy #1
        jsr stall
        nop
        nop

        ldy #16

    1:  ; copy to palette RAM
        sty irq_tmp
        pla
        tay ; background color in Y
        pla ; color 1 in A
        tax ; background color in X
        pla ; color 2 in A
        sty $2007
        stx $2007
        sta $2007
        pla ; color 3 in A
        sta $2007
        ldy irq_tmp
        dey ; four DEYs take the same amount of time
        dey ; as subtract by four
        dey 
        dey 

        beq 1f  ; exit if four loops complete

        tya
        pha
        ldy #6
        jsr stall
        pla
        tay
        nop
        bne 1b


    1:  ; reset everything before updating scroll
        ldy irq_table_offset
        

        ;; CODE BORROWED FROM THE NESDEV WIKI
        ; The first two PPU writes can come anytime during the scanline:
        ; Nametable number << 2 to $2006.
        
        lda irq_table+7,y  ; nametable ID 
        asl
        asl
        sta $2006

        ; Y position to $2005.
        lda irq_table+6,y  ; nametable ID 
        sta $2005
        
        ; Prepare for the 2 later writes:
        ; We reuse new_x to hold (Y & $F8) << 2.
        and #%11111000
        asl
        asl
        ldx irq_table+5,y  ; X position in X for $2005 later.
        sta irq_tmp

        ; ((Y & $F8) << 2) | (X >> 3) in A for $2006 later.
        txa
        lsr
        lsr
        lsr
        ora irq_tmp

        
        ldy #2
        jsr stall

        ;nop
        ;nop

        ldy PPU_MASK_VAR
        ; The last two PPU writes must happen during hblank:
        stx $2005
        sta $2006
        
        ; Restore new_x.
        ;stx irq_tmp

        sty $2001

        inc PAL_UPDATE
        rts




