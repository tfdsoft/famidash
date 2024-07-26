# makefile for nesdoug example code, for Linux

ifeq ($(OS),Windows_NT)
# Windows
CC65 = ./BIN/cc65.exe
CA65 = ./BIN/ca65.exe
LD65 = ./BIN/ld65.exe
DEL = del
MKDIR = mkdir
PYTHON = python
else ifeq ($(OS),MSDOS)
# MS-DOS
# add "set OS=MSDOS" to autoexec
# DJGPP, GNU fileutils for DJGPP need to be installed
CC65 = ./BIN/cc65d.exe
CA65 = ./BIN/ca65d.exe
LD65 = ./BIN/ld65d.exe
DEL = del
MKDIR = mkdir
PYTHON = python
else
# Ubuntu/Debian
CC65 = cc65
CA65 = ca65
LD65 = ld65
DEL = rm
MKDIR = mkdir
PYTHON = python3
endif

define cc65IncDir
-I $(1)
endef
define ca65IncDir
-I $(1) --bin-include-dir $(1)
endef
define ld65IncDir
-L $(1) --obj-path $(1)
endef

NAME = famidash
CFG = CONFIG/mmc3.cfg
OUTDIR = BUILD
TMPDIR = TMP

.PHONY: default clean

default: $(OUTDIR)/$(NAME).nes


#target: dependencies

$(OUTDIR):
	$(MKDIR) $(OUTDIR)

$(TMPDIR):
	$(MKDIR) $(TMPDIR)

$(OUTDIR)/$(NAME).nes: $(OUTDIR) $(TMPDIR)/$(NAME).o $(TMPDIR)/crt0.o $(CFG)
	$(LD65) -C $(CFG) -o $(OUTDIR)/$(NAME).nes $(call ld65IncDir,$(TMPDIR)) $(call ld65IncDir,LIB) crt0.o $(NAME).o nes.lib --dbgfile $(OUTDIR)/famidash.dbg
	@echo $(NAME).nes created

$(TMPDIR)/crt0.o: GRAPHICS/*.chr LIB/asm/*.s LEVELS/*.s METATILES/*.s METATILES/*.inc MUSIC/EXPORTS/*.s MUSIC/EXPORTS/music_bank*.dmc $(TMPDIR)/BUILD_FLAGS.s
	$(CA65) LIB/asm/crt0.s --cpu 6502X -g $(call ca65IncDir,.) $(call ca65IncDir,MUSIC/EXPORTS) $(call ca65IncDir,$(TMPDIR)) -o $(TMPDIR)/crt0.o

$(TMPDIR)/$(NAME).o: $(TMPDIR)/$(NAME).s
	$(CA65) --cpu 6502X $(call ca65IncDir,LIB/asm) $(TMPDIR)/$(NAME).s -g 

$(TMPDIR)/BUILD_FLAGS.s: BUILD_FLAGS.h defines_to_asm.py
	$(PYTHON) defines_to_asm.py

$(TMPDIR)/$(NAME).s: $(TMPDIR) SAUCE/$(NAME).c SAUCE/*.h SAUCE/gamestates/*.h SAUCE/gamemodes/*.h SAUCE/defines/*.h SAUCE/functions/*.h METATILES/metatiles.h LEVELS/*.h LIB/headers/*.h MUSIC/EXPORTS/musicDefines.h 
	$(CC65) -Osir -g --eagerly-inline-funcs SAUCE/$(NAME).c $(call cc65IncDir,LIB/headers) $(call cc65IncDir,.) -E --add-source -o $(TMPDIR)/$(NAME).c
	$(CC65) -Osir -g --eagerly-inline-funcs SAUCE/$(NAME).c $(call cc65IncDir,LIB/headers) $(call cc65IncDir,.) --add-source -o $(TMPDIR)/$(NAME).s

clean:
ifeq ($(OS),Windows_NT)
	clean.bat
else ifeq ($(OS),MSDOS)
	rm -rf $(TMPDIR)/*.*
else
	rm -rf $(TMPDIR)
endif
