// BUILD FLAGS ================================================
// Change how the game compiles with this one simple trick!
// assembly programmers HATE this!
// ============================================================



// ADDITIONAL FEATURES ========================================
// Some extra things
//
// Kando's Fun Stuff
// uncomment to enable kandowontu's added features that aren't
// in vanilla geometry dash.
#define FLAG_KANDO_FUN_STUFF
// ============================================================



// DEBUGGING FEATURES =========================================
// Useful stuff for making a ROM hack or mod.
//
// Enable Test Levels
// uncomment to enable every level id. will break after TEST4.
// #define FLAG_ENABLE_TEST_LEVELS
//
// Print Metatiles When Compiling
// set to 1 to display metatile data when compiling via the
// command line.
#define PRINT_METATILES 0
// ============================================================



// VERSION NUMBER STUFF =======================================
// These change how the version number is displayed.
//
// Enable Version Number
// uncomment to enable the version number on the credits screen
// you can ignore everything below this if disabled.
#define FLAG_ENABLE_VER_NUM
//
// Beta Build
// uncomment if compiling a demo or beta build.
#define FLAG_BETA_BUILD
//
// Major Version Number 
// set if releasing a demo/beta.
#define FLAG_MAJ_VER '1'
//
// Minor Version Number
// increment by 1 for officially released patches.
// does nothing if FLAG_BETA_BUILD is uncommented.
#define FLAG_MIN_VER '3'
// ============================================================



// ADVANCED SETTINGS ==========================================
// !! ONLY CHANGE IF YOU KNOW WHAT YOU'RE DOING !!
//
// Save File Version
// increase by 1 if SRAM values are added, changed or deleted.
#define FLAG_SAVE_VER 0x23
// ============================================================