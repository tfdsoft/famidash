struct Metatile {
    u8 topleft;
    u8 topright;
    u8 bottomleft;
    u8 bottomright;
};

struct Metatile_Attr {
    u8 palette : 2;

    u8 topleft : 1;
    u8 topright : 1;
    u8 bottomleft : 1;
    u8 bottomright : 1;

    u8 type : 2;
};