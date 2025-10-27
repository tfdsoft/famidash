INCLUDE common.ld
INCLUDE c-in-ram.ld

/* set bank start positions before the
default linker script does it for me */

__prg_rom_22 = 0xa000;
__prg_rom_23 = 0xa000;
__prg_rom_24 = 0xa000;
__prg_rom_25 = 0xa000;
__prg_rom_26 = 0xa000;
__prg_rom_27 = 0xa000;
__prg_rom_28 = 0xa000;
__prg_rom_29 = 0xa000;
__prg_rom_30 = 0xa000;
__prg_rom_31 = 0xa000;

__prg_rom_32 = 0xa000;
__prg_rom_33 = 0xa000;
__prg_rom_34 = 0xa000;
__prg_rom_35 = 0xa000;
__prg_rom_36 = 0xa000;
__prg_rom_37 = 0xa000;
__prg_rom_38 = 0xa000;
__prg_rom_39 = 0xa000;
__prg_rom_40 = 0xa000;
__prg_rom_41 = 0xa000;
__prg_rom_42 = 0xa000;
__prg_rom_43 = 0xa000;
__prg_rom_44 = 0xa000;
__prg_rom_45 = 0xa000;
__prg_rom_46 = 0xa000;
__prg_rom_47 = 0xa000;

__prg_rom_48 = 0xa000;
__prg_rom_49 = 0xa000;
__prg_rom_50 = 0xa000;
__prg_rom_51 = 0xa000;
__prg_rom_52 = 0xa000;
__prg_rom_53 = 0xa000;
__prg_rom_54 = 0xa000;
__prg_rom_55 = 0xa000;
__prg_rom_56 = 0xa000;
__prg_rom_57 = 0xa000;
__prg_rom_58 = 0xa000;
__prg_rom_59 = 0xa000;
__prg_rom_60 = 0xa000;
__prg_rom_61 = 0xa000;

INCLUDE prg-rom-banked-mode-1.ld