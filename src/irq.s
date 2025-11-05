; welcome to the world's worst IRQ function ever :sob:

; you can't use ANY function in here that uses the
; imaginary registers (rc0-rc31). have fun!

IRQ_LATCH   = $c000
IRQ_RELOAD  = $c001
IRQ_DISABLE = $e000
IRQ_ENABLE  = $e001

.globl irq_count, irq_args
.globl irq_reload_value, irq_ptr

.section .zp.bss
    irq_count:          .fill 1 ; how many IRQs have
                                ; been executed this
                                ; frame
    irq_args:           .fill 4 ; arguments for advanced
                                ; interrupts

.section .bss
    irq_reload_value:   .fill 1 ; scanlines to wait
    irq_ptr:            .fill 2 ; where to jump

.section .text.irq,"a",@progbits
.globl irq
    irq:
        pha     ; store A
        txa
        pha     ; store X
        tya
        pha     ; store Y

        sta IRQ_DISABLE ; disable mmc3 irq

        jsr .Lreturn_point  ; jsr here first since the
                            ; OG 6502 doesn't have an 
                            ; indirect JSR opcode

        ; code will return here after an rts
        pla     ; get Y
        tay
        pla     ; get X
        tax
        pla     ; get A
        
        rti

    .Lreturn_point:
        jmp (irq_ptr)


stall:
    1:          ; stall for a bit so that the
        dey     ; register updates are outside
        bne 1b  ; the active display
        rts

    
.globl irq_basic
    irq_basic:
        inc irq_count
        rts



.globl irq_set_x_scroll
    ; args+0 = new X scroll value
    irq_set_x_scroll:
        ldy #$9
        jsr stall
        
        lda irq_args+0
        sta $2005 ;PPU_SCROLL
        sta $2005 ;PPU_SCROLL
        
        inc irq_count
        rts

.globl irq_set_chr
    ; args+0 = chr bank ID
    ; args+1 = chr bank value
    irq_set_chr:
        ldy #$9
        jsr stall

        lda irq_args+0
        ldx irq_args+1
        
        jsr set_chr_bank    ; args were loaded
                            ; at the start
        inc irq_count
        rts

.globl irq_set_chr_and_scroll
    ; args+0 = chr bank ID
    ; args+1 = chr bank value
    ; args+2 = new X scroll value
    irq_set_chr_and_scroll:
        ldy #$8
        jsr stall
        nop     ; this nop is for timing purposes

        lda irq_args+0
        ldx irq_args+1
        ldy irq_args+2

        sty $2005 ; PPU_SCROLL
        sty $2005 ; PPU_SCROLL

        ;jsr set_chr_bank    ; args were loaded
        ;                    ; at the start
        ;fuck it, we inline
        ora __bank_select_hi
        sta $8000
        stx $8001

        inc irq_count
        rts



;.globl irq_enable_sprites
;    irq_enable_sprites:
;        ; DMA the sprites, in the event that decay occurred
;        ;lda #$00
;        ;sta $2003   ; OAM_ADDR
;        ;lda #$02
;        ;sta $4014   ; OAM_DMA
;        
;        ; enable sprites
;        lda #$10    
;        sta $2001   ; PPU_MASK
;
;        ; stall for at least 8 lines
;        ldy #$40
;        jsr stall   
;
;        ; disable sprites
;        jsr get_ppu_mask_var
;        sta $2001   ; PPU_MASK
;
;        rts