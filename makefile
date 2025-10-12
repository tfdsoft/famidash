CC = mos-nes-mmc3-clang
CARGS = -Os
NAME = famidash-llvm


default: make


make:
	rm -rf ./OUT
	mkdir OUT
	ca65 ./src/famistudio/famistudio_ca65.s -o famistudio.o
	ca65 ./src/famistudio/callback.s -o famistudio.o
	$(CC) ./src/main.c ./src/famistudio/*.o $(CARGS) -o ./OUT/main.nes -T link.ld -std=gnu23