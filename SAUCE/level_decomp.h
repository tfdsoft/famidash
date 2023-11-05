void init_rld(void){
    i = 0;
    run = 0;    // amount of tiles to place
    value = 0;  // the tile to repeat
    tmp1 = 0;
}

void load_next_column(unsigned char level, unsigned char column){
    tmp1 = 0;
    if (column = 0) {
        value = level_list[level][0]; // set the value and run to the first tile type and length
        run = level_list[level][1];
    }
    while (tmp1 < 27) { // level is 27 tiles high, so run for 27 tiles
        columnBuffer[(tmp1)] = value; // write a value to the column buffer

        tmp2 = columnBuffer[tmp1];
        collisionMap[(tmp1)+column] = tmp2;
        // NEVER use two pointers on the same line.
        // it will compile to 55 instructions whereas doing the above compiles to just 10

        --run; // decrement run by 1
        ++tmp1; // increment column buffer write location
        if (run = 0){
            ++i; // go to the next rle index in the level data
            value = level_list[level][(i*2)]; // set the value and run to the next tile type and length
            run = level_list[level][(i*2)+1];
        }
    }
    
    tmp1 = 0;
    /*
    while (tmp1 < 27) { // write the column buffer to the collision map
        tmp2 = columnBuffer[tmp1];
        collisionMap[(tmp1<<4)+column] = tmp2;
        ++tmp1;
    }
    */
}