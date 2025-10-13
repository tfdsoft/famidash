__attribute__((section(".aligned"),retain)) struct OAM_BUF {
    unsigned char y;
    unsigned char tile;
    unsigned char attr;
    unsigned char x;
} OAM_BUF[64];


unsigned char gamestate;



