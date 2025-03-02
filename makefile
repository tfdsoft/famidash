# makefile for nesdoug example code, for Linux

ifeq ($(OS),Windows_NT)
# Windows
CC65 := ./BIN/cc65.exe
CA65 := ./BIN/ca65.exe
LD65 := ./BIN/ld65.exe
DEL := del
MKDIR := mkdir
PYTHON := python
else ifeq ($(OS),MSDOS)
# MS-DOS
# add "set OS=MSDOS" to autoexec
# DJGPP, GNU fileutils for DJGPP need to be installed
CC65 := ./BIN/cc65d.exe
CA65 := ./BIN/ca65d.exe
LD65 := ./BIN/ld65d.exe
DEL := del
MKDIR := mkdir
PYTHON := python
else
# Ubuntu/Debian
CC65 := cc65
CA65 := ca65
LD65 := ld65
DEL := rm -rf
MKDIR := mkdir -p
PYTHON := python3
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

NAME := famidash
NSF_CFG := CONFIG/nsf.cfg
OUTDIR_PREFIX = BUILD
TMPDIR_PREFIX = TMP
OUTDIR ?= $(OUTDIR_PREFIX)/main
TMPDIR ?= $(TMPDIR_PREFIX)/main
CFG ?= CONFIG/mmc3.cfg

.PHONY: default clean distclean nsf vs-sys

main: $(OUTDIR)/ $(OUTDIR)/$(NAME).nes
all: main vs-sys
nsf-main: $(TMPDIR_PREFIX)/main/$(NAME)_prg.bin $(TMPDIR_PREFIX)/main/$(NAME)_nsfprg.bin $(TMPDIR_PREFIX)/main/$(NAME)_meta.bin $(TMPDIR_PREFIX)/main/$(NAME)_hdr.bin

vs-sys: CC65_DEFINES += -D__VS_SYSTEM=1
vs-sys: CA65_DEFINES += -D__VS_SYSTEM=1
vs-sys: OUTDIR = $(OUTDIR_PREFIX)/$@
vs-sys: TMPDIR = $(TMPDIR_PREFIX)/$@
vs-sys: CFG = CONFIG/vs-sys.cfg
vs-sys:
	@echo Building VS System version...
	@$(MAKE) \
	CC65_DEFINES=$(CC65_DEFINES) \
	CA65_DEFINES=$(CA65_DEFINES) \
	OUTDIR=$(OUTDIR) TMPDIR=$(TMPDIR) CFG=$(CFG) \
	--no-print-directory

#target: dependencies

$(OUTDIR)/:
	$(MKDIR) $(OUTDIR)

$(TMPDIR)/:
	$(MKDIR) $(TMPDIR)

$(OUTDIR)/$(NAME).nes: $(OUTDIR)/ $(TMPDIR)/$(NAME).o $(TMPDIR)/crt0.o $(CFG)
	$(LD65) -C $(CFG) -o $(OUTDIR)/$(NAME).nes $(call ld65IncDir,$(TMPDIR)) $(call ld65IncDir,LIB) crt0.o $(NAME).o nes.lib --dbgfile $(OUTDIR)/famidash.dbg
	@echo $(NAME).nes created

$(TMPDIR)/crt0.o: GRAPHICS/*.chr LIB/asm/*.s LEVELS/*.s METATILES/*.s METATILES/*.inc MUSIC/EXPORTS/*.s MUSIC/EXPORTS/music_bank*.dmc $(TMPDIR)/BUILD_FLAGS.s
	$(CA65) $(CA65_DEFINES) LIB/asm/crt0.s -l $(OUTDIR)/crt0.lst --cpu 6502X -g $(call ca65IncDir,.) $(call ca65IncDir,MUSIC/EXPORTS) $(call ca65IncDir,$(TMPDIR)) -o $(TMPDIR)/crt0.o

$(TMPDIR)/$(NAME).o: $(TMPDIR)/$(NAME).s
	$(CA65) $(CA65_DEFINES) -l $(OUTDIR)/$(NAME).lst --cpu 6502X $(call ca65IncDir,LIB/asm) $(TMPDIR)/$(NAME).s -g 

$(TMPDIR)/BUILD_FLAGS.s: BUILD_FLAGS.h defines_to_asm.py
	$(PYTHON) defines_to_asm.py $(TMPDIR)/BUILD_FLAGS.s BUILD_FLAGS.h

$(TMPDIR)/$(NAME).s: $(TMPDIR)/ SAUCE/$(NAME).c SAUCE/*.h SAUCE/gamestates/*.h SAUCE/gamemodes/*.h SAUCE/defines/*.h SAUCE/functions/*.h METATILES/metatiles.h LEVELS/*.h LIB/headers/*.h MUSIC/EXPORTS/*.h 
	$(CC65) $(CC65_DEFINES) -Osir -g --eagerly-inline-funcs SAUCE/$(NAME).c $(call cc65IncDir,LIB/headers) $(call cc65IncDir,.) -E --add-source -o $(TMPDIR)/$(NAME).pp.c
	$(CC65) $(CC65_DEFINES) -Osir -g --eagerly-inline-funcs SAUCE/$(NAME).c $(call cc65IncDir,LIB/headers) $(call cc65IncDir,.) --add-source -o $(TMPDIR)/$(NAME).s

$(TMPDIR)/$(NAME)_prg.bin $(TMPDIR)/$(NAME)_nsfprg.bin $(TMPDIR)/$(NAME)_meta.bin $(TMPDIR)/$(NAME)_hdr.bin: $(OUTDIR) $(TMPDIR)/$(NAME).o $(TMPDIR)/crt0_nsf.o $(NSF_CFG)
	$(LD65) -C $(NSF_CFG) -o $(TMPDIR)/$(NAME) $(call ld65IncDir,$(TMPDIR)) $(call ld65IncDir,LIB) crt0_nsf.o $(NAME).o nes.lib --dbgfile $(OUTDIR)/famidash_nsf.dbg
	@echo $(NAME).nsf created

$(TMPDIR)/crt0_nsf.o: NSF/*.* LIB/asm/*.inc MUSIC/EXPORTS/*.s
	$(CA65) $(CA65_DEFINES) NSF/crt0.s -l $(OUTDIR)/crt0_nsf.lst --cpu 6502X -g $(call ca65IncDir,.) $(call ca65IncDir,MUSIC/EXPORTS) $(call ca65IncDir,$(TMPDIR)) $(call ca65IncDir,LIB/asm) -o $(TMPDIR)/crt0_nsf.o

clean:
ifeq ($(OS),Windows_NT)
	clean.bat
else ifeq ($(OS),MSDOS)
	rm -rf $(TMPDIR_PREFIX)/*.*
else
	rm -rf $(TMPDIR_PREFIX)
endif

distclean:
ifeq ($(OS),Windows_NT)
	clean.bat
else ifeq ($(OS),MSDOS)
	rm -rf $(OUTDIR_PREFIX)/*.*
else
	rm -rf $(OUTDIR_PREFIX)
endif
