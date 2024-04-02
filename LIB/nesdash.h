// Custom functions implemented specifically for famidash (some are totally not stolen from famitower)

//set metasprite in OAM buffer (vertically flipped)
//meta sprite is a const unsigned char array, it contains four bytes per sprite
//in order x offset, y offset, tile, attribute
//x=128 is end of a meta sprite
// Note: sprid removed for speed
void __fastcall__ oam_meta_spr_vflipped(unsigned char x,unsigned char y,const unsigned char *data);

/**
 * ======================================================================================================================
 * famistudio_music_play (public)
 * 
 * Plays a song from and loads the music data according to the bank.
 * 
 * [in] song_index : Song index.
 * ======================================================================================================================
 */
void __fastcall__ music_play(unsigned char song);

/**
 * ======================================================================================================================
 * famistudio_update (public)
 * 
 * Main update function, should be called once per frame, ideally at the end of NMI. Will update the tempo, advance
 * the song if needed, update instrument and apply any change to the APU registers.
 * 
 * [in] no input params.
 * ======================================================================================================================
 */
void __fastcall__ music_update (void);

extern unsigned char parallax_scroll_column;
extern unsigned char parallax_scroll_column_start;

#define low2bytes(a) *((unsigned short*)&a)
#define high2bytes(a) *((unsigned short*)&a+1)

#define vram_put(a) POKE(0x2007, a)