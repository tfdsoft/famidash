struct Metatile {
    u8 topleft;
    u8 topright;
    u8 bottomleft;
    u8 bottomright;
};



// one byte crammed full of info.
// the guide:

// palettes: 0 = background, 1 = ground, 2/3 = color channels
// 
struct Metatile_Attr {
    u8 palette : 2;
    u8 type : 2;
    union {
        u8 collision : 4;
        struct {
            u8 collision_tl : 1;
            u8 collision_tr : 1;
            u8 collision_bl : 1;
            u8 collision_br : 1;
        };
    };
};