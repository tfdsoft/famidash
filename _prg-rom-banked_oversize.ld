PROVIDE(__prg_rom_size = 1024);

ASSERT(__prg_rom_size > 32,
       "For less than 32KiB of PRG-ROM, use fixed banking.");

__prg_rom_0_lma  = 0x000000 + __prg_rom_0;
__prg_rom_1_lma  = 0x010000 + __prg_rom_1;
__prg_rom_2_lma  = 0x020000 + __prg_rom_2;
__prg_rom_3_lma  = 0x030000 + __prg_rom_3;
__prg_rom_4_lma  = 0x040000 + __prg_rom_4;
__prg_rom_5_lma  = 0x050000 + __prg_rom_5;
__prg_rom_6_lma  = 0x060000 + __prg_rom_6;
__prg_rom_7_lma  = 0x070000 + __prg_rom_7;
__prg_rom_8_lma  = 0x080000 + __prg_rom_8;
__prg_rom_9_lma  = 0x090000 + __prg_rom_9;
__prg_rom_10_lma = 0x0a0000 + __prg_rom_10;
__prg_rom_11_lma = 0x0b0000 + __prg_rom_11;
__prg_rom_12_lma = 0x0c0000 + __prg_rom_12;
__prg_rom_13_lma = 0x0d0000 + __prg_rom_13;
__prg_rom_14_lma = 0x0e0000 + __prg_rom_14;
__prg_rom_15_lma = 0x0f0000 + __prg_rom_15;
__prg_rom_16_lma = 0x100000 + __prg_rom_16;
__prg_rom_17_lma = 0x110000 + __prg_rom_17;
__prg_rom_18_lma = 0x120000 + __prg_rom_18;
__prg_rom_19_lma = 0x130000 + __prg_rom_19;
__prg_rom_20_lma = 0x140000 + __prg_rom_20;
__prg_rom_21_lma = 0x150000 + __prg_rom_21;
__prg_rom_22_lma = 0x160000 + __prg_rom_22;
__prg_rom_23_lma = 0x170000 + __prg_rom_23;
__prg_rom_24_lma = 0x180000 + __prg_rom_24;
__prg_rom_25_lma = 0x190000 + __prg_rom_25;
__prg_rom_26_lma = 0x1a0000 + __prg_rom_26;
__prg_rom_27_lma = 0x1b0000 + __prg_rom_27;
__prg_rom_28_lma = 0x1c0000 + __prg_rom_28;
__prg_rom_29_lma = 0x1d0000 + __prg_rom_29;
__prg_rom_30_lma = 0x1e0000 + __prg_rom_30;
__prg_rom_31_lma = 0x1f0000 + __prg_rom_31;
__prg_rom_32_lma = 0x200000 + __prg_rom_32;
__prg_rom_33_lma = 0x210000 + __prg_rom_33;
__prg_rom_34_lma = 0x220000 + __prg_rom_34;
__prg_rom_35_lma = 0x230000 + __prg_rom_35;
__prg_rom_36_lma = 0x240000 + __prg_rom_36;
__prg_rom_37_lma = 0x250000 + __prg_rom_37;
__prg_rom_38_lma = 0x260000 + __prg_rom_38;
__prg_rom_39_lma = 0x270000 + __prg_rom_39;
__prg_rom_40_lma = 0x280000 + __prg_rom_40;
__prg_rom_41_lma = 0x290000 + __prg_rom_41;
__prg_rom_42_lma = 0x2a0000 + __prg_rom_42;
__prg_rom_43_lma = 0x2b0000 + __prg_rom_43;
__prg_rom_44_lma = 0x2c0000 + __prg_rom_44;
__prg_rom_45_lma = 0x2d0000 + __prg_rom_45;
__prg_rom_46_lma = 0x2e0000 + __prg_rom_46;
__prg_rom_47_lma = 0x2f0000 + __prg_rom_47;
__prg_rom_48_lma = 0x300000 + __prg_rom_48;
__prg_rom_49_lma = 0x310000 + __prg_rom_49;
__prg_rom_50_lma = 0x320000 + __prg_rom_50;
__prg_rom_51_lma = 0x330000 + __prg_rom_51;
__prg_rom_52_lma = 0x340000 + __prg_rom_52;
__prg_rom_53_lma = 0x350000 + __prg_rom_53;
__prg_rom_54_lma = 0x360000 + __prg_rom_54;
__prg_rom_55_lma = 0x370000 + __prg_rom_55;
__prg_rom_56_lma = 0x380000 + __prg_rom_56;
__prg_rom_57_lma = 0x390000 + __prg_rom_57;
__prg_rom_58_lma = 0x3a0000 + __prg_rom_58;
__prg_rom_59_lma = 0x3b0000 + __prg_rom_59;
__prg_rom_60_lma = 0x3c0000 + __prg_rom_60;
__prg_rom_61_lma = 0x3d0000 + __prg_rom_61;
__prg_rom_62_lma = 0x3e0000 + __prg_rom_62;
__prg_rom_63_lma = 0x3f0000 + __prg_rom_63;
__prg_rom_64_lma = 0x400000 + __prg_rom_64;
__prg_rom_65_lma = 0x410000 + __prg_rom_65;
__prg_rom_66_lma = 0x420000 + __prg_rom_66;
__prg_rom_67_lma = 0x430000 + __prg_rom_67;
__prg_rom_68_lma = 0x440000 + __prg_rom_68;
__prg_rom_69_lma = 0x450000 + __prg_rom_69;
__prg_rom_70_lma = 0x460000 + __prg_rom_70;
__prg_rom_71_lma = 0x470000 + __prg_rom_71;
__prg_rom_72_lma = 0x480000 + __prg_rom_72;
__prg_rom_73_lma = 0x490000 + __prg_rom_73;
__prg_rom_74_lma = 0x4a0000 + __prg_rom_74;
__prg_rom_75_lma = 0x4b0000 + __prg_rom_75;
__prg_rom_76_lma = 0x4c0000 + __prg_rom_76;
__prg_rom_77_lma = 0x4d0000 + __prg_rom_77;
__prg_rom_78_lma = 0x4e0000 + __prg_rom_78;
__prg_rom_79_lma = 0x4f0000 + __prg_rom_79;
__prg_rom_80_lma = 0x500000 + __prg_rom_80;
__prg_rom_81_lma = 0x510000 + __prg_rom_81;
__prg_rom_82_lma = 0x520000 + __prg_rom_82;
__prg_rom_83_lma = 0x530000 + __prg_rom_83;
__prg_rom_84_lma = 0x540000 + __prg_rom_84;
__prg_rom_85_lma = 0x550000 + __prg_rom_85;
__prg_rom_86_lma = 0x560000 + __prg_rom_86;
__prg_rom_87_lma = 0x570000 + __prg_rom_87;
__prg_rom_88_lma = 0x580000 + __prg_rom_88;
__prg_rom_89_lma = 0x590000 + __prg_rom_89;
__prg_rom_90_lma = 0x5a0000 + __prg_rom_90;
__prg_rom_91_lma = 0x5b0000 + __prg_rom_91;
__prg_rom_92_lma = 0x5c0000 + __prg_rom_92;
__prg_rom_93_lma = 0x5d0000 + __prg_rom_93;
__prg_rom_94_lma = 0x5e0000 + __prg_rom_94;
__prg_rom_95_lma = 0x5f0000 + __prg_rom_95;
__prg_rom_96_lma = 0x600000 + __prg_rom_96;
__prg_rom_97_lma = 0x610000 + __prg_rom_97;
__prg_rom_98_lma = 0x620000 + __prg_rom_98;
__prg_rom_99_lma = 0x630000 + __prg_rom_99;
__prg_rom_100_lma = 0x640000 + __prg_rom_100;
__prg_rom_101_lma = 0x650000 + __prg_rom_101;
__prg_rom_102_lma = 0x660000 + __prg_rom_102;
__prg_rom_103_lma = 0x670000 + __prg_rom_103;
__prg_rom_104_lma = 0x680000 + __prg_rom_104;
__prg_rom_105_lma = 0x690000 + __prg_rom_105;
__prg_rom_106_lma = 0x6a0000 + __prg_rom_106;
__prg_rom_107_lma = 0x6b0000 + __prg_rom_107;
__prg_rom_108_lma = 0x6c0000 + __prg_rom_108;
__prg_rom_109_lma = 0x6d0000 + __prg_rom_109;
__prg_rom_110_lma = 0x6e0000 + __prg_rom_110;
__prg_rom_111_lma = 0x6f0000 + __prg_rom_111;
__prg_rom_112_lma = 0x700000 + __prg_rom_112;
__prg_rom_113_lma = 0x710000 + __prg_rom_113;
__prg_rom_114_lma = 0x720000 + __prg_rom_114;
__prg_rom_115_lma = 0x730000 + __prg_rom_115;
__prg_rom_116_lma = 0x740000 + __prg_rom_116;
__prg_rom_117_lma = 0x750000 + __prg_rom_117;
__prg_rom_118_lma = 0x760000 + __prg_rom_118;
__prg_rom_119_lma = 0x770000 + __prg_rom_119;
__prg_rom_120_lma = 0x780000 + __prg_rom_120;
__prg_rom_121_lma = 0x790000 + __prg_rom_121;
__prg_rom_122_lma = 0x7a0000 + __prg_rom_122;
__prg_rom_123_lma = 0x7b0000 + __prg_rom_123;
__prg_rom_124_lma = 0x7c0000 + __prg_rom_124;
__prg_rom_125_lma = 0x7d0000 + __prg_rom_125;


__prg_rom_0_offset  = 0x00000;
__prg_rom_1_offset  = 0x02000;
__prg_rom_2_offset  = 0x04000;
__prg_rom_3_offset  = 0x06000;
__prg_rom_4_offset  = 0x08000;
__prg_rom_5_offset  = 0x0a000;
__prg_rom_6_offset  = 0x0c000;
__prg_rom_7_offset  = 0x0e000;
__prg_rom_8_offset  = 0x10000;
__prg_rom_9_offset  = 0x12000;
__prg_rom_10_offset = 0x14000;
__prg_rom_11_offset = 0x16000;
__prg_rom_12_offset = 0x18000;
__prg_rom_13_offset = 0x1a000;
__prg_rom_14_offset = 0x1c000;
__prg_rom_15_offset = 0x1e000;
__prg_rom_16_offset = 0x20000;
__prg_rom_17_offset = 0x22000;
__prg_rom_18_offset = 0x24000;
__prg_rom_19_offset = 0x26000;
__prg_rom_20_offset = 0x28000;
__prg_rom_21_offset = 0x2a000;
__prg_rom_22_offset = 0x2c000;
__prg_rom_23_offset = 0x2e000;
__prg_rom_24_offset = 0x30000;
__prg_rom_25_offset = 0x32000;
__prg_rom_26_offset = 0x34000;
__prg_rom_27_offset = 0x36000;
__prg_rom_28_offset = 0x38000;
__prg_rom_29_offset = 0x3a000;
__prg_rom_30_offset = 0x3c000;
__prg_rom_31_offset = 0x3e000;
__prg_rom_32_offset = 0x40000;
__prg_rom_33_offset = 0x42000;
__prg_rom_34_offset = 0x44000;
__prg_rom_35_offset = 0x46000;
__prg_rom_36_offset = 0x48000;
__prg_rom_37_offset = 0x4a000;
__prg_rom_38_offset = 0x4c000;
__prg_rom_39_offset = 0x4e000;
__prg_rom_40_offset = 0x50000;
__prg_rom_41_offset = 0x52000;
__prg_rom_42_offset = 0x54000;
__prg_rom_43_offset = 0x56000;
__prg_rom_44_offset = 0x58000;
__prg_rom_45_offset = 0x5a000;
__prg_rom_46_offset = 0x5c000;
__prg_rom_47_offset = 0x5e000;
__prg_rom_48_offset = 0x60000;
__prg_rom_49_offset = 0x62000;
__prg_rom_50_offset = 0x64000;
__prg_rom_51_offset = 0x66000;
__prg_rom_52_offset = 0x68000;
__prg_rom_53_offset = 0x6a000;
__prg_rom_54_offset = 0x6c000;
__prg_rom_55_offset = 0x6e000;
__prg_rom_56_offset = 0x70000;
__prg_rom_57_offset = 0x72000;
__prg_rom_58_offset = 0x74000;
__prg_rom_59_offset = 0x76000;
__prg_rom_60_offset = 0x78000;
__prg_rom_61_offset = 0x7a000;
__prg_rom_62_offset = 0x7c000;
__prg_rom_63_offset = 0x7e000;
__prg_rom_64_offset = 0x80000;
__prg_rom_65_offset = 0x82000;
__prg_rom_66_offset = 0x84000;
__prg_rom_67_offset = 0x86000;
__prg_rom_68_offset = 0x88000;
__prg_rom_69_offset = 0x8a000;
__prg_rom_70_offset = 0x8c000;
__prg_rom_71_offset = 0x8e000;
__prg_rom_72_offset = 0x90000;
__prg_rom_73_offset = 0x92000;
__prg_rom_74_offset = 0x94000;
__prg_rom_75_offset = 0x96000;
__prg_rom_76_offset = 0x98000;
__prg_rom_77_offset = 0x9a000;
__prg_rom_78_offset = 0x9c000;
__prg_rom_79_offset = 0x9e000;
__prg_rom_80_offset = 0xa0000;
__prg_rom_81_offset = 0xa2000;
__prg_rom_82_offset = 0xa4000;
__prg_rom_83_offset = 0xa6000;
__prg_rom_84_offset = 0xa8000;
__prg_rom_85_offset = 0xaa000;
__prg_rom_86_offset = 0xac000;
__prg_rom_87_offset = 0xae000;
__prg_rom_88_offset = 0xb0000;
__prg_rom_89_offset = 0xb2000;
__prg_rom_90_offset = 0xb4000;
__prg_rom_91_offset = 0xb6000;
__prg_rom_92_offset = 0xb8000;
__prg_rom_93_offset = 0xba000;
__prg_rom_94_offset = 0xbc000;
__prg_rom_95_offset = 0xbe000;
__prg_rom_96_offset = 0xc0000;
__prg_rom_97_offset = 0xc2000;
__prg_rom_98_offset = 0xc4000;
__prg_rom_99_offset = 0xc6000;
__prg_rom_100_offset = 0xc8000;
__prg_rom_101_offset = 0xca000;
__prg_rom_102_offset = 0xcc000;
__prg_rom_103_offset = 0xce000;
__prg_rom_104_offset = 0xd0000;
__prg_rom_105_offset = 0xd2000;
__prg_rom_106_offset = 0xd4000;
__prg_rom_107_offset = 0xd6000;
__prg_rom_108_offset = 0xd8000;
__prg_rom_109_offset = 0xda000;
__prg_rom_110_offset = 0xdc000;
__prg_rom_111_offset = 0xde000;
__prg_rom_112_offset = 0xe0000;
__prg_rom_113_offset = 0xe2000;
__prg_rom_114_offset = 0xe4000;
__prg_rom_115_offset = 0xe6000;
__prg_rom_116_offset = 0xe8000;
__prg_rom_117_offset = 0xea000;
__prg_rom_118_offset = 0xec000;
__prg_rom_119_offset = 0xee000;
__prg_rom_120_offset = 0xf0000;
__prg_rom_121_offset = 0xf2000;
__prg_rom_122_offset = 0xf4000;
__prg_rom_123_offset = 0xf6000;
__prg_rom_124_offset = 0xf8000;

MEMORY {
  prg_rom_0     : ORIGIN = __prg_rom_0_lma,  LENGTH = 0x2000
  prg_rom_1     : ORIGIN = __prg_rom_1_lma,  LENGTH = 0x2000
  prg_rom_2     : ORIGIN = __prg_rom_2_lma,  LENGTH = 0x2000
  prg_rom_3     : ORIGIN = __prg_rom_3_lma,  LENGTH = 0x2000
  prg_rom_4     : ORIGIN = __prg_rom_4_lma,  LENGTH = 0x2000
  prg_rom_5     : ORIGIN = __prg_rom_5_lma,
                  /* The fixed region may take either two or three banks. */
                  LENGTH =
                    __prg_rom_size >= 128 || __prg_rom_total_fixed_size == 0x4000 ? 0x2000 : 0
  prg_rom_6     : ORIGIN = __prg_rom_6_lma,  LENGTH = __prg_rom_size >= 128  ? 0x2000 : 0
  prg_rom_7     : ORIGIN = __prg_rom_7_lma,  LENGTH = __prg_rom_size >= 128 ? 0x2000 : 0
  prg_rom_8     : ORIGIN = __prg_rom_8_lma,  LENGTH = __prg_rom_size >= 128 ? 0x2000 : 0
  prg_rom_9     : ORIGIN = __prg_rom_9_lma,  LENGTH = __prg_rom_size >= 128 ? 0x2000 : 0
  prg_rom_10    : ORIGIN = __prg_rom_10_lma, LENGTH = __prg_rom_size >= 128 ? 0x2000 : 0
  prg_rom_11    : ORIGIN = __prg_rom_11_lma, LENGTH = __prg_rom_size >= 128 ? 0x2000 : 0
  prg_rom_12    : ORIGIN = __prg_rom_12_lma, LENGTH = __prg_rom_size >= 128 ? 0x2000 : 0
  prg_rom_13    : ORIGIN = __prg_rom_13_lma,
                  LENGTH = (__prg_rom_size >= 128 &&
                             (__prg_rom_size >= 256 ||
                              __prg_rom_total_fixed_size == 0x4000)) ? 0x2000 : 0
  prg_rom_14    : ORIGIN = __prg_rom_14_lma, LENGTH = __prg_rom_size >= 256 ? 0x2000 : 0
  prg_rom_15    : ORIGIN = __prg_rom_15_lma, LENGTH = __prg_rom_size >= 256 ? 0x2000 : 0
  prg_rom_16    : ORIGIN = __prg_rom_16_lma, LENGTH = __prg_rom_size >= 256 ? 0x2000 : 0
  prg_rom_17    : ORIGIN = __prg_rom_17_lma, LENGTH = __prg_rom_size >= 256 ? 0x2000 : 0
  prg_rom_18    : ORIGIN = __prg_rom_18_lma, LENGTH = __prg_rom_size >= 256 ? 0x2000 : 0
  prg_rom_19    : ORIGIN = __prg_rom_19_lma, LENGTH = __prg_rom_size >= 256 ? 0x2000 : 0
  prg_rom_20    : ORIGIN = __prg_rom_20_lma, LENGTH = __prg_rom_size >= 256 ? 0x2000 : 0
  prg_rom_21    : ORIGIN = __prg_rom_21_lma, LENGTH = __prg_rom_size >= 256 ? 0x2000 : 0
  prg_rom_22    : ORIGIN = __prg_rom_22_lma, LENGTH = __prg_rom_size >= 256 ? 0x2000 : 0
  prg_rom_23    : ORIGIN = __prg_rom_23_lma, LENGTH = __prg_rom_size >= 256 ? 0x2000 : 0
  prg_rom_24    : ORIGIN = __prg_rom_24_lma, LENGTH = __prg_rom_size >= 256 ? 0x2000 : 0
  prg_rom_25    : ORIGIN = __prg_rom_25_lma, LENGTH = __prg_rom_size >= 256 ? 0x2000 : 0
  prg_rom_26    : ORIGIN = __prg_rom_26_lma, LENGTH = __prg_rom_size >= 256 ? 0x2000 : 0
  prg_rom_27    : ORIGIN = __prg_rom_27_lma, LENGTH = __prg_rom_size >= 256 ? 0x2000 : 0
  prg_rom_28    : ORIGIN = __prg_rom_28_lma, LENGTH = __prg_rom_size >= 256 ? 0x2000 : 0
  prg_rom_29    : ORIGIN = __prg_rom_29_lma,
                  LENGTH = (__prg_rom_size >= 256 &&
                             (__prg_rom_size >= 512 ||
                              __prg_rom_total_fixed_size == 0x4000)) ? 0x2000 : 0
  prg_rom_30    : ORIGIN = __prg_rom_30_lma, LENGTH = __prg_rom_size >= 512 ? 0x2000 : 0
  prg_rom_31    : ORIGIN = __prg_rom_31_lma, LENGTH = __prg_rom_size >= 512 ? 0x2000 : 0
  prg_rom_32    : ORIGIN = __prg_rom_32_lma, LENGTH = __prg_rom_size >= 512 ? 0x2000 : 0
  prg_rom_33    : ORIGIN = __prg_rom_33_lma, LENGTH = __prg_rom_size >= 512 ? 0x2000 : 0
  prg_rom_34    : ORIGIN = __prg_rom_34_lma, LENGTH = __prg_rom_size >= 512 ? 0x2000 : 0
  prg_rom_35    : ORIGIN = __prg_rom_35_lma, LENGTH = __prg_rom_size >= 512 ? 0x2000 : 0
  prg_rom_36    : ORIGIN = __prg_rom_36_lma, LENGTH = __prg_rom_size >= 512 ? 0x2000 : 0
  prg_rom_37    : ORIGIN = __prg_rom_37_lma, LENGTH = __prg_rom_size >= 512 ? 0x2000 : 0
  prg_rom_38    : ORIGIN = __prg_rom_38_lma, LENGTH = __prg_rom_size >= 512 ? 0x2000 : 0
  prg_rom_39    : ORIGIN = __prg_rom_39_lma, LENGTH = __prg_rom_size >= 512 ? 0x2000 : 0
  prg_rom_40    : ORIGIN = __prg_rom_40_lma, LENGTH = __prg_rom_size >= 512 ? 0x2000 : 0
  prg_rom_41    : ORIGIN = __prg_rom_41_lma, LENGTH = __prg_rom_size >= 512 ? 0x2000 : 0
  prg_rom_42    : ORIGIN = __prg_rom_42_lma, LENGTH = __prg_rom_size >= 512 ? 0x2000 : 0
  prg_rom_43    : ORIGIN = __prg_rom_43_lma, LENGTH = __prg_rom_size >= 512 ? 0x2000 : 0
  prg_rom_44    : ORIGIN = __prg_rom_44_lma, LENGTH = __prg_rom_size >= 512 ? 0x2000 : 0
  prg_rom_45    : ORIGIN = __prg_rom_45_lma, LENGTH = __prg_rom_size >= 512 ? 0x2000 : 0
  prg_rom_46    : ORIGIN = __prg_rom_46_lma, LENGTH = __prg_rom_size >= 512 ? 0x2000 : 0
  prg_rom_47    : ORIGIN = __prg_rom_47_lma, LENGTH = __prg_rom_size >= 512 ? 0x2000 : 0
  prg_rom_48    : ORIGIN = __prg_rom_48_lma, LENGTH = __prg_rom_size >= 512 ? 0x2000 : 0
  prg_rom_49    : ORIGIN = __prg_rom_49_lma, LENGTH = __prg_rom_size >= 512 ? 0x2000 : 0
  prg_rom_50    : ORIGIN = __prg_rom_50_lma, LENGTH = __prg_rom_size >= 512 ? 0x2000 : 0
  prg_rom_51    : ORIGIN = __prg_rom_51_lma, LENGTH = __prg_rom_size >= 512 ? 0x2000 : 0
  prg_rom_52    : ORIGIN = __prg_rom_52_lma, LENGTH = __prg_rom_size >= 512 ? 0x2000 : 0
  prg_rom_53    : ORIGIN = __prg_rom_53_lma, LENGTH = __prg_rom_size >= 512 ? 0x2000 : 0
  prg_rom_54    : ORIGIN = __prg_rom_54_lma, LENGTH = __prg_rom_size >= 512 ? 0x2000 : 0
  prg_rom_55    : ORIGIN = __prg_rom_55_lma, LENGTH = __prg_rom_size >= 512 ? 0x2000 : 0
  prg_rom_56    : ORIGIN = __prg_rom_56_lma, LENGTH = __prg_rom_size >= 512 ? 0x2000 : 0
  prg_rom_57    : ORIGIN = __prg_rom_57_lma, LENGTH = __prg_rom_size >= 512 ? 0x2000 : 0
  prg_rom_58    : ORIGIN = __prg_rom_58_lma, LENGTH = __prg_rom_size >= 512 ? 0x2000 : 0
  prg_rom_59    : ORIGIN = __prg_rom_59_lma, LENGTH = __prg_rom_size >= 512 ? 0x2000 : 0
  prg_rom_60    : ORIGIN = __prg_rom_60_lma, LENGTH = __prg_rom_size >= 512 ? 0x2000 : 0
  prg_rom_61    : ORIGIN = __prg_rom_61_lma,
                  LENGTH = (__prg_rom_size >= 512 &&
                             (__prg_rom_size >= 1024 ||
                              __prg_rom_total_fixed_size == 0x4000)) ? 0x2000 : 0
  prg_rom_62    : ORIGIN = __prg_rom_62_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_63    : ORIGIN = __prg_rom_63_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_64    : ORIGIN = __prg_rom_64_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_65    : ORIGIN = __prg_rom_65_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_66    : ORIGIN = __prg_rom_66_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_67    : ORIGIN = __prg_rom_67_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_68    : ORIGIN = __prg_rom_68_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_69    : ORIGIN = __prg_rom_69_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_70    : ORIGIN = __prg_rom_70_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_71    : ORIGIN = __prg_rom_71_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_72    : ORIGIN = __prg_rom_72_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_73    : ORIGIN = __prg_rom_73_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_74    : ORIGIN = __prg_rom_74_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_75    : ORIGIN = __prg_rom_75_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_76    : ORIGIN = __prg_rom_76_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_77    : ORIGIN = __prg_rom_77_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_78    : ORIGIN = __prg_rom_78_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_79    : ORIGIN = __prg_rom_79_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_80    : ORIGIN = __prg_rom_80_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_81    : ORIGIN = __prg_rom_81_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_82    : ORIGIN = __prg_rom_82_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_83    : ORIGIN = __prg_rom_83_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_84    : ORIGIN = __prg_rom_84_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_85    : ORIGIN = __prg_rom_85_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_86    : ORIGIN = __prg_rom_86_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_87    : ORIGIN = __prg_rom_87_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_88    : ORIGIN = __prg_rom_88_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_89    : ORIGIN = __prg_rom_89_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_90    : ORIGIN = __prg_rom_90_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_91    : ORIGIN = __prg_rom_91_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_92    : ORIGIN = __prg_rom_92_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_93    : ORIGIN = __prg_rom_93_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_94    : ORIGIN = __prg_rom_94_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_95    : ORIGIN = __prg_rom_95_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_96    : ORIGIN = __prg_rom_96_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_97    : ORIGIN = __prg_rom_97_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_98    : ORIGIN = __prg_rom_98_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_99    : ORIGIN = __prg_rom_99_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_100    : ORIGIN = __prg_rom_100_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_101    : ORIGIN = __prg_rom_101_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_102    : ORIGIN = __prg_rom_102_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_103    : ORIGIN = __prg_rom_103_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_104    : ORIGIN = __prg_rom_104_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_105    : ORIGIN = __prg_rom_105_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_106    : ORIGIN = __prg_rom_106_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_107    : ORIGIN = __prg_rom_107_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_108    : ORIGIN = __prg_rom_108_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_109    : ORIGIN = __prg_rom_109_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_110    : ORIGIN = __prg_rom_110_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_111    : ORIGIN = __prg_rom_111_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_112    : ORIGIN = __prg_rom_112_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_113    : ORIGIN = __prg_rom_113_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_114    : ORIGIN = __prg_rom_114_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_115    : ORIGIN = __prg_rom_115_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_116    : ORIGIN = __prg_rom_116_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_117    : ORIGIN = __prg_rom_117_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_118    : ORIGIN = __prg_rom_118_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_119    : ORIGIN = __prg_rom_119_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_120    : ORIGIN = __prg_rom_120_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_121    : ORIGIN = __prg_rom_121_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_122    : ORIGIN = __prg_rom_122_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_123    : ORIGIN = __prg_rom_123_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
  prg_rom_124    : ORIGIN = __prg_rom_124_lma, LENGTH = __prg_rom_size >= 1024 ? 0x2000 : 0
}

SECTIONS {
  .prg_rom_0     : { *(.prg_rom_0     .prg_rom_0.*)     } >prg_rom_0
  .prg_rom_1     : { *(.prg_rom_1     .prg_rom_1.*)     } >prg_rom_1
  .prg_rom_2     : { *(.prg_rom_2     .prg_rom_2.*)     } >prg_rom_2
  .prg_rom_3     : { *(.prg_rom_3     .prg_rom_3.*)     } >prg_rom_3
  .prg_rom_4     : { *(.prg_rom_4     .prg_rom_4.*)     } >prg_rom_4
  .prg_rom_5     : { *(.prg_rom_5     .prg_rom_5.*)     } >prg_rom_5
  .prg_rom_6     : { *(.prg_rom_6     .prg_rom_6.*)     } >prg_rom_6
  .prg_rom_7     : { *(.prg_rom_7     .prg_rom_7.*)     } >prg_rom_7
  .prg_rom_8     : { *(.prg_rom_8     .prg_rom_8.*)     } >prg_rom_8
  .prg_rom_9     : { *(.prg_rom_9     .prg_rom_9.*)     } >prg_rom_9
  .prg_rom_10    : { *(.prg_rom_10    .prg_rom_10.*)    } >prg_rom_10
  .prg_rom_11    : { *(.prg_rom_11    .prg_rom_11.*)    } >prg_rom_11
  .prg_rom_12    : { *(.prg_rom_12    .prg_rom_12.*)    } >prg_rom_12
  .prg_rom_13    : { *(.prg_rom_13    .prg_rom_13.*)    } >prg_rom_13
  .prg_rom_14    : { *(.prg_rom_14    .prg_rom_14.*)    } >prg_rom_14
  .prg_rom_15    : { *(.prg_rom_15    .prg_rom_15.*)    } >prg_rom_15
  .prg_rom_16    : { *(.prg_rom_16    .prg_rom_16.*)    } >prg_rom_16
  .prg_rom_17    : { *(.prg_rom_17    .prg_rom_17.*)    } >prg_rom_17
  .prg_rom_18    : { *(.prg_rom_18    .prg_rom_18.*)    } >prg_rom_18
  .prg_rom_19    : { *(.prg_rom_19    .prg_rom_19.*)    } >prg_rom_19
  .prg_rom_20    : { *(.prg_rom_20    .prg_rom_20.*)    } >prg_rom_20
  .prg_rom_21    : { *(.prg_rom_21    .prg_rom_21.*)    } >prg_rom_21
  .prg_rom_22    : { *(.prg_rom_22    .prg_rom_22.*)    } >prg_rom_22
  .prg_rom_23    : { *(.prg_rom_23    .prg_rom_23.*)    } >prg_rom_23
  .prg_rom_24    : { *(.prg_rom_24    .prg_rom_24.*)    } >prg_rom_24
  .prg_rom_25    : { *(.prg_rom_25    .prg_rom_25.*)    } >prg_rom_25
  .prg_rom_26    : { *(.prg_rom_26    .prg_rom_26.*)    } >prg_rom_26
  .prg_rom_27    : { *(.prg_rom_27    .prg_rom_27.*)    } >prg_rom_27
  .prg_rom_28    : { *(.prg_rom_28    .prg_rom_28.*)    } >prg_rom_28
  .prg_rom_29    : { *(.prg_rom_29    .prg_rom_29.*)    } >prg_rom_29
  .prg_rom_30    : { *(.prg_rom_30    .prg_rom_30.*)    } >prg_rom_30
  .prg_rom_31    : { *(.prg_rom_31    .prg_rom_31.*)    } >prg_rom_31
  .prg_rom_32    : { *(.prg_rom_32    .prg_rom_32.*)    } >prg_rom_32
  .prg_rom_33    : { *(.prg_rom_33    .prg_rom_33.*)    } >prg_rom_33
  .prg_rom_34    : { *(.prg_rom_34    .prg_rom_34.*)    } >prg_rom_34
  .prg_rom_35    : { *(.prg_rom_35    .prg_rom_35.*)    } >prg_rom_35
  .prg_rom_36    : { *(.prg_rom_36    .prg_rom_36.*)    } >prg_rom_36
  .prg_rom_37    : { *(.prg_rom_37    .prg_rom_37.*)    } >prg_rom_37
  .prg_rom_38    : { *(.prg_rom_38    .prg_rom_38.*)    } >prg_rom_38
  .prg_rom_39    : { *(.prg_rom_39    .prg_rom_39.*)    } >prg_rom_39
  .prg_rom_40    : { *(.prg_rom_40    .prg_rom_40.*)    } >prg_rom_40
  .prg_rom_41    : { *(.prg_rom_41    .prg_rom_41.*)    } >prg_rom_41
  .prg_rom_42    : { *(.prg_rom_42    .prg_rom_42.*)    } >prg_rom_42
  .prg_rom_43    : { *(.prg_rom_43    .prg_rom_43.*)    } >prg_rom_43
  .prg_rom_44    : { *(.prg_rom_44    .prg_rom_44.*)    } >prg_rom_44
  .prg_rom_45    : { *(.prg_rom_45    .prg_rom_45.*)    } >prg_rom_45
  .prg_rom_46    : { *(.prg_rom_46    .prg_rom_46.*)    } >prg_rom_46
  .prg_rom_47    : { *(.prg_rom_47    .prg_rom_47.*)    } >prg_rom_47
  .prg_rom_48    : { *(.prg_rom_48    .prg_rom_48.*)    } >prg_rom_48
  .prg_rom_49    : { *(.prg_rom_49    .prg_rom_49.*)    } >prg_rom_49
  .prg_rom_50    : { *(.prg_rom_50    .prg_rom_50.*)    } >prg_rom_50
  .prg_rom_51    : { *(.prg_rom_51    .prg_rom_51.*)    } >prg_rom_51
  .prg_rom_52    : { *(.prg_rom_52    .prg_rom_52.*)    } >prg_rom_52
  .prg_rom_53    : { *(.prg_rom_53    .prg_rom_53.*)    } >prg_rom_53
  .prg_rom_54    : { *(.prg_rom_54    .prg_rom_54.*)    } >prg_rom_54
  .prg_rom_55    : { *(.prg_rom_55    .prg_rom_55.*)    } >prg_rom_55
  .prg_rom_56    : { *(.prg_rom_56    .prg_rom_56.*)    } >prg_rom_56
  .prg_rom_57    : { *(.prg_rom_57    .prg_rom_57.*)    } >prg_rom_57
  .prg_rom_58    : { *(.prg_rom_58    .prg_rom_58.*)    } >prg_rom_58
  .prg_rom_59    : { *(.prg_rom_59    .prg_rom_59.*)    } >prg_rom_59
  .prg_rom_60    : { *(.prg_rom_60    .prg_rom_60.*)    } >prg_rom_60
  .prg_rom_61    : { *(.prg_rom_61    .prg_rom_61.*)    } >prg_rom_61
  .prg_rom_62    : { *(.prg_rom_62    .prg_rom_62.*)    } >prg_rom_62
  .prg_rom_63    : { *(.prg_rom_63    .prg_rom_63.*)    } >prg_rom_63
  .prg_rom_64    : { *(.prg_rom_64    .prg_rom_64.*)    } >prg_rom_64
  .prg_rom_65    : { *(.prg_rom_65    .prg_rom_65.*)    } >prg_rom_65
  .prg_rom_66    : { *(.prg_rom_66    .prg_rom_66.*)    } >prg_rom_66
  .prg_rom_67    : { *(.prg_rom_67    .prg_rom_67.*)    } >prg_rom_67
  .prg_rom_68    : { *(.prg_rom_68    .prg_rom_68.*)    } >prg_rom_68
  .prg_rom_69    : { *(.prg_rom_69    .prg_rom_69.*)    } >prg_rom_69
  .prg_rom_70    : { *(.prg_rom_70    .prg_rom_70.*)    } >prg_rom_70
  .prg_rom_71    : { *(.prg_rom_71    .prg_rom_71.*)    } >prg_rom_71
  .prg_rom_72    : { *(.prg_rom_72    .prg_rom_72.*)    } >prg_rom_72
  .prg_rom_73    : { *(.prg_rom_73    .prg_rom_73.*)    } >prg_rom_73
  .prg_rom_74    : { *(.prg_rom_74    .prg_rom_74.*)    } >prg_rom_74
  .prg_rom_75    : { *(.prg_rom_75    .prg_rom_75.*)    } >prg_rom_75
  .prg_rom_76    : { *(.prg_rom_76    .prg_rom_76.*)    } >prg_rom_76
  .prg_rom_77    : { *(.prg_rom_77    .prg_rom_77.*)    } >prg_rom_77
  .prg_rom_78    : { *(.prg_rom_78    .prg_rom_78.*)    } >prg_rom_78
  .prg_rom_79    : { *(.prg_rom_79    .prg_rom_79.*)    } >prg_rom_79
  .prg_rom_80    : { *(.prg_rom_80    .prg_rom_80.*)    } >prg_rom_80
  .prg_rom_81    : { *(.prg_rom_81    .prg_rom_81.*)    } >prg_rom_81
  .prg_rom_82    : { *(.prg_rom_82    .prg_rom_82.*)    } >prg_rom_82
  .prg_rom_83    : { *(.prg_rom_83    .prg_rom_83.*)    } >prg_rom_83
  .prg_rom_84    : { *(.prg_rom_84    .prg_rom_84.*)    } >prg_rom_84
  .prg_rom_85    : { *(.prg_rom_85    .prg_rom_85.*)    } >prg_rom_85
  .prg_rom_86    : { *(.prg_rom_86    .prg_rom_86.*)    } >prg_rom_86
  .prg_rom_87    : { *(.prg_rom_87    .prg_rom_87.*)    } >prg_rom_87
  .prg_rom_88    : { *(.prg_rom_88    .prg_rom_88.*)    } >prg_rom_88
  .prg_rom_89    : { *(.prg_rom_89    .prg_rom_89.*)    } >prg_rom_89
  .prg_rom_90    : { *(.prg_rom_90    .prg_rom_90.*)    } >prg_rom_90
  .prg_rom_91    : { *(.prg_rom_91    .prg_rom_91.*)    } >prg_rom_91
  .prg_rom_92    : { *(.prg_rom_92    .prg_rom_92.*)    } >prg_rom_92
  .prg_rom_93    : { *(.prg_rom_93    .prg_rom_93.*)    } >prg_rom_93
  .prg_rom_94    : { *(.prg_rom_94    .prg_rom_94.*)    } >prg_rom_94
  .prg_rom_95    : { *(.prg_rom_95    .prg_rom_95.*)    } >prg_rom_95
  .prg_rom_96    : { *(.prg_rom_96    .prg_rom_96.*)    } >prg_rom_96
  .prg_rom_97    : { *(.prg_rom_97    .prg_rom_97.*)    } >prg_rom_97
  .prg_rom_98    : { *(.prg_rom_98    .prg_rom_98.*)    } >prg_rom_98
  .prg_rom_99    : { *(.prg_rom_99    .prg_rom_99.*)    } >prg_rom_99
  .prg_rom_100    : { *(.prg_rom_100    .prg_rom_100.*)    } >prg_rom_100
  .prg_rom_101    : { *(.prg_rom_101    .prg_rom_101.*)    } >prg_rom_101
  .prg_rom_102    : { *(.prg_rom_102    .prg_rom_102.*)    } >prg_rom_102
  .prg_rom_103    : { *(.prg_rom_103    .prg_rom_103.*)    } >prg_rom_103
  .prg_rom_104    : { *(.prg_rom_104    .prg_rom_104.*)    } >prg_rom_104
  .prg_rom_105    : { *(.prg_rom_105    .prg_rom_105.*)    } >prg_rom_105
  .prg_rom_106    : { *(.prg_rom_106    .prg_rom_106.*)    } >prg_rom_106
  .prg_rom_107    : { *(.prg_rom_107    .prg_rom_107.*)    } >prg_rom_107
  .prg_rom_108    : { *(.prg_rom_108    .prg_rom_108.*)    } >prg_rom_108
  .prg_rom_109    : { *(.prg_rom_109    .prg_rom_109.*)    } >prg_rom_109
  .prg_rom_110    : { *(.prg_rom_110    .prg_rom_110.*)    } >prg_rom_110
  .prg_rom_111    : { *(.prg_rom_111    .prg_rom_111.*)    } >prg_rom_111
  .prg_rom_112    : { *(.prg_rom_112    .prg_rom_112.*)    } >prg_rom_112
  .prg_rom_113    : { *(.prg_rom_113    .prg_rom_113.*)    } >prg_rom_113
  .prg_rom_114    : { *(.prg_rom_114    .prg_rom_114.*)    } >prg_rom_114
  .prg_rom_115    : { *(.prg_rom_115    .prg_rom_115.*)    } >prg_rom_115
  .prg_rom_116    : { *(.prg_rom_116    .prg_rom_116.*)    } >prg_rom_116
  .prg_rom_117    : { *(.prg_rom_117    .prg_rom_117.*)    } >prg_rom_117
  .prg_rom_118    : { *(.prg_rom_118    .prg_rom_118.*)    } >prg_rom_118
  .prg_rom_119    : { *(.prg_rom_119    .prg_rom_119.*)    } >prg_rom_119
  .prg_rom_120    : { *(.prg_rom_120    .prg_rom_120.*)    } >prg_rom_120
  .prg_rom_121    : { *(.prg_rom_121    .prg_rom_121.*)    } >prg_rom_121
  .prg_rom_122    : { *(.prg_rom_122    .prg_rom_122.*)    } >prg_rom_122
  .prg_rom_123    : { *(.prg_rom_123    .prg_rom_123.*)    } >prg_rom_123
  .prg_rom_124    : { *(.prg_rom_124    .prg_rom_124.*)    } >prg_rom_124
  .prg_rom_fixed : { *(.prg_rom_fixed .prg_rom_fixed.*) } >prg_rom_fixed
}
