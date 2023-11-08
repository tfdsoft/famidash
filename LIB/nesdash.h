// Custom functions implemented specifically for famidash (some are totally not stolen from famitower)

//set metasprite in OAM buffer (vertically flipped)
//meta sprite is a const unsigned char array, it contains four bytes per sprite
//in order x offset, y offset, tile, attribute
//x=128 is end of a meta sprite
// Note: sprid removed for speed

void __fastcall__ oam_meta_spr_vflipped(unsigned char x,unsigned char y,const unsigned char *data);

// Reset run-length decoder back to zero
void __fastcall__ init_rld(unsigned char level);

// This should explain itself
void __fastcall__ unrle_next_column(void);
