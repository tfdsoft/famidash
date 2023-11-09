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

	  0,  0,0x0b,0,
	  8,  0,0x0c,0,
	  0,  8,0x0d,0,
	  8,  8,0x0e,0,
	0x80
};
const unsigned char Ship_1[]={

	  0,  0,0x10,0,
	  8,  0,0x11,0,
	  0,  8,0x12,0,
	  8,  8,0x13,0,
	0x80
};
const unsigned char Ship_2[]={

	  0,  0,0x14,0,
	  8,  1,0x15,0,
	  0,  8,0x16,0,
	  8,  9,0x17,0,
	0x80
};
const unsigned char Ship_3[]={

	  0,  0,0x14,0,
	  8,  0,0x15,0,
	  0,  8,0x16,0,
	  8,  8,0x17,0,
	0x80
};
const unsigned char Ship_4[]={

	  0,  0,0x14,0,
	  8,- 1,0x15,0,
	  0,  8,0x16,0,
	  8,  7,0x17,0,
	0x80
};
const unsigned char Ship_5[]={

	  0,  0,0x18,0,
	  8,  0,0x19,0,
	  0,  8,0x1a,0,
	  8,  8,0x1b,0,
	0x80
};
const unsigned char Ship_6[]={

	  0,  0,0x1c,0,
	  8,  0,0x1d,0,
	  0,  8,0x1e,0,
	  8,  8,0x1f,0,
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



// Portals
const unsigned char Portal_Gamemode_Cube[]={

	  0,  0,0x20,0,
	  3,  8,0x21,0,
	  6, 16,0x22,0,
	  6, 24,0x22,0|OAM_FLIP_V,

	  3, 32,0x21,0|OAM_FLIP_V,
	  0, 40,0x20,0|OAM_FLIP_V,
	  6,  0,0x26,1,
	  9,  8,0x27,1,

	 12, 16,0x28,1,
	 12, 24,0x28,1|OAM_FLIP_V,
	  9, 32,0x27,1|OAM_FLIP_V,
	  6, 40,0x26,1|OAM_FLIP_V,
	0x80
};

const unsigned char Portal_Gamemode_Ship[]={

	  0,  0,0x20,1,
	  3,  8,0x21,1,
	  6, 16,0x22,1,
	  6, 24,0x22,1|OAM_FLIP_V,

	  3, 32,0x21,1|OAM_FLIP_V,
	  0, 40,0x20,1|OAM_FLIP_V,
	  6,  0,0x26,1,
	  9,  8,0x27,1,

	 12, 16,0x28,1,
	 12, 24,0x28,1|OAM_FLIP_V,
	  9, 32,0x27,1|OAM_FLIP_V,
	  6, 40,0x26,1|OAM_FLIP_V,
	0x80
};



const unsigned char Portal_Gravity_Down[]={

	  0,-16,0x23,0,
	  3,- 8,0x24,0,
	  6,  0,0x25,0,
	  6,  8,0x25,0|OAM_FLIP_V,

	  3, 16,0x24,0|OAM_FLIP_V,
	  0, 24,0x23,0|OAM_FLIP_V,
	0x80
};

const unsigned char Portal_Gravity_Up[]={

	  0,-16,0x23,1,
	  3,- 8,0x24,1,
	  6,  0,0x25,1,
	  6,  8,0x25,1|OAM_FLIP_V,

	  3, 16,0x24,1|OAM_FLIP_V,
	  0, 24,0x23,1|OAM_FLIP_V,
	0x80
};




const unsigned char * const Portals[]={Portal_Gamemode_Cube, Portal_Gamemode_Ship, Portal_Gravity_Down, Portal_Gravity_Up};
