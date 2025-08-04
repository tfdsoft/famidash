;
; zeropage.inc
;
; (C) Copyright 2002-2012, Ullrich von Bassewitz (uz@cc65.org)
;

; Assembler include file that imports the runtime zero page locations used
; by the compiler, ready for usage in asm code.


        .globalzp       sp, sreg, regsave
        .globalzp       ptr1, ptr2, ptr3, ptr4
        .globalzp       tmp1, tmp2, tmp3, tmp4
        .globalzp       regbank

        .export c_sp := sp

        ; Export C bindings for cc65 tmp vars
        .repeat 4, I
        .exportzp .ident(.sprintf("_cc65_ptr%s", .string(I+1))) = .ident(.sprintf("ptr%s", .string(I+1)))
        .exportzp .ident(.sprintf("_cc65_tmp%s", .string(I+1))) = .ident(.sprintf("tmp%s", .string(I+1)))
        .endrepeat
        .export _cc65_sreg := sreg
        .export _cc65_sp := sp

; The size of the register bank
regbanksize     = 6

; The total amount of zero page space used
zpspace         = 26

; The amount of space that needs to be saved by an interrupt handler that
; calls C code (does not include the register bank, which is saved by the
; generated C code if required).
zpsavespace     = zpspace - regbanksize