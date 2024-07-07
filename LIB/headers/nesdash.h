// Custom functions and macros implemented specifically for famidash

// replacements for C stack
extern uint8_t xargs[4];
#pragma zpsym("xargs")
#define wxargs ((uint16_t * const)xargs)
#define pxargs ((const void ** const)xargs)

#define storeWordToSreg(word) (__AX__ = word, __EAX__<<=16)
#define storeBytesToSreg(a, b) (__AX__ = (byte(b)<<8)|byte(a), __EAX__<<=16)
#define storeByteToSreg(byte) (__A__ = byte, __asm__("sta sreg+0"))

/**
 * @brief set metasprite in OAM buffer (horizontally and/or vertically flipped, depending on flip parameter)
 * @param flip
 * @param x
 * @param y
 * @param data meta sprite is a const uint8_t array, it contains four bytes per sprite - in order x offset, y offset, tile, attribute; x=128 is end of a meta sprite
 * @note sprid removed for speed
 */
#define oam_meta_spr_flipped(flip, x, y, data)(xargs[0] = flip, storeBytesToSreg(x, y), __AX__ = (uintptr_t)data, _oam_meta_spr_flipped(__EAX__))
void __fastcall__ _oam_meta_spr_flipped(uint32_t args);

/**
 * @name famistudio_music_play
 *
 * @brief Plays a song from and loads the music data according to the bank.
 *
 * @param song Song index.
 *
 */
void __fastcall__ music_play(uint8_t song);

/**
 * @brief Main update function, should be called once per frame, ideally at the end of NMI.
 * Will update the tempo, advance the song if needed, update instrument and apply any change to the APU registers.
 * 
 */
void __fastcall__ music_update();

/**
 * @brief Plays a sound effect.
 * 
 * @param sfx_index Sound effect index (0...127)
 * @param channel Offset of sound effect channel, should be FAMISTUDIO_SFX_CH0..FAMISTUDIO_SFX_CH3
 *
 */
#define sfx_play(sfx_index, channel) (__AX__ = (uint16_t)(byte(channel))<<8|sfx_index, _sfx_play(__AX__))
void __fastcall__ _sfx_play(uint16_t args);

/**
 * @name one_vram_buffer_repeat
 *
 * @brief Update the PPU using the VRAM buffer with a single tile repeated @c len number of times.
 *
 * @param data The byte to repeat.
 * @param len The amount of times to repeat the byte.
 * @param ppu_address The PPU address to put the repeated byte at.
 *
 * @note @c len must not be greater than 0x7F!
 */
///@{
/**
 * @brief Repeat a single tile horizontally.
 */
#define one_vram_buffer_horz_repeat(data, len, ppu_address) (storeBytesToSreg(data, len), __A__ = LSB(ppu_address), __AX__<<=8, __AX__ |= MSB(ppu_address)|NT_UPD_HORZ, _one_vram_buffer_repeat(__EAX__))
/**
 * @brief Repeat a single tile vertically.
 */
#define one_vram_buffer_vert_repeat(data, len, ppu_address) (storeBytesToSreg(data, len), __A__ = LSB(ppu_address), __AX__<<=8, __AX__ |= MSB(ppu_address)|NT_UPD_VERT, _one_vram_buffer_repeat(__EAX__))
///@}
void __fastcall__ _one_vram_buffer_repeat(uint32_t args);

/**
 * @brief Draw a string, padded to be in the center of a block.
 *
 * @param data The string to center.
 * @param len The length of the string.
 * @param total_len The length of the block to center it in.
 * @param ppu_address The PPU address to put it at.
 */
#define draw_padded_text(data, len, total_len, ppu_address) (pxargs[0] = data, storeBytesToSreg(total_len, len), __A__ = LSB(ppu_address), __AX__<<=8, __AX__ |= MSB(ppu_address)|NT_UPD_HORZ, _draw_padded_text(__EAX__))
void __fastcall__ _draw_padded_text(uint32_t args);

/**
 * @brief Play a raw PCM sample. Hangs the game until done.
 *
 * @note Sample parameters (offset, bank, sample rate) are specified in tables inside the routine and found by the @c sample parameter. 
 *
 * @param sample The sample to play.
 */
void __fastcall__ playPCM(uint8_t sample);

/**
 * @brief Convert a 16-bit number to 5 decimal digits.
 *
 * @param input The number to convert to decimal.
 *
 * @retval Returns the 4 low digits of the result in @c __EAX___, and the 5th byte is returned in @c xargs[0].
 */
uint32_t __fastcall__ hexToDec (uint16_t input);

/**
 * @brief Poll both controllers
 *
 * @note Stores the states in @c pad and @c pad_new automatically.
 */
void pad_poll_both();

#define low_word(a) *((uint16_t*)&a)
#define high_word(a) *((uint16_t*)&a+1)

#define vram_adr(a) (POKE(0x2006, MSB(a)), POKE(0x2006, LSB(a)))
#define vram_put(a) POKE(0x2007, a)

#define GET_BANK(sym) (__asm__("ldx #0\nlda #<.bank(%v)", sym), __A__)

// limit stuff to certain amounts
#define byte(x) (((x)&0xFF))
#define word(x) (((x)&0xFFFF))

// redefined from neslib

#define LSB(x)	((byte(x)))
#define MSB(x)	((byte(x>>8)))
#define SB3(x)	((byte(x##L>>16)))
#define SB4(x)	((byte(x##L>>24)))

#define LSW(x)	((word(x)))
#define MSW(x)	((word((x##L)>>16)))

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
#define idx16_lo(arr, idx) (*(((uint8_t * const)arr)+((idx<<1))))
#define idx16_hi(arr, idx) (*(((uint8_t * const)(arr+1))+((idx<<1))))

// same as above but idx < 128
#define idx16_lo_NOC(arr, idx) (__A__ = idx<<1, __asm__("tay\n lda %v, y", arr), __A__)
#define idx16_hi_NOC(arr, idx) (__A__ = idx<<1, __asm__("tay\n lda %v+1, y", arr), __A__)

#define uint8_load(arr, idx) ( \
	__A__ = idx, \
	__asm__("tay"), \
	__asm__("ldx #0 \n lda %v, y", arr), \
	__A__ \
)

#define uint8_dec(arr, idx) ( \
	__AX__ = idx << 8, \
	__asm__("dec %v,x", arr), \
	__asm__("lda %v,x", arr), \
	__A__ \
)

#define uint8_inc(arr, idx) ( \
	__AX__ = idx << 8, \
	__asm__("inc %v,x", arr), \
	__asm__("lda %v,x", arr), \
	__A__ \
)

#define uint8_store(arr, idx, val) ( \
	__A__ = idx, \
	__asm__("tay"), \
	__A__ = val, \
	__asm__("sta %v, y", arr))

// Yes i had to actually fucking use inline asm to get this to run fast
#define uint16_store_NOC(arr, idx, word) ( \
    __A__ = idx<<1, \
    __asm__("tay"), \
    __A__ = LSB(word), \
    __asm__("sta %v,y", arr), \
    __A__ = MSB(word), \
    __asm__("sta %v+1, y", arr))

// store a word's high and low bytes into separate places
#define storeWordSeparately(word, low, high) \
                            (__AX__ = word, \
                            __asm__("STA %v", low), \
                            __asm__("STX %v", high))

extern uint8_t auto_fs_updates;
#define pal_fade_to_withmusic(from, to) (++auto_fs_updates, pal_fade_to(from, to), auto_fs_updates = 0)

// set palette color, index 0..31
// completely inlines and replaces neslib's
extern uint8_t PAL_UPDATE;
extern uint8_t PAL_BUF[32];
#pragma zpsym("PAL_UPDATE")
#define pal_col(index, color) do { PAL_BUF[index&0x1F] = (color); ++PAL_UPDATE; } while(0);

#define swapbyte(a, b) do { \
  __A__ = (a); \
  __asm__("pha"); \
  (a) = (b); \
  __asm__("pla"); \
  (b) = __A__; \
} while(0);

// For more than 16 bits use extra macros and shit
// Naming convention: crossPRGBankJump<bitsIn>
#define crossPRGBankJump0(sym, args) (__asm__("lda #<%v \n ldx #>%v \n ldy #<.bank(%v) \n jsr crossPRGBankJump ", sym, sym, sym), __asm__("lda ptr3 \n ldx ptr3+1"), __AX__)
#define crossPRGBankJump8(sym, args) (__A__ = args, __asm__("sta ptr3 "), crossPRGBankJump0(sym, args))
#define crossPRGBankJump16(sym, args) (__AX__ = args, __asm__("sta ptr3 \n stx ptr3+1"),crossPRGBankJump0(sym, args))

#define uint16SepArrLoad(sym, idx) (__A__ = idx, __asm__("tay \n lda %v, y \n ldx %v, y", sym##_lo, sym##_hi), __AX__)

#define fc_mic_poll() (PEEK(0x4016) & 4)