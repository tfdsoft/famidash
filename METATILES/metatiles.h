#define COL_SLOPE_LD 0x0c
#define COL_SLOPE_RD 0x0b

#define COL_SLOPE_SUPPORT 0x0a

#define COL_FLOOR_CEIL 0x09
#define COL_DEATH 0x08
#define COL_ALL 0x07
#define COL_BOTTOM 0x06
#define COL_TOP 0x05
#define COL_DEATH_BOTTOM 0x04
#define COL_DEATH_TOP 0x03
#define COL_DEATH_LEFT 0x02
#define COL_DEATH_RIGHT 0x01

extern const unsigned char metatiles_top1[];
extern const unsigned char metatiles_top2[];
extern const unsigned char metatiles_bot1[];
extern const unsigned char metatiles_bot2[];
extern const unsigned char metatiles_attr[];
extern const unsigned char is_solid[];

// const unsigned char metatiles1[]={
	// 0, 0, 0, 0,  0,
	// 26, 27, 42, 43,  1,
	// 26, 27, 26, 27,  1,
	// 0, 0, 36, 37,  1,
	// 255, 255, 255, 255,  1,
	// 27, 27, 43, 43,  1,
	// 27, 27, 27, 27,  1,
	// 32, 33, 48, 49,  0,
	// 255, 255, 255, 255,  1,
	// 255, 255, 255, 255,  1,
	// 255, 255, 255, 255,  1,
	// 255, 255, 255, 255,  1,
	// 255, 255, 255, 255,  1,
	// 255, 255, 255, 255,  1,
	// 255, 255, 255, 255,  1,
	// 255, 255, 255, 255,  1,

	// 32, 33, 48, 49,  0,
	// 34, 35, 50, 51,  0,
	// 0, 0, 52, 53,  0,

	// 209, 211, 255, 255,  1,
	// 209, 212, 255, 255,  1,
	// 209, 213, 255, 255,  1,
	// 36, 37, 54, 55,  0,
	// 46, 47, 0, 0,  0,
	// 0, 0, 54, 55,  0,
	// 36, 37, 0, 0,  0,

	// 12, 13, 28, 29,  0,
	// 44, 45, 60, 61,  0,
	// 14, 15, 30, 31,  0,
	// 40, 0, 56, 0,  0,
	// 38, 39, 0, 0,  0,
	// 0, 41, 0, 57,  0,

	// 64, 65, 80, 81,  0,
	// 68, 69, 86, 87,  0,
	// 70, 67, 86, 83,  0,
	// 70, 71, 84, 85,  0,
	// 66, 71, 82, 87,  0,
	// 64, 69, 82, 87,  0,
	// 68, 65, 86, 83,  0,

	// 70, 67, 84, 81,  0,
	// 66, 71, 80, 85,  0,
	// 72, 71, 86, 87,  0,
	
	// 70, 73, 86, 87,  0,
	// 70, 71, 86, 89,  0,
	// 70, 71, 88, 87,  0,
	// 66, 67, 82, 83,  0,
	// 68, 69, 84, 85,  0,
	// 70, 71, 86, 87,  0,

	// 64, 65, 82, 83,  0,
	// 68, 65, 84, 81,  0,
	// 66, 67, 80, 81,  0,
	// 64, 69, 80, 85,  0,
	// 96, 97, 112, 113, 0,
	// 0, 0, 98, 99, 0,
	// 114, 115, 0, 0, 0
// };

//#define COL_TOP 0x20
//#define COL_BOTTOM 0x10
//#define COL_DEATH_TOP 0x08
//#define COL_DEATH_BOTTOM 0x04
// const unsigned char is_solid[]={

// 	// go find famidash.bmp for a reference point

// 	0,			// the blank tile
// 	COL_ALL,	// start of ground tiles
// 	COL_ALL,

// //	COL_BOTTOM, 
// 	COL_ALL, 

// 	COL_ALL, 
// 	COL_ALL,
// 	COL_ALL,
// 	0, 
// 	COL_ALL,
// 	COL_ALL,
// 	COL_ALL,
// 	COL_ALL,
// 	COL_ALL,	// end of ground tiles
// 	0,
// 	0,
// 	0,		//16
	
// 	COL_ALL,	// default block
// 	COL_DEATH,	// big spike

// 	COL_DEATH,	// big spike
// //	COL_DEATH_BOTTOM,	// small spike

// 	0,			// yellow pad
// 	0,			// yellow orb
// 	0,			// pink pad
// 	COL_ALL,	// half-slab with ground spikes

// //	COL_DEATH_TOP,	// ceiling spikes
// //	COL_DEATH_BOTTOM,	// ground spikes
// 	COL_DEATH,
// 	COL_DEATH,

// //	COL_TOP,	// half-slab
// 	COL_ALL,

// 	COL_DEATH,	// the other spikes
// 	COL_DEATH,
// 	COL_DEATH,
// 	COL_DEATH,

// 	COL_DEATH,
// //	COL_DEATH_TOP,

// 	COL_DEATH,

// 	COL_ALL,	// default block 2
// 	COL_ALL,	// start of checkerboard blocks
// 	COL_ALL,
// 	COL_ALL,
// 	COL_ALL,
// 	COL_ALL,
// 	COL_ALL,
// 	COL_ALL,
// 	COL_ALL,
// 	COL_ALL,
// 	COL_ALL,
// 	COL_ALL,
// 	COL_ALL,
// 	COL_ALL,
// 	COL_ALL,	
// 	0,
	// COL_ALL,
	// COL_ALL,
	// COL_ALL,
	// COL_ALL,		// end of checkerboard blocks
	// 0,		// white outlines
	// 0,		// 
	// 0		// 
// };