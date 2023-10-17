# makefile for nesdoug example code, for Linux
# this version won't move the final files to BUILD folder
# also won't rebuild on changes to neslib/nesdoug/famitone files

CC65 = cc65
CA65 = ca65
LD65 = ld65
NAME = famidash
CFG = nrom_32k_vert.cfg


.PHONY: default clean

default: $(NAME).nes


#target: dependencies



$(NAME).nes: $(NAME).o crt0.o $(CFG)
	$(LD65) -C $(CFG) -o ./BUILD/$(NAME).nes crt0.o $(NAME).o nes.lib -Ln labels.txt --dbgfile dbg.txt
	rm *.o
	@echo $(NAME).nes created

crt0.o: crt0.s famidash.chr
	$(CA65) crt0.s

$(NAME).o: $(NAME).s
	$(CA65) $(NAME).s -g

$(NAME).s: $(NAME).c include.h gamemode_cube.c gamemode_ship.c Sprites.h famidash.h level_data.c BG/Room1_.c
	$(CC65) -Oirs $(NAME).c --add-source

clean:
	rm ./BUILD/$(NAME).nes