__attribute__((section(".prg_rom_"STR(extra_code_bank_1)".1")))
const uint8_t tt_bg0[] = {
    // alright, here's how the structure works:
    // - width
    // - height
    // - tile order (BYTE COUNT MUST MATCH WIDTH * HEIGHT)

    // this lets the write_parallax function figure
    // out how many animation frames to write, and where

    12, // width
    8, // height
    0x40, 0x42, 0x44, 0x46, 0x48, 0x4a,  0x4d, 0x4f, 0x51, 0x53, 0x55, 0x57,
    0x41, 0x43, 0x45, 0x47, 0x49, 0x4b,  0x6c, 0x6e, 0x70, 0x72, 0x74, 0x76,
    0x60, 0x62, 0x64, 0x66, 0x68, 0x6a,  0x58, 0x5a, 0x5c, 0x5e, 0x78, 0x7a,
    0x4c, 0x4e, 0x50, 0x52, 0x54, 0x56,  0x59, 0x5b, 0x5d, 0x5f, 0x7c, 0x7e,
    0x4d, 0x4f, 0x51, 0x53, 0x55, 0x57,  0x40, 0x42, 0x44, 0x46, 0x48, 0x4a,
    0x6c, 0x6e, 0x70, 0x72, 0x74, 0x76,  0x41, 0x43, 0x45, 0x47, 0x49, 0x4b,
    0x58, 0x5a, 0x5c, 0x5e, 0x78, 0x7a,  0x60, 0x62, 0x64, 0x66, 0x68, 0x6a,
    0x59, 0x5b, 0x5d, 0x5f, 0x7c, 0x7e,  0x4c, 0x4e, 0x50, 0x52, 0x54, 0x56,
};


__attribute__((section(".prg_rom_"STR(extra_code_bank_1)".010")))
const uint8_t * const bg_table_ptr[] = {
    tt_bg0
};




__attribute__((noinline))
void vram_write_parallax(uint8_t bg_id){
    // lots of ugly stuff is happening in this
    // function, brace yourselves
    //uint8_t prev_bank = get_prg_a000();
    uint8_t width, height, wtimesh;
    const uint8_t * ptr;

    __attribute__((leaf)) __asm__ volatile (
        "lda __prg_a000 \n"
        "pha \n"
        "lda #"STR(extra_code_bank_1)" \n"
        "jsr set_prg_a000 \n"
        :
        :
        :"a"
    );

    // ok so first, actually switch to the bank
    // where the tile patterns tables are
    set_prg_a000(extra_code_bank_1);

    // get the pointer to the requested bg table
    ptr = bg_table_ptr[bg_id];

    // get the width and height
    width = ptr[0];
    height = ptr[1];
    wtimesh = (width * height);

    // increment the pointer by two, which
    // *should* make the loop faster since
    // it won't have to add two each time
    ptr += 2;

    for(char i=0; i<30; i++){ // i = y
        for(char j=0; j<32; j++){ // j = x
            uint8_t tileid = (j % width);
            tileid += ((i * width) % wtimesh);
            PPU.vram.data = ptr[tileid];
        }
    }

    __attribute__((leaf)) __asm__ volatile (
        "pla \n"
        "jsr set_prg_a000"
        :
        :
        :"a"
    );
    // and finally, go back.
    //set_prg_a000(prev_bank);
}