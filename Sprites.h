// a 16x16 pixel metasprite
// cube starts here
const unsigned char Cube_0[]={

	  0,  0,0x01,0,
	  0,  8,0x01,0|OAM_FLIP_V,
	  8,  0,0x01,0|OAM_FLIP_H,
	  8,  8,0x01,0|OAM_FLIP_H|OAM_FLIP_V,
	0x80
};
const unsigned char Cube_1[]={

	  0,  0,0x09,0,
	  0,  8,0x0a,0|OAM_FLIP_H|OAM_FLIP_V,
	  8,  0,0x0a,0,
	  8,  8,0x09,0|OAM_FLIP_H|OAM_FLIP_V,
	0x80
};
const unsigned char Cube_2[]={

	  0,- 4,0x02,0,
	  8,- 4,0x03,0,
	- 4,  4,0x04,0,
	  4,  4,0x05,0,

	 12,  4,0x04,0|OAM_FLIP_H|OAM_FLIP_V,
	  0, 12,0x03,0|OAM_FLIP_H|OAM_FLIP_V,
	  8, 12,0x02,0|OAM_FLIP_H|OAM_FLIP_V,
	0x80
};
const unsigned char Cube_3[]={

	  0,- 4,0x06,0,
	  8,- 4,0x06,0|OAM_FLIP_H,
	- 4,  4,0x07,0,
	  4,  4,0x08,0,

	 12,  4,0x07,0|OAM_FLIP_H,
	  0, 12,0x06,0|OAM_FLIP_V,
	  8, 12,0x06,0|OAM_FLIP_H|OAM_FLIP_V,
	0x80
};
const unsigned char Cube_4[]={

	  0,- 4,0x03,0|OAM_FLIP_H,
	  8,- 4,0x02,0|OAM_FLIP_H,
	- 4,  4,0x04,0|OAM_FLIP_V,
	  4,  4,0x05,0|OAM_FLIP_H,

	 12,  4,0x04,0|OAM_FLIP_H,
	  0, 12,0x02,0|OAM_FLIP_V,
	  8, 12,0x03,0|OAM_FLIP_V,
	0x80
};
const unsigned char Cube_5[]={

	  0,  0,0x0a,0|OAM_FLIP_H,
	  0,  8,0x09,0|OAM_FLIP_V,
	  8,  0,0x09,0|OAM_FLIP_H,
	  8,  8,0x0a,0|OAM_FLIP_V,
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


const unsigned char * const SHIP[] = {Ship_0, Ship_0, Ship_1, Ship_2, Ship_3, Ship_4, Ship_5, Ship_6};
// end ship