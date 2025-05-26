# makefile for nesdoug example code, for Linux

ifeq ($(OS),Windows_NT)
# Windows
CC65 := ./BIN/cc65.exe
CA65 := ./BIN/ca65.exe
LD65 := ./BIN/ld65.exe

define del
del $(subst /,\\,$(1))
endef

define mkdir
mkdir $(subst /,\\,$(1))
endef

PYTHON := python
else ifeq ($(OS),MSDOS)
# MS-DOS
# add "set OS=MSDOS" to autoexec
# DJGPP, GNU fileutils for DJGPP need to be installed
CC65 := ./BIN/cc65d.exe
CA65 := ./BIN/ca65d.exe
LD65 := ./BIN/ld65d.exe

define del
del $(subst /,\\,$(1))
endef

define mkdir
mkdir $(subst /,\\,$(1))
endef

PYTHON := python
DIRSEP := \\
else
# Ubuntu/Debian
CC65 := cc65
CA65 := ca65
LD65 := ld65

define del
rm -rf $(1)
endef

define mkdir
mkdir -p $(1)
endef

PYTHON := python3
DIRSEP := /
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

.DEFAULT_GOAL = main

NAME := famidash
NSF_CFG := CONFIG/nsf.cfg
OUTDIR_PREFIX = BUILD
TMPDIR_PREFIX = TMP
OUTDIR ?= $(OUTDIR_PREFIX)
TMPDIR ?= $(TMPDIR_PREFIX)
CFG ?= CONFIG/mmc3.cfg

ifneq ($(findstring build,$(MAKECMDGOALS)),)
ifeq ($(LEVELSET),)
$(error Level set not specified, you are not calling this makefile correctly)
endif
endif

.PHONY: default clean distclean build nsf vs-sys main b-sides

build: $(OUTDIR) $(OUTDIR)/$(NAME).nes
all: main vs-sys b-sides c-sides
nsf-main: $(TMPDIR_PREFIX)/main/$(NAME)_prg.bin $(TMPDIR_PREFIX)/main/$(NAME)_nsfprg.bin $(TMPDIR_PREFIX)/main/$(NAME)_meta.bin $(TMPDIR_PREFIX)/main/$(NAME)_hdr.bin

main: LEVELSET = A
main: OUTDIR = $(OUTDIR_PREFIX)/$@
main: TMPDIR = $(TMPDIR_PREFIX)/$@
main:
	@echo Building main...
	@$(MAKE) build LEVELSET=$(LEVELSET) \
	CC65_DEFINES=$(CC65_DEFINES) \
	CA65_DEFINES=$(CA65_DEFINES) \
	OUTDIR=$(OUTDIR) TMPDIR=$(TMPDIR) CFG=$(CFG) \
	--no-print-directory

vs-sys: LEVELSET = A
vs-sys: CC65_DEFINES += -D__VS_SYSTEM=1
vs-sys: CA65_DEFINES += -D__VS_SYSTEM=1
vs-sys: OUTDIR = $(OUTDIR_PREFIX)/$@
vs-sys: TMPDIR = $(TMPDIR_PREFIX)/$@
vs-sys: CFG = CONFIG/vs-sys.cfg
vs-sys:
	@echo Building VS System version...
	@$(MAKE) build LEVELSET=$(LEVELSET) \
	CC65_DEFINES=$(CC65_DEFINES) \
	CA65_DEFINES=$(CA65_DEFINES) \
	OUTDIR=$(OUTDIR) TMPDIR=$(TMPDIR) CFG=$(CFG) \
	--no-print-directory

b-sides: LEVELSET = B
b-sides: OUTDIR = $(OUTDIR_PREFIX)/$@
b-sides: TMPDIR = $(TMPDIR_PREFIX)/$@
b-sides:
	@echo Building B-Sides...
	@$(MAKE) build LEVELSET=$(LEVELSET) \
	CC65_DEFINES=$(CC65_DEFINES) \
	CA65_DEFINES=$(CA65_DEFINES) \
	OUTDIR=$(OUTDIR) TMPDIR=$(TMPDIR) CFG=$(CFG) \
	--no-print-directory

c-sides: LEVELSET = C
c-sides: OUTDIR = $(OUTDIR_PREFIX)/$@
c-sides: TMPDIR = $(TMPDIR_PREFIX)/$@
c-sides:
	@echo Building C-Sides...
	@$(MAKE) build LEVELSET=$(LEVELSET) \
	CC65_DEFINES=$(CC65_DEFINES) \
	CA65_DEFINES=$(CA65_DEFINES) \
	OUTDIR=$(OUTDIR) TMPDIR=$(TMPDIR) CFG=$(CFG) \
	--no-print-directory

#target: dependencies

$(OUTDIR):
	$(call mkdir,$(OUTDIR))

$(TMPDIR):
	$(call mkdir,$(TMPDIR))

$(OUTDIR)/$(NAME).nes: $(OUTDIR) $(TMPDIR)/$(NAME).o $(TMPDIR)/crt0.o $(CFG)
	$(LD65) -C $(CFG) -o $(OUTDIR)/$(NAME).nes $(call ld65IncDir,$(TMPDIR)) $(call ld65IncDir,LIB) crt0.o $(NAME).o nes.lib --dbgfile $(OUTDIR)/famidash.dbg
	@echo $(NAME).nes created

$(TMPDIR)/crt0.o: GRAPHICS/*.chr LIB/asm/*.s LEVELS/include/lvlset_$(LEVELSET)/*.s METATILES/*.s METATILES/*.inc MUSIC/EXPORTS/lvlset_$(LEVELSET)/*.s MUSIC/EXPORTS/lvlset_$(LEVELSET)/music_bank*.dmc $(TMPDIR)/BUILD_FLAGS.s
	$(CA65) $(CA65_DEFINES) LIB/asm/crt0.s -l $(OUTDIR)/crt0.lst --cpu 6502X -g $(call ca65IncDir,.) $(call ca65IncDir,MUSIC/EXPORTS/lvlset_$(LEVELSET)) $(call ca65IncDir,LEVELS/include/lvlset_$(LEVELSET)) $(call ca65IncDir,$(TMPDIR)) -o $(TMPDIR)/crt0.o

$(TMPDIR)/$(NAME).o: $(TMPDIR)/$(NAME).s
	$(CA65) $(CA65_DEFINES) -l $(OUTDIR)/$(NAME).lst --cpu 6502X $(call ca65IncDir,LIB/asm) $(TMPDIR)/$(NAME).s -g 

$(TMPDIR)/BUILD_FLAGS.s: BUILD_FLAGS.h defines_to_asm.py LEVELS/include/lvlset_$(LEVELSET)/level_defines.h SAUCE/defines/space_defines.h SAUCE/defines/physics_defines.h
	$(PYTHON) defines_to_asm.py $(TMPDIR)/BUILD_FLAGS.s BUILD_FLAGS.h LEVELS/include/lvlset_$(LEVELSET)/level_defines.h SAUCE/defines/space_defines.h SAUCE/defines/physics_defines.h

$(TMPDIR)/$(NAME).s: $(TMPDIR) SAUCE/$(NAME).c SAUCE/*.h SAUCE/*/*.h SAUCE/*/*.c SAUCE/*/*/*.h SAUCE/*/*/*.c METATILES/metatiles.h LEVELS/include/lvlset_$(LEVELSET)/*.h LIB/headers/*.h MUSIC/EXPORTS/lvlset_$(LEVELSET)/*.h 
	$(CC65) $(CC65_DEFINES) -Osir -g --eagerly-inline-funcs SAUCE/$(NAME).c $(call cc65IncDir,LIB/headers) $(call cc65IncDir,.) $(call cc65IncDir,MUSIC/EXPORTS/lvlset_$(LEVELSET)) $(call cc65IncDir,LEVELS/include/lvlset_$(LEVELSET)) -E --add-source -o $(TMPDIR)/$(NAME).pp.c
	$(CC65) $(CC65_DEFINES) -Osir -g --eagerly-inline-funcs SAUCE/$(NAME).c $(call cc65IncDir,LIB/headers) $(call cc65IncDir,.) $(call cc65IncDir,MUSIC/EXPORTS/lvlset_$(LEVELSET)) $(call cc65IncDir,LEVELS/include/lvlset_$(LEVELSET)) --add-source -o $(TMPDIR)/$(NAME).s

$(TMPDIR)/$(NAME)_prg.bin $(TMPDIR)/$(NAME)_nsfprg.bin $(TMPDIR)/$(NAME)_meta.bin $(TMPDIR)/$(NAME)_hdr.bin: $(OUTDIR) $(TMPDIR)/$(NAME).o $(TMPDIR)/crt0_nsf.o $(NSF_CFG)
	$(LD65) -C $(NSF_CFG) -o $(TMPDIR)/$(NAME) $(call ld65IncDir,$(TMPDIR)) $(call ld65IncDir,LIB) crt0_nsf.o $(NAME).o nes.lib --dbgfile $(OUTDIR)/famidash_nsf.dbg
	@echo $(NAME).nsf created

$(TMPDIR)/crt0_nsf.o: NSF/*.* LIB/asm/*.inc MUSIC/EXPORTS/lvlset_$(LEVELSET)/*.s
	$(CA65) $(CA65_DEFINES) NSF/crt0.s -l $(OUTDIR)/crt0_nsf.lst --cpu 6502X -g $(call ca65IncDir,.) $(call ca65IncDir,MUSIC/EXPORTS/lvlset_$(LEVELSET)) $(call ca65IncDir,LEVELS/include/lvlset_$(LEVELSET)) $(call ca65IncDir,$(TMPDIR)) $(call ca65IncDir,LIB/asm) -o $(TMPDIR)/crt0_nsf.o

clean:
ifeq ($(OS),Windows_NT)
	clean.bat
else ifeq ($(OS),MSDOS)
	$(call del,$(TMPDIR_PREFIX)/*.*)
else
	rm -rf $(TMPDIR_PREFIX)
endif

distclean:
ifeq ($(OS),Windows_NT)
	clean.bat
else ifeq ($(OS),MSDOS)
	$(call del,$(OUTDIR_PREFIX)/*.*)
else
	rm -rf $(OUTDIR_PREFIX)
endif
