banked(fixed.func) void level_fetch_metatile_tiles(u8 column, u8 y_offset, u8 side){

    
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

banked(fixed.func) void level_draw_metatile_column(u8 column, u8 y_offset){
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

banked(fixed.func)
u8 num_to_ascii(u8 n){
    n &= 0x0f;
    if(n > 0x09) return (n + 0x37);
    return (n + 0x30);
}