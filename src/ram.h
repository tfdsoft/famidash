__attribute__((section(".aligned.0"),retain)) struct OAM_BUF {
    unsigned char y;
    unsigned char tile;
    unsigned char attr;
    unsigned char x;
} OAM_BUF[64];



unsigned char gamestate=0xff;

unsigned char song = 0;
unsigned char interrupt_scroll;
