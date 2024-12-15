#pragma once

// Huffmunch
// Brad Smith, 2019
// https://github.com/bbbradsmith/huffmunch

// setting this to 0 disables the effect of huffmunch_debug() and removes some redundant checks
#define HUFFMUNCH_DEBUG 1

// huffmunch_compress return values
const int HUFFMUNCH_OK = 0;
const int HUFFMUNCH_OUTPUT_OVERFLOW = 1; // too much data for output buffer (output_size will contain the needed size)
const int HUFFMUNCH_VERIFY_FAIL = 2; // internal error: verify failed
const int HUFFMUNCH_INTERNAL_ERROR = 3; // internal error: use HUFFMUNCH_DEBUG_INTERNAL for diagnostic
const int HUFFMUNCH_INVALID_SPLITS = 4; // splits must start with 0 and have increasing order
const int HUFFMUNCH_HEADER_OVERFLOW = 5; // split values overflow header width

// huffmunch_error_description
//   brief description of the return values above
extern const char* huffmunch_error_description(int e);

// huffmunch_compress
//   data
//     data to be compressed
//   data_size
//     length of data to be compressed
//   output
//     buffer to be filled with compressed output
//     if NULL output_size will still be computed
//   output_size
//     in: size of buffer to be filled
//     out: number of bytes used for compressed output
//   splits
//     list of points to split the compressed data for access in split pieces
//     must begin with 0 and continue in increasing order
//     NULL implies a split_count of 1 (at 0)
//   split_count
//     number of entries in splits
extern int huffmunch_compress(
	const unsigned char* data,
	unsigned int data_size,
	unsigned char* output,
	unsigned int& output_size,
	const unsigned int *splits,
	unsigned int split_count);

// huffmunch_decompress
//   data
//     data to be uncompressed
//   data_size
//     length of data to be uncompressed
//   output
//     buffer to be filled with decompressed output
//   output_size
//     size of the decompressed output
extern int huffmunch_decompress(
	const unsigned char* data,
	unsigned int data_size,
	unsigned char* output,
	unsigned int& output_size);

enum
{
	HUFFMUNCH_SEARCH_WIDTH, // maximum symbols to merge per pass, 2-16, default 3
	HUFFMUNCH_SEARCH_CUTOFF, // number of retries before concluding search, default 100, 0 unlimited
	HUFFMUNCH_HEADER_WIDTH, // width of integers in header 1-4, default 2
};

// huffmunch_configure
extern bool huffmunch_configure(
	unsigned int parameter,
	unsigned int value);

// huffmunch_debug diagnostic bitfield
const unsigned int HUFFMUNCH_DEBUG_OFF       = 0x00000000UL;
const unsigned int HUFFMUNCH_DEBUG_TREE      = 0x00000001UL;
const unsigned int HUFFMUNCH_DEBUG_MUNCH     = 0x00000002UL;
const unsigned int HUFFMUNCH_DEBUG_VERIFY    = 0x00000004UL;
const unsigned int HUFFMUNCH_DEBUG_INTERNAL  = 0x00000008UL;
const unsigned int HUFFMUNCH_DEBUG_HEADER    = 0x00000010UL;
const unsigned int HUFFMUNCH_DEBUG_DOT       = 0x00000020UL;
const unsigned int HUFFMUNCH_DEBUG_FULL      = 0xFFFFFFFFUL;

// huffmunch_debug
//   debug_level
//     parameter for debug output
//   text
//     1 = display symbols as text
//     0 = display symbols as hex
//    -1 = auto
extern void huffmunch_debug(unsigned int debug_bits, int text=-1);

// end of file
