; welcome to the world's worst IRQ function ever :sob:

; you can't use ANY function in here that uses the
; imaginary registers (rc0-rc31). have fun!

IRQ_LATCH   = $c000
IRQ_RELOAD  = $c001
IRQ_DISABLE = $e000
IRQ_ENABLE  = $e001

.globl irq_ptr
.globl irq_count
.globl irq_table, irq_table_offset

.section .zp.bss
    irq_count:          .fill 1     ; how many IRQs have
                                    ; been executed this
                                    ; frame

.section .bss
    irq_ptr:            .fill 2     ; pointer to next IRQ function
    irq_table_offset:   .fill 1     ; offset in below table

    irq_table:          .fill 31    ; 31 bytes should be enough.
                                    ; 6 bytes * 5 interrupts 
                                    ; = 30 bytes total. have the
                                    ; extra byte to catch the
                                    ; end of the table.

; yes, i am fully aware that there is a better way to do this:
; - only increment the offset by the amount of arguments
; - bake the function pointers into the reload value,
;   using a lookup table
;
;   it's 6:30 am. don't harass me over this, alex

.section .text.irq,"a",@progbits
.globl irq
    irq:
        pha     ; store A
        txa
        pha     ; store X
        tya
        pha     ; store Y

        sta IRQ_DISABLE ; disable mmc3 irq

        ; RUN THIS INTERRUPT
        
        ; setup new pointer
        ldy irq_table_offset
        lda irq_table+1,y
        sta irq_ptr+0
        lda irq_table+2,y
        sta irq_ptr+1

        jsr 1f              ; jsr here first since the
                            ; OG 6502 doesn't have an 
                            ; indirect JSR opcode

        ; SETUP NEXT INTERRUPT
        ; code will return here after an rts

        ; increment table offset
        lda irq_table_offset
        clc
        adc #$6
        sta irq_table_offset
        tay

        lda irq_table,y
        sta IRQ_LATCH
        sta IRQ_RELOAD
        sta IRQ_ENABLE

        
        ; EXIT IRQ
        pla     ; get Y
        tay
        pla     ; get X
        tax
        pla     ; get A
        
        rti

    1:
        jmp (irq_ptr)






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
        ldy #$7
        jsr stall

        ldy irq_table_offset

        lda irq_table+3,y
        ldx irq_table+4,y
        
        jsr set_chr_bank    ; args were loaded
                            ; at the start
        ;inc irq_count
        rts



.globl irq_set_chr_and_scroll
    ; ptr+3 = chr bank ID
    ; ptr+4 = chr bank value
    ; ptr+5 = new X scroll value
    irq_set_chr_and_scroll:
        ldy #$2
        jsr stall

        ldy irq_table_offset

        ; push chr bank for faster access later
        lda irq_table+3,y
        pha
        lda irq_table+4,y
        pha

        lda irq_table+5,y
        
        sta $2005 ; PPU_SCROLL
        sta $2005 ; PPU_SCROLL

        pla
        tax
        pla
        ora __bank_select_hi
        sta $8000
        stx $8001

        ;inc irq_count
        rts






