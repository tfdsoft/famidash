#include <ines.h>
#include <mapper.h>

// maxed out mmc3 prg
MAPPER_PRG_ROM_KB(512);

// extra memory!
MAPPER_PRG_NVRAM_KB(8);
MAPPER_USE_BATTERY;

// 64kb of chr-ram should be fine
MAPPER_CHR_ROM_KB(0);
MAPPER_CHR_RAM_KB(64);



// four screens of characters
MAPPER_USE_4_SCREEN_NAMETABLE;

// multiregion
INES_TIMING_MULTIREGION;
