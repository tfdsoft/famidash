



void vram_copy(const unsigned char* from, unsigned short count){
    //PPU_CTRL_VAR &= 0b01111111;
    //PPU.control = PPU_CTRL_VAR;
    for(unsigned short i=0; i<count; i++){
        PPU.vram.data = from[i];
    }
    //PPU_CTRL_VAR |= 0b10000000;
    //PPU.control = PPU_CTRL_VAR;
}


void pal_fade_to(unsigned char from, unsigned char to){

    if(from < to) {
        while (from < to){
            pal_bright(++from);
            ppu_wait_nmi();
            ppu_wait_nmi();
        }
    }else{
        while (from > to){
            pal_bright(--from);
            ppu_wait_nmi();
            ppu_wait_nmi();
        }
    }
}


__attribute__((section(".aligned"))) void oam_and_readjoypad(){
    __attribute__((leaf)) __asm__ volatile (
        // save the previous controller state for calcuating the previous results
        "lda joypad1"
        "sta TEMP + 4"

        // and do the same for the controller 2
        "lda joypad2"
        "sta TEMP + 5"

        // Save the previous mouse state so we can calculate the next frames press/release
        "lda mouse + kMouseY"
        "sta TEMP + 0"
        "lda mouse + kMouseX"
        "sta TEMP + 1"
        "lda mouse + kMouseButtons"
        "sta TEMP + 2"

        // Strobe the joypads.
        "LDX #$00"
        "LDY #$01"
        "STY mouse"
        "STY CTRL_PORT1"

    ".if 0"
        // Clock official mouse sensitivity. NOTE: This can be removed if not needed.
        "LDA advance_sensitivity"
        "BEQ 1f"
        "LDA MOUSE_PORT"
        "STX advance_sensitivity"
    "1:"
    ".endif"

        "STX CTRL_PORT1"

        "LDA #>OAM_BUF"
        "STA PPU_OAM_DMA"
    
        // Desync cycles: 432, 576, 672, 848, 432*2-4 (860)

        // DMC DMA:         // PUT GET PUT GET        // Starts: 0

    "1:"
        "LDA mouse_mask "    // get put get*     *576  // Starts: 4, 158, 312, 466, [620]
        "AND MOUSE_PORT"   // put get put GET
        "CMP #$01"           // put get
        "ROL mouse,X"        // put get put get* PUT GET  *432
        "BCC 1b "            // put get (put)

        "INX"                // put get
        "CPX #$04"           // put get
        "STY mouse,X"        // put get put GET
        "BNE 1b"             // put get (put)

    "1:"
        "LDA CONTROLLER_PORT" // put get put GET        // Starts: 619
        "AND #$03"           // put get*         *672
        "CMP #$01"           // put get
        "ROL joypad1" // put get put get put    // This can desync, but we finish before it matters.
        "BCC 1b"             // get put (get)

    ".if 0" // TODO support SNES extra buttons 
        "STY joypad1+1" // get put get
        "NOP"                // put get
    "1:"
        "LDA CONTROLLER_PORT" // put get* put GET *848  // Starts: 751, [879]
        "AND #$03"           // put get
        "CMP #$01"           // put get
        "ROL joypad1+1" // put get put get put    // This can desync, but we finish before it matters.
        "BCC 1b"             // get* put (get)   *860

        // NEXT: 878
    .endif // CONTROLLER_SIZE = 2
    );
}