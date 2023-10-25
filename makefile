# makefile for nesdoug example code, for Linux

ifeq ($(OS),Windows_NT)
# Windows
CC65 = ./bin/cc65.exe
CA65 = ./bin/ca65.exe
LD65 = ./bin/ld65.exe
DEL = del
MKDIR = mkdir
else ifeq ($(OS),MSDOS)
# MS-DOS
# add "set OS=MSDOS" to autoexec
# DJGPP, GNU fileutils for DJGPP need to be installed
CC65 = ./bin/cc65d.exe
CA65 = ./bin/ca65d.exe
LD65 = ./bin/ld65d.exe
DEL = del
MKDIR = mkdir
else
# Ubuntu/Debian
CC65 = cc65
CA65 = ca65
LD65 = ld65
DEL = rm
MKDIR = mkdir
endif

NAME = famidash
CFG = nrom_32k_vert.cfg
OUT_FOLDER = BUILD
TMP_FOLDER = TMP

.PHONY: default clean

default: $(OUT_FOLDER)/$(NAME).nes


#target: dependencies

$(OUT_FOLDER):
	$(MKDIR) $(OUT_FOLDER)

$(TMP_FOLDER):
	$(MKDIR) $(TMP_FOLDER)

$(OUT_FOLDER)/$(NAME).nes: $(OUT_FOLDER) $(TMP_FOLDER)/$(NAME).o $(TMP_FOLDER)/crt0.o $(CFG)
	$(LD65) -C $(CFG) -o $(OUT_FOLDER)/$(NAME).nes --obj-path $(TMP_FOLDER) crt0.o $(NAME).o nes.lib -Ln $(OUT_FOLDER)/labels.txt --dbgfile $(OUT_FOLDER)/dbg.txt
	@echo $(NAME).nes created

$(TMP_FOLDER)/crt0.o: crt0.s famidash.chr LIB/*.s MUSIC/*.s MUSIC/*.dmc
	$(CA65) crt0.s -o $(TMP_FOLDER)/crt0.o

$(TMP_FOLDER)/$(NAME).o: $(TMP_FOLDER)/$(NAME).s
	$(CA65) $(TMP_FOLDER)/$(NAME).s -g

$(TMP_FOLDER)/$(NAME).s: $(TMP_FOLDER) $(NAME).c include.h gamemode_cube.c gamemode_ship.c Sprites.h famidash.h level_data.c BG/stereomadness_.c
	$(CC65) -Oirs $(NAME).c --add-source -o $(TMP_FOLDER)/$(NAME).s

clean:
ifeq ($(OS),Windows_NT)
	clean.bat
else ifeq ($(OS),MSDOS)
	rm -rf $(TMP_FOLDER)/*.*
else
	rm -rf $(TMP_FOLDER)
endif
