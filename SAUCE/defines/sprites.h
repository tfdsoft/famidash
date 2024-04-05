// a 16x16 pixel metasprite
// cube starts here
const unsigned char Mini_Cube_0[]={

	  0,  0,0x43,0,
	  8,  0,0x43,0|OAM_FLIP_H,
	0x80
	
};
	
const unsigned char * const MINI_CUBE[] = {Mini_Cube_0, Mini_Cube_0, Mini_Cube_0, Mini_Cube_0, Mini_Cube_0, Mini_Cube_0, Mini_Cube_0, Mini_Cube_0};
	
const unsigned char Cube_0[]={

	  0,  0,0x01,0,
	  8,  0,0x01,0|OAM_FLIP_H,
	0x80
};
const unsigned char Cube_1[]={

	  0,  0,0x03,0,
	  8,  0,0x03,0|OAM_FLIP_H|OAM_FLIP_V,
	0x80
};
const unsigned char Cube_2[]={

	- 4,- 3,0x05,0,
	  4,- 4,0x07,0,
	  4,  4,0x07,0|OAM_FLIP_H|OAM_FLIP_V,
	 12,  3,0x05,0|OAM_FLIP_H|OAM_FLIP_V,
	0x80
};
const unsigned char Cube_3[]={

	- 4,  0,0x09,0,
	  4,- 4,0x0b,0,
	  4,  4,0x0b,0|OAM_FLIP_V,
	 12,  0,0x09,0|OAM_FLIP_H,
	0x80
};
const unsigned char Cube_4[]={

	- 4,  3,0x05,0|OAM_FLIP_V,
	  4,  4,0x07,0|OAM_FLIP_V,
	  4,- 4,0x07,0|OAM_FLIP_H,
	 12,- 3,0x05,0|OAM_FLIP_H,
	0x80
};
const unsigned char Cube_5[]={

	  0,  0,0x03,0|OAM_FLIP_V,
	  8,  0,0x03,0|OAM_FLIP_H,
	0x80
};



const unsigned char * const CUBE[] = {Cube_0, Cube_1, Cube_2, Cube_3, Cube_4, Cube_5, Cube_0, Cube_0};
// end cube




// ship starts here
const unsigned char Ship_0[]={

	  0,  0,0x0d,0,
	  8,  0,0x0f,0,
	0x80
};
const unsigned char Ship_1[]={

	  0,  0,0x11,0,
	  8,  0,0x13,0,
	0x80
};
const unsigned char Ship_2[]={

	  0,- 1,0x15,0,
	  8,  0,0x17,0,
	0x80
};
const unsigned char Ship_3[]={

	  0,  0,0x15,0,
	  8,  0,0x17,0,
	0x80
};
const unsigned char Ship_4[]={

	  0,  0,0x15,0,
	  8,- 1,0x17,0,
	0x80
};
const unsigned char Ship_5[]={

	  0,  0,0x19,0,
	  8,  0,0x1b,0,
	0x80
};
const unsigned char Ship_6[]={

	  0,  0,0x1d,0,
	  8,  0,0x1f,0,
	0x80
};


const unsigned char * const SHIP[] = {Ship_0, Ship_0, Ship_1, Ship_2, Ship_4, Ship_5, Ship_6, Ship_6};
// end ship



const unsigned char COIN_SPRITE[]={

	  0,  0,0xB1,1,
	  8,  0,0xB1,1|OAM_FLIP_H,
	0x80
};
const unsigned char COIN_1[]={

	  0,  0,0xB3,1,
	  8,  0,0xB5,1,
	0x80
};
const unsigned char COIN_2[]={

	  0,  0,0xB7,1,
	  8,  0,0xB7,1|OAM_FLIP_H,
	0x80
};
const unsigned char COIN_3[]={

	  0,  0,0xB5,1|OAM_FLIP_H,
	  8,  0,0xB3,1|OAM_FLIP_H,
	0x80
};



const unsigned char Ball_0[]={

	  0,  0,0x21,0,
	  8,  0,0x21,0|OAM_FLIP_H,
	0x80
};
const unsigned char Ball_1[]={

	  0,  0,0x23,0,
	  8,  0,0x23,0|OAM_FLIP_H,
	0x80
};

const unsigned char * const BALL[]={Ball_0, Ball_0, Ball_0, Ball_0, Ball_1, Ball_1, Ball_1, Ball_1};
// ================================================================

const unsigned char Portal_Gamemode_Cube[]={

	  0,  0,0xC1,0,
	  0, 16,0xC7,0,
	  0, 32,0xC1,0|OAM_FLIP_V,
	  8,  0,0xC3,0,

	  8, 16,0xc9,0,
	  8, 32,0xC3,0|OAM_FLIP_V,
	 16,  0,0xC5,0,
	 16, 16,0xCB,0,

	 16, 32,0xC5,0|OAM_FLIP_V,
	0x80
};
const unsigned char Portal_Gamemode_Ship[]={

	  0,  0,0xC1,1,
	  0, 16,0xC7,1,
	  0, 32,0xC1,1|OAM_FLIP_V,
	  8,  0,0xC3,1,

	  8, 16,0xC9,1,
	  8, 32,0xC3,1|OAM_FLIP_V,
	 16,  0,0xC5,1,
	 16, 16,0xCB,1,

	 16, 32,0xC5,1|OAM_FLIP_V,
	0x80
};
const unsigned char Portal_Gamemode_Ball[]={

	  0,  0,0xC1,2,
	  0, 16,0xC7,2,
	  0, 32,0xC1,2|OAM_FLIP_V,
	  8,  0,0xC3,2,

	  8, 16,0xC9,2,
	  8, 32,0xC3,2|OAM_FLIP_V,
	 16,  0,0xC5,2,
	 16, 16,0xCB,2,

	 16, 32,0xC5,2|OAM_FLIP_V,
	0x80
};
const unsigned char Portal_Gravity_Down[]={
	  0,  0,0x8d,0,  
	  0, 16,0x93,0,  
	  0, 32,0x8d,0|OAM_FLIP_V, 
	  8,  0,0x8f,0,  

	  8, 16,0x95,0,
	  8, 32,0x8f,0|OAM_FLIP_V,  
	 16,  0,0x91,0,  
	 16, 16,0x97,0, 

	 16, 32,0x91,0|OAM_FLIP_V, 
	0x80
};
const unsigned char Portal_Gravity_Up[]={

	  0,  0,0x8d,1,  
	  0, 16,0x93,1,  
	  0, 32,0x8d,1|OAM_FLIP_V, 
	  8,  0,0x8f,1,  

	  8, 16,0x95,1,
	  8, 32,0x8f,1|OAM_FLIP_V,  
	 16,  0,0x91,0,  
	 16, 16,0x97,0, 

	 16, 32,0x91,0|OAM_FLIP_V, 
	0x80
};
const unsigned char Portal_Gravity_Down_Horizontal_Downwards[]={

	8,0,0xAD,0,
	16,0,0xAF,0,
	24,0,0xAf,0|OAM_FLIP_H,
	32,0,0xAD,0|OAM_FLIP_H,

	  0,  16,0xA1,0,  
	  8, 16,0xA3,0,  
	  16, 16,0xA5,0,
	  24, 16,0xA5,0|OAM_FLIP_H,  

	  32, 16,0xA3,0|OAM_FLIP_H,
	 40, 16,0xA1,0|OAM_FLIP_H,  

	0x80
};
const unsigned char Portal_Gravity_Down_Horizontal_Upwards[]={

	8,16,0xAD,0|OAM_FLIP_V,
	16,16,0xAF,0|OAM_FLIP_V,
	24,16,0xAf,0|OAM_FLIP_V|OAM_FLIP_H,
	32,16,0xAD,0|OAM_FLIP_V|OAM_FLIP_H,

	  0,  0,0xA1,0|OAM_FLIP_V,  
	  8, 0,0xA3,0|OAM_FLIP_V,  
	  16, 0,0xA5,0|OAM_FLIP_V,
	  24, 0,0xA5,0|OAM_FLIP_V|OAM_FLIP_H,  

	  32, 0,0xA3,0|OAM_FLIP_V|OAM_FLIP_H,
	 40, 0,0xA1,0|OAM_FLIP_V|OAM_FLIP_H,  

	0x80
};
const unsigned char Portal_Gravity_Up_Horizontal_Downwards[]={

	8,0,0xAD,0,
	16,0,0xAF,0,
	24,0,0xAf,0|OAM_FLIP_H,
	32,0,0xAD,0|OAM_FLIP_H,

	  0,  16,0xA1,1,  
	  8, 16,0xA3,1,  
	  16, 16,0xA5,1,
	  24, 16,0xA5,1|OAM_FLIP_H,  

	  32, 16,0xA3,1|OAM_FLIP_H,
	 40, 16,0xA1,1|OAM_FLIP_H,  

	0x80
};
const unsigned char Portal_Gravity_Up_Horizontal_Upwards[]={

	8,16,0xAD,0|OAM_FLIP_V,
	16,16,0xAF,0|OAM_FLIP_V,
	24,16,0xAf,0|OAM_FLIP_V|OAM_FLIP_H,
	32,16,0xAD,0|OAM_FLIP_V|OAM_FLIP_H,

	  0,  0,0xA1,1|OAM_FLIP_V,  
	  8, 0,0xA3,1|OAM_FLIP_V,  
	  16, 0,0xA5,1|OAM_FLIP_V,
	  24, 0,0xA5,1|OAM_FLIP_V|OAM_FLIP_H,  

	  32, 0,0xA3,1|OAM_FLIP_V|OAM_FLIP_H,
	 40, 0,0xA1,1|OAM_FLIP_V|OAM_FLIP_H,  

	0x80
};




// ================================================================

const unsigned char Yellow_Jump_Orb[]={

//	  0,  0,0x45,2,
//	  8,  0,0x45,2|OAM_FLIP_H,
	  4,  0,0xBB,1,
	0x80
};

const unsigned char Blue_Jump_Orb[]={

	  4,  0,0xBB,4,
	0x80
};
const unsigned char Pink_Jump_Orb[]={

//	  0,  0,0x45,6,
//	  8,  0,0x45,6|OAM_FLIP_H,
	  4,  0,0xBB,7,
	0x80
};

const unsigned char Yellow_Jump_Pad[]={

	  0,-8,0x99,1,
	  8,-8,0x9B,1|OAM_FLIP_H,
	0x80
};
const unsigned char Yellow_Jump_Pad2[]={

	  0,-8,0x9B,1,
	  8,-8,0x9D,1|OAM_FLIP_H,
	0x80
};
const unsigned char Yellow_Jump_Pad3[]={

	  0,-8,0x9D,1,
	  8,-8,0x9F,1|OAM_FLIP_H,
	0x80
};
const unsigned char Yellow_Jump_Pad4[]={

	  0,-8,0x9F,1,
	  8,-8,0x99,1|OAM_FLIP_H,
	0x80
};

const unsigned char Yellow_Jump_Pad_U[]={

	  0,-0,0x99,1|OAM_FLIP_V,
	  8,-0,0x9B,1|OAM_FLIP_H|OAM_FLIP_V,
	0x80
};
const unsigned char Yellow_Jump_Pad_U2[]={

	  0,-0,0x9B,1|OAM_FLIP_V,
	  8,-0,0x9D,1|OAM_FLIP_H|OAM_FLIP_V,
	0x80
};
const unsigned char Yellow_Jump_Pad_U3[]={

	  0,-0,0x9D,1|OAM_FLIP_V,
	  8,-0,0x9F,1|OAM_FLIP_H|OAM_FLIP_V,
	0x80
};
const unsigned char Yellow_Jump_Pad_U4[]={

	  0,-0,0x9F,1|OAM_FLIP_V,
	  8,-0,0x99,1|OAM_FLIP_H|OAM_FLIP_V,
	0x80
};

const unsigned char Gravity_Pad[]={

	  0,-0,0x99,4,
	  8,-0,0x9B,4|OAM_FLIP_H,
	0x80
};
const unsigned char Gravity_Pad2[]={

	  0,-0,0x9B,4,
	  8,-0,0x9D,4|OAM_FLIP_H,
	0x80
};
const unsigned char Gravity_Pad3[]={

	  0,-0,0x9D,4,
	  8,-0,0x9F,4|OAM_FLIP_H,
	0x80
};
const unsigned char Gravity_Pad4[]={

	  0,-0,0x9F,4,
	  8,-0,0x99,4|OAM_FLIP_H,
	0x80
};

const unsigned char Gravity_Pad_U[]={

	  0, -0,0x99,4|OAM_FLIP_V,
	  8, -0,0x9B,4|OAM_FLIP_H|OAM_FLIP_V,
	0x80
};
const unsigned char Gravity_Pad_U2[]={

	  0, -0,0x9B,4|OAM_FLIP_V,
	  8, -0,0x9D,4|OAM_FLIP_H|OAM_FLIP_V,
	0x80
};
const unsigned char Gravity_Pad_U3[]={

	  0, -0,0x9D,4|OAM_FLIP_V,
	  8, -0,0x9F,4|OAM_FLIP_H|OAM_FLIP_V,
	0x80
};
const unsigned char Gravity_Pad_U4[]={

	  0, -0,0x9F,4|OAM_FLIP_V,
	  8, -0,0x99,4|OAM_FLIP_H|OAM_FLIP_V,
	0x80
};

struct SpriteFrame {
	unsigned short frame_count; // use a two byte length value for alignment
	const unsigned char* ptr;
};

const struct SpriteFrame COIN_SPRITES[]={
	{5, COIN_SPRITE},
	{5, COIN_1},
	{5, COIN_2},
	{5, COIN_3},
};

const struct SpriteFrame YELLOW_PAD_SPRITES[]={
	{5, Yellow_Jump_Pad},
	{5, Yellow_Jump_Pad2},
	{5, Yellow_Jump_Pad3},
	{5, Yellow_Jump_Pad4},
};

const struct SpriteFrame YELLOW_PAD_U_SPRITES[]={
	{5, Yellow_Jump_Pad_U},
	{5, Yellow_Jump_Pad_U2},
	{5, Yellow_Jump_Pad_U3},
	{5, Yellow_Jump_Pad_U4},
};

const struct SpriteFrame GRAVITY_PAD_SPRITES[]={
	{5, Gravity_Pad},
	{5, Gravity_Pad2},
	{5, Gravity_Pad3},
	{5, Gravity_Pad4},
};

const struct SpriteFrame GRAVITY_PAD_U_SPRITES[]={
	{5, Gravity_Pad_U},
	{5, Gravity_Pad_U2},
	{5, Gravity_Pad_U3},
	{5, Gravity_Pad_U4},
};

const unsigned char nometa[] = {0x80};

const unsigned char * const Metasprites[]={
	Portal_Gamemode_Cube,
	Portal_Gamemode_Ship, 
	Portal_Gamemode_Ball, // ball
	nometa, // ufo
	nometa, // wave
	Blue_Jump_Orb, // bobot
	Pink_Jump_Orb, 
	COIN_SPRITE, // swing
	Portal_Gravity_Down,
	Portal_Gravity_Up,
	Yellow_Jump_Pad,
	Yellow_Jump_Orb,
	Yellow_Jump_Pad_U,
	Gravity_Pad,
	Gravity_Pad_U,	  //Coin Disappear
	nometa, // end stage trigger

	Portal_Gravity_Down_Horizontal_Downwards,
	Portal_Gravity_Down_Horizontal_Upwards,
	Portal_Gravity_Up_Horizontal_Downwards,
	Portal_Gravity_Up_Horizontal_Upwards,
	};


// Animation data
const void* animation_frame_list[] = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	COIN_SPRITES,
	NULL, // Portal_Gravity_Down,
	NULL, // Portal_Gravity_Up,
	YELLOW_PAD_SPRITES, // Yellow_Jump_Pad,
	NULL, // Yellow_Jump_Orb,
	YELLOW_PAD_U_SPRITES, // Yellow_Jump_Pad_U,
	GRAVITY_PAD_SPRITES, // Gravity_Pad,
	GRAVITY_PAD_U_SPRITES, // Gravity_Pad_U,	  //Coin Disappear
	NULL, // nometa, // end stage trigger
};

// Number of UNIQUE animation frames
const unsigned char animation_frame_length[] = {
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	sizeof(COIN_SPRITES) / sizeof(struct SpriteFrame), // COIN_SPRITE
	0, // Portal_Gravity_Down,
	0, // Portal_Gravity_Up,
	sizeof(YELLOW_PAD_SPRITES) / sizeof(struct SpriteFrame), // Yellow_Jump_Pad,
	0, // Yellow_Jump_Orb,
	sizeof(YELLOW_PAD_U_SPRITES) / sizeof(struct SpriteFrame), // Yellow_Jump_Pad_U,
	sizeof(GRAVITY_PAD_SPRITES) / sizeof(struct SpriteFrame), // Gravity_Pad,
	sizeof(YELLOW_PAD_U_SPRITES) / sizeof(struct SpriteFrame), // Gravity_Pad_U,	  //Coin Disappear
	0, // nometa, // end stage trigger
};
