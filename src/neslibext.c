



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
/*
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
*/
    __attribute__((leaf)) __asm__ volatile (
        	// A = from
            // X = to

            // sta TEMP+9 ;to
            // jsr popa
            "stx __rc11 \n"	//to
            "sta __rc12 \n" //from
            "jmp 4f \n"
            
        "1: \n	" // fade_loop:
            "lda #2 \n"
            "jsr ppu_wait_nmi \n" //wait 1 frames
            "jsr ppu_wait_nmi \n"
            
            "lda __rc12 \n" //from
            "cmp __rc11 \n" //to
            "bcs 3f \n"
            
        "2:	\n" // less:
            "clc \n"
            "adc #1 \n"
            "sta __rc12 \n" //from
            "jsr pal_bright \n"
            "jmp 4f \n"
            
        "3: \n" // more:
            "sec \n"
            "sbc #1 \n"
            "sta __rc12 \n" //from
            "jsr pal_bright \n"
            
        "4: \n" // check_equal:
            "lda __rc12 \n"
            "cmp __rc11 \n"
            "bne 1b \n"
            
        "5: \n" // done:
            "jsr ppu_wait_nmi \n" //do 1 final, make sure the last change goes
        :
        :"a"(from),"x"(to)
        :"y","p","rc11","rc12"
    );

}

__attribute__((retain)) 
    unsigned char __zp 
    mouse[4], 
    joypad1[3], 
    controllingplayer[2], 
    mouse_mask,
    noMouse;

#define player1_hold (*((unsigned char*)&joypad1[0]))
#define player1_pressed (*((unsigned char*)&joypad1[1]))
#define player1_released (*((unsigned char*)&joypad1[2]))

#define player2_hold (*((unsigned char*)&mouse[1]))
#define player2_pressed (*((unsigned char*)&jmouse[2]))
#define player2_released (*((unsigned char*)&mouse[3]))

// the fact that this worked first-try is batshit insane
__attribute__((section(".aligned"))) void oam_and_readjoypad(){
    __attribute__((leaf)) __asm__ volatile (
        "joypad2 = mouse+1 \n"
        "CTRL_PORT2 = $4017 \n"
        "CTRL_PORT1 = $4016 \n"
        "MOUSE_PORT = CTRL_PORT2 \n"
        "CONTROLLER_PORT = CTRL_PORT1 \n"
        "kMouseZero = 0\n"
        "kMouseButtons = 1 \n"
        "kMouseY = 2 \n"
        "kMouseX = 3 \n"

        // save the previous controller state for calcuating the previous results
        "lda joypad1 \n"
        "sta __rc6 \n"

        // and do the same for the controller 2
        "lda joypad2 \n"
        "sta __rc7 \n"

        // Save the previous mouse state so we can calculate the next frames press/release
        "lda mouse + kMouseY \n"
        "sta __rc2 \n"
        "lda mouse + kMouseX \n"
        "sta __rc3 \n"
        "lda mouse + kMouseButtons \n"
        "sta __rc4 \n"

        // Strobe the joypads.
        "LDX #$00 \n"
        "LDY #$01 \n"
        "STY mouse \n"
        "STY CTRL_PORT1 \n"

    //".if 0"
        // Clock official mouse sensitivity. NOTE: This can be removed if not needed.
    //    "LDA advance_sensitivity"
    //    "BEQ 1f"
    //    "LDA MOUSE_PORT"
    //    "STX advance_sensitivity"
    //"1:"
    //".endif"

        "STX CTRL_PORT1 \n"

        "LDA #$02 \n"
        "STA $4014 \n"
    
        // Desync cycles: 432, 576, 672, 848, 432*2-4 (860)

        // DMC DMA:         // PUT GET PUT GET        // Starts: 0

    "1: \n"
        "LDA mouse_mask  \n"    // get put get*     *576  // Starts: 4, 158, 312, 466, [620]
        "AND MOUSE_PORT \n"   // put get put GET
        "CMP #$01 \n"           // put get
        "ROL mouse,X \n"        // put get put get* PUT GET  *432
        "BCC 1b  \n"            // put get (put)

        "INX \n"                // put get
        "CPX #$04 \n"           // put get
        "STY mouse,X \n"        // put get put GET
        "BNE 1b \n"             // put get (put)

    "11: \n"
        "LDA CONTROLLER_PORT \n" // put get put GET        // Starts: 619
        "AND #$03 \n"           // put get*         *672
        "CMP #$01 \n"           // put get
        "ROL joypad1 \n" // put get put get put    // This can desync, but we finish before it matters.
        "BCC 11b \n"             // get put (get)

    //".if 0" // TODO support SNES extra buttons 
    //    "STY joypad1+1" // get put get
    //    "NOP"                // put get
    //"1:"
    //    "LDA CONTROLLER_PORT \n" // put get* put GET *848  // Starts: 751, [879]
    //    "AND #$03 \n"           // put get
    //    "CMP #$01 \n"           // put get
    //    "ROL joypad1+1 \n" // put get put get put    // This can desync, but we finish before it matters.
    //    "BCC 1b \n"             // get* put (get)   *860

        // NEXT: 878
    //.endif // CONTROLLER_SIZE = 2




    // now that that's over...
    // it would probably be best if i just
    // reset the ppu's registers now, since
    // i'm not gonna update anything else


        //PPU.status; // read ppu status. thanks llvm-mos!
        "lda $2002 \n"
        //PPU.scroll = SCROLL_X;
        "lda SCROLL_X \n"
        "sta $2005 \n"
        //PPU.scroll = SCROLL_Y;
        "lda SCROLL_Y \n"
        "sta $2005 \n"
        //PPU.control = PPU_CTRL_VAR;
        "lda PPU_CTRL_VAR \n"
        "sta $2000 \n"
    /*"jmp 1f \n"





    "MOUSE_Y_MINIMUM = 1 \n"
    "MOUSE_X_MINIMUM = 1 \n"
    "MOUSE_Y_MAXIMUM = 239 \n"
    "MOUSE_X_MAXIMUM = 255 \n"

    "MouseBoundsMin: \n"
        ".byte MOUSE_Y_MINIMUM, MOUSE_X_MINIMUM \n"
    "MouseBoundsMax: \n"
        ".byte MOUSE_Y_MAXIMUM, MOUSE_X_MAXIMUM \n"

    //".scope calculate_extra_fields: \n"
    "1: \n"
        // Pressed
        "lda __rc6 \n"
        "eor #$ff \n"
        "and joypad1 \n"
        "sta joypad1 + 1 \n"

        // Released
        "lda joypad1 \n"
        "eor #$ff \n"
        "and __rc6 \n"
        "sta joypad1 + 2 \n"

        // Check the report to see if we have a snes mouse plugged in
        "lda mouse + kMouseButtons \n"
        "and #$0f \n"
        "cmp #$01 \n"
        "beq 1f \n"
            // treat this as a standard NES controller instead and
            // calculate the press/release for it
            "lda mouse + kMouseZero \n"
            "sta joypad2 \n"
            // Pressed
            "lda __rc7 \n"
            "eor #$ff \n"
            "and joypad2 \n"
            "sta joypad2 + 1 \n"

            // Released
            "lda joypad2 \n"
            "eor #$ff \n"
            "and __rc7 \n"
            "sta joypad2 + 2 \n"

            // no snes mouse, so leave the first field empty
            "lda #0 \n"
            "sta mouse + kMouseZero \n"
        "lda #1 \n"
        "sta noMouse \n"
            "jmp 9f \n"
    "1: \n" // snes_mouse_detected:
    //.if !VS_SYSTEM
        // convert the X/Y displacement into X/Y positions on the screen
        "ldx #1 \n"
    "10: \n" // loop:
            "lda mouse + kMouseY,x \n"
            "bpl 11f \n" // :+
                // subtract the negative number instead
                "and #$7f \n"
                "sta mouse + kMouseZero \n" // reuse this value as a temp value
                "lda __rc2,x \n"
                "sec  \n"
                "sbc mouse + kMouseZero \n"
                // check if we underflowed
                "bcc 1f \n"
                // check the lower bounds
                "cmp MouseBoundsMin,x \n"
                "bcs 2f \n" // didn't wrap so set the value now
            "1: \n" // wrappednegative
                "lda MouseBoundsMin,x \n"
                "jmp 2f \n"
            "11: \n" // :
            // add the positive number
            "clc \n"
            "adc __rc2,x \n"
            // check if we wrapped, set to the max bounds if we did
            "bcs 1f \n"
            // check the upper bounds
            "cmp MouseBoundsMax,x \n"
            "bcc 2f \n" // didn't wrap so set the value
    "1: \n" // wrapped:
            "lda MouseBoundsMax,x \n"
    "2: \n" // setvalue:
            "sta mouse + kMouseY,x \n"
            "dex \n"
            "bpl 10b \n"
        // calculate newly pressed buttons and shift it into byte zero
        "lda __rc4 \n"
        "eor #$C0 \n"
        "and mouse + kMouseButtons \n"
        "rol \n"
        "ror mouse + kMouseZero \n"
        "rol \n"
        "ror mouse + kMouseZero \n"
        
        // calculate newly released buttons
        "lda mouse + kMouseButtons \n"
        "eor #$C0 \n"
        "and __rc4 \n"
        "rol \n"
        "ror mouse + kMouseZero \n"
        "rol \n"
        "ror mouse + kMouseZero \n"

        // Set the connected bit
        "sec \n"
        "ror mouse + kMouseZero \n"
    //.endif

    "9: \n"
    //".endscope \n"
    */
        :
        :
        :"a","x","y","p","rc2","rc3","rc4","rc6","rc7"
    );
    
}