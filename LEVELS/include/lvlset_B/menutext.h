
// Exported by export_levels.py

#include "defines/color1_charmap.h"

const char levelText00[ 7] = "STEREO ";
const char levelText01[ 7] = "MADNESS";
const char levelText02[10] = "LEVEL EASY";
const char levelText03[12] = "SUPER CYCLES";
const char levelText04[11] = "PG CLUBSTEP";
const char levelText05[ 9] = "CATACLYSM";


const char* const levelTextsUpper[] = {
	levelText00,
	NULL,
	NULL,
	NULL,
	NULL,
};

const uint8_t levelTextsUpperSize[] = {
	sizeof(levelText00),
	0,
	0,
	0,
	0,
};


const char* const levelTextsLower[] = {
	levelText01,
	levelText02,
	levelText03,
	levelText04,
	levelText05,
};

const uint8_t levelTextsLowerSize[] = {
	sizeof(levelText01),
	sizeof(levelText02),
	sizeof(levelText03),
	sizeof(levelText04),
	sizeof(levelText05),
};
