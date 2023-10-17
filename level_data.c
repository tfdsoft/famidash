enum{
    PORTAL_GAMEMODE_CUBE, 
    PORTAL_GAMEMODE_SHIP, 
    PORTAL_GRAVITY_DOWN,
    PORTAL_GRAVITY_UP
};

////////////////////////////////
// Y, room, X, object #
const unsigned char obj_polargeist[]={
    0x50, 20, 0x10, PORTAL_GAMEMODE_SHIP, 
    0x50, 27, 0xb0, PORTAL_GAMEMODE_CUBE, 
    0x60, 27, 0xb0, PORTAL_GAMEMODE_CUBE, 
TURN_OFF
};


const unsigned char * const obj_list[]={ obj_polargeist };