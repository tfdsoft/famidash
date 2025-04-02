# makefile for nesdoug example code, for Linux

ifeq ($(OS),Windows_NT)
# Windows
CC65 = ./BIN/cc65.exe
CA65 = ./BIN/ca65.exe
LD65 = ./BIN/ld65.exe
DEL = del
MKDIR = mkdir
PYTHON = python
CAT = type
DS = \\
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
CAT = type
DS = \\
else
# Ubuntu/Debian
CC65 = cc65
CA65 = ca65
LD65 = ld65
DEL = rm
MKDIR = mkdir
PYTHON = python3
CAT = cat
DS = /
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
NSF_CFG=CONFIG/nsf.cfg
OUTDIR = BUILD
TMPDIR = TMP

.PHONY: default clean nsf

default: $(OUTDIR)/$(NAME).nes
nsf: $(TMPDIR)/$(NAME)_prg.bin $(TMPDIR)/$(NAME)_nsfprg.bin $(TMPDIR)/$(NAME)_meta.bin $(TMPDIR)/$(NAME)_hdr.bin

#target: dependencies

$(OUTDIR):
	$(MKDIR) $(OUTDIR)

$(TMPDIR):
	$(MKDIR) $(TMPDIR)

$(OUTDIR)/$(NAME).nes: $(OUTDIR) $(TMPDIR)/$(NAME).o $(TMPDIR)/crt0.o $(CFG)
	$(LD65) -C $(CFG) -o $(OUTDIR)/$(NAME).nes $(call ld65IncDir,$(TMPDIR)) $(call ld65IncDir,LIB) crt0.o $(NAME).o nes.lib --dbgfile $(OUTDIR)/famidash.dbg
	@echo $(NAME).nes created

$(TMPDIR)/crt0.o: GRAPHICS/*.chr LIB/asm/*.s LEVELS/*.s METATILES/*.s METATILES/*.inc MUSIC/EXPORTS/*.s MUSIC/EXPORTS/music_bank*.dmc $(TMPDIR)/BUILD_FLAGS.s $(TMPDIR)/C_defines.s
	$(CA65) LIB/asm/crt0.s -l $(OUTDIR)/crt0.lst --cpu 6502X -g $(call ca65IncDir,.) $(call ca65IncDir,MUSIC/EXPORTS) $(call ca65IncDir,$(TMPDIR)) -o $(TMPDIR)/crt0.o

$(TMPDIR)/$(NAME).o: $(TMPDIR)/$(NAME).s
	$(CA65) -l $(OUTDIR)/$(NAME).lst --cpu 6502X $(call ca65IncDir,LIB/asm) $(TMPDIR)/$(NAME).s -g 

$(TMPDIR)/BUILD_FLAGS.s: BUILD_FLAGS.h defines_to_asm.py
	$(PYTHON) defines_to_asm.py BUILD_FLAGS.h

$(TMPDIR)/C_defines.s: SAUCE/defines/*_defines.h defines_to_asm.py
	$(PYTHON) defines_to_asm.py SAUCE/defines/space_defines.h SAUCE/defines/physics_defines.h SAUCE/defines/level_defines.h
	$(CAT) $(TMPDIR)$(DS)space_defines.s $(TMPDIR)$(DS)physics_defines.s $(TMPDIR)$(DS)level_defines.s > $(TMPDIR)$(DS)C_defines.s

$(TMPDIR)/$(NAME).s: $(TMPDIR) SAUCE/$(NAME).c SAUCE/*.h SAUCE/gamestates/*.h SAUCE/defines/*.h METATILES/metatiles.h LEVELS/*.h LIB/headers/*.h MUSIC/EXPORTS/*.h 
	$(CC65) -Osir -g --eagerly-inline-funcs SAUCE/$(NAME).c $(call cc65IncDir,LIB/headers) $(call cc65IncDir,.) -E --add-source -o $(TMPDIR)/$(NAME).c
	$(CC65) -Osir -g --eagerly-inline-funcs SAUCE/$(NAME).c $(call cc65IncDir,LIB/headers) $(call cc65IncDir,.) --add-source -o $(TMPDIR)/$(NAME).s

$(TMPDIR)/$(NAME)_prg.bin $(TMPDIR)/$(NAME)_nsfprg.bin $(TMPDIR)/$(NAME)_meta.bin $(TMPDIR)/$(NAME)_hdr.bin: $(OUTDIR) $(TMPDIR)/$(NAME).o $(TMPDIR)/crt0_nsf.o $(NSF_CFG)
	$(LD65) -C $(NSF_CFG) -o $(TMPDIR)/$(NAME) $(call ld65IncDir,$(TMPDIR)) $(call ld65IncDir,LIB) crt0_nsf.o $(NAME).o nes.lib --dbgfile $(OUTDIR)/famidash_nsf.dbg
	@echo $(NAME).nsf created

$(TMPDIR)/crt0_nsf.o: NSF/*.* LIB/asm/*.inc MUSIC/EXPORTS/*.s
	$(CA65) NSF/crt0.s -l $(OUTDIR)/crt0_nsf.lst --cpu 6502X -g $(call ca65IncDir,.) $(call ca65IncDir,MUSIC/EXPORTS) $(call ca65IncDir,$(TMPDIR)) $(call ca65IncDir,LIB/asm) -o $(TMPDIR)/crt0_nsf.o

clean:
ifeq ($(OS),Windows_NT)
	clean.bat
else ifeq ($(OS),MSDOS)
	rm -rf $(TMPDIR)/*.*
else
	rm -rf $(TMPDIR)
endif
