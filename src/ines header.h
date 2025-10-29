#include <ines.h>
#include <mapper.h>

// maxed out mmc3 prg
MAPPER_PRG_ROM_KB(512);

// 8kB of chr-ram
// Will be increased to 256k with parallax implementation
MAPPER_CHR_ROM_KB(0);
MAPPER_CHR_RAM_KB(16);

// four screens of characters
MAPPER_USE_4_SCREEN_NAMETABLE;

// multiregion
INES_TIMING_MULTIREGION;
