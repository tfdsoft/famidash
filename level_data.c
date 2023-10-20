enum{
    PORTAL_GAMEMODE_CUBE,
    PORTAL_GAMEMODE_SHIP,
    PORTAL_GRAVITY_DOWN,
    PORTAL_GRAVITY_UP,
    n4,
    n5,
    n6,
    n7,
    n8,
    n9,
    n10,
    n11,
    n12,
    n13,
    n14,
    n15,

    TRIG_BG_DR,              // Red BG
    TRIG_BG_DO,              // Orange BG
    TRIG_BG_DY,              // Yellow BG
    TRIG_BG_DG0,             // Green BG 1
    TRIG_BG_DG1,             // Green BG 2
    TRIG_BG_DT,              // Teal BG
    TRIG_BG_DB0,             // Blue BG 1
    TRIG_BG_DB1,             // Blue BG 2
    TRIG_BG_DI,              // Indigo BG
    TRIG_BG_DV,              // Violet BG
    TRIG_BG_DP,              // Pink BG
    TRIG_BG_DM,              // Magenta BG
    TRIG_BG_DGRAY,
    n29,
    n30,
    TRIG_BG_BLACK,

    TRIG_BG_R,              // Red BG
    TRIG_BG_O,              // Orange BG
    TRIG_BG_Y,              // Yellow BG
    TRIG_BG_G0,             // Green BG 1
    TRIG_BG_G1,             // Green BG 2
    TRIG_BG_T,              // Teal BG
    TRIG_BG_B0,             // Blue BG 1
    TRIG_BG_B1,             // Blue BG 2
    TRIG_BG_I,              // Indigo BG
    TRIG_BG_V,              // Violet BG
    TRIG_BG_P,              // Pink BG
    TRIG_BG_M,              // Magenta BG
    TRIG_BG_GRAY,
    n45,
    n46,
    n47,

    TRIG_BG_LR,              // Red BG
    TRIG_BG_LO,              // Orange BG
    TRIG_BG_LY,              // Yellow BG
    TRIG_BG_LG0,             // Green BG 1
    TRIG_BG_LG1,             // Green BG 2
    TRIG_BG_LT,              // Teal BG
    TRIG_BG_LB0,             // Blue BG 1
    TRIG_BG_LB1,             // Blue BG 2
    TRIG_BG_LI,              // Indigo BG
    TRIG_BG_LV,              // Violet BG
    TRIG_BG_LP,              // Pink BG
    TRIG_BG_LM,              // Magenta BG
    TRIG_BG_WHITE
};
#define obj0 PORTAL_GAMEMODE_CUBE
#define obj1 PORTAL_GAMEMODE_SHIP
#define obj2 PORTAL_GRAVITY_DOWN
#define obj3 PORTAL_GRAVITY_UP
#define obj4 NULL
#define obj5 NULL
#define obj6 NULL
#define obj7 NULL
#define obj8 NULL
#define obj9 NULL
#define obj10 NULL
#define obj11 NULL
#define obj12 NULL
#define obj13 NULL
#define obj14 NULL
#define obj15 NULL

#define obj16 TRIG_BG_DR
#define obj17 TRIG_BG_DO
#define obj18 TRIG_BG_DY
#define obj19 TRIG_BG_DG0
#define obj20 TRIG_BG_DG1
#define obj21 TRIG_BG_DT
#define obj22 TRIG_BG_DB0
#define obj23 TRIG_BG_DB1
#define obj24 TRIG_BG_DI
#define obj25 TRIG_BG_DV
#define obj26 TRIG_BG_DP
#define obj27 TRIG_BG_DM
#define obj28 TRIG_BG_DGRAY
#define obj29 NULL
#define obj30 NULL
#define obj31 TRIG_BG_BLACK

#define obj32 TRIG_BG_R
#define obj33 TRIG_BG_O
#define obj34 TRIG_BG_Y
#define obj35 TRIG_BG_G0
#define obj36 TRIG_BG_G1
#define obj37 TRIG_BG_T
#define obj38 TRIG_BG_B0
#define obj39 TRIG_BG_B1
#define obj40 TRIG_BG_I
#define obj41 TRIG_BG_V
#define obj42 TRIG_BG_P
#define obj43 TRIG_BG_M
#define obj44 TRIG_BG_GRAY
#define obj45 NULL
#define obj46 NULL
#define obj47 NULL

#define obj48 TRIG_BG_LR
#define obj49 TRIG_BG_LO
#define obj50 TRIG_BG_LY
#define obj51 TRIG_BG_LG0
#define obj52 TRIG_BG_LG1
#define obj53 TRIG_BG_LT
#define obj54 TRIG_BG_LB0
#define obj55 TRIG_BG_LB1
#define obj56 TRIG_BG_LI
#define obj57 TRIG_BG_LV
#define obj58 TRIG_BG_LP
#define obj59 TRIG_BG_LM
#define obj60 TRIG_BG_WHITE
#define obj61 NULL
////////////////////////////////

// Y, room, X, object #
const unsigned char obj_stereomadness[]={
0x00, 0, 0x00, obj39, 
0x00, 7, 0xf0, obj41, 
0x00, 15, 0x50, obj25, 
0x00, 15, 0x60, obj31, 
0x70, 16, 0xa0, obj1, 
0x00, 16, 0xb0, obj26, 
0x00, 16, 0xc0, obj42, 
0x70, 26, 0x20, obj0, 
0x80, 26, 0x20, obj0, 
0x00, 26, 0x30, obj41, 
0x00, 31, 0xe0, obj41, 
0x00, 31, 0xf0, obj42, 
0x00, 32, 0x00, obj43, 
0x00, 32, 0x10, obj32, 
0x00, 47, 0xc0, obj43, 
0x70, 47, 0xc0, obj1, 
0x80, 47, 0xc0, obj1, 
0x00, 47, 0xd0, obj42, 
0x00, 47, 0xe0, obj41, 
TURN_OFF

};


const unsigned char * const obj_list[]={ obj_stereomadness };