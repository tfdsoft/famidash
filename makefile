
ifeq ($(OS),Windows_NT)
# Windows
CC = ./BIN/mos-nes-mmc3-clang.exe
CA65 := ./BIN/ca65.exe

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
CC = ./BIN/mos-nes-mmc3-clang.exe
CA65 := ./BIN/ca65d.exe

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
CC = mos-nes-mmc3-clang
CA65 := ca65

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

NAME = famidash-llvm
OUTDIR_PREFIX = OUT
TMPDIR_PREFIX = TMP
OUTDIR ?= $(OUTDIR_PREFIX)
TMPDIR ?= $(TMPDIR_PREFIX)
CFG ?= link.ld

CFLAGS = -flto -Oz -ffast-math -fnonreentrant -std=gnu23 -Wall -Wextra
LDFLAGS = -mreserve-zp=27 -T $(CFG)

ifneq ($(findstring build,$(MAKECMDGOALS)),)
ifeq ($(LEVELSET),)
$(error Level set not specified, you are not calling this makefile correctly)
endif
endif

.PHONY: default clean distclean build main


# optimize for code size (the ideal method)
build: $(TMPDIR) $(OUTDIR) $(OUTDIR)/$(NAME).nes
	


all: main

main: LEVELSET = A
main: OUTDIR = $(OUTDIR_PREFIX)/$@
main: TMPDIR = $(TMPDIR_PREFIX)/$@
main:
	@echo Building main...
	@$(MAKE) build LEVELSET=$(LEVELSET) \
	CA65_DEFINES=$(CA65_DEFINES) \
	OUTDIR=$(OUTDIR) TMPDIR=$(TMPDIR) CFG=$(CFG) \
	--no-print-directory

#target: dependencies


$(OUTDIR):
	$(call mkdir,$(OUTDIR))

$(TMPDIR):
	$(call mkdir,$(TMPDIR))


$(TMPDIR)/famistudio.o: music/*.s
	$(CA65) music/music_assets.s -o $@

$(TMPDIR)/music.o: music/EXPORTS/lvlset_$(LEVELSET)/music_bank*.dmc music/EXPORTS/lvlset_$(LEVELSET)/music_*.s music/NoteTables/*.* 
#	compile all of the music assets into one giant object file
	$(CA65) music/EXPORTS/lvlset_$(LEVELSET)/music_data_header.s -o $@

$(TMPDIR)/donut.o: src/chr/*.s
	$(CA65) src/chr/donut.s -o $@

$(TMPDIR)/assets.o: src/chr/dnt/*.bin src/assets.c src/assets.h
	$(CC) -c src/assets.c $(CFLAGS) -o $@

$(OUTDIR)/$(NAME).nes: $(OUTDIR) $(TMPDIR)/famistudio.o $(TMPDIR)/music.o $(TMPDIR)/assets.o $(TMPDIR)/donut.o src/*.h src/*.c src/gamestates/*.c music/EXPORTS/lvlset_$(LEVELSET)/*.h $(CFG)
	$(CC) src/main.c $(call cc65IncDir,music/EXPORTS/lvlset_$(LEVELSET)) $(TMPDIR)/*.o $(CFLAGS) $(LDFLAGS) -o $@
	




clean:
ifeq ($(OS),Windows_NT)
	$(call del,$(TMPDIR_PREFIX)/*.*)
else ifeq ($(OS),MSDOS)
	$(call del,$(TMPDIR_PREFIX)/*.*)
else
	rm -rf $(TMPDIR_PREFIX)
endif

distclean:
ifeq ($(OS),Windows_NT)
	$(call del,$(OUTDIR_PREFIX)/*.*)
else ifeq ($(OS),MSDOS)
	$(call del,$(OUTDIR_PREFIX)/*.*)
else
	rm -rf $(OUTDIR_PREFIX)
endif
