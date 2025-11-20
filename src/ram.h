__attribute__((section(".aligned.0"),retain)) struct OAM_BUF {
    unsigned char y;
    unsigned char tile;
    unsigned char attr;
    unsigned char x;
} OAM_BUF[64];



unsigned char gamestate=0xff;

unsigned char song;



struct LVL_HDR {
    uint8_t name[32]; // 31 + null terminator

    struct color {
        uint8_t bg;
        uint8_t g;

        //uint8_t obj;
        //uint8_t line;

        //uint8_t col1;
        //uint8_t col2;
        //uint8_t col3;   // colors 3 and 4 are only
        //uint8_t col4;   // for advanced color mode
    } color;

    struct tileset {
        struct blocks { // one 1k bank can hold four sets of blocks
            // active
            uint8_t set_0;
            uint8_t set_1;
            uint8_t set_2;
            uint8_t set_3;

            // standby
            //uint8_t set_4;
            //uint8_t set_5;
            //uint8_t set_6;
            //uint8_t set_7;

            //uint8_t set_8; 
            //uint8_t set_9;
            //uint8_t set_a;
            //uint8_t set_b;

            //uint8_t set_c; 
            //uint8_t set_d;
            //uint8_t set_e;
            //uint8_t set_f;
        } blocks; // TODO: bitpack these

        /*struct sawblades {
            uint8_t set_0;  // 0-7 

                            // one 1k bank can hold 
                            // one animation frame of
                            // saws; hence, only one
                            // set can be used in a 
        } sawblades;        // level*/

        /*struct slopes { // one 1k bank can hold one set of slopes
            // active
            uint8_t set_0;  // 0-15

            // standby
            uint8_t set_1;  // if set_0 is 0xff, slopes are disabled
            
            uint8_t set_2;

            uint8_t set_3;  
        } slopes;*/

        /*struct sprites {
            uint8_t spike_deco; // 0-7
            uint8_t saw_deco;   // 0-7
        } sprites;*/
    } tileset;

    struct settings {
        uint8_t gamemode;
        uint8_t song;
        //uint8_t speed;

    } settings;

    struct ptr { // pointer for all the data n whatnot
        uint8_t * level_addr;
        uint8_t level_bank;
        uint8_t * sprite_addr;
        uint8_t sprite_bank;
    } ptr;
    
    // pad to 128 bytes
    uint8_t padding[81];
};

// i plan on putting an array of these in prg_rom_0
// 8192 bytes (bank) / 128 bytes (level header) = 64 levels

// note that some of the struct is commented out for now;
// i'm gonna add 1.0 stuff first, then work up to 1.9



/*
struct LVL_HDR {
    uint8_t name[32];   // 32

    struct color {
        uint8_t bg;
        uint8_t g;

        uint8_t obj;
        uint8_t line;

        uint8_t col1;
        uint8_t col2;
        uint8_t col3;   // colors 3 and 4 are only
        uint8_t col4;   // for advanced color mode
    } color;                  // 40

    struct tileset {
        struct blocks { // one 1k bank can hold four sets of blocks
            // active
            uint8_t set_0;
            uint8_t set_1;
            uint8_t set_2;
            uint8_t set_3;

            // standby
            uint8_t set_4;
            uint8_t set_5;
            uint8_t set_6;
            uint8_t set_7;

            uint8_t set_8; 
            uint8_t set_9;
            uint8_t set_a;
            uint8_t set_b;

            uint8_t set_c; 
            uint8_t set_d;
            uint8_t set_e;
            uint8_t set_f;
        } blocks;

        struct sawblades {
            uint8_t set_0;  // 0-7 

                            // one 1k bank can hold 
                            // one animation frame of
                            // saws; hence, only one
                            // set can be used in a 
        } sawblades;        // level

        struct slopes { // one 1k bank can hold one set of slopes
            // active
            uint8_t set_0;  // 0-15

            // standby
            uint8_t set_1;  // if set_0 is 0xff, slopes are disabled
            
            uint8_t set_2;

            uint8_t set_3;  
        } slopes;

        struct sprites {
            uint8_t spike_deco; // 0-7
            uint8_t saw_deco;   // 0-7
        } sprites;
    } tileset;

    struct settings {
        uint8_t gamemode;
        uint8_t song;
        uint8_t speed;

    } settings;
    
    
    
};


*/
struct Player {
    // X
    union {
        unsigned _BitInt(24) int24;
        struct {
            uint8_t subpixel;
            uint8_t lo;
            uint8_t hi;
        };
        struct {
            uint8_t notimportant;
            uint16_t word;
        };
    } x;
    uint8_t width;

    // Y
    union {
        unsigned _BitInt(24) int24;
        struct {
            uint8_t subpixel;
            uint8_t lo;
            uint8_t hi;
        };
        struct {
            uint8_t notimportant;
            uint16_t word;
        };
    } y;
    uint8_t height;

    // properties
    struct {
        uint8_t speed : 3;
        uint8_t can_jump : 1;
        uint8_t click_buffered : 1;
        uint8_t dead : 1;
    } prop;
};
struct Camera {
    union {
        unsigned _BitInt(24) x;
        struct {
            uint8_t subpixel;
            uint8_t lo;
            uint8_t hi;
        };
        struct {
            uint8_t notimportant;
            uint16_t word;
        };
    } x;
    union {
        unsigned _BitInt(24) y;
        struct {
            uint8_t subpixel;
            uint8_t lo;
            uint8_t hi;
        };
        struct {
            uint8_t notimportant;
            uint16_t word;
        };
    } y;
};


__attribute__((retain))
uint8_t loaded_bg_set, loaded_g_set,
        return_gamestate;

__attribute__((retain)) struct Player player;
__attribute__((retain)) struct Camera camera;
__attribute__((retain)) int16_t player_speed_x, player_speed_y;

__attribute__((section(".prg_ram"),retain)) 
uint8_t sram_buffer[2048], background_set, ground_set;

#define bg_buffer (&sram_buffer[0])
#define coll_buffer (&sram_buffer[0])

#define bg_buffer_1 (&bg_buffer[0])
#define bg_buffer_2 (&bg_buffer[1024])


__attribute__((section(".prg_ram"),retain)) 
uint8_t saved_menu_theme;