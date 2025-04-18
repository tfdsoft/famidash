

#ifndef FAMISTUDIO_H
#define FAMISTUDIO_H

// Workaround for code analyzers that don't know about fastcall
#ifndef __fastcall__
#define __fastcall__ 
#endif

/**
 * =====================================================================================================================
 * famistudio_init (public)
 *
 * Reset APU, initialize the sound engine with some music data.
 *
 * [in] platform : Playback platform, zero for PAL, non-zero for NTSC.
 * [in] music_data : Pointer to music data 
 * ======================================================================================================================
 */
#define FAMISTUDIO_PLATFORM_PAL 0
#define FAMISTUDIO_PLATFORM_NTSC 1

// call `famistudio_init` with the parameters listed below
// void famistudio_init(unsigned char platform, unsigned char* music_data);
#define famistudio_init(platform, music_data)         \
    (__AX__ = ((unsigned int)(music_data))),          \
    __asm__ ("pha\n"),                                \
    __asm__ ("txa\n"),                                \
    __asm__ ("tay\n"),                                \
    __asm__ ("pla\n"),                                \
    __asm__ ("tax\n"),                                \
    __asm__ ("lda #%b\n", (unsigned char)(platform)), \
    __asm__ ("jsr _famistudio_init\n");


/**
 * ======================================================================================================================
 * famistudio_music_play (public)
 * 
 * Plays a song from the loaded music data (from a previous call to famistudio_init).
 * 
 * [in] song_index : Song index.
 * ======================================================================================================================
 */

void __fastcall__ famistudio_music_play(unsigned char song_index);

/**
 * ======================================================================================================================
 * famistudio_music_pause (public)
 * 
 * Pause/unpause the currently playing song. Note that this will not update the APU, so sound might linger. Calling
 * famistudio_update after this will update the APU.
 * 
 * [in] mode : zero to play, non-zero to pause.
 * ======================================================================================================================
 */
#define FAMISTUDIO_PLAY 0
#define FAMISTUDIO_PAUSE 1

void __fastcall__ famistudio_music_pause(unsigned char mode);

/**
 * ======================================================================================================================
 * famistudio_music_stop (public)
 * 
 * Stops any music currently playing, if any. Note that this will not update the APU, so sound might linger. Calling
 * famistudio_update after this will update the APU.
 * 
 * [in] no input params.
 * ======================================================================================================================
 */

void __fastcall__ famistudio_music_stop();

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

void __fastcall__ famistudio_update();



/**
 * ======================================================================================================================
 * famistudio_sfx_init(public)
 * 
 * Initialize the sound effect player.
 * 
 * [in] sfx_data: Sound effect data pointer
 * ======================================================================================================================
 */

// call `famistudio_sfx_init` with the parameters listed below
// void famistudio_sfx_init(unsigned char sfx_data[]);
#define famistudio_sfx_init(sfx_data)      \
    (__AX__ = ((unsigned int)(sfx_data))), \
    __asm__ ("pha\n"),                     \
    __asm__ ("txa\n"),                     \
    __asm__ ("tay\n"),                     \
    __asm__ ("pla\n"),                     \
    __asm__ ("tax\n"),                     \
    __asm__ ("jsr _famistudio_sfx_init\n");


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

// #define FAMISTUDIO_SFX_STRUCT_SIZE = 15
#define FAMISTUDIO_SFX_CH0 0
#define FAMISTUDIO_SFX_CH1 15 // 1 * FAMISTUDIO_SFX_STRUCT_SIZE
#define FAMISTUDIO_SFX_CH2 30 // 2 * FAMISTUDIO_SFX_STRUCT_SIZE
#define FAMISTUDIO_SFX_CH3 45 // 3 * FAMISTUDIO_SFX_STRUCT_SIZE

// call `famistudio_sfx_play` with the parameters listed below
// void famistudio_sfx_play(unsigned char sfx_index, unsigned char channel);
#define famistudio_sfx_play(sfx_index, channel)                          \
    (__AX__ = ((unsigned char)(channel)<<8)|(unsigned char)(sfx_index)), \
    __asm__ ("jsr _famistudio_sfx_play\n");


/**
 * ======================================================================================================================
 * famistudio_sfx_sample_play (public)
 * 
 * Play DPCM sample with higher priority, for sound effects
 * 
 * [in] index: Sample index, 1...63.
 * ======================================================================================================================
 */

void __fastcall__ famistudio_sfx_sample_play(unsigned char sample_index);


#endif
