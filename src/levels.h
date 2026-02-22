#define level_bank_0 1

struct Level {
    u8 name[24];

    struct {
        u8 bg;
        u8 g;
        //u8 obj;
        //u8 line;
    } color;

    u8* tile_data; u8 tile_bank;
    u8* sprite_data; u8 sprite_bank;
};