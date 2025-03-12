// game states
#define MENU 0x01
#define GAME 0x02


#define COIN_1 0x01
#define COIN_2 0x02
#define COIN_3 0x04

// gamemodes
#define GAMEMODE_CUBE   0x00
#define GAMEMODE_SHIP   0x01
#define GAMEMODE_BALL   0x02
#define GAMEMODE_UFO    0x03
#define GAMEMODE_ROBOT  0x04
#define GAMEMODE_SPIDER 0x05
#define GAMEMODE_WAVE   0x06
#define GAMEMODE_SWING  0x07
#define GAMEMODE_NINJA  0x08

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

uint8_t currplayer_mini;
uint16_t currplayer_x;
uint16_t currplayer_y;
int16_t currplayer_vel_x;
int16_t currplayer_vel_y;
uint8_t currplayer_gravity;
uint8_t currplayer_x_small;
uint8_t currplayer_y_small;
int8_t currplayer_vel_y_small;
int8_t currplayer_slope_frames;
uint8_t currplayer_was_on_slope_counter;
uint8_t currplayer_slope_type;
uint8_t currplayer_last_slope_type;
uint8_t currplayer_direction;

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

uint8_t mini[2];
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
int8_t slope_frames[2];

uint8_t slope_type[2];
uint8_t was_on_slope_counter[2];
uint8_t * sprite_data;
uint8_t * level_data;

#pragma zpsym("sprite_data")
#pragma zpsym("level_data")


// SRAM
#pragma bss-name(pop)
#pragma bss-name(push, "SRAM")
uint8_t SRAM_VALIDATE[4];

uint8_t coin1_obtained[MAX_LEVEL_COMPLETE];
uint8_t coin2_obtained[MAX_LEVEL_COMPLETE];
uint8_t coin3_obtained[MAX_LEVEL_COMPLETE];

uint8_t LEVELCOMPLETE[MAX_LEVEL_COMPLETE];
uint8_t level_completeness_normal[MAX_LEVEL_COMPLETE*2];
#define level_completeness_practice (&level_completeness_normal[MAX_LEVEL_COMPLETE])
uint8_t achievements[0x20];

uint8_t invisible;
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
uint8_t exitPortalTimer;
uint8_t menu_music;
#if !__VS_SYSTEM
uint8_t auto_practicepoints;
#endif


uint8_t jimsheatballalive[MAX_FIREBALLS]; //jims heatball shit
uint16_t jimsheatballx[MAX_FIREBALLS]; //jims heatball shit
uint16_t jimsheatbally[MAX_FIREBALLS];
int16_t jimsheatball_vel_x[MAX_FIREBALLS];
int16_t jimsheatball_vel_y[MAX_FIREBALLS];
uint8_t jimsheatballframe[MAX_FIREBALLS];

//uint8_t greyscale_mode;

//uint8_t practice_famistudio_state[0xbf];

uint8_t practice_point_count; // = 0;
uint8_t curr_practice_point;
uint8_t latest_practice_point;


lohi_arr16_decl(practice_player_1_x, MAX_PRACTICE_POINTS);
lohi_arr16_decl(practice_player_1_vel_x, MAX_PRACTICE_POINTS);
lohi_arr16_decl(practice_player_1_y, MAX_PRACTICE_POINTS);
lohi_arr16_decl(practice_player_1_vel_y, MAX_PRACTICE_POINTS);
lohi_arr16_decl(practice_cube_1_rotate, MAX_PRACTICE_POINTS);

lohi_arr16_decl(practice_player_2_x, MAX_PRACTICE_POINTS);
lohi_arr16_decl(practice_player_2_vel_x, MAX_PRACTICE_POINTS);
lohi_arr16_decl(practice_player_2_y, MAX_PRACTICE_POINTS);
lohi_arr16_decl(practice_player_2_vel_y, MAX_PRACTICE_POINTS);
lohi_arr16_decl(practice_cube_2_rotate, MAX_PRACTICE_POINTS);

uint8_t practice_player_1_gravity[MAX_PRACTICE_POINTS];
uint8_t practice_player_2_gravity[MAX_PRACTICE_POINTS];
uint8_t practice_player_1_mini[MAX_PRACTICE_POINTS];
uint8_t practice_player_2_mini[MAX_PRACTICE_POINTS];
uint8_t practice_player_1_was_on_slope_counter[MAX_PRACTICE_POINTS];
uint8_t practice_player_2_was_on_slope_counter[MAX_PRACTICE_POINTS];
int8_t practice_player_1_slope_frames[MAX_PRACTICE_POINTS];
int8_t practice_player_2_slope_frames[MAX_PRACTICE_POINTS];
int8_t practice_player_1_slope_type[MAX_PRACTICE_POINTS];
int8_t practice_player_2_slope_type[MAX_PRACTICE_POINTS];
int8_t practice_player_1_last_slope_type[MAX_PRACTICE_POINTS];
int8_t practice_player_2_last_slope_type[MAX_PRACTICE_POINTS];

lohi_arr32_decl(practice_scroll_x, MAX_PRACTICE_POINTS);
lohi_arr16_decl(practice_scroll_y, MAX_PRACTICE_POINTS);
lohi_arr16_decl(practice_min_scroll_y, MAX_PRACTICE_POINTS);
lohi_arr16_decl(practice_seam_scroll_y, MAX_PRACTICE_POINTS);
lohi_arr16_decl(practice_old_draw_scroll_y, MAX_PRACTICE_POINTS);
lohi_arr16_decl(practice_target_scroll_y, MAX_PRACTICE_POINTS);

uint8_t practice_nocamlockforced[MAX_PRACTICE_POINTS];
uint8_t practice_player_gamemode[MAX_PRACTICE_POINTS];
uint8_t practice_dual[MAX_PRACTICE_POINTS];
uint8_t practice_speed[MAX_PRACTICE_POINTS];
uint8_t practice_parallax_scroll_x[MAX_PRACTICE_POINTS];
uint8_t practice_outline_color[MAX_PRACTICE_POINTS];
uint8_t practice_g_color_type[MAX_PRACTICE_POINTS];
uint8_t practice_bg_color_type[MAX_PRACTICE_POINTS];
//uint8_t practice_trail_sprites_visible[9];
//uint8_t practice_player_old_posy[9];
uint8_t practice_orbactive[MAX_PRACTICE_POINTS];

unsigned char practice_famistudio_state[200 * MAX_PRACTICE_POINTS];
unsigned char practice_famistudio_registers[11 * MAX_PRACTICE_POINTS];

unsigned char practice_music_sync;

#define poweroffcheck SRAM_VALIDATE[3]
// Regular NES RAM
#pragma bss-name(pop)

extern unsigned char famistudio_state[200];
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
uint8_t kandokidshack4;

#if __VS_SYSTEM

uint8_t coins_inserted;
uint8_t CREDITS1_PREV;
uint8_t CREDITS2_PREV;

#endif

uint16_t exittimer;
uint16_t jumps;
uint8_t orbed[2];
uint8_t speed;
uint8_t shuffle_offset;
uint8_t count;
uint8_t coins;
uint8_t currplayer;
uint8_t menuMusicCurrentlyPlaying;
uint8_t ball_switched[2];
uint8_t processXMovement;
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
uint8_t nocamlockforced;
uint8_t nestopia;

uint8_t last_slope_type[2];

uint8_t gameState;

uint8_t teleport_output;

uint8_t normalorcommlevels;
uint8_t mouse_timer;
uint8_t prev_mouse_x;
uint8_t prev_mouse_y;
#if __VS_SYSTEM
uint8_t showarrownow;
#endif

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
uint8_t make_cube_jump_higher;

uint8_t animating;
uint8_t coin1_timer;
uint8_t coin2_timer;
uint8_t coin3_timer;
uint16_t coin1_speed;
uint16_t coin2_speed;
uint16_t coin3_speed;

#if __VS_SYSTEM
uint16_t menutimer;
#endif

// trail stuff
uint8_t orbactive;
uint8_t trail_sprites_visible[9];

uint8_t ufo_orbed;

uint8_t dashing[2];

uint8_t minicoins;

#if !__VS_SYSTEM
uint16_t auto_practicepoint_timer;
#endif

// Sprite Storage
lohi_arr16_decl(activesprites_x, max_loaded_sprites);
lohi_arr16_decl(activesprites_y, max_loaded_sprites);
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
uint8_t pauseStatus;

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
	0x00,0x0f,0x24,0x38,
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
#if __VS_SYSTEM
const uint8_t gameoverpalette[16] = { //MAIN MENU
    0x11,0x0F,0x24,0x30,
    0x11,0x0f,0x06,0x30,
    0x11,0x0F,0x27,0x30,
    0x11,0x0F,0x11,0x30
};
#endif
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