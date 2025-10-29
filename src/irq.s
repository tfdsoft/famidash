; welcome to the world's worst IRQ function ever :sob:

; you can't use ANY function in here that uses the
; imaginary registers (rc0-rc31). have fun!

IRQ_LATCH   = $c000
IRQ_RELOAD  = $c001
IRQ_DISABLE = $e000
IRQ_ENABLE  = $e001

.globl irq_count
.globl irq_reload_value, irq_ptr

.section .zp.bss
    irq_count:          .fill 1 ; how many IRQs have
                                ; been executed this
                                ; frame

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

    
    
.globl irq_basic
    irq_basic:
        inc irq_count
        rts


