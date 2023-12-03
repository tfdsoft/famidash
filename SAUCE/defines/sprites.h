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


const unsigned char * const SHIP[] = {Ship_0, Ship_0, Ship_1, Ship_2, Ship_3, Ship_4, Ship_5, Ship_6, Ship_6};
// end ship


const unsigned char Ball[]={

	  0,  0,0x29,0,
	  8,  0,0x29,0|OAM_FLIP_H,
	  0,  8,0x29,0|OAM_FLIP_V,
	  8,  8,0x29,0|OAM_FLIP_H|OAM_FLIP_V,
	0x80
};

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

const unsigned char Jump_Orb[]={

	  0,  0,0x45,2,
	  8,  0,0x45,2|OAM_FLIP_H,
	  4,  0,0x47,1,
	0x80
};
const unsigned char Jump_Pad[]={

	  0,- 8,0x49,1,
	  8,- 8,0x49,1|OAM_FLIP_H,
	0x80
};





const unsigned char nometa[] = {0x80};

const unsigned char * const Metasprites[]={
	Portal_Gamemode_Cube,
	Portal_Gamemode_Ship, 
	nometa, // ball
	nometa, // ufo
	nometa, // wave
	nometa, // bobot
	nometa, // spider
	nometa, // swing
	Portal_Gravity_Down,
	Portal_Gravity_Up,
	Jump_Pad,
	Jump_Orb,
	nometa,
	nometa,
	nometa,
	nometa, // end stage trigger

	// start of color triggers


	};
