// Version number stuff

// uncomment to enable the version number on the title screen
#define FLAG_ENABLE_VER_NUM

// set to 1 if compiling beta builds; else set to 0
#define FLAG_BETA_BUILD 1

// major version number !!DOES NOT WORK IF FLAG_BETA_BUILD IS SET!!
#define FLAG_MAJ_VER '0'

// minor version number !!DOES NOT WORK IF FLAG_BETA_BUILD IS SET!!
#define FLAG_MIN_VER '5'

// Set to 1 to make some code in nesdash.s slightly faster
// Since the carts are gonna be multiregion and famiclones have
// issues supporting illegal opcodes, this should be disabled
// for actual cart releases
#define USE_ILLEGAL_OPCODES 1

// set to 1 to enable metatile printing
// #define PRINT_METATILES 1