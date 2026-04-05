struct Level {
    u8 name[24];

    struct {
        u8 bg;
        u8 g;
        //u8 obj;
        //u8 line;
    } color;

    struct {
        const u8* blocks[4];
        const struct Metatile* metatiles[4];
    } tileset;

    u8 song;

    u8 height;

    u8* tile_data; u8 tile_bank;
    u8* sprite_data; u8 sprite_bank;
};


#define grid16(x,y) ((x&15)|(y<<4))