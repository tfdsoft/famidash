#include <ines.h>
#include <mapper.h>

// maxed out mmc3 prg
MAPPER_PRG_ROM_KB(512);

// 8kb of chr-ram
MAPPER_CHR_ROM_KB(0);
MAPPER_CHR_RAM_KB(8);

// four screens of characters
MAPPER_USE_4_SCREEN_NAMETABLE;

// multiregion
INES_TIMING_MULTIREGION;
