#define putinbank(bank) __attribute__((section(bank),retain))

#define IDENT(x) x
#define XSTR(x) #x
#define STR(x) XSTR(x)

#define file(symbol, bank) __attribute__((section((".prg_rom_"STR(bank))),retain)) const unsigned char symbol[]

// LEVELS
// banks 0-31 are reserved for level data.

// GRAPHICS
#define chr_bank_0 32       // menu graphics
#define chr_bank_1 33       // level graphics
#define chr_bank_2 34       // 
#define chr_bank_3 35

// MUSIC DATA
#define sfx_bank 36         // sound fx!
#define music_bank_0 37     // the freakin' music.
#define music_bank_1 38     // |    go to src/famistudio/music_assets.s
#define music_bank_2 39     // V    to set these banks manually.

// SAMPLES
#define dpcm_bank_0 40      // the samplOH MY GOD WHY ARE THERE SO MANY
#define dpcm_bank_1 41      // |    yeah i guess kando wasn't joking
#define dpcm_bank_2 42      // |    when he said "no more space"
#define dpcm_bank_3 43      // |
#define dpcm_bank_4 44      // |
#define dpcm_bank_5 45      // |
#define dpcm_bank_6 46      // |
#define dpcm_bank_7 47      // |
#define dpcm_bank_8 48      // |
#define dpcm_bank_9 49      // |
#define dpcm_bank_10 50     // |
#define dpcm_bank_11 51     // |
#define dpcm_bank_12 52     // |
#define dpcm_bank_13 53     // |    on top of all this, there's still
#define dpcm_bank_14 54     // |    a whole sample bank being left
#define dpcm_bank_15 55     // V    out: bank16.

// banks 56-57 are reserved, on the off-chance we need more extra code

#define extra_code_bank 59  // gamestates that don't need to switch
                            // banks frequently can go in here

#define nametable_bank_0 60 // neslib-rle-packed nametables
#define nametable_bank_1 61 // V

// banks 62 and 63 are fixed. not much i can do about that


file(chr_logo, chr_bank_0) = {
    #embed "./chr/Logo.chr" // 1.00 kb
};    
file(chr_font, chr_bank_0) = {
    #embed "./chr/Font.chr" // 1.50 kb
};    


file(chr_tiles_global, chr_bank_1) = {
    #embed "./chr/General.chr" // 1.00 kb
};    
file(chr_tiles_grid, chr_bank_1) = {
    #embed "./chr/Grid.chr" // 1.00 kb
};    
file(chr_tiles_cross, chr_bank_1) = {
    #embed "./chr/Cross.chr" // 0.25 kb
};
file(chr_tiles_brick, chr_bank_1) = {
    #embed "./chr/Brick.chr" // 0.25 kb
};
file(chr_tiles_black, chr_bank_1) = {
    #embed "./chr/Black.chr" // 0.25 kb
};

//embed(); // 1.00 kb
//embed(, );      // 0.25 kb
//embed(, );    // 0.25 kb
//embed(, );    // 0.25 kb
//embed(, );    // 0.25 kb





//putinbank(".prg_rom_fixed_lo") 



/*putinbank(".prg_rom_fixed_lo") const unsigned char nt_logo[99]={
    0x01,0x00,0x01,0xfe,0x00,0x01,0x4c,0x80,0x81,0x00,0x01,0x1c,0x82,0x83,0x84,0x85,
    0x00,0x01,0x1a,0x86,0x87,0x88,0x89,0x00,0x01,0x1a,0x8a,0x8b,0x8c,0x8d,0x00,0x00,
    0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,0x95,0x00,0x01,0x12,0x96,0x97,0x98,0x99,0x9a,
    0x9b,0x9c,0x9d,0x9e,0x9f,0xa0,0xa1,0xa2,0x00,0x01,0x12,0x96,0x97,0xa3,0xa4,0xa5,
    0x00,0x01,0x1a,0x96,0x97,0xa6,0xa7,0xa8,0x00,0x01,0x1a,0xa9,0xaa,0x00,0x00,0xab,
    0x00,0x01,0x1c,0x50,0x52,0x45,0x53,0x45,0x4e,0x54,0x53,0x00,0x01,0xfe,0x00,0x01,
    0xac,0x01,0x00
};*/


file(dpcm_0, dpcm_bank_0) = {
    #embed "./famistudio/music_0_bank0.dmc"
};
file(dpcm_1, dpcm_bank_1) = {
    #embed "./famistudio/music_0_bank1.dmc"
};
file(dpcm_2, dpcm_bank_2) = {
    #embed "./famistudio/music_0_bank2.dmc"
};
file(dpcm_3, dpcm_bank_3) = {
    #embed "./famistudio/music_0_bank3.dmc"
};
file(dpcm_4, dpcm_bank_4) = {
    #embed "./famistudio/music_0_bank4.dmc"
};
file(dpcm_5, dpcm_bank_5) = {
    #embed "./famistudio/music_0_bank5.dmc"
};
file(dpcm_6, dpcm_bank_6) = {
    #embed "./famistudio/music_0_bank6.dmc"
};
file(dpcm_7, dpcm_bank_7) = {
    #embed "./famistudio/music_0_bank7.dmc"
};
file(dpcm_8, dpcm_bank_8) = {
    #embed "./famistudio/music_0_bank8.dmc"
};
file(dpcm_9, dpcm_bank_9) = {
    #embed "./famistudio/music_0_bank9.dmc"
};
file(dpcm_10, dpcm_bank_10) = {
    #embed "./famistudio/music_0_bank10.dmc"
};
file(dpcm_11, dpcm_bank_11) = {
    #embed "./famistudio/music_0_bank11.dmc"
};
file(dpcm_12, dpcm_bank_12) = {
    #embed "./famistudio/music_0_bank12.dmc"
};
file(dpcm_13, dpcm_bank_13) = {
    #embed "./famistudio/music_0_bank13.dmc"
};
file(dpcm_14, dpcm_bank_14) = {
    #embed "./famistudio/music_0_bank14.dmc"
};
file(dpcm_15, dpcm_bank_15) = {
    #embed "./famistudio/music_0_bank15.dmc"
};
//embed_dpcm("music_0_bank0.dmc", dpcm_0, dpcm_bank_0);
//embed_dpcm("music_0_bank1.dmc", dpcm_1, dpcm_bank_1);
//embed_dpcm("music_0_bank2.dmc", dpcm_2, dpcm_bank_2);
//embed_dpcm("music_0_bank3.dmc", dpcm_3, dpcm_bank_3);
//embed_dpcm("music_0_bank4.dmc", dpcm_4, dpcm_bank_4);
//embed_dpcm("music_0_bank5.dmc", dpcm_5, dpcm_bank_5);
//embed_dpcm("music_0_bank6.dmc", dpcm_6, dpcm_bank_6);

