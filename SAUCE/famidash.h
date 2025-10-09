// Defines

#define NINJABANK 92
#define MOUSEBANK 94
#define LETTERBANK 96
#define MENUBANK 98
#define MENUICONBANK 102
#define LEVELCOMPLETEBANK 106
#define PRACTICECOMPLETEBANK 110

#define SPIKESA 0
#define SPIKESB 2
#define BLOCKSA 4
#define BLOCKSB 6
#define BLOCKSC 8
#define BLOCKSD 10
#define SAWBLADESA 12
#define SLOPESA 14

// game states
#define MENU 0x01
#define GAME 0x02


#define MAX_ICONS 27 //total icons

// physics defines
#define ORB_HEIGHT_YELLOW_UPSIDE2 -0x580
#define PAD_HEIGHT_BLUE -0x3A0

#define ORB_BALL_HEIGHT_BLUE -0x1A0

#define CUBE_WIDTH 0x0F
#define CUBE_HEIGHT 0x0F

#define MINI_CUBE_WIDTH 0x08
#define MINI_CUBE_HEIGHT 0x07

#define WAVE_WIDTH 0x03
#define WAVE_HEIGHT 0x03

#define MINI_WAVE_WIDTH 0x01
#define MINI_WAVE_HEIGHT 0x01

#define JUMP_VEL -0x590
#define MINI_JUMP_VEL -0x4D0

#define UFO_JUMP_VEL -0x2F0
#define MINI_UFO_JUMP_VEL -0x2D0

#define ROBOT_JUMP_VEL -0x2B0
#define MINI_ROBOT_JUMP_VEL -0x2B0

#define CUBE_SPEED_X05 0x23B
#define CUBE_SPEED_X1 0x2C4
#define CUBE_SPEED_X2 0x371
#define CUBE_SPEED_X3 0x429
#define CUBE_SPEED_X4 0x51E

#define ROBOT_JUMP_TIME 18

#define UFO_MAX_FALLSPEED 0x320
#define MINI_UFO_MAX_FALLSPEED 0x350
#define CUBE_MAX_FALLSPEED 0x600
#define CUBE_GRAVITY 0x6B

#define MINI_CUBE_MAX_FALLSPEED 0x600
#define MINI_CUBE_GRAVITY 0x6F

#define UFO_GRAVITY 0x2C
#define MINI_UFO_GRAVITY 0x32

#define BALL_GRAVITY 0x53
#define BALL_MAX_FALLSPEED 0x600
#define SWING_GRAVITY 0x38
#define SWING_MAX_FALLSPEED 0x4D0
#define MINI_SWING_GRAVITY 0x38
#define MINI_SWING_MAX_FALLSPEED 0x4D0
#define MINI_BALL_GRAVITY 0x57
#define MINI_BALL_MAX_FALLSPEED 0x600

#define SHIP_MAX_FALLSPEED 0x2B0
#define MINI_SHIP_MAX_FALLSPEED 0x380

#define SHIP_GRAVITY 0x2F
#define MINI_SHIP_GRAVITY 0x31

#define JIMSHEATBALL_MAX_FALLSPEED 0x300
#define JIMSHEATBALL_GRAVITY 0x34
#define JIMSHEATBALL_JUMP_VEL -0x390

#define COIN_1 0x01
#define COIN_2 0x02
#define COIN_3 0x04


// Zeropage variables
#pragma bss-name(push, "ZEROPAGE")

uint8_t tmp1;
uint8_t tmp2;
uint8_t tmp3;
uint8_t tmp4;
uint16_t tmp5;
uint16_t tmp6;
uint8_t tmp7;
uint8_t tmp8;
uint8_t tmp9;
uint16_t tmpA;
uint16_t tmpB;
uint8_t temptemp5;
int16_t fallspeed_big;
int16_t fallspeed_mini;
int16_t gravity_big;
int16_t gravity_mini;
uint8_t iconbank1;
uint8_t iconbank2;
uint8_t iconbank3;
uint8_t* tmpptr1;
uint8_t* tmpptr2;
uint32_t tmplong;
uint8_t selectedbgm;
uint8_t selectedsfx;
int8_t tmpi8;

#pragma zpsym("tmpptr1")
#pragma zpsym("tmpptr2")

extern volatile unsigned char VRAM_UPDATE;
#pragma zpsym ("VRAM_UPDATE")

uint16_t currplayer_x;
uint16_t currplayer_y;
int16_t currplayer_vel_x;
int16_t currplayer_vel_y;
uint8_t currplayer_gravity;
uint8_t currplayer_x_small;
uint8_t currplayer_y_small;
int8_t currplayer_vel_y_small;

uint8_t gamemode;
uint8_t cube_data[2];
uint16_t cube_rotate[2];

uint8_t collision;
uint8_t collision_L;
uint8_t collision_R;
uint8_t collision_U;
uint8_t collision_D;

uint16_t old_x;
uint16_t old_y;

uint8_t mini;
uint8_t eject_L; // from the left
uint8_t eject_R; // remember these from the collision sub routine
uint8_t eject_D; // from below
uint8_t eject_U; // from up

uintptr_t address;
uint8_t x; // room loader code
uint8_t y;
uint8_t index;
uint8_t temp_x;
uint8_t temp_y;
uint8_t temp_room;
uint8_t dual;
int8_t slope_frames;

uint8_t slope_type;
uint8_t was_on_slope_counter;
uint8_t * sprite_data;
uint8_t * level_data;

#pragma zpsym("sprite_data")
#pragma zpsym("level_data")


// SRAM

#pragma bss-name("SRAM")
uint8_t SRAM_VALIDATE[4];

//moved to BUILD FLAGS
#ifdef FLAG_ENABLE_TEST_LEVELS
	#define LEVEL_COUNT 256
#else
	#define LEVEL_COUNT 13
#endif

#ifdef FLAG_ENABLE_TEST_LEVELS
	#define LEVEL_COUNT2 256
#else
	#define LEVEL_COUNT2 20
#endif


uint8_t coin1_obtained[0x40];
uint8_t coin2_obtained[0x40];
uint8_t coin3_obtained[0x40];

uint8_t LEVELCOMPLETE[0x40];
uint8_t level_completeness_normal[0x40*2];
#define level_completeness_practice (&level_completeness_normal[0x40])
uint8_t achievements[0x20];

uint8_t invisible;
uint8_t PRACTICE_ENABLED = 1;
uint8_t twoplayer;

/* memory optimization */
//uint8_t oneptwoplayer;
//uint8_t jumpsound;
//uint8_t platformer;
//uint8_t musicoff;
//uint8_t sfxoff;
uint8_t options;
#define oneptwoplayer 0x01
#define jumpsound 0x02
#define platformer 0x04
#define debugtoggle 0x08

#define sfxoff 0x40
#define musicoff 0x80

uint8_t icon;
uint8_t icon_colors[3];

#define color1 icon_colors[0]
#define color2 icon_colors[1]
#define color3 icon_colors[2]

uint8_t cursedmusic;
uint8_t discomode;
uint8_t trails;
uint8_t viseffects;
uint8_t retro_mode;
uint8_t palette_cycle_mode;
uint8_t gameboy_mode;
uint8_t invisblocks;
uint8_t cam_seesaw;
uint8_t forced_credits;
extern uint8_t extceil;
uint8_t exitingLevelSelect;
uint8_t drawBarFlag;

#define MAX_FIREBALLS 20

uint8_t jimsheatballalive[MAX_FIREBALLS]; //jims heatball shit
uint16_t jimsheatballx[MAX_FIREBALLS]; //jims heatball shit
uint16_t jimsheatbally[MAX_FIREBALLS];
int16_t jimsheatball_vel_x[MAX_FIREBALLS];
int16_t jimsheatball_vel_y[MAX_FIREBALLS];
uint8_t jimsheatballframe[MAX_FIREBALLS];

//uint8_t greyscale_mode;

//uint8_t practice_famistudio_state[0xbf];


#define poweroffcheck SRAM_VALIDATE[3]
// Regular NES RAM
#pragma bss-name("BSS")

uint8_t last_gameState;

//extern uint8_t famistudio_state[0xbf];



uint16_t player_x[2];
uint16_t player_y[2];
int16_t player_vel_x[2];
int16_t player_vel_y[2];
uint8_t player_gravity[2];

uint8_t long_temp_x;

uint8_t kandokidshack;
uint8_t kandokidshack2;
uint8_t kandokidshack3;

uint16_t exittimer;
uint8_t jumps;
uint8_t orbed[2];
uint8_t speed;
uint8_t shuffle_offset;
uint8_t count;
uint8_t coins;
uint8_t currplayer;
uint8_t kandotemp;
uint8_t kandotemp2[2];
uint8_t kandotemp3;
//uint8_t kandotemp4;
//uint8_t kandotemp5;
uint8_t kandoframecnt;
// NOTE: joypad2 in memory is before joypad1 due to ram saving reasons
// so controllingplayer = 0 is player 2, and controllingplayer = 1 is player 1
// uint8_t controllingplayer;
uint8_t spiderframe[2];
uint8_t robotframe[2];
uint8_t ballframe;
uint8_t robotjumpframe[2];
uint8_t robotjumptime[2];
uint8_t hblocked[2];
uint8_t jblocked[2];
uint8_t fblocked[2];
uint8_t ninjajumps[2];
uint8_t slowmode;
uint8_t use_auto_chrswitch;
uint8_t level; // = 0x00;
uint8_t level_data_bank;
uint8_t sprite_data_bank;
uint8_t menuselection; // = 0x00;
uint8_t settingvalue;
uint8_t mouseframe;
uint8_t hold_timer;
uint8_t titlemode;
uint8_t titlecolor1;
uint8_t titlecolor2;
uint8_t titlecolor3;
uint8_t titleicon;
uint8_t kandodebugmode;
//uint8_t kandodebug2;
uint8_t all_levels_complete;
uint16_t triggers;
uint16_t top_triggers;

uint8_t nocamlock;

uint8_t last_slope_type;

uint8_t gameState = 0x01;

uint8_t teleport_output;

uint8_t normalorcommlevels;
uint8_t mouse_timer;
uint8_t prev_mouse_x;
uint8_t prev_mouse_y;

extern uint8_t parallax_scroll_column;
extern uint8_t parallax_scroll_column_start;
uint8_t parallax_scroll_x;
uint8_t invincible_counter;
uint32_t scroll_x; // gotta love massive levels amirite fellas
uint16_t scroll_y;
uint16_t old_trail_scroll_y;
uint16_t target_scroll_y;
//uint16_t reload_target_scroll_y;
uint8_t song;
uint8_t songplaying;
uint8_t temptemp6;

uint8_t animating;
uint8_t coin1_timer;
uint8_t coin2_timer;
uint8_t coin3_timer;
uint16_t coin1_speed;
uint16_t coin2_speed;
uint16_t coin3_speed;

// trail stuff
uint8_t orbactive;
uint8_t trail_sprites_visible[9];

uint8_t dashing[2];

uint8_t disable_dpcm_bankswitch;
uint8_t has_practice_point; // = 0;
uint8_t curr_practice_point;

#define MAX_PRACTICE_POINTS 8

uint16_t practice_player_x[2*MAX_PRACTICE_POINTS];
uint16_t practice_player_y[2*MAX_PRACTICE_POINTS];
uint8_t practice_player_gamemode[MAX_PRACTICE_POINTS];
uint8_t practice_mini[MAX_PRACTICE_POINTS];
uint8_t practice_dual[MAX_PRACTICE_POINTS];
uint8_t practice_speed[MAX_PRACTICE_POINTS];
uint16_t practice_cube_rotate[2*MAX_PRACTICE_POINTS];
int16_t practice_player_vel_x[2*MAX_PRACTICE_POINTS];
int16_t practice_player_vel_y[2*MAX_PRACTICE_POINTS];
uint8_t practice_player_gravity[2*MAX_PRACTICE_POINTS];
uint32_t practice_scroll_x[MAX_PRACTICE_POINTS];
uint16_t practice_scroll_y[MAX_PRACTICE_POINTS];
uint8_t practice_parallax_scroll_x[MAX_PRACTICE_POINTS];
uint8_t practice_g_color[MAX_PRACTICE_POINTS];
uint8_t practice_bg_color[MAX_PRACTICE_POINTS];
uint8_t practice_g_color_type[MAX_PRACTICE_POINTS];
uint8_t practice_bg_color_type[MAX_PRACTICE_POINTS];
//uint8_t practice_trail_sprites_visible[9];
//uint8_t practice_player_old_posy[9];
uint8_t practice_orbactive[MAX_PRACTICE_POINTS];
uint16_t practice_target_scroll_y[MAX_PRACTICE_POINTS];

// the funny uh uhhhhh um the uhh sprite storidge
// X_lowbyte, X_highbyte, Y_lowbyte, Y_highbyte, object id, unused, unused, unused
#define max_loaded_sprites 16
uint8_t activesprites_x_lo[max_loaded_sprites];
uint8_t activesprites_x_hi[max_loaded_sprites];
uint8_t activesprites_y_lo[max_loaded_sprites];
uint8_t activesprites_y_hi[max_loaded_sprites];
uint8_t activesprites_type[max_loaded_sprites];
uint8_t activesprites_anim_frame[max_loaded_sprites];
int8_t activesprites_anim_frame_count[max_loaded_sprites];

uint8_t activesprites_realx[max_loaded_sprites];
uint8_t activesprites_realy[max_loaded_sprites];
uint8_t activesprites_active[max_loaded_sprites];
uint8_t activesprites_activated[max_loaded_sprites];



uint8_t DEBUG_MODE; // = 0;
uint8_t lastgcolortype;
uint8_t lastbgcolortype;
uint8_t iconbank;
uint8_t dblocked[2];


uint8_t player_old_posy[9];
uint8_t discorefreshrate;
uint8_t discoframe;
uint8_t no_parallax;
uint8_t outline_color;
uint8_t forced_trails;

uint8_t attemptCounter[7];
uint8_t triggers_hit[3];

/*
uint8_t gnd_palette_transition_timer;
uint8_t original_gnd_palette_idx_0;
uint8_t original_gnd_palette_idx_1;
uint8_t original_gnd_palette_color_0;
uint8_t original_gnd_palette_color_1;

uint8_t bg_palette_transition_timer;
uint8_t original_bg_palette_idx_0;
uint8_t original_bg_palette_idx_1;
uint8_t original_bg_palette_idx_2;
uint8_t original_bg_palette_color_0;
uint8_t original_bg_palette_color_1;
uint8_t original_bg_palette_color_2;

uint8_t current_transition_timer_length;
*/

#ifdef FLAG_KANDO_FUN_STUFF
uint16_t target_x_scroll_stop;
uint16_t curr_x_scroll_stop;
uint8_t disco_sprites;
uint8_t tallmode;
uint8_t longmode;
uint8_t bigboi;
uint8_t gravity_mod;
#endif

uint8_t kandowatchesyousleep;	//variable to say whether to go back to main menu or level select

extern uint16_t min_scroll_y;
extern uint16_t seam_scroll_y;

extern volatile uint8_t hexToDecOutputBuffer[5];

//struct player {
//	uint16_t x; // low byte is sub-pixel
//	uint16_t y;
//	int16_t vel_x; // speed, signed, low byte is sub-pixel
//	int16_t vel_y;
//};

//struct player player = {0x0000,0xb000};

//struct player2 {
//	uint16_t x; // low byte is sub-pixel
//	uint16_t y;
//	int16_t vel_x; // speed, signed, low byte is sub-pixel
//	int16_t vel_y;
//};

//struct player2 player2 = {0x0000,0xb000};

struct Base {
	uint8_t x;
	uint8_t y;
	uint8_t width;
	uint8_t height;
};

struct Base Generic;
struct Base Generic2;

// Palette declarations for some reason

const uint8_t paletteDefault[16] = {
    0x11,0x01,0x0F,0x30,	// palette 0, used for level tiles
	0x00,0x01,0x11,0x30,	// palette 1, used for ground
	0x00,0x01,0x0F,0x2A,	// palette 2, used for decorations
	0x00,0x0F,0x00,0x30 	// palette 3, used for text
};

const uint8_t paletteDefaultSP[16]={
	0x00,0x0f,0x2a,0x21,
	0x00,0x0f,0x24,0x28,
	0x00,0x0f,0x16,0x30,
	0x00,0x0f,0x2a,0x2C,
};

const uint8_t paletteMenu[16] = { //SUBMENUS (minus settings)
	0x17,0x0f,0x10,0x30,
	0x11,0x0f,0x2a,0x39,
	0x17,0x0f,0x17,0x27,
	0x17,0x0f,0x11,0x21
};
const uint8_t paletteSettings[16] = {
	0x17,0x0f,0x10,0x30,
	0x11,0x0f,0x2a,0x39,
	0x17,0x0F,0x16,0x26,
	0x17,0x0f,0x11,0x21
};

const uint8_t splashMenu[16] = { //MAIN MENU
    0x11,0x0F,0x27,0x30,
    0x11,0x0f,0x2a,0x39,
    0x11,0x0F,0x27,0x30,
    0x11,0x0F,0x11,0x30
};

const uint8_t oldsplashMenu[16] = { //MAIN MENU
    0x11,0x0F,0x11,0x30,
    0x11,0x0f,0x2a,0x39,
    0x11,0x0F,0x27,0x30,
    0x11,0x0F,0x11,0x30
};

const uint8_t splashMenu2[16] = { //MAIN MENU
    0x11,0x0F,0x14,0x37,
    0x11,0x0f,0x2a,0x39,
    0x11,0x0F,0x27,0x30,
    0x11,0x0F,0x11,0x30
};

const uint8_t paletteLVLSelectSP[16] = {
	0x11, 0x0f, 0x2a, 0x30,
	0x11, 0x0f, 0x11, 0x30,
	0x11, 0x0f, 0x11, 0x30,
	0x11, 0x0f, 0x30, 0x30,
};