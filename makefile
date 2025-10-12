CC = mos-nes-mmc3-clang
CARGS = -Os
NAME = famidash-llvm


default: make


make:
	rm -rf ./OUT
	mkdir OUT
	$(CC) ./src/main.c ./famistudio.o $(CARGS) -o ./OUT/main.nes -T link.ld -std=gnu23