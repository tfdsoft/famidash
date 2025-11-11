//
// NESLIB IMPLEMENTATION IN C
// by usersniper
// feel free to use this lmao
//

#include <nes.h>

#define high_byte(a) *((unsigned char*)&a+1)
#define low_byte(a) *((unsigned char*)&a)

// implemented:
// _pal_all,_pal_bg,_pal_spr,_pal_col,_pal_clear
// _pal_bright,_pal_spr_bright,_pal_bg_bright
// _ppu_off,_ppu_on_all,_ppu_on_bg,_ppu_on_spr,_ppu_mask
// _oam_clear,_oam_spr,_oam_meta_spr
// _ppu_wait_nmi
// _scroll,_split
// _bank_spr, _bank_bg
// _vram_read,_vram_write,_vram_unrle

// !!!!FAMITONE 2 NOT INCLUDED!!!!

// _pad_poll
//
// _vram_adr,_vram_put,_vram_fill,_vram_inc
//
// _memfill
// _get_ppu_ctrl_var,_set_ppu_ctrl_var
//


// todo:
// ,_ppu_system
// ,_oam_size,_oam_hide_rest
// _rand8,_rand16,_set_rand
// ,_pad_trigger,_pad_state
// _rand8,_rand16,_set_rand
// 
// _set_vram_update,_flush_vram_update
// ,_delay
//
// _nesclock


// el memory section!!!!!!
//static unsigned char spin;
__attribute__((retain)) static volatile unsigned char FRAME_CNT;
__attribute__((retain)) static volatile unsigned char VRAM_UPDATE;
__attribute__((retain)) static volatile unsigned char PPU_MASK_VAR, PPU_CTRL_VAR;
__attribute__((retain)) static volatile unsigned char PPU_CTRL_VAR1;
__attribute__((retain)) static unsigned char SCROLL_X, SCROLL_Y;
__attribute__((retain)) static unsigned char SCROLL_X1;//, SCROLL_Y1;
//#define PAL_BUF ((volatile uint8_t*)0x100) 
__attribute__((retain)) static uint8_t __zp PAL_BUF[32];
__attribute__((retain)) 
    volatile unsigned char PAD_STATE[2], PAD_STATEP[2], PAD_STATET[2];
//static unsigned char TEMP;
__attribute__((retain)) static unsigned char SPRID;
__attribute__((retain)) static unsigned char LEN;
__attribute__((retain)) static unsigned char PAL_UPDATE;
__attribute__((retain)) static unsigned char I;

__attribute__((retain)) static uint8_t * __zp PAL_BG_PTR;
__attribute__((retain)) static uint8_t * __zp PAL_SPR_PTR;

__attribute__((section(".zp.name_upd_adr"),retain)) volatile const char *NAME_UPD_ADR;
__attribute__((section(".zp.name_upd_enable"),retain)) volatile char NAME_UPD_ENABLE;


static const uint8_t palBrightTable[192] = {
    // 0
    0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f,
    0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f,

    // 1
    0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f,
    0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f,
    
    // 2
    0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f,
    0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f,
    
    // 3
    0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f,
    0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f,
    
    // 4
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,

    // 5
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
    0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x0d, 0x00, 0x00,

    // 6
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
    0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x10, 0x10,

    // 7
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
    0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x30, 0x30,

    // 8
    0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
    0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,

    0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
    0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,

    0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
    0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
    
    0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
    0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30
};
#define palBrightTable0 *((const uint8_t*)&palBrightTable[0])
#define palBrightTable1 *((const uint8_t*)&palBrightTable[0x10])
#define palBrightTable2 *((const uint8_t*)&palBrightTable[0x20])
#define palBrightTable3 *((const uint8_t*)&palBrightTable[0x30])
#define palBrightTable4 *((const uint8_t*)&palBrightTable[0x40])
#define palBrightTable5 *((const uint8_t*)&palBrightTable[0x50])
#define palBrightTable6 *((const uint8_t*)&palBrightTable[0x60])
#define palBrightTable7 *((const uint8_t*)&palBrightTable[0x70])
#define palBrightTable8 *((const uint8_t*)&palBrightTable[0x80])

#define PAD_A			0x80
#define PAD_B			0x40
#if __VS_SYSTEM
#define PAD_START		0x20
#define PAD_SELECT		0x10
#else
#define PAD_SELECT		0x20
#define PAD_START		0x10
#endif
#define PAD_UP			0x08
#define PAD_DOWN		0x04
#define PAD_LEFT		0x02
#define PAD_RIGHT		0x01



/*
 *  ppu_wait_nmi()
 *  wait for vblank.
*/
__attribute__((noinline)) void ppu_wait_nmi(){
    // stall until FRAME_CNT is updated by nmi()
    //while (FRAME_CNT == FRAME_COUNT_OLD){}

        VRAM_UPDATE = 1;

    __attribute__((leaf)) __asm__ volatile (
        "lda FRAME_CNT \n"
        "1:"
        "cmp FRAME_CNT \n"
        "beq 1b \n"
    );
}





/*
 *  ppu_off()
 *  wait for vblank and turn off the screen!
*/
void ppu_off(){
    PPU_MASK_VAR &= 0b11100111;
    ppu_wait_nmi();
}

/*
 *  ppu_on_all()
 *  wait for vblank and turn on the screen!
*/
void ppu_on_all(){
    PPU_MASK_VAR |= 0b00011000;
    ppu_wait_nmi();
}

/*
 *  ppu_on_bg()
 *  wait for vblank and turn on the background layer.
*/
void ppu_on_bg(){
    PPU_MASK_VAR |= 0b00001000;
    ppu_wait_nmi();
}

/*
 *  ppu_on_spr()
 *  wait for vblank and turn on the sprite layer.
*/
void ppu_on_spr(){
    PPU_MASK_VAR |= 0b00010000;
    ppu_wait_nmi();
}

/*
 *  ppu_mask()
 *  set the mask value (to be applied at end of vblank).
*/
void ppu_mask(unsigned char mask){
    PPU_MASK_VAR = mask;
}





// internal function used by the library;
// do not call
static void pal_copy(const unsigned char * const data){
    if(I == 0){
        while (LEN > 0){
            PAL_BUF[I] = data[I];
            LEN--;
            I++;
        }
    } else {
        while (LEN > 0){
            PAL_BUF[I] = data[I-0x10];
            LEN--;
            I++;
        }
    }
    
}

/*
 * pal_all(data)
 * set the palettes for everything
*/
__attribute__((noinline)) void pal_all(const unsigned char * const data){
    LEN = 0x20;
    I = 0x00;
    pal_copy(data);
    PAL_UPDATE++;
}

/*
 * pal_bg(data)
 * set the palettes for the background
*/
__attribute__((noinline)) void pal_bg(const unsigned char * const data){
    LEN = 0x10;
    I = 0x00;
    pal_copy(data);
    PAL_UPDATE++;
}

/*
 * pal_spr(data)
 * set the palettes for sprites
*/
__attribute__((noinline)) void pal_spr(const unsigned char * const data){
    LEN = 0x10;
    I = 0x10;
    pal_copy(data);
    PAL_UPDATE++;
}

/*
 * pal_col(index, color)
 * change one specific color in the palette.
*/
__attribute__((noinline)) void pal_col(uint8_t index, uint8_t color){
    index &= 0x1f;
    color &= 0x3f;
    PAL_BUF[index] = color;
    PAL_UPDATE++;
}

/*
 * pal_clear()
 * DARKEN IT ALL!
*/
__attribute__((noinline)) void pal_clear(){
    for (uint8_t I=0; I<32; I++){
        PAL_BUF[I] = 0x0f;
    }
    PAL_UPDATE++;
}

/*
 * pal_spr_bright(bright)
 * change the brightness of the sprites!
*/
__attribute__((noinline)) void pal_spr_bright(char bright){
    PAL_SPR_PTR = ((uint8_t*)(&palBrightTable[(bright << 4)]));
    PAL_UPDATE++;
}

/*
 * pal_bg_bright(bright)
 * change the brightness of the background!
*/
__attribute__((noinline)) void pal_bg_bright(char bright){
    PAL_BG_PTR = ((uint8_t*)(&palBrightTable[(bright << 4)]));
    PAL_UPDATE++;
}

/*
 * pal_bright(bright)
 * change the brightness of EVERYTHING.
*/
__attribute__((noinline)) void pal_bright(char bright){
    PAL_BG_PTR = ((uint8_t*)(&palBrightTable[(bright << 4)]));
    PAL_SPR_PTR = PAL_BG_PTR;
    PAL_UPDATE++;
}





/*
 * oam_clear()
 * clear the oam buffer.
*/
__attribute__((noinline)) void oam_clear(){
    //if (SPRID > 64) 
    SPRID = 0;
    do{
        POKE((0x200 + SPRID), 0xff);
        SPRID+=4;
    }while(SPRID != 0);
}

/*
 * oam_spr(x, y, tile, attr)
 * add a sprite to the oam buffer
*/
// if I laid this out correctly,
// .A = x
// .X = y
// .__rc2 = tile
// .__rc3 = attr 
// no clue how the compiler is gonna optimize it though
__attribute__((noinline)) void oam_spr(char x, char y, char tile, char attr){
    if(SPRID >= 64) return;
    OAM_BUF[SPRID].y = --y,
    OAM_BUF[SPRID].tile = tile,
    OAM_BUF[SPRID].attr = attr,
    OAM_BUF[SPRID].x = x,
    SPRID++;
}

/*
 * oam_meta_spr(x, y, data)
 * add multiple sprites to the oam buffer
*/
// TODO: optimize this function so it doesn't
// take 8 billion years to execute
__attribute__((noinline)) void oam_meta_spr(char x, char y, const unsigned char* const data){
    char* ptr = ((char*)data);
    char* oam_ptr = (((char*)OAM_BUF) + (SPRID<<2));
    y--;
    while (ptr[0] != 0x80){
        if (SPRID >= 64) return;
        //OAM_BUF[SPRID].x = (ptr[0] + x);
        //OAM_BUF[SPRID].y = (ptr[1] + y);
        //OAM_BUF[SPRID].tile = ptr[2];
        //OAM_BUF[SPRID].attr = ptr[3];

        POKE(oam_ptr + 3, (ptr[0] + x));
        POKE(oam_ptr + 0, (ptr[1] + y));
        POKE(oam_ptr + 1, ptr[2]);
        POKE(oam_ptr + 2, ptr[3]);
        ptr += 4;
        oam_ptr += 4;
        SPRID++;
    }
}





/*
 *  scroll(x,y)
 *  set the scroll x and y values.
 *  
 *  __inputs__
 *  x: set x scroll
 *  y: set y scroll
*/
__attribute__((noinline)) void scroll(unsigned short x, unsigned short y){
    unsigned char tmp = 0;

    // if lsb is greater than or equal to 240:
    if(low_byte(y) >= 240){
        // engage in attribute corruption prevention
        SCROLL_Y = (low_byte(y) - 240);
    } else {
        // don't otherwise.
        SCROLL_Y = low_byte(y);
    }


    if(high_byte(y) & 1){
        tmp = 2;
    }

    SCROLL_X = low_byte(x);

    // set ppu ctrl to do its thing i guess
    tmp |= (high_byte(x) & 1); // get lowest bit of x high byte
    PPU_CTRL_VAR &= 0xfc; // clear the bits to set
    PPU_CTRL_VAR |= tmp; // throw 'em in there

}

/*
 *  split(x)
 *  use the sprite zero hit to split the screen!
 *  
 *  __inputs__
 *  x: set x scroll
*/
__attribute__((noinline)) void split(unsigned short x){
    unsigned char tmp;

    tmp = (high_byte(x) & 1);
    PPU_CTRL_VAR1 = ((PPU_CTRL_VAR & 0xfc) | tmp);

    __attribute__((leaf)) __asm__ volatile (
        "@3: \n"
        "bit $2002 \n" // this is PPU.status
        "bvs @3 \n"

        "@4: \n"
        "bit $2002 \n"
        "bvc @4 \n"
    ); // wait for sprite zero hit and then wait for it to clear
    PPU.scroll = SCROLL_X1;
    PPU.scroll = 0;
    PPU.control = PPU_CTRL_VAR1;
}





/*
 * bank_spr(n)
 * set the graphics page for sprites
*/
__attribute__((noinline)) void bank_spr(char n){
    PPU_CTRL_VAR &= 0b11110111;
    PPU_CTRL_VAR |= ((n & 1) << 3);
}

/*
 * bank_bg(n)
 * set the graphics page for the background
*/
__attribute__((noinline)) void bank_bg(char n){
    PPU_CTRL_VAR &= 0b11101111;
    PPU_CTRL_VAR |= ((n & 1) << 4);
}





/*
 * vram_read(*dest, size)
 * get contents from vram.
*/
__attribute__((noinline)) void vram_read(unsigned char* const dest, unsigned short size){
    for(unsigned short i=0; i<size; i++){
        dest[i] = PPU.vram.data;
    }
}

/*
 * vram_write(*src, size)
 * write a chunk of data to vram
*/
__attribute__((noinline)) void vram_write(const unsigned char* const src, unsigned short size){
    for(unsigned short i=0; i<size; i++){
        PPU.vram.data = src[i];
    }
}

/*
 * vram_unrle(*src)
 * decompress a nametable
*/
__attribute__((noinline)) void vram_unrle(const unsigned char* src){
    unsigned char tag = src[0]; // tag is the least common byte
    unsigned char value, run;
    src++;

    // disable (and re-enable) nmi while doing this

    //PPU_CTRL_VAR &= 0b01111111;
    //PPU.control = PPU_CTRL_VAR;

    while(1){
        if (src[0] != tag) { 
            // if its not equal to the tag,
            // just write the byte, plain and simple.
            PPU.vram.data = value = src[0];
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
                PPU.vram.data = value;
                run--;
            }
        }
        src++; // move onto the next byte!
    }
    
    //PPU_CTRL_VAR |= 0b10000000;
    //PPU.control = PPU_CTRL_VAR;
}



/*
 * pad_poll(p)
 * get controller input!
*/
__attribute__((noinline)) void pad_poll(unsigned char pad){
    __attribute__((leaf)) __asm__ volatile (
            "ldx #3 \n"

        ".padPollPort: \n"

            "lda #1 \n"
            "sta $4016 \n"
            "sta __rc2,x \n"
            "lda #0 \n"
            "sta $4016 \n"

        ".padPollLoop: \n"

            "lda $4016,y \n"
            "lsr a \n"
            "rol __rc2,x \n"
            "bcc .padPollLoop \n"

            "dex \n"
            "bne .padPollPort \n"

            "lda __rc3 \n"
            "cmp __rc4 \n"
            "beq .done \n"
            "cmp __rc5 \n"
            "beq .done \n"
            "lda __rc4 \n"

        ".done: \n"

            "sta PAD_STATE,y \n"
            "tax \n"
            "eor PAD_STATEP,y \n"
            "and PAD_STATE ,y \n"
            "sta PAD_STATET,y \n"
            "txa \n"
            "sta PAD_STATEP,y \n"
        :
        :"y"(pad)
        :"a","x","p","rc2","rc3","rc4","rc5"
    );
    
}





//
// this is where the random number generator would go
// IF I HAD ONE!!!!!!!!!
//





/*
 * vram_adr(address)
 * set the address of video memory
*/
void vram_adr(unsigned short address){
    PPU.vram.address = high_byte(address);
    PPU.vram.address = low_byte(address);
}

/*
 * vram_put(data)
 * put something in video memory (use vram_adr() first)
*/
void vram_put(unsigned char data){
    PPU.vram.data = low_byte(data);
}

/*
 * vram_fill(n,length)
 * fill video memory with a value (use vram_adr() first)
*/
void vram_fill(unsigned char n, unsigned short length){
    for(unsigned short i=0; i<length; i++){
        PPU.vram.data = n;
    }
}

/*
 * vram_inc(n)
 * zero to increment by 1, nonzero to increment by 32!
*/
void vram_inc(unsigned char n){
    if(n){
        PPU_CTRL_VAR &= 0b11111011;
    } else {
        PPU_CTRL_VAR |= 0b00000100;
    }
}





/*
 * set_vram_update(*buf)
 * set the pointer to the vram buffer.
*/
__attribute__((noinline)) void set_vram_update(const char *buf) {
    NAME_UPD_ADR = buf;
    NAME_UPD_ENABLE = NAME_UPD_ADR != 0;
}





/*
 * memfill(*dest,value,size)
 * fill memory with whatever funny byte you desire!
*/
void memfill(unsigned char* const dest, unsigned char value, unsigned short size){
    for(unsigned short i=0; i<size; i++){
        dest[i] = value;
    }
}





/*
 * get_ppu_ctrl_var()
 * title is self-explanatory
*/
unsigned char get_ppu_ctrl_var(){
    return PPU_CTRL_VAR;
}

/*
 * set_ppu_ctrl_var()
 * title is self-explanatory
*/
void set_ppu_ctrl_var(unsigned char var){
    PPU_CTRL_VAR = var;
}





/*  (CUSTOM)
 *  ppu_emphasis()
 *  tint the screen!
 *
 *  __inputs__
 *  bgr: 0b000 = normal, 0b111 = dark
*/
void ppu_emphasis(unsigned char bgr){
    PPU_MASK_VAR = ((PPU_MASK_VAR & 0b00011111) | ((bgr<<5) & 0b11100000));
    PPU.mask = PPU_MASK_VAR;
    return;
}



/*  (CUSTOM)
 *  ppu_grayscale()
 *  tint the screen!
 *
 *  __inputs__
 *  grayscale: 0 = off, 1 = on
*/
void ppu_grayscale(unsigned char grayscale){
    PPU_MASK_VAR = ((PPU_MASK_VAR & 0b11111110) | (grayscale & 0b00000001));
    PPU.mask = PPU_MASK_VAR;
    return;
}
