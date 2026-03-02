#include "levels.h"

nesram struct Level active_lvl;

nesram u8 lvl_column_buffer[15+15+12+3];
//nesram u8 lvl_column_offset;

nesram u8* lvl_rle_pointer;
nesram u8 lvl_rle_value, lvl_rle_run, lvl_rle_x_offset;



banked(fixed.func) void level_rle_init(struct Level lvl){
    active_lvl = lvl;
    
    set_prg_a000(active_lvl.tile_bank);

    lvl_rle_pointer = active_lvl.tile_data;
    //lvl_rle_bank = active_lvl.tile_bank;

    lvl_rle_value = lvl_rle_pointer[0];
    lvl_rle_run = lvl_rle_pointer[1];
    lvl_rle_x_offset = 0;

    /*for(char x=0; x < 16; x++) {
        for(char y = (active_lvl.height-1); !(y & 0x80); y--){
            // run while i isn't negative

        }
    }*/
}

static void __level_rle_fetch_next_tile(){
    if(lvl_rle_run == 0) {
        lvl_rle_pointer+=2;

        //if(lvl_rle_pointer == (u8*)0xc000) {
        //    lvl_rle_pointer == 0xa000
        //}

        lvl_rle_value = lvl_rle_pointer[0];
        lvl_rle_run = lvl_rle_pointer[1];
    }
    lvl_rle_run--;
}
static void __level_rle_fetch_previous_tile(){
    if(lvl_rle_run == lvl_rle_pointer[1]) {
        lvl_rle_pointer-=2;

        //if(lvl_rle_pointer == (u8*)0xc000) {
        //    lvl_rle_pointer == 0xa000
        //}

        lvl_rle_value = lvl_rle_pointer[0];
        lvl_rle_run = 0;
    }
    lvl_rle_run++;
}

void level_rle_fetch_columns(s8 count, u8 y_offset){
    set_prg_a000(active_lvl.tile_bank);
    y_offset %= 30; // nes nametables are 30 tiles tall

    if(count >= 0){
        for(; count>0; count--){ // fetch this many columns

            // decompress columns into the table
            for(u8 height=0; height<active_lvl.height; height++){
                __level_rle_fetch_next_tile();
                collision_map_0[grid16(lvl_rle_x_offset,height)] = lvl_rle_value;
            }

            ++lvl_rle_x_offset;
            //lvl_rle_x_offset &= 0x0f;
        }
    } else {
        // go backward code
        for(; count!=0; count++) {
            --lvl_rle_x_offset;
            // decompress tiles into the table
            for(u8 height=active_lvl.height; height>0; height--){
                __level_rle_fetch_previous_tile();
                collision_map_0[grid16(lvl_rle_x_offset,height-1)] = lvl_rle_value;
            }
        }

    }
}


void level_fetch_metatile_tiles(u8 column, u8 y_offset, u8 side){

    
    if(side) for(u8 i=0; i<15; i++){
        u8 tile = collision_map_0[grid16((column),(y_offset+i))];
        tile_buffer[i<<1] = metatiles_TR[tile];
        tile_buffer[1+(i<<1)] = metatiles_BR[tile];
    }
    else for(u8 i=0; i<15; i++){
        u8 tile = collision_map_0[grid16((column),(y_offset+i))];
        tile_buffer[i<<1] = metatiles_TL[tile];
        tile_buffer[1+(i<<1)] = metatiles_BL[tile];
    }
}

void level_draw_metatile_column(u8 column, u8 y_offset){
    column &= 0xfe;
    y_offset &= 0xfe;
    u8 y_offset_mod30 = (y_offset % 30);
    u8 y_offset_mod60 = (y_offset % 60);
    u16 seam_address_1 = nametable_address_A((column&30),y_offset_mod30);
    u16 seam_address_2 = nametable_address_C((column&30),0);
    if(column&32) {
        seam_address_1 += 0x400;
        seam_address_2 += 0x400;
    }
    if(y_offset_mod60 >= 30) {
        seam_address_1 += 0x800;
        seam_address_2 -= 0x800;
    }

    level_fetch_metatile_tiles(column>>1,y_offset>>1,0);

    se_multi_vram_buffer_vertical(
        (const char*)&tile_buffer[0],
        (30 - y_offset_mod30),
        seam_address_1
    );
    se_multi_vram_buffer_vertical(
        (const char*)&tile_buffer[(30-y_offset_mod30)],
        y_offset_mod30,
        seam_address_2
    );

    level_fetch_metatile_tiles(column>>1,y_offset>>1,1);

    se_multi_vram_buffer_vertical(
        (const char*)&tile_buffer[0],
        (30 - y_offset_mod30),
        seam_address_1+1
    );
    se_multi_vram_buffer_vertical(
        (const char*)&tile_buffer[(30-y_offset_mod30)],
        y_offset_mod30,
        seam_address_2+1
    );
}