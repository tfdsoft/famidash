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

/**
 * Update the PPU using the VRAM buffer with a single tile repeated LENGTH number of times.
 * Length must not be greater than 0x7f!
 */
void __fastcall__ one_vram_buffer_horz_repeat(unsigned char data, unsigned char len, int ppu_address);
void __fastcall__ one_vram_buffer_vert_repeat(unsigned char data, unsigned char len, int ppu_address);

extern unsigned char parallax_scroll_column;
extern unsigned char parallax_scroll_column_start;

#define low2bytes(a) *((unsigned short*)&a)
#define high2bytes(a) *((unsigned short*)&a+1)

#define vram_put(a) POKE(0x2007, a)

#define GET_BANK(sym) (__asm__("ldx #0\nlda #<.bank(%v)", sym), __A__)

// add byte with No Overflow Check
#define addNOC_b(a, b) (((a & 0xFF)+b)&0xFF)
// add word with No Overflow Check beyond the 16 bits
#define addNOC_w(a, b) (((a & 0xFFFF)+b)&0xFFFF)

// add to the low byte of a word, not overflowing into high
#define addloNOC(a, b) (addNOC_b(a, b))|(a & 0xFF00)

// subtract byte with No Overflow Check
#define subNOC_b(a, b) (((a & 0xFF)-b)&0xFF)
// subtract word with No Overflow Check beyond the 16 bits
#define subNOC_w(a, b) (((a & 0xFFFF)-b)&0xFFFF)

// subtract from the low byte of a word, not overflowing into high
#define subloNOC(a, b) (subNOC_b(a, b))|(a & 0xFF00)