unsigned char pad_old;
unsigned char pad_new;



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


/*
 * pad_poll(p)
 * get controller input, AND if it was just pressed!
*/

void pad_poll_plus(){
    unsigned char PAD_BUF;

    pad_old = pad[0];

    JOYPAD[0] = 1; // poll by writing 1, then 0
    JOYPAD[0] = 0;

    for(char i=0; i<8; i++){
        PAD_BUF <<= 1;  // get the bits!
        PAD_BUF |= (JOYPAD[0] & 1);
    }
    pad[0] = PAD_BUF;
    /*
    __attribute__((leaf)) __asm__ volatile (
        "lda pad,x \n"
        "eor pad_old,x \n"
        "and pad,x \n"
        "sta pad_new,x \n"
        :
        :"x"(p)
        :"a","y","p"
    );
    */

    pad_new = ((pad_old ^ pad[0]) & pad[0]);
}
    