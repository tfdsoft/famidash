banked(chr_bank_2.table)
const u8 tt_bg0[] = {
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

banked(chr_bank_2.table)
const u8 tt_bg1[] = {

    6, // width
    6, // height
    
    0x40, 0x42, 0x44, 0x46, 0x48, 0x4a, 
    0x41, 0x43, 0x45, 0x47, 0x49, 0x4b, 
    0x60, 0x62, 0x64, 0x66, 0x68, 0x6a, 
    0x4c, 0x4e, 0x50, 0x52, 0x54, 0x56, 
    0x4d, 0x4f, 0x51, 0x53, 0x55, 0x57, 
    0x6c, 0x6e, 0x70, 0x72, 0x74, 0x76, 
};

banked(chr_bank_2.table)
const u8 tt_bg2[] = {

    6, // width
    6, // height
    0x40, 0x42, 0x44, 0x46, 0x48, 0x4a,
    0x41, 0x43, 0x45, 0x47, 0x49, 0x4b,
    0x60, 0x62, 0x64, 0x66, 0x68, 0x6a,
    0x46, 0x48, 0x4a, 0x40, 0x42, 0x44, 
    0x47, 0x49, 0x4b, 0x41, 0x43, 0x45, 
    0x66, 0x68, 0x6a, 0x60, 0x62, 0x64, 
};


banked(chr_bank_2.table)
const u8 * const bg_table_ptr[] = {
    tt_bg0, tt_bg1, tt_bg2
};


banked(chr_bank_2.table)
const u8 mspr_loading[] = {
    -32, -4, 0, 0,
    -24, -4,  0, 0,
    -16, -4, 0, 0,
    -8, -4, 0, 0,
    0, -4, 0, 0,
    8, -4, 0, 0,
    16, -4, 0, 0,
    24, -4, 0, 0,
    0x80
};

u8 loaded_bg_width;

__attribute__((noinline))
void vram_write_parallax(const u8 bg_id){
    //disable_nmi();
    // lots of ugly stuff is happening in this
    // function, brace yourselves
    //uint8_t prev_bank = get_prg_a000();
    u8 width, height, wtimesh;
    //uint8_t i,j;
    const u8 * ptr;

    //push_prg_a000();
    __asm__(
        "lda __prg_a000 \n"
        "pha \n"
    );

    // ok so first, actually switch to the bank
    // where the tile patterns tables are
    set_prg_a000(chr_bank_2);

    
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

    for(u8 i=0,itw=0; i<30; i++,itw+=width){ // i = y
        if(itw >= wtimesh) itw -= wtimesh; // (i * width)

        for(u8 j=0, jmw=0; j<32; j++, jmw++){ // j = x
            if(jmw >= width) jmw -= width; // (j % width)
            u8 tileid = (jmw);
            tileid += (itw);
            PPU.vram.data = ptr[tileid];
        }
    }

    for(u8 i=0; i<64; i++){
        PPU.vram.data = 0;
    }

    __asm__(
        "pla \n"
        "jsr set_prg_a000 \n"
    );
}


__attribute__((noinline))
void vram_generate_parallax(u8 bg_id){
    #define bg_buffer (&sram_buffer[0])
    #define coll_buffer (&sram_buffer[0])

    #define bg_buffer_1 (&bg_buffer[0])
    #define bg_buffer_2 (&bg_buffer[1024])

    const u8 * ptr;
    u8 width, height;

    // empty the parallax buffer
    // don't do it anymore (we need all the frames)
    se_memory_fill((void*)0x6000, 0, sizeof(sram_buffer));

    __asm__(
        "lda __prg_a000 \n"
        "pha \n"
    );
    set_prg_a000(chr_bank_2);

    // get the pointer to the requested bg table
    ptr = bg_table_ptr[bg_id];

    // get the width and height
    width = ptr[0];
    height = ptr[1];

    loaded_bg_width = (width << 2);

    // increment the pointer by two, which
    // *should* make the loop faster since
    // it won't have to add two each time
    ptr += 2;


    __asm__("php \n sei");
    APU.delta_mod.length = 0;
    APU.status &= 0b00001111;
    disable_nmi(); // just in case music_update runs.
    for(u8 step = 0; step < 4; step++){
        // fetch the next bg frame from the ppu
        // (gotta run this four times)
        set_chr_bank(2,0x10+step);
        se_vram_address(0);
        PPU.vram.data; // prime the read

        for(u8 i=0; i<4; i++){
            u8 j=0;
            do{
                bg_buffer_2[(i<<8)+j] = PPU.vram.data;
                j++;
            } while (j != 0);
        }
        


        // 1. get the id of the next tile to write
        // 2. set up a pointer to that tile's data
        // 3. copy that tile to vram
        // 4. repeat from 1. until all tiles are copied
        for (u8 bg_width = 1; bg_width < width; bg_width++){
            set_chr_bank(2,(0x10+(bg_width<<2)+step));
            se_vram_address(0);
            
            for (u8 j=0, jtw=0; j<height; j++, jtw += width){ // y
                u8 tile_end = jtw+width;
                
                for (u8 tileidx = jtw, newtileidx = (width-bg_width); 
                    tileidx < tile_end; 
                    tileidx++, newtileidx++
                ){
                    if(newtileidx >= (width)) newtileidx = 0;

                    u8 tile = ptr[tileidx];//(i + jtw);
                    u8 newtile = (ptr[newtileidx+jtw]-0x40);

                    //uint8_t newtile = (i+(width-bg_width));
                    //if(newtile >= width) newtile -= width;
                    //newtile += jtw;

                    //tile = (ptr[tile]);
                    //newtile = (ptr[newtile]-0x40);
                    
                    for (u8 k=8; k<16; k++){
                        bg_buffer_1[(newtile<<4)|k] = bg_buffer_1[(tile<<4)|k];
                    }
                }
            }
            
            se_vram_address(0);
            se_memory_copy((void*)0x2007, bg_buffer_1, 0x400);
        }
        
    }
    set_chr_bank(2,4);
    enable_nmi();

    __asm__("plp");
    __asm__(
        "pla \n"
        "jsr set_prg_a000 \n"
    );
}

/*
for (uint8_t j=0, jtw=0; j<height; j++, jtw += width){ // y
    for (uint8_t i=0; i<width; i++){ // x

        uint8_t tile = (i + jtw);

        uint8_t newtile = (i+(width-bg_width));
        if(newtile >= width) newtile -= width;
        newtile += jtw;

        tile = (ptr[tile]);
        newtile = (ptr[newtile]-0x40);
        
        for (uint8_t k=0; k<16; k++){
            bg_buffer_1[(newtile<<4)+k] = bg_buffer_1[(tile<<4)+k];
        }
    }
}
*/