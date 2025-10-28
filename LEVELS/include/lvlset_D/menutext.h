
// Exported by export_levels.py

const char levelText00[ 5] = "WINDY";
const char levelText01[ 6] = "SILENT";
const char levelText02[15] = "DEMON CRYOGENIC";
const char levelText03[ 9] = "LANDSCAPE";
const char levelText04[ 8] = "CLUBSTEP";
const char levelText05[ 6] = "KRATOS";
const char levelText06[14] = "SLAUGHTERHOUSE";
const char levelText07[13] = "AFTERCATABATH";


const char* const levelTextsUpper[] = {
	NULL,
	levelText00,
	levelText01,
	NULL,
	NULL,
	NULL,
};

const uint8_t levelTextsUpperSize[] = {
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
};

const uint8_t levelTextsLowerSize[] = {
	sizeof(levelText02),
	sizeof(levelText03),
	sizeof(levelText04),
	sizeof(levelText05),
	sizeof(levelText06),
	sizeof(levelText07),
};
