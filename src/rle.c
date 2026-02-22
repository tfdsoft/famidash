#include "levels.h"

u8* level_tile_ptr;
u8 level_tile_bank;
u8* level_sprite_ptr;
u8 level_sprite_bank;
u8 level_rle_byte;
u8 level_rle_length;


void init_level_rle(struct Level level){
    level_tile_ptr = level.tile_data;
    level_tile_bank = level.tile_bank;
    level_sprite_ptr = level.sprite_data;
    level_sprite_bank = level.sprite_bank;

    set_prg_a000(level_tile_bank);


    for(char i=0; i<15; i++){

    }
        //collision_map_0
}