//moved to BUILD FLAGS
#ifdef FLAG_ENABLE_TEST_LEVELS
	#define LEVEL_COUNT 256
#else
	#define LEVEL_COUNT 18
#endif

#ifdef FLAG_ENABLE_TEST_LEVELS
	#define LEVEL_COUNT2 256
#else
	#define LEVEL_COUNT2 41
#endif

#define MAX_ICONS 27 //total icons
#define MAX_FIREBALLS 20
#define MAX_PRACTICE_POINTS 8
#define max_loaded_sprites 16
#define SLOPESA 16