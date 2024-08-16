// BUILD FLAGS ================================================
//
// Change how the game compiles with this one simple trick!
// assembly programmers HATE this!
//
// ============================================================

// kandos additional features

#define FLAG_KANDO_FUN_STUFF 1


// DEBUGGING FEATURES =========================================
//
// Enable Test Levels
// uncomment to enable every level id. will break after TEST4.
#define FLAG_ENABLE_TEST_LEVELS
//
// ============================================================



// VERSION NUMBER STUFF =======================================
//
// These change how the version number is displayed.
//
//
// Enable Version Number
// uncomment to enable the version number on the credits screen
// you can ignore everything below this if disabled.
#define FLAG_ENABLE_VER_NUM
//
// Beta Build
// set to 1 if compiling demo/beta builds; otherwise set to 0.
#define FLAG_BETA_BUILD 0
//
// Major Version Number 
// set if releasing a demo/beta.
#define FLAG_MAJ_VER '1'
//
// Minor Version Number
// increment by 1 for officially released patches.
// does nothing if FLAG_BETA_BUILD is set.
#define FLAG_MIN_VER '0'
// ============================================================



// OPTIMIZATION SETTINGS ======================================
// 
// Use Illegal Opcodes
// set this to 1 to speed up some code in nesdash.h.
// we do not recommend turning this on if testing on
// real hardware.
#define USE_ILLEGAL_OPCODES 0
//
// Print Metatiles When Compiling
// set to 1 to display metatile data when compiling via the
// command line.
#define PRINT_METATILES 0
// ============================================================



// ADVANCED SETTINGS ==========================================
//
// !! ONLY CHANGE IF YOU KNOW WHAT YOU'RE DOING !!
//
//
// Save File Version
// increase by 1 if SRAM values are added or deleted. 
#define FLAG_SAVE_VER 0x03
// ============================================================