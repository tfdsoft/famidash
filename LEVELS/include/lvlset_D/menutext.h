
// Exported by export_levels.py

const char levelText00[ 5] = "WINDY";
const char levelText01[ 6] = "SILENT";
const char levelText02[ 9] = "LANDSCAPE";
const char levelText03[ 8] = "CLUBSTEP";
const char levelText04[ 6] = "KRATOS";
const char levelText05[14] = "SLAUGHTERHOUSE";
const char levelText06[13] = "AFTERCATABATH";


const char* const levelTextsUpper[] = {
	levelText00,
	levelText01,
	NULL,
	NULL,
	NULL,
};

const uint8_t levelTextsUpperSize[] = {
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
};

const uint8_t levelTextsLowerSize[] = {
	sizeof(levelText02),
	sizeof(levelText03),
	sizeof(levelText04),
	sizeof(levelText05),
	sizeof(levelText06),
};
