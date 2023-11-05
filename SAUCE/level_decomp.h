void init_rld(void){
    i = 0;
    run = 0;
    value = 0;
}

void load_next_column(unsigned char level, unsigned char column){
    tmp1 = 0;
    value = level_list[level][(tmp1*2)];
    run = level_list[level][(tmp1*2)+1];
    while (tmp1 != 0x1A) {
        while (run > 0) {
            columnBuffer[(tmp1)] = value;
            tmp2 = collisionMap[(tmp1<<4)+column];
            columnBuffer[tmp1] = tmp2;
            --run;
            ++tmp1;
        }
        value = level_list[level][(tmp1*2)];
        run = level_list[level][(tmp1*2)+1];
    }
    
    tmp1 = 0;
    while (tmp1 < 0x1A) {
        tmp2 = collisionMap[(tmp1<<4)+column];
        columnBuffer[tmp1] = tmp2;
        ++tmp1;
    }
    
}