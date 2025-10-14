CC = mos-nes-mmc3-clang
CARGS = -Oz -mreserve-zp=9
NAME = famidash-llvm


default: make


make:
	rm -rf ./OUT
	rm *.o
	mkdir OUT
#ca65 ./src/famistudio/famistudio_ca65.s -o famistudio.o
	ca65 ./src/famistudio/music_assets.s -o music.o
	$(CC) ./src/main.c ./*.o $(CARGS) -o ./OUT/main.nes -T link.ld -std=gnu23