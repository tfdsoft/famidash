const unsigned char metatiles1[]={
	0, 0, 0, 0,  0,
	10, 11, 26, 27,  1,
	26, 27, 26, 27,  1,
	42, 43, 42, 43,  1,
	42, 43, 58, 59,  1,
	11, 11, 27, 27,  1,
	27, 27, 27, 27,  1,
	43, 43, 43, 43,  1,
	43, 43, 59, 59,  1,
	255, 255, 255, 255,  1,
	255, 255, 255, 255,  1,
	255, 255, 255, 255,  1,
	255, 255, 255, 255,  1,
	255, 255, 255, 255,  1,
	255, 255, 255, 255,  1,
	255, 255, 255, 255,  1,
	32, 33, 48, 49,  0,
	34, 35, 50, 51,  0,
	0, 0, 52, 53,  0,
	255, 255, 255, 255,  0,
	255, 255, 255, 255,  0,
	164, 165, 180, 181,  0,
	166, 167, 182, 183,  0,
	46, 47, 0, 0,  0,
	0, 0, 54, 55,  0,
	36, 37, 0, 0,  0,
	12, 13, 28, 29,  0,
	44, 45, 60, 61,  0,
	14, 15, 30, 31,  0,
	40, 0, 56, 0,  0,
	38, 39, 0, 0,  0,
	0, 41, 0, 57,  0,
	64, 65, 80, 81,  0,
	68, 69, 86, 87,  0,
	70, 67, 86, 83,  0,
	70, 71, 84, 85,  0,
	66, 71, 82, 87,  0,
	64, 69, 82, 87,  0,
	68, 65, 86, 83,  0,
	70, 67, 84, 81,  0,
	66, 71, 80, 85,  0,
	72, 71, 86, 87,  0,
	70, 73, 86, 87,  0,
	70, 71, 86, 89,  0,
	70, 71, 88, 87,  0,
	66, 67, 82, 83,  0,
	68, 69, 84, 85,  0,
	70, 71, 86, 87,  0,
	64, 65, 82, 83,  0,
	68, 65, 84, 81,  0,
	66, 67, 80, 81,  0,
	64, 69, 80, 85,  0
};


#define COL_DEATH 0x80
#define COL_ALL 0x40
const unsigned char is_solid[]={

	// go find famidash.bmp for a reference point

	0,			// the blank tile
	COL_ALL,	// start of ground tiles
	COL_ALL,
	COL_ALL, 
	COL_ALL, 
	COL_ALL,
	COL_ALL,
	COL_ALL, 
	COL_ALL,
	COL_ALL,
	COL_ALL,
	COL_ALL,
	COL_ALL,	// end of ground tiles
	0,
	0,
	0,
	
	COL_ALL,	// default block
	COL_DEATH,	// big spike
	COL_DEATH,	// small spike
	0,			// yellow pad
	0,			// yellow orb
	0,			// pink pad
	0,			// pink orb
	COL_DEATH,	// ceiling spikes
	COL_DEATH,	// ground spikes
	COL_ALL,	// half-slab 2
	COL_DEATH,	// the other spikes
	COL_DEATH,
	COL_DEATH,
	COL_DEATH,
	COL_DEATH,
	COL_DEATH,

	COL_ALL,	// default block 2
	COL_ALL,	// start of checkerboard blocks
	COL_ALL,
	COL_ALL,
	COL_ALL,
	COL_ALL,
	COL_ALL,
	COL_ALL,
	COL_ALL,
	COL_ALL,
	COL_ALL,
	COL_ALL,
	COL_ALL,
	COL_ALL,
	COL_ALL,	
	0,

	COL_ALL,
	COL_ALL,
	COL_ALL,
	COL_ALL		// end of checkerboard blocks
};