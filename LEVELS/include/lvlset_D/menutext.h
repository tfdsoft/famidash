
// Exported by export_levels.py

const char levelText00[ 5] = "WINDY";
const char levelText01[ 6] = "SILENT";
const char levelText02[11] = "GOLDEN HAZE";
const char levelText03[15] = "DEMON CRYOGENIC";
const char levelText04[13] = "FOREST TEMPLE";
const char levelText05[ 9] = "LANDSCAPE";
const char levelText06[ 8] = "CLUBSTEP";
const char levelText07[ 6] = "KRATOS";
const char levelText08[13] = "AFTERCATABATH";
const char levelText09[14] = "SLAUGHTERHOUSE";


const char* const levelTextsUpper[] = {
	NULL,
	NULL,
	NULL,
	levelText00,
	levelText01,
	NULL,
	NULL,
	NULL,
};

const uint8_t levelTextsUpperSize[] = {
	0,
	0,
	0,
	sizeof(levelText00),
	sizeof(levelText01),
	0,
	0,
	0,
};


const char* const levelTextsLower[] = {
	levelText02,
	levelText03,
	levelText04,
	levelText05,
	levelText06,
	levelText07,
	levelText08,
	levelText09,
};

const uint8_t levelTextsLowerSize[] = {
	sizeof(levelText02),
	sizeof(levelText03),
	sizeof(levelText04),
	sizeof(levelText05),
	sizeof(levelText06),
	sizeof(levelText07),
	sizeof(levelText08),
	sizeof(levelText09),
};
