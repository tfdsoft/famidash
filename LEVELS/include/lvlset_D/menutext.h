
// Exported by export_levels.py

const char levelText00[ 5] = "WINDY";
const char levelText01[ 6] = "SILENT";
const char levelText02[ 7] = "ELEMENT";
const char levelText03[11] = "GOLDEN HAZE";
const char levelText04[ 9] = "GAME OVER";
const char levelText05[15] = "DEMON CRYOGENIC";
const char levelText06[13] = "FOREST TEMPLE";
const char levelText07[ 9] = "LANDSCAPE";
const char levelText08[ 8] = "CLUBSTEP";
const char levelText09[13] = "AFTERCATABATH";
const char levelText0A[11] = "SHARDSCAPES";
const char levelText0B[ 6] = "111 RG";
const char levelText0C[14] = "SLAUGHTERHOUSE";
const char levelText0D[ 6] = "KRATOS";


const char* const levelTextsUpper[] = {
	NULL,
	NULL,
	NULL,
	NULL,
	levelText00,
	levelText01,
	NULL,
	NULL,
	levelText02,
	NULL,
	NULL,
};

const uint8_t levelTextsUpperSize[] = {
	0,
	0,
	0,
	0,
	sizeof(levelText00),
	sizeof(levelText01),
	0,
	0,
	sizeof(levelText02),
	0,
	0,
};


const char* const levelTextsLower[] = {
	levelText03,
	levelText04,
	levelText05,
	levelText06,
	levelText07,
	levelText08,
	levelText09,
	levelText0A,
	levelText0B,
	levelText0C,
	levelText0D,
};

const uint8_t levelTextsLowerSize[] = {
	sizeof(levelText03),
	sizeof(levelText04),
	sizeof(levelText05),
	sizeof(levelText06),
	sizeof(levelText07),
	sizeof(levelText08),
	sizeof(levelText09),
	sizeof(levelText0A),
	sizeof(levelText0B),
	sizeof(levelText0C),
	sizeof(levelText0D),
};
