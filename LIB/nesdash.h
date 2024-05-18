// Custom functions implemented specifically for famidash (some are totally not stolen from famitower)

//set metasprite in OAM buffer (vertically flipped)
//meta sprite is a const unsigned char array, it contains four bytes per sprite
//in order x offset, y offset, tile, attribute
//x=128 is end of a meta sprite
// Note: sprid removed for speed
void __fastcall__ oam_meta_spr_flipped(unsigned char flip,unsigned char x,unsigned char y,const unsigned char *data);

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
 * ======================================================================================================================
 * famistudio_sfx_play (public)
 * 
 * Plays a sound effect.
 * 
 * [in] sfx_index: Sound effect index (0...127)
 * [in] channel: Offset of sound effect channel, should be FAMISTUDIO_SFX_CH0..FAMISTUDIO_SFX_CH3
 * ======================================================================================================================
 */

void __fastcall__ _sfx_play(unsigned int args);
#define sfx_play(sfx_index, channel) (__AX__ = (unsigned int)(byte(sfx_index))<<8|channel, _sfx_play(__AX__))

/**
 * Update the PPU using the VRAM buffer with a single tile repeated LENGTH number of times.
 * Length must not be greater than 0x7f!
 */
void __fastcall__ _one_vram_buffer_horz_repeat(unsigned long args);
#define one_vram_buffer_horz_repeat(data, len, ppu_address) (loadBytesInSreg(data, len), __AX__ = ppu_address, _one_vram_buffer_horz_repeat(__EAX__))

void __fastcall__ _one_vram_buffer_vert_repeat(unsigned char data, unsigned char len, int ppu_address);
#define one_vram_buffer_vert_repeat(data, len, ppu_address) (loadBytesInSreg(data, len), __AX__ = ppu_address, _one_vram_buffer_vert_repeat(__EAX__))

void __fastcall__ _draw_padded_text(unsigned long args);
#define draw_padded_text(len, total_len, ppu_address) \
(loadBytesInSreg(total_len, len), __AX__ = ppu_address|(NT_UPD_HORZ<<8), _draw_padded_text(__EAX__))
#define draw_padded_text_setAddr(data, len, total_len, ppu_address) (tmpptr1 = (void *)data, draw_padded_text(len, total_len, ppu_address))

void __fastcall__ playPCM();

extern unsigned char parallax_scroll_column;
extern unsigned char parallax_scroll_column_start;

#define low_word(a) *((unsigned short*)&a)
#define high_word(a) *((unsigned short*)&a+1)

#define vram_adr(a) (POKE(0x2006, MSB(a)), POKE(0x2006, LSB(a)))
#define vram_put(a) POKE(0x2007, a)

#define GET_BANK(sym) (__asm__("ldx #0\nlda #<.bank(%v)", sym), __A__)

// limit stuff to certain amounts
#define byte(x) (((x)&0xFF))
#define word(x) (((x)&0xFFFF))

// add byte with No Overflow Check
#define addNOC_b(a, b) byte(byte(a)+b)
// add word with No Overflow Check beyond the 16 bits
#define addNOC_w(a, b) word(word(a)+b)

// add to the low byte of a word, not overflowing into high
#define addloNOC(a, b) (addNOC_b(a, b))|(a & 0xFF00)

// subtract byte with No Overflow Check
#define subNOC_b(a, b) byte(byte(a)-b)
// subtract word with No Overflow Check beyond the 16 bits
#define subNOC_w(a, b) word(word(a)-b)

// subtract from the low byte of a word, not overflowing into high
#define subloNOC(a, b) (subNOC_b(a, b))|(a & 0xFF00)

// get specific byte from a word array
#define idx16_lo(arr, idx) (*((char *)arr+((idx<<1))))
#define idx16_hi(arr, idx) (*((char *)(arr+1)+((idx<<1))))

// same as above but idx < 128
#define idx16_lo_NOC(arr, idx) (*((char *)arr+(byte(idx<<1))))
#define idx16_hi_NOC(arr, idx) (*(((char *)(arr)+1)+(byte(idx<<1))))

// store a word's high and low bytes into separate places
#define storeWordSeparately(word, low, high) \
                            (__AX__ = word, \
                            __asm__("STA %v", low), \
                            __asm__("STX %v", high))

#define pal_fade_to_withmusic(from, to) (++auto_fs_updates, pal_fade_to(from, to), auto_fs_updates = 0)

// Yes i had to actually fucking use inline asm to get this to run fast
#define store_short_arr_NOC(arr, idx, word) ( \
    __A__ = idx<<1, \
    __asm__("tay"), \
    __A__ = low_byte(word), \
    __asm__("sta %v,y", arr), \
    __A__ = high_byte(word), \
    __asm__("sta %v+1, y", arr))

// set palette color, index 0..31
// completely inlines and replaces neslib's
extern unsigned char PAL_UPDATE;
extern char PAL_BUF[32];
#pragma zpsym("PAL_UPDATE")
#define pal_col(index, color) do { PAL_BUF[index&0x1F] = (color); ++PAL_UPDATE; } while(0);

#define swapbyte(a, b) do { \
  __A__ = (a); \
  __asm__("pha"); \
  (a) = (b); \
  __asm__("pla"); \
  (b) = __A__; \
} while(0);

#define loadWordInSreg(word) (__AX__ = word, __EAX__<<=16)
#define loadBytesInSreg(a, b) (__AX__ = (byte(b)<<8)|byte(a), __EAX__<<=16)
#define loadByteInSreg(byte) (__A__ = byte, __asm__("sta sreg+0"))