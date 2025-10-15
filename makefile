CC = mos-nes-mmc3-clang
CARGS = -Oz -mreserve-zp=7
NAME = famidash-llvm


default: make


make:

# 	remove duplicate dpcm files
	rm -rf ./src/famistudio/music_[!0]_bank*.dmc
	
# 	OUT is where the rom will be
	mkdir OUT -p
	mkdir TMP -p

#	compile all of the music assets into one giant object file
	ca65 ./src/famistudio/music_assets.s -o ./TMP/music.o

# 	run llvm-mos
	$(CC) ./src/main.c ./TMP/*.o $(CARGS) -o ./OUT/$(NAME).nes -T link.ld -std=gnu23

#	delete object files
	rm -rf ./TMP
