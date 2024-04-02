// a 16x16 pixel metasprite
// cube starts here
const unsigned char Cube_0[]={

	  0,  0,0x03,0,
	  8,  0,0x03,0|OAM_FLIP_H,
	0x80
};
const unsigned char Cube_1[]={

	  0,  0,0x05,0,
	  8,  0,0x05,0|OAM_FLIP_H|OAM_FLIP_V,
	0x80
};
const unsigned char Cube_2[]={

	- 4,- 3,0x07,0,
	  4,- 4,0x09,0,
	  4,  4,0x09,0|OAM_FLIP_H|OAM_FLIP_V,
	 12,  3,0x07,0|OAM_FLIP_H|OAM_FLIP_V,
	0x80
};
const unsigned char Cube_3[]={

	- 4,  0,0x0b,0,
	  4,- 4,0x0d,0,
	  4,  4,0x0d,0|OAM_FLIP_V,
	 12,  0,0x0b,0|OAM_FLIP_H,
	0x80
};
const unsigned char Cube_4[]={

	- 4,  3,0x07,0|OAM_FLIP_V,
	  4,  4,0x09,0|OAM_FLIP_V,
	  4,- 4,0x09,0|OAM_FLIP_H,
	 12,- 3,0x07,0|OAM_FLIP_H,
	0x80
};
const unsigned char Cube_5[]={

	  0,  0,0x05,0|OAM_FLIP_V,
	  8,  0,0x05,0|OAM_FLIP_H,
	0x80
};



const unsigned char * const CUBE[] = {Cube_0, Cube_1, Cube_2, Cube_3, Cube_4, Cube_5, Cube_0, Cube_0};
// end cube




// ship starts here
const unsigned char Ship_0[]={

	  0,  0,0x0f,0,
	  8,  0,0x11,0,
	0x80
};
const unsigned char Ship_1[]={

	  0,  0,0x13,0,
	  8,  0,0x15,0,
	0x80
};
const unsigned char Ship_2[]={

	  0,- 1,0x17,0,
	  8,  0,0x19,0,
	0x80
};
const unsigned char Ship_3[]={

	  0,  0,0x17,0,
	  8,  0,0x19,0,
	0x80
};
const unsigned char Ship_4[]={

	  0,  0,0x17,0,
	  8,- 1,0x19,0,
	0x80
};
const unsigned char Ship_5[]={

	  0,  0,0x1b,0,
	  8,  0,0x1d,0,
	0x80
};
const unsigned char Ship_6[]={

	  0,  0,0x1f,0,
	  8,  0,0x21,0,
	0x80
};


const unsigned char * const SHIP[] = {Ship_0, Ship_0, Ship_1, Ship_2, Ship_4, Ship_5, Ship_6, Ship_6};
// end ship



const unsigned char COIN_SPRITE[]={

	  0,  0,0x4D,1,
	  8,  0,0x4D,1|OAM_FLIP_H,
	0x80
};
const unsigned char COIN_1[]={

	  0,  0,0x4F,1,
	  8,  0,0x51,1,
	0x80
};
const unsigned char COIN_2[]={

	  0,  0,0x53,1,
	  8,  0,0x53,1|OAM_FLIP_H,
	0x80
};
const unsigned char COIN_3[]={

	  0,  0,0x51,1|OAM_FLIP_H,
	  8,  0,0x4F,1|OAM_FLIP_H,
	0x80
};


const unsigned char * const COIN_SPRITES[]={COIN_SPRITE, COIN_SPRITE, COIN_SPRITE, COIN_SPRITE, COIN_SPRITE, COIN_1, COIN_1, COIN_1, COIN_1, COIN_1, COIN_2, COIN_2, COIN_2, COIN_2, COIN_2, COIN_3, COIN_3, COIN_3, COIN_3, COIN_3};


const unsigned char Ball_0[]={

	  0,  0,0x23,0,
	  8,  0,0x23,0|OAM_FLIP_H,
	0x80
};
const unsigned char Ball_1[]={

	  0,  0,0x55,0,
	  8,  0,0x55,0|OAM_FLIP_H,
	0x80
};

const unsigned char * const BALL[]={Ball_0, Ball_0, Ball_0, Ball_1, Ball_1, Ball_1};
// ================================================================

const unsigned char Portal_Gamemode_Cube[]={

	  0,  0,0x25,0,
	  0, 16,0x2b,0,
	  0, 32,0x25,0|OAM_FLIP_V,
	  8,  0,0x27,0,

	  8, 16,0x41,0,
	  8, 32,0x27,0|OAM_FLIP_V,
	 16,  0,0x29,0,
	 16, 16,0x2d,0,

	 16, 32,0x29,0|OAM_FLIP_V,
	0x80
};
const unsigned char Portal_Gamemode_Ship[]={

	  0,  0,0x25,1,
	  0, 16,0x2b,1,
	  0, 32,0x25,1|OAM_FLIP_V,
	  8,  0,0x27,1,

	  8, 16,0x41,1,
	  8, 32,0x27,1|OAM_FLIP_V,
	 16,  0,0x29,1,
	 16, 16,0x2d,1,

	 16, 32,0x29,1|OAM_FLIP_V,
	0x80
};
const unsigned char Portal_Gamemode_Ball[]={

	  0,  0,0x25,2,
	  0, 16,0x2b,2,
	  0, 32,0x25,2|OAM_FLIP_V,
	  8,  0,0x27,2,

	  8, 16,0x41,2,
	  8, 32,0x27,2|OAM_FLIP_V,
	 16,  0,0x29,2,
	 16, 16,0x2d,2,

	 16, 32,0x29,2|OAM_FLIP_V,
	0x80
};
const unsigned char Portal_Gravity_Down[]={

	  0,  0,0x31,0,
	  0, 16,0x37,0,
	  0, 32,0x31,0|OAM_FLIP_V,
	  8,  0,0x3b,0,

	  8, 16,0x43,0,
	  8, 32,0x3b,0|OAM_FLIP_V,
	 16,  0,0x3d,0,
	 16, 16,0x3f,0,

	 16, 32,0x3d,0|OAM_FLIP_V,
	0x80
};
const unsigned char Portal_Gravity_Up[]={

	  0,  0,0x31,1,
	  0, 16,0x37,1,
	  0, 32,0x31,1|OAM_FLIP_V,
	  8,  0,0x3b,1,

	  8, 16,0x43,1,
	  8, 32,0x3b,1|OAM_FLIP_V,
	 16,  0,0x3d,0,
	 16, 16,0x3f,0,

	 16, 32,0x3d,0|OAM_FLIP_V,
	0x80
};



// ================================================================

const unsigned char Yellow_Jump_Orb[]={

//	  0,  0,0x45,2,
//	  8,  0,0x45,2|OAM_FLIP_H,
	  4,  0,0x47,1,
	0x80
};

const unsigned char Blue_Jump_Orb[]={

	  4,  0,0x47,4,
	0x80
};
const unsigned char Pink_Jump_Orb[]={

//	  0,  0,0x45,6,
//	  8,  0,0x45,6|OAM_FLIP_H,
	  4,  0,0x47,7,
	0x80
};

const unsigned char Yellow_Jump_Pad[]={

	  0,0,0x49,1,
	  8,0,0x49,1|OAM_FLIP_H,
	0x80
};
const unsigned char Yellow_Jump_Pad_U[]={

	  0,-8,0x49,1|OAM_FLIP_V,
	  8,-8,0x49,1|OAM_FLIP_H|OAM_FLIP_V,
	0x80
};

const unsigned char Gravity_Pad[]={

	  0,8,0x49,4,
	  8,8,0x49,4|OAM_FLIP_H,
	0x80
};
const unsigned char Gravity_Pad_U[]={

	  0,-8,0x49,4|OAM_FLIP_V,
	  8,-8,0x49,4|OAM_FLIP_H|OAM_FLIP_V,
	0x80
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
	Yellow_Jump_Orb, // end stage trigger

	// start of color triggers


	};
