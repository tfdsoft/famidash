.section .zp.0
    mouse: .fill 4
    joypad1: .fill 3
    mouse_mask: .fill 1
    noMouse: .fill 1
    fivezptmp: .fill 5
    
.section .prg_rom_fixed_lo,"ax",@progbits

    joypad2 = mouse+1
    CTRL_PORT2 = $4017
    CTRL_PORT1 = $4016
    MOUSE_PORT = CTRL_PORT2 
    CONTROLLER_PORT = CTRL_PORT1
    kMouseZero = 0
    kMouseButtons = 1
    kMouseY = 2
    kMouseX = 3

    .globl oam_and_readjoypad
    oam_and_readjoypad:

    ; save the previous controller state for calcuating the previous results
        lda joypad1 
        sta fivezptmp + 4 

        ; and do the same for the controller 2
        lda joypad2 
        sta fivezptmp + 5 

        ; Save the previous mouse state so we can calculate the next frames press/release
        lda mouse + kMouseY 
        sta fivezptmp + 0 
        lda mouse + kMouseX 
        sta fivezptmp + 1 
        lda mouse + kMouseButtons 
        sta fivezptmp + 2 

        ; Strobe the joypads.
        LDX #$00 
        LDY #$01 
        STY mouse 
        STY CTRL_PORT1 

    ;.if 0
        ; Clock official mouse sensitivity. NOTE: This can be removed if not needed.
    ;    LDA advance_sensitivity
    ;    BEQ 1f
    ;    LDA MOUSE_PORT
    ;    STX advance_sensitivity
    ;1:
    ;.endif

        STX CTRL_PORT1 

        LDA #$02 
        STA $4014 
    
        ; Desync cycles: 432, 576, 672, 848, 432*2-4 (860)

        ; DMC DMA:         ; PUT GET PUT GET        ; Starts: 0

    1: 
        LDA mouse_mask      ; get put get*     *576  ; Starts: 4, 158, 312, 466, [620]
        AND MOUSE_PORT    ; put get put GET
        CMP #$01            ; put get
        ROL mouse,X         ; put get put get* PUT GET  *432
        BCC 1b              ; put get (put)

        INX                 ; put get
        CPX #$04            ; put get
        STY mouse,X         ; put get put GET
        BNE 1b              ; put get (put)

    1: 
        LDA CONTROLLER_PORT  ; put get put GET        ; Starts: 619
        AND #$03            ; put get*         *672
        CMP #$01            ; put get
        ROL joypad1  ; put get put get put    ; This can desync, but we finish before it matters.
        BCC 1b              ; get put (get)

    rts
    

    ;.if 0 ; TODO support SNES extra buttons 
    ;    STY joypad1+1 ; get put get
    ;    NOP                ; put get
    ;1:
    ;    LDA CONTROLLER_PORT  ; put get* put GET *848  ; Starts: 751, [879]
    ;    AND #$03            ; put get
    ;    CMP #$01            ; put get
    ;    ROL joypad1+1  ; put get put get put    ; This can desync, but we finish before it matters.
    ;    BCC 1b              ; get* put (get)   *860

    