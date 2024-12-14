// OBJECT DEFINES =============================================
//
// This is where the obj ids are defined. You probably don't
// want to touch this unless you're planning to add custom
// objects. I highly advise against doing this, since it strays
// away from the vision of this project.
//
// ============================================================

#define CUBE_MODE 				0X00
#define SHIP_MODE 				0X01
#define BALL_MODE 				0X02
#define UFO_MODE 				0X03
#define ROBOT_MODE 				0X04
#define BLUE_ORB 				0X05
#define PINK_ORB 				0X06
#define COIN1 					0X07
#define GRAVITY_DOWN_PORTAL 			0X08
#define GRAVITY_UP_PORTAL 			0X09
#define YELLOW_PAD_DOWN 			0X0A
#define YELLOW_ORB 				0X0B
#define YELLOW_PAD_UP	 			0X0C
#define GRAVITY_PAD_DOWN 			0X0D
#define GRAVITY_PAD_UP	 			0X0E
#define LEVEL_END_TRIGGER 			0X0F
#define GRAVITY_DOWN_UPWARDS_PORTAL 		0X10
#define GRAVITY_DOWN_DOWNWARDS_PORTAL 		0X11
#define GRAVITY_UP_UPWARDS_PORTAL 		0X12
#define GRAVITY_UP_DOWNWARDS_PORTAL 		0X13
#define SPEED_05_PORTAL		 		0X14
#define SPEED_10_PORTAL		 		0X15
#define SPEED_20_PORTAL		 		0X16
#define SPIDER_MODE		 		0X17
#define MINI_PORTAL		 		0X18
#define GROWTH_PORTAL		 		0X19
#define COIN2					0X1A
#define COIN3					0X1B
#define COINGOTTEN1				0X1C
#define COINGOTTEN2				0X1D
#define COINGOTTEN3				0X1E
#define YELLOW_ORB_BIGGER			0X1F
#define SPEED_30_PORTAL				0X20
#define SPEED_40_PORTAL				0X21
#define DUAL_PORTAL				0X22
#define SINGLE_PORTAL				0X23
#define WAVE_MODE				0X24
#define PINK_PAD_DOWN				0X25
#define PINK_PAD_UP				0X26
#define GREEN_ORB				0X27
#define RED_ORB					0X28
#define YELLOW_ORB_SMALLER			0x29
#define DECO_START				0x2A
#define LONG_LIGHT				0x2A
#define MEDIUM_LIGHT				0x2B
#define SHORT_LIGHT				0x2C
#define CHAIN					0x2D
#define BG_SPIKE_GROUP1				0x2E
#define BG_SPIKE_GROUP2				0x2F
#define BG_SPIKE_GROUP3				0x30
#define BG_SPIKE_GROUP4				0x31
#define BIG_DIAMOND				0x32
#define RIGHT_HALF_DIAMOND			0x33
#define QUESTION_MARK				0x34
#define EXCLAMATION_MARK			0x35
#define RIGHT_ARROW				0x36
#define BIG_X					0x37
#define SHORT_LIGHT_RIGHT			0x38
#define SHORT_LIGHT_LEFT			0x39
#define LONG_LIGHT_U				0x3A
#define MEDIUM_LIGHT_U				0x3B
#define SHORT_LIGHT_U				0x3C
#define CHAIN_U					0x3D
#define MEDIUM_LIGHT_RIGHT			0x3E
#define MEDIUM_LIGHT_LEFT			0x3F
#define LONG_LIGHT_RIGHT			0x40
#define LONG_LIGHT_LEFT				0x41
#define SHORT_LIGHT_U_8_PIXELS			0x42
#define CHAIN_U_8_PIXELS			0x43
#define DECO_END				0x43
#define BLACK_ORB				0x44
#define DASH_ORB				0x45
#define DASH_GRAVITY_ORB			0x46
#define BG_SPIKE_GROUP2_UP8			0x47
#define DIAMOND_SHIFTED_			0x48
#define PULSE_ORB				0x49
#define MUSIC_NOTE				0x4A
#define SWING_MODE				0x4B
#define DASH_ORB_45DEG_UP			0x4C
#define DASH_GRAVITY_ORB_45DEG_UP		0x4D
#define TELEPORT_PORTAL_ENTER			0x4E
#define TELEPORT_PORTAL_EXIT			0x4F
#define DASH_ORB_45DEG_DOWN			0x50
#define DASH_GRAVITY_ORB_45DEG_DOWN		0x51
#define RED_PAD_DOWN				0x52
#define RED_PAD_UP				0x53
#define SPIDER_ORB_UP				0x54
#define SPIDER_ORB_DOWN				0x55
#define SPIDER_PAD_UP				0x56
#define SPIDER_PAD_DOWN				0x57
#define NINJA_MODE				0x58
#define TELEPORT_SQUARE_ENTER			0x59
#define TELEPORT_SQUARE_EXIT			0x5A
#define DASH_ORB_UPWARDS			0x5B
#define DASH_GRAVITY_ORB_UPWARDS		0x5C
#define DASH_ORB_DOWNWARDS			0x5D
#define DASH_GRAVITY_ORB_DOWNWARDS		0x5E
#define GRAVITY_13_PORTAL			0x5F
#define GRAVITY_12_PORTAL			0x60
#define GRAVITY_23_PORTAL			0x61
#define GRAVITY_2X_PORTAL			0x62
#define GRAVITY_1X_PORTAL			0x63
#define RANDOM_MODE_PORTAL			0x64
#define GREEN_PAD				0x65
#define TELEPORT_PORTAL_UPWARDS_ENTER		0x66
#define TELEPORT_PORTAL_DOWNWARDS_EXIT		0x67
#define TELEPORT_PORTAL_DOWNWARDS_ENTER		0x68
#define TELEPORT_PORTAL_UPWARDS_EXIT		0x69
#define TALLBOI_MODE_ENTER			0x6A
#define LONGBOI_MODE_ENTER			0x6B
#define BIGBOI_MODE_ENTER			0x6C
#define SPEED_SLOW				0x6D

#define X_SCROLL_SETTING			0xDE	//bottom floor is 0XB0, reset to standard at 0x50
#define DEATH_CHANCE				0xDF

#define TELEPORT_PORTAL_ENTER_EXTENSION		0xED
#define MASK_SPRITES_ON				0xEE
#define MASK_SPRITES_OFF			0xEF

#define FORCED_TRAILS_ON			0xF0
#define FORCED_TRAILS_OFF			0xF1
#define PLAYER_TRAILS_ON			0xF2
#define PLAYER_TRAILS_OFF			0xF3
#define SLOWMODE_ON				0xF4
#define SLOWMODE_OFF				0xF5

#define F_BLOCK					0xF6
#define J_BLOCK					0xF7
#define H_BLOCK					0xF8
#define S_BLOCK					0xF9
#define D_BLOCK					0xFA
#define GRAVITY_UP_INVISIBLE_PORTAL		0XFB
#define GRAVITY_DOWN_INVISIBLE_PORTAL		0XFC
#define GRAVITY_PAD_DOWN_INVISIBLE		0XFD
#define GRAVITY_PAD_UP_INVISIBLE		0XFE
#define NOSPRITE				0XFF
#define TURN_OFF				0XFF