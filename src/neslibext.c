

/*void __temporary_prg_a000(char bank_id){
    __attribute__((leaf)) __asm__ volatile(
        "pha \n"
        "tax \n"
        "lda #0b111 \n"
        "ora __bank_select_hi \n"
        "jmp __set_reg_retry \n"
    );
}

void __pop_prg_a000(){
    __attribute__((leaf)) __asm__ volatile(
        "pla \n"
        "sta __prg_a000\n"
        "tax \n"
        "lda #0b111 \n"
        "ora __bank_select_hi \n"
        "jmp __set_reg_retry \n"
    );
}*/

void push_prg_a000(){
    __attribute__((leaf)) __asm__ volatile (
        "lda __prg_a000 \n"
        "pha \n"
        :
        :
        :"a","x","y","p"
    );
}

void pop_prg_a000(){
    __attribute__((leaf)) __asm__ volatile (
        "pla \n"
        "jsr set_prg_a000"
        :
        :
        :"a","x","y","p"
    );
}


void vram_copy(const unsigned char* const from, unsigned short count){
    //PPU_CTRL_VAR &= 0b01111111;
    //PPU.control = PPU_CTRL_VAR;
    for(unsigned short i=0; i<count; i++){
        PPU.vram.data = from[i];
    }
    //PPU_CTRL_VAR |= 0b10000000;
    //PPU.control = PPU_CTRL_VAR;
}


void pal_fade_to(unsigned char from, unsigned char to){
    __attribute__((leaf)) __asm__ volatile (
        	// A = from
            // X = to

            // sta TEMP+9 ;to
            // jsr popa
            "stx __rc11 \n"	//to
            "sta __rc12 \n" //from
            "jmp 4f \n"
            
        "1: \n	" // fade_loop:
            "ldx #2 \n" //wait this many frames
        "11:"
            "jsr ppu_wait_nmi \n" 
            "dex \n"
            "bne 11b \n"
            
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



//
//  OAMDMA-aligned controller polling
//  if this looks scary, that's because it is.
//  getting this to work in llvm-mos has been
//  an absolute bloody nightmare.
//

__attribute__((retain)) 
    unsigned char __zp
    joypad[7], 
    //joypad1[3], 
    mouse_mask,
    noMouse;

#define MOUSE_Y_MINIMUM 1
#define MOUSE_X_MINIMUM 1
#define MOUSE_Y_MAXIMUM 239
#define MOUSE_X_MAXIMUM 255

__attribute__((section(".prg_rom_fixed_lo.1"),retain))
    const unsigned char MouseBoundsMin[] = {
        MOUSE_Y_MINIMUM, 
        MOUSE_X_MINIMUM
    };

__attribute__((section(".prg_rom_fixed_lo.1"),retain))
    const unsigned char MouseBoundsMax[] = {
        MOUSE_Y_MAXIMUM, 
        MOUSE_X_MAXIMUM
    };

__attribute__((section(".prg_rom_fixed_lo"),noinline)) void oam_and_readjoypad(){
    __attribute__((leaf)) __asm__ volatile (
        //".section .zp \n"
        //"mouse: .fill 4 \n"
        //"joypad1: .fill 3 \n"
        //"mouse_mask: .fill 1 \n"
        //"noMouse: .fill 1 \n"
        
        //".section .aligned,\"a\",@progbits \n"

        "joypad2 = joypad+1 \n"
        "joypad1 = joypad+4 \n"
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
        "lda joypad + kMouseY \n"
        "sta __rc2 \n"
        "lda joypad + kMouseX \n"
        "sta __rc3 \n"
        "lda joypad + kMouseButtons \n"
        "sta __rc4 \n"

        // Strobe the joypads.
        "LDX #$00 \n"
        "LDY #$01 \n"
        "STY joypad \n"
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
        "LDA mouse_mask \n"    // get put get*     *576  // Starts: 4, 158, 312, 466, [620]
        "AND MOUSE_PORT \n"   // put get put GET
        "CMP #$01 \n"           // put get
        "ROL joypad,X \n"        // put get put get* PUT GET  *432
        "BCC 1b  \n"            // put get (put)

        "INX \n"                // put get
        "CPX #$04 \n"           // put get
        "STY joypad,X \n"        // put get put GET
        "BNE 1b \n"             // put get (put)

    "1: \n"
        "LDA CONTROLLER_PORT \n" // put get put GET        // Starts: 619
        "AND #$03 \n"           // put get*         *672
        "CMP #$01 \n"           // put get
        "ROL joypad1 \n" // put get put get put    // This can desync, but we finish before it matters.
        "BCC 1b \n"             // get put (get)

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
    "jmp 1f \n"





    

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
        "lda joypad + kMouseButtons \n"
        "and #$0f \n"
        "cmp #$01 \n"
        "beq 1f \n"
            // treat this as a standard NES controller instead and
            // calculate the press/release for it
            "lda joypad + kMouseZero \n"
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
            "sta joypad + kMouseZero \n"
        "lda #1 \n"
        "sta noMouse \n"
            "jmp 9f \n"
    "1: \n" // snes_mouse_detected:
    //.if !VS_SYSTEM
        // convert the X/Y displacement into X/Y positions on the screen
        "ldx #1 \n"
    "10: \n" // loop:
            "lda joypad + kMouseY,x \n"
            "bpl 11f \n" // :+
                // subtract the negative number instead
                "and #$7f \n"
                "sta joypad + kMouseZero \n" // reuse this value as a temp value
                "lda __rc2,x \n"
                "sec  \n"
                "sbc joypad + kMouseZero \n"
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
            "sta joypad + kMouseY,x \n"
            "dex \n"
            "bpl 10b \n"
        // calculate newly pressed buttons and shift it into byte zero
        "lda __rc4 \n"
        "eor #$C0 \n"
        "and joypad + kMouseButtons \n"
        "rol \n"
        "ror joypad + kMouseZero \n"
        "rol \n"
        "ror joypad + kMouseZero \n"
        
        // calculate newly released buttons
        "lda joypad + kMouseButtons \n"
        "eor #$C0 \n"
        "and __rc4 \n"
        "rol \n"
        "ror joypad + kMouseZero \n"
        "rol \n"
        "ror joypad + kMouseZero \n"

        // Set the connected bit
        "sec \n"
        "ror joypad + kMouseZero \n"
    //.endif

    "9: \n"
    //".endscope \n"
    
        :
        :
        :"a","x","y","p","rc2","rc3","rc4","rc6","rc7"
    );
    
}
#define player1_hold (*((unsigned char*)&joypad[4]))
#define player1_pressed (*((unsigned char*)&joypad[5]))
#define player1_released (*((unsigned char*)&joypad[6]))

#define player2_hold (*((unsigned char*)&joypad[1]))
#define player2_pressed (*((unsigned char*)&joypad[2]))
#define player2_released (*((unsigned char*)&joypad[3]))


//
//  ...and that's enough of that.
//
struct pad {
    union {
        unsigned char hold;
        struct {
            unsigned char right : 1;
            unsigned char left : 1;
            unsigned char down : 1;
            unsigned char up : 1;
            #if __VS_SYSTEM
            unsigned char select : 1;
            unsigned char start : 1;
            #else
            unsigned char start : 1;
            unsigned char select : 1;
            #endif
            unsigned char b : 1;
            unsigned char a : 1;
        };
    };
    union {
        unsigned char press;
        struct {
            unsigned char press_right : 1;
            unsigned char press_left : 1;
            unsigned char press_down : 1;
            unsigned char press_up : 1;
            #if __VS_SYSTEM
            unsigned char press_select : 1;
            unsigned char press_start : 1;
            #else
            unsigned char press_start : 1;
            unsigned char press_select : 1;
            #endif
            unsigned char press_b : 1;
            unsigned char press_a : 1;
        };
    };
    union {
        unsigned char release;
        struct {
            unsigned char release_right : 1;
            unsigned char release_left : 1;
            unsigned char release_down : 1;
            unsigned char release_up : 1;
            #if __VS_SYSTEM
            unsigned char release_select : 1;
            unsigned char release_start : 1;
            #else
            unsigned char release_start : 1;
            unsigned char release_select : 1;
            #endif
            unsigned char release_b : 1;
            unsigned char release_a : 1;
        };
    };
};



void disable_nmi(){
    PPU_CTRL_VAR &= 0b01111111;
    PPU.control = PPU_CTRL_VAR;
}
void enable_nmi(){
    PPU_CTRL_VAR |= 0b10000000;
    PPU.control = PPU_CTRL_VAR;
}


/*
 * vram_unrle_ignore0(*src)
 * decompress a nametable, but don't write zero
*/
__attribute__((noinline))
void vram_unrle_ignore0(const unsigned char* src){
    unsigned char tag = src[0]; // tag is the least common byte
    unsigned char value, run;
    src++;

    // this sounds batshit insane, but the APU DMC is
    // causing extra read cycles. i have to disable
    // it here
    APU.delta_mod.length = 0;
    APU.status &= 0b00001111;
    disable_nmi(); // just in case music_update runs.
    // i genuinely can't think of a better way to do this

    while(1){
        if (src[0] != tag) { 
            // if its not equal to the tag,
            // just write the byte, plain and simple.
            value = src[0];
            if(value != 0) {
                PPU.vram.data = value;
            } 
            else {PPU.vram.data;}
        } else {
            // if it IS the tag,
            src++;
            run = src[0]; // grab the run length.

            if (run == 0) { 
                // if the run length is 0,
                // break out of the loop.
                break;
            }
            if (run == 1) {
                // if the run length is 1,
                // write the tag.
                PPU.vram.data = tag;
            }
            while (run > 0) {
                if(value != 0) {
                    PPU.vram.data = value;
                }
                else {PPU.vram.data;}
                run--;
            }
        }
        src++; // move onto the next byte!
    }

    APU.status |= 0b00010000;
    enable_nmi();
    //PPU_CTRL_VAR |= 0b10000000;
    //PPU.control = PPU_CTRL_VAR;
}


uint8_t fast_mod8(uint8_t n, uint8_t mod){
    __attribute__((leaf)) __asm__ volatile (
        "stx __rc2 \n"
        "cmp __rc2 \n"
        "bcc 9f \n" // if number is less than mod,
                    // don't run the loop
        "1: \n"
        "sec \n"
        "sbc __rc2 \n"
        "cmp __rc2 \n"
        "bcs 1b \n"

        "9: \n"
        :"=a"(n)
        :"a"(n),"x"(mod)
        :"y","p","rc2"
    );

    return n;
}


// DO NOT USE IF MULT CAN BE ZERO
uint8_t fast_mult8(uint8_t n, uint8_t mult){
    __attribute__((leaf)) __asm__ volatile (
        "stx __rc2 \n"
        "cmp __rc2 \n"
        "beq 9f \n" // if mult = 1,
                    // don't run the loop
        "dex \n"
        "sta __rc2 \n"

        "1: \n"
        "clc \n"
        "adc __rc2 \n"
        "dex \n"
        "bne 1b \n"

        "9: \n"
        :"=a"(n)
        :"a"(n),"x"(mult)
        :"y","p","rc2"
    );

    return n;
}

uint8_t fast_multby6(uint8_t n){
    return ((n<<2)+(n<<1));
}


__attribute__((noinline)) 
uint8_t get_ppu_mask_var() {return PPU_MASK_VAR;}