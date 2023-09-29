// a 16x16 pixel metasprite

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

