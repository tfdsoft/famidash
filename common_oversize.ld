/* NES-MMC3 iNES file linker script. */

INCLUDE nes.ld

ASSERT(__prg_ram_size + __prg_nvram_size <= 8,
       "MMC3 only supports up to 8KiB of PRG-(NV)RAM.")
ASSERT(__prg_rom_size <= 1024, "MMC3 Oversize only supports up to 1MiB of PRG-ROM.")

MEMORY {
  prg_ram : ORIGIN = 0x6000, LENGTH = (__prg_ram_size + __prg_nvram_size) * 1024

  chr_rom_0   : ORIGIN = 0x01000000, LENGTH = __chr_rom_size >= 1   ? 0x400 : 0
  chr_rom_1   : ORIGIN = 0x01000400, LENGTH = __chr_rom_size >= 2   ? 0x400 : 0
  chr_rom_2   : ORIGIN = 0x01000800, LENGTH = __chr_rom_size >= 4   ? 0x400 : 0
  chr_rom_3   : ORIGIN = 0x01000c00, LENGTH = __chr_rom_size >= 4   ? 0x400 : 0
  chr_rom_4   : ORIGIN = 0x01001000, LENGTH = __chr_rom_size >= 8   ? 0x400 : 0
  chr_rom_5   : ORIGIN = 0x01001400, LENGTH = __chr_rom_size >= 8   ? 0x400 : 0
  chr_rom_6   : ORIGIN = 0x01001800, LENGTH = __chr_rom_size >= 8   ? 0x400 : 0
  chr_rom_7   : ORIGIN = 0x01001c00, LENGTH = __chr_rom_size >= 8   ? 0x400 : 0
  chr_rom_8   : ORIGIN = 0x01002000, LENGTH = __chr_rom_size >= 16  ? 0x400 : 0
  chr_rom_9   : ORIGIN = 0x01002400, LENGTH = __chr_rom_size >= 16  ? 0x400 : 0
  chr_rom_10  : ORIGIN = 0x01002800, LENGTH = __chr_rom_size >= 16  ? 0x400 : 0
  chr_rom_11  : ORIGIN = 0x01002c00, LENGTH = __chr_rom_size >= 16  ? 0x400 : 0
  chr_rom_12  : ORIGIN = 0x01003000, LENGTH = __chr_rom_size >= 16  ? 0x400 : 0
  chr_rom_13  : ORIGIN = 0x01003400, LENGTH = __chr_rom_size >= 16  ? 0x400 : 0
  chr_rom_14  : ORIGIN = 0x01003800, LENGTH = __chr_rom_size >= 16  ? 0x400 : 0
  chr_rom_15  : ORIGIN = 0x01003c00, LENGTH = __chr_rom_size >= 16  ? 0x400 : 0
  chr_rom_16  : ORIGIN = 0x01004000, LENGTH = __chr_rom_size >= 32  ? 0x400 : 0
  chr_rom_17  : ORIGIN = 0x01004400, LENGTH = __chr_rom_size >= 32  ? 0x400 : 0
  chr_rom_18  : ORIGIN = 0x01004800, LENGTH = __chr_rom_size >= 32  ? 0x400 : 0
  chr_rom_19  : ORIGIN = 0x01004c00, LENGTH = __chr_rom_size >= 32  ? 0x400 : 0
  chr_rom_20  : ORIGIN = 0x01005000, LENGTH = __chr_rom_size >= 32  ? 0x400 : 0
  chr_rom_21  : ORIGIN = 0x01005400, LENGTH = __chr_rom_size >= 32  ? 0x400 : 0
  chr_rom_22  : ORIGIN = 0x01005800, LENGTH = __chr_rom_size >= 32  ? 0x400 : 0
  chr_rom_23  : ORIGIN = 0x01005c00, LENGTH = __chr_rom_size >= 32  ? 0x400 : 0
  chr_rom_24  : ORIGIN = 0x01006000, LENGTH = __chr_rom_size >= 32  ? 0x400 : 0
  chr_rom_25  : ORIGIN = 0x01006400, LENGTH = __chr_rom_size >= 32  ? 0x400 : 0
  chr_rom_26  : ORIGIN = 0x01006800, LENGTH = __chr_rom_size >= 32  ? 0x400 : 0
  chr_rom_27  : ORIGIN = 0x01006c00, LENGTH = __chr_rom_size >= 32  ? 0x400 : 0
  chr_rom_28  : ORIGIN = 0x01007000, LENGTH = __chr_rom_size >= 32  ? 0x400 : 0
  chr_rom_29  : ORIGIN = 0x01007400, LENGTH = __chr_rom_size >= 32  ? 0x400 : 0
  chr_rom_30  : ORIGIN = 0x01007800, LENGTH = __chr_rom_size >= 32  ? 0x400 : 0
  chr_rom_31  : ORIGIN = 0x01007c00, LENGTH = __chr_rom_size >= 32  ? 0x400 : 0
  chr_rom_32  : ORIGIN = 0x01008000, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_33  : ORIGIN = 0x01008400, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_34  : ORIGIN = 0x01008800, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_35  : ORIGIN = 0x01008c00, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_36  : ORIGIN = 0x01009000, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_37  : ORIGIN = 0x01009400, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_38  : ORIGIN = 0x01009800, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_39  : ORIGIN = 0x01009c00, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_40  : ORIGIN = 0x0100a000, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_41  : ORIGIN = 0x0100a400, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_42  : ORIGIN = 0x0100a800, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_43  : ORIGIN = 0x0100ac00, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_44  : ORIGIN = 0x0100b000, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_45  : ORIGIN = 0x0100b400, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_46  : ORIGIN = 0x0100b800, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_47  : ORIGIN = 0x0100bc00, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_48  : ORIGIN = 0x0100c000, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_49  : ORIGIN = 0x0100c400, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_50  : ORIGIN = 0x0100c800, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_51  : ORIGIN = 0x0100cc00, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_52  : ORIGIN = 0x0100d000, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_53  : ORIGIN = 0x0100d400, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_54  : ORIGIN = 0x0100d800, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_55  : ORIGIN = 0x0100dc00, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_56  : ORIGIN = 0x0100e000, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_57  : ORIGIN = 0x0100e400, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_58  : ORIGIN = 0x0100e800, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_59  : ORIGIN = 0x0100ec00, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_60  : ORIGIN = 0x0100f000, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_61  : ORIGIN = 0x0100f400, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_62  : ORIGIN = 0x0100f800, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_63  : ORIGIN = 0x0100fc00, LENGTH = __chr_rom_size >= 64  ? 0x400 : 0
  chr_rom_64  : ORIGIN = 0x01010000, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_65  : ORIGIN = 0x01010400, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_66  : ORIGIN = 0x01010800, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_67  : ORIGIN = 0x01010c00, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_68  : ORIGIN = 0x01011000, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_69  : ORIGIN = 0x01011400, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_70  : ORIGIN = 0x01011800, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_71  : ORIGIN = 0x01011c00, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_72  : ORIGIN = 0x01012000, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_73  : ORIGIN = 0x01012400, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_74  : ORIGIN = 0x01012800, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_75  : ORIGIN = 0x01012c00, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_76  : ORIGIN = 0x01013000, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_77  : ORIGIN = 0x01013400, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_78  : ORIGIN = 0x01013800, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_79  : ORIGIN = 0x01013c00, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_80  : ORIGIN = 0x01014000, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_81  : ORIGIN = 0x01014400, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_82  : ORIGIN = 0x01014800, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_83  : ORIGIN = 0x01014c00, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_84  : ORIGIN = 0x01015000, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_85  : ORIGIN = 0x01015400, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_86  : ORIGIN = 0x01015800, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_87  : ORIGIN = 0x01015c00, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_88  : ORIGIN = 0x01016000, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_89  : ORIGIN = 0x01016400, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_90  : ORIGIN = 0x01016800, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_91  : ORIGIN = 0x01016c00, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_92  : ORIGIN = 0x01017000, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_93  : ORIGIN = 0x01017400, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_94  : ORIGIN = 0x01017800, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_95  : ORIGIN = 0x01017c00, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_96  : ORIGIN = 0x01018000, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_97  : ORIGIN = 0x01018400, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_98  : ORIGIN = 0x01018800, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_99  : ORIGIN = 0x01018c00, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_100 : ORIGIN = 0x01019000, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_101 : ORIGIN = 0x01019400, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_102 : ORIGIN = 0x01019800, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_103 : ORIGIN = 0x01019c00, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_104 : ORIGIN = 0x0101a000, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_105 : ORIGIN = 0x0101a400, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_106 : ORIGIN = 0x0101a800, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_107 : ORIGIN = 0x0101ac00, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_108 : ORIGIN = 0x0101b000, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_109 : ORIGIN = 0x0101b400, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_110 : ORIGIN = 0x0101b800, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_111 : ORIGIN = 0x0101bc00, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_112 : ORIGIN = 0x0101c000, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_113 : ORIGIN = 0x0101c400, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_114 : ORIGIN = 0x0101c800, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_115 : ORIGIN = 0x0101cc00, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_116 : ORIGIN = 0x0101d000, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_117 : ORIGIN = 0x0101d400, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_118 : ORIGIN = 0x0101d800, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_119 : ORIGIN = 0x0101dc00, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_120 : ORIGIN = 0x0101e000, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_121 : ORIGIN = 0x0101e400, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_122 : ORIGIN = 0x0101e800, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_123 : ORIGIN = 0x0101ec00, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_124 : ORIGIN = 0x0101f000, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_125 : ORIGIN = 0x0101f400, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_126 : ORIGIN = 0x0101f800, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_127 : ORIGIN = 0x0101fc00, LENGTH = __chr_rom_size >= 128 ? 0x400 : 0
  chr_rom_128 : ORIGIN = 0x01020000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_129 : ORIGIN = 0x01020400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_130 : ORIGIN = 0x01020800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_131 : ORIGIN = 0x01020c00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_132 : ORIGIN = 0x01021000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_133 : ORIGIN = 0x01021400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_134 : ORIGIN = 0x01021800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_135 : ORIGIN = 0x01021c00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_136 : ORIGIN = 0x01022000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_137 : ORIGIN = 0x01022400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_138 : ORIGIN = 0x01022800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_139 : ORIGIN = 0x01022c00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_140 : ORIGIN = 0x01023000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_141 : ORIGIN = 0x01023400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_142 : ORIGIN = 0x01023800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_143 : ORIGIN = 0x01023c00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_144 : ORIGIN = 0x01024000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_145 : ORIGIN = 0x01024400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_146 : ORIGIN = 0x01024800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_147 : ORIGIN = 0x01024c00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_148 : ORIGIN = 0x01025000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_149 : ORIGIN = 0x01025400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_150 : ORIGIN = 0x01025800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_151 : ORIGIN = 0x01025c00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_152 : ORIGIN = 0x01026000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_153 : ORIGIN = 0x01026400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_154 : ORIGIN = 0x01026800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_155 : ORIGIN = 0x01026c00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_156 : ORIGIN = 0x01027000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_157 : ORIGIN = 0x01027400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_158 : ORIGIN = 0x01027800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_159 : ORIGIN = 0x01027c00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_160 : ORIGIN = 0x01028000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_161 : ORIGIN = 0x01028400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_162 : ORIGIN = 0x01028800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_163 : ORIGIN = 0x01028c00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_164 : ORIGIN = 0x01029000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_165 : ORIGIN = 0x01029400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_166 : ORIGIN = 0x01029800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_167 : ORIGIN = 0x01029c00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_168 : ORIGIN = 0x0102a000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_169 : ORIGIN = 0x0102a400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_170 : ORIGIN = 0x0102a800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_171 : ORIGIN = 0x0102ac00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_172 : ORIGIN = 0x0102b000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_173 : ORIGIN = 0x0102b400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_174 : ORIGIN = 0x0102b800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_175 : ORIGIN = 0x0102bc00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_176 : ORIGIN = 0x0102c000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_177 : ORIGIN = 0x0102c400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_178 : ORIGIN = 0x0102c800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_179 : ORIGIN = 0x0102cc00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_180 : ORIGIN = 0x0102d000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_181 : ORIGIN = 0x0102d400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_182 : ORIGIN = 0x0102d800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_183 : ORIGIN = 0x0102dc00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_184 : ORIGIN = 0x0102e000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_185 : ORIGIN = 0x0102e400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_186 : ORIGIN = 0x0102e800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_187 : ORIGIN = 0x0102ec00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_188 : ORIGIN = 0x0102f000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_189 : ORIGIN = 0x0102f400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_190 : ORIGIN = 0x0102f800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_191 : ORIGIN = 0x0102fc00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_192 : ORIGIN = 0x01030000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_193 : ORIGIN = 0x01030400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_194 : ORIGIN = 0x01030800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_195 : ORIGIN = 0x01030c00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_196 : ORIGIN = 0x01031000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_197 : ORIGIN = 0x01031400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_198 : ORIGIN = 0x01031800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_199 : ORIGIN = 0x01031c00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_200 : ORIGIN = 0x01032000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_201 : ORIGIN = 0x01032400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_202 : ORIGIN = 0x01032800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_203 : ORIGIN = 0x01032c00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_204 : ORIGIN = 0x01033000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_205 : ORIGIN = 0x01033400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_206 : ORIGIN = 0x01033800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_207 : ORIGIN = 0x01033c00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_208 : ORIGIN = 0x01034000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_209 : ORIGIN = 0x01034400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_210 : ORIGIN = 0x01034800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_211 : ORIGIN = 0x01034c00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_212 : ORIGIN = 0x01035000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_213 : ORIGIN = 0x01035400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_214 : ORIGIN = 0x01035800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_215 : ORIGIN = 0x01035c00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_216 : ORIGIN = 0x01036000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_217 : ORIGIN = 0x01036400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_218 : ORIGIN = 0x01036800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_219 : ORIGIN = 0x01036c00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_220 : ORIGIN = 0x01037000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_221 : ORIGIN = 0x01037400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_222 : ORIGIN = 0x01037800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_223 : ORIGIN = 0x01037c00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_224 : ORIGIN = 0x01038000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_225 : ORIGIN = 0x01038400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_226 : ORIGIN = 0x01038800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_227 : ORIGIN = 0x01038c00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_228 : ORIGIN = 0x01039000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_229 : ORIGIN = 0x01039400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_230 : ORIGIN = 0x01039800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_231 : ORIGIN = 0x01039c00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_232 : ORIGIN = 0x0103a000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_233 : ORIGIN = 0x0103a400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_234 : ORIGIN = 0x0103a800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_235 : ORIGIN = 0x0103ac00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_236 : ORIGIN = 0x0103b000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_237 : ORIGIN = 0x0103b400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_238 : ORIGIN = 0x0103b800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_239 : ORIGIN = 0x0103bc00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_240 : ORIGIN = 0x0103c000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_241 : ORIGIN = 0x0103c400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_242 : ORIGIN = 0x0103c800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_243 : ORIGIN = 0x0103cc00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_244 : ORIGIN = 0x0103d000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_245 : ORIGIN = 0x0103d400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_246 : ORIGIN = 0x0103d800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_247 : ORIGIN = 0x0103dc00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_248 : ORIGIN = 0x0103e000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_249 : ORIGIN = 0x0103e400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_250 : ORIGIN = 0x0103e800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_251 : ORIGIN = 0x0103ec00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_252 : ORIGIN = 0x0103f000, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_253 : ORIGIN = 0x0103f400, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_254 : ORIGIN = 0x0103f800, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0
  chr_rom_255 : ORIGIN = 0x0103fc00, LENGTH = __chr_rom_size >= 256 ? 0x400 : 0

  chr_rom_0_1     : ORIGIN = 0x01000000, LENGTH = __chr_rom_size >= 1   ? 0x800 : 0
  chr_rom_2_3     : ORIGIN = 0x01000800, LENGTH = __chr_rom_size >= 2   ? 0x800 : 0
  chr_rom_4_5     : ORIGIN = 0x01001000, LENGTH = __chr_rom_size >= 4   ? 0x800 : 0
  chr_rom_6_7     : ORIGIN = 0x01001800, LENGTH = __chr_rom_size >= 8   ? 0x800 : 0
  chr_rom_8_9     : ORIGIN = 0x01002000, LENGTH = __chr_rom_size >= 16  ? 0x800 : 0
  chr_rom_10_11   : ORIGIN = 0x01002800, LENGTH = __chr_rom_size >= 16  ? 0x800 : 0
  chr_rom_12_13   : ORIGIN = 0x01003000, LENGTH = __chr_rom_size >= 16  ? 0x800 : 0
  chr_rom_14_15   : ORIGIN = 0x01003800, LENGTH = __chr_rom_size >= 16  ? 0x800 : 0
  chr_rom_16_17   : ORIGIN = 0x01004000, LENGTH = __chr_rom_size >= 32  ? 0x800 : 0
  chr_rom_18_19   : ORIGIN = 0x01004800, LENGTH = __chr_rom_size >= 32  ? 0x800 : 0
  chr_rom_20_21   : ORIGIN = 0x01005000, LENGTH = __chr_rom_size >= 32  ? 0x800 : 0
  chr_rom_22_23   : ORIGIN = 0x01005800, LENGTH = __chr_rom_size >= 32  ? 0x800 : 0
  chr_rom_24_25   : ORIGIN = 0x01006000, LENGTH = __chr_rom_size >= 32  ? 0x800 : 0
  chr_rom_26_27   : ORIGIN = 0x01006800, LENGTH = __chr_rom_size >= 32  ? 0x800 : 0
  chr_rom_28_29   : ORIGIN = 0x01007000, LENGTH = __chr_rom_size >= 32  ? 0x800 : 0
  chr_rom_30_31   : ORIGIN = 0x01007800, LENGTH = __chr_rom_size >= 32  ? 0x800 : 0
  chr_rom_32_33   : ORIGIN = 0x01008000, LENGTH = __chr_rom_size >= 64  ? 0x800 : 0
  chr_rom_34_35   : ORIGIN = 0x01008800, LENGTH = __chr_rom_size >= 64  ? 0x800 : 0
  chr_rom_36_37   : ORIGIN = 0x01009000, LENGTH = __chr_rom_size >= 64  ? 0x800 : 0
  chr_rom_38_39   : ORIGIN = 0x01009800, LENGTH = __chr_rom_size >= 64  ? 0x800 : 0
  chr_rom_40_41   : ORIGIN = 0x0100a000, LENGTH = __chr_rom_size >= 64  ? 0x800 : 0
  chr_rom_42_43   : ORIGIN = 0x0100a800, LENGTH = __chr_rom_size >= 64  ? 0x800 : 0
  chr_rom_44_45   : ORIGIN = 0x0100b000, LENGTH = __chr_rom_size >= 64  ? 0x800 : 0
  chr_rom_46_47   : ORIGIN = 0x0100b800, LENGTH = __chr_rom_size >= 64  ? 0x800 : 0
  chr_rom_48_49   : ORIGIN = 0x0100c000, LENGTH = __chr_rom_size >= 64  ? 0x800 : 0
  chr_rom_50_51   : ORIGIN = 0x0100c800, LENGTH = __chr_rom_size >= 64  ? 0x800 : 0
  chr_rom_52_53   : ORIGIN = 0x0100d000, LENGTH = __chr_rom_size >= 64  ? 0x800 : 0
  chr_rom_54_55   : ORIGIN = 0x0100d800, LENGTH = __chr_rom_size >= 64  ? 0x800 : 0
  chr_rom_56_57   : ORIGIN = 0x0100e000, LENGTH = __chr_rom_size >= 64  ? 0x800 : 0
  chr_rom_58_59   : ORIGIN = 0x0100e800, LENGTH = __chr_rom_size >= 64  ? 0x800 : 0
  chr_rom_60_61   : ORIGIN = 0x0100f000, LENGTH = __chr_rom_size >= 64  ? 0x800 : 0
  chr_rom_62_63   : ORIGIN = 0x0100f800, LENGTH = __chr_rom_size >= 64  ? 0x800 : 0
  chr_rom_64_65   : ORIGIN = 0x01010000, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_66_67   : ORIGIN = 0x01010800, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_68_69   : ORIGIN = 0x01011000, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_70_71   : ORIGIN = 0x01011800, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_72_73   : ORIGIN = 0x01012000, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_74_75   : ORIGIN = 0x01012800, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_76_77   : ORIGIN = 0x01013000, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_78_79   : ORIGIN = 0x01013800, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_80_81   : ORIGIN = 0x01014000, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_82_83   : ORIGIN = 0x01014800, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_84_85   : ORIGIN = 0x01015000, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_86_87   : ORIGIN = 0x01015800, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_88_89   : ORIGIN = 0x01016000, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_90_91   : ORIGIN = 0x01016800, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_92_93   : ORIGIN = 0x01017000, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_94_95   : ORIGIN = 0x01017800, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_96_97   : ORIGIN = 0x01018000, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_98_99   : ORIGIN = 0x01018800, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_100_101 : ORIGIN = 0x01019000, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_102_103 : ORIGIN = 0x01019800, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_104_105 : ORIGIN = 0x0101a000, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_106_107 : ORIGIN = 0x0101a800, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_108_109 : ORIGIN = 0x0101b000, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_110_111 : ORIGIN = 0x0101b800, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_112_113 : ORIGIN = 0x0101c000, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_114_115 : ORIGIN = 0x0101c800, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_116_117 : ORIGIN = 0x0101d000, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_118_119 : ORIGIN = 0x0101d800, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_120_121 : ORIGIN = 0x0101e000, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_122_123 : ORIGIN = 0x0101e800, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_124_125 : ORIGIN = 0x0101f000, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_126_127 : ORIGIN = 0x0101f800, LENGTH = __chr_rom_size >= 128 ? 0x800 : 0
  chr_rom_128_129 : ORIGIN = 0x01020000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_130_131 : ORIGIN = 0x01020800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_132_133 : ORIGIN = 0x01021000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_134_135 : ORIGIN = 0x01021800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_136_137 : ORIGIN = 0x01022000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_138_139 : ORIGIN = 0x01022800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_140_141 : ORIGIN = 0x01023000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_142_143 : ORIGIN = 0x01023800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_144_145 : ORIGIN = 0x01024000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_146_147 : ORIGIN = 0x01024800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_148_149 : ORIGIN = 0x01025000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_150_151 : ORIGIN = 0x01025800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_152_153 : ORIGIN = 0x01026000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_154_155 : ORIGIN = 0x01026800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_156_157 : ORIGIN = 0x01027000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_158_159 : ORIGIN = 0x01027800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_160_161 : ORIGIN = 0x01028000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_162_163 : ORIGIN = 0x01028800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_164_165 : ORIGIN = 0x01029000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_166_167 : ORIGIN = 0x01029800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_168_169 : ORIGIN = 0x0102a000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_170_171 : ORIGIN = 0x0102a800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_172_173 : ORIGIN = 0x0102b000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_174_175 : ORIGIN = 0x0102b800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_176_177 : ORIGIN = 0x0102c000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_178_179 : ORIGIN = 0x0102c800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_180_181 : ORIGIN = 0x0102d000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_182_183 : ORIGIN = 0x0102d800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_184_185 : ORIGIN = 0x0102e000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_186_187 : ORIGIN = 0x0102e800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_188_189 : ORIGIN = 0x0102f000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_190_191 : ORIGIN = 0x0102f800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_192_193 : ORIGIN = 0x01030000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_194_195 : ORIGIN = 0x01030800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_196_197 : ORIGIN = 0x01031000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_198_199 : ORIGIN = 0x01031800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_200_201 : ORIGIN = 0x01032000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_202_203 : ORIGIN = 0x01032800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_204_205 : ORIGIN = 0x01033000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_206_207 : ORIGIN = 0x01033800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_208_209 : ORIGIN = 0x01034000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_210_211 : ORIGIN = 0x01034800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_212_213 : ORIGIN = 0x01035000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_214_215 : ORIGIN = 0x01035800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_216_217 : ORIGIN = 0x01036000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_218_219 : ORIGIN = 0x01036800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_220_221 : ORIGIN = 0x01037000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_222_223 : ORIGIN = 0x01037800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_224_225 : ORIGIN = 0x01038000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_226_227 : ORIGIN = 0x01038800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_228_229 : ORIGIN = 0x01039000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_230_231 : ORIGIN = 0x01039800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_232_233 : ORIGIN = 0x0103a000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_234_235 : ORIGIN = 0x0103a800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_236_237 : ORIGIN = 0x0103b000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_238_239 : ORIGIN = 0x0103b800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_240_241 : ORIGIN = 0x0103c000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_242_243 : ORIGIN = 0x0103c800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_244_245 : ORIGIN = 0x0103d000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_246_247 : ORIGIN = 0x0103d800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_248_249 : ORIGIN = 0x0103e000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_250_251 : ORIGIN = 0x0103e800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_252_253 : ORIGIN = 0x0103f000, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
  chr_rom_254_255 : ORIGIN = 0x0103f800, LENGTH = __chr_rom_size >= 256 ? 0x800 : 0
}

SECTIONS {
  .prg_ram (NOLOAD) : { *(.prg_ram .prg_ram.*) } >prg_ram

  .chr_rom_0   : { KEEP(*(.chr_rom_0   .chr_rom_0.*)) }   >chr_rom_0
  .chr_rom_1   : { KEEP(*(.chr_rom_1   .chr_rom_1.*)) }   >chr_rom_1
  .chr_rom_2   : { KEEP(*(.chr_rom_2   .chr_rom_2.*)) }   >chr_rom_2
  .chr_rom_3   : { KEEP(*(.chr_rom_3   .chr_rom_3.*)) }   >chr_rom_3
  .chr_rom_4   : { KEEP(*(.chr_rom_4   .chr_rom_4.*)) }   >chr_rom_4
  .chr_rom_5   : { KEEP(*(.chr_rom_5   .chr_rom_5.*)) }   >chr_rom_5
  .chr_rom_6   : { KEEP(*(.chr_rom_6   .chr_rom_6.*)) }   >chr_rom_6
  .chr_rom_7   : { KEEP(*(.chr_rom_7   .chr_rom_7.*)) }   >chr_rom_7
  .chr_rom_8   : { KEEP(*(.chr_rom_8   .chr_rom_8.*)) }   >chr_rom_8
  .chr_rom_9   : { KEEP(*(.chr_rom_9   .chr_rom_9.*)) }   >chr_rom_9
  .chr_rom_10  : { KEEP(*(.chr_rom_10  .chr_rom_10.*)) }  >chr_rom_10
  .chr_rom_11  : { KEEP(*(.chr_rom_11  .chr_rom_11.*)) }  >chr_rom_11
  .chr_rom_12  : { KEEP(*(.chr_rom_12  .chr_rom_12.*)) }  >chr_rom_12
  .chr_rom_13  : { KEEP(*(.chr_rom_13  .chr_rom_13.*)) }  >chr_rom_13
  .chr_rom_14  : { KEEP(*(.chr_rom_14  .chr_rom_14.*)) }  >chr_rom_14
  .chr_rom_15  : { KEEP(*(.chr_rom_15  .chr_rom_15.*)) }  >chr_rom_15
  .chr_rom_16  : { KEEP(*(.chr_rom_16  .chr_rom_16.*)) }  >chr_rom_16
  .chr_rom_17  : { KEEP(*(.chr_rom_17  .chr_rom_17.*)) }  >chr_rom_17
  .chr_rom_18  : { KEEP(*(.chr_rom_18  .chr_rom_18.*)) }  >chr_rom_18
  .chr_rom_19  : { KEEP(*(.chr_rom_19  .chr_rom_19.*)) }  >chr_rom_19
  .chr_rom_20  : { KEEP(*(.chr_rom_20  .chr_rom_20.*)) }  >chr_rom_20
  .chr_rom_21  : { KEEP(*(.chr_rom_21  .chr_rom_21.*)) }  >chr_rom_21
  .chr_rom_22  : { KEEP(*(.chr_rom_22  .chr_rom_22.*)) }  >chr_rom_22
  .chr_rom_23  : { KEEP(*(.chr_rom_23  .chr_rom_23.*)) }  >chr_rom_23
  .chr_rom_24  : { KEEP(*(.chr_rom_24  .chr_rom_24.*)) }  >chr_rom_24
  .chr_rom_25  : { KEEP(*(.chr_rom_25  .chr_rom_25.*)) }  >chr_rom_25
  .chr_rom_26  : { KEEP(*(.chr_rom_26  .chr_rom_26.*)) }  >chr_rom_26
  .chr_rom_27  : { KEEP(*(.chr_rom_27  .chr_rom_27.*)) }  >chr_rom_27
  .chr_rom_28  : { KEEP(*(.chr_rom_28  .chr_rom_28.*)) }  >chr_rom_28
  .chr_rom_29  : { KEEP(*(.chr_rom_29  .chr_rom_29.*)) }  >chr_rom_29
  .chr_rom_30  : { KEEP(*(.chr_rom_30  .chr_rom_30.*)) }  >chr_rom_30
  .chr_rom_31  : { KEEP(*(.chr_rom_31  .chr_rom_31.*)) }  >chr_rom_31
  .chr_rom_32  : { KEEP(*(.chr_rom_32  .chr_rom_32.*)) }  >chr_rom_32
  .chr_rom_33  : { KEEP(*(.chr_rom_33  .chr_rom_33.*)) }  >chr_rom_33
  .chr_rom_34  : { KEEP(*(.chr_rom_34  .chr_rom_34.*)) }  >chr_rom_34
  .chr_rom_35  : { KEEP(*(.chr_rom_35  .chr_rom_35.*)) }  >chr_rom_35
  .chr_rom_36  : { KEEP(*(.chr_rom_36  .chr_rom_36.*)) }  >chr_rom_36
  .chr_rom_37  : { KEEP(*(.chr_rom_37  .chr_rom_37.*)) }  >chr_rom_37
  .chr_rom_38  : { KEEP(*(.chr_rom_38  .chr_rom_38.*)) }  >chr_rom_38
  .chr_rom_39  : { KEEP(*(.chr_rom_39  .chr_rom_39.*)) }  >chr_rom_39
  .chr_rom_40  : { KEEP(*(.chr_rom_40  .chr_rom_40.*)) }  >chr_rom_40
  .chr_rom_41  : { KEEP(*(.chr_rom_41  .chr_rom_41.*)) }  >chr_rom_41
  .chr_rom_42  : { KEEP(*(.chr_rom_42  .chr_rom_42.*)) }  >chr_rom_42
  .chr_rom_43  : { KEEP(*(.chr_rom_43  .chr_rom_43.*)) }  >chr_rom_43
  .chr_rom_44  : { KEEP(*(.chr_rom_44  .chr_rom_44.*)) }  >chr_rom_44
  .chr_rom_45  : { KEEP(*(.chr_rom_45  .chr_rom_45.*)) }  >chr_rom_45
  .chr_rom_46  : { KEEP(*(.chr_rom_46  .chr_rom_46.*)) }  >chr_rom_46
  .chr_rom_47  : { KEEP(*(.chr_rom_47  .chr_rom_47.*)) }  >chr_rom_47
  .chr_rom_48  : { KEEP(*(.chr_rom_48  .chr_rom_48.*)) }  >chr_rom_48
  .chr_rom_49  : { KEEP(*(.chr_rom_49  .chr_rom_49.*)) }  >chr_rom_49
  .chr_rom_50  : { KEEP(*(.chr_rom_50  .chr_rom_50.*)) }  >chr_rom_50
  .chr_rom_51  : { KEEP(*(.chr_rom_51  .chr_rom_51.*)) }  >chr_rom_51
  .chr_rom_52  : { KEEP(*(.chr_rom_52  .chr_rom_52.*)) }  >chr_rom_52
  .chr_rom_53  : { KEEP(*(.chr_rom_53  .chr_rom_53.*)) }  >chr_rom_53
  .chr_rom_54  : { KEEP(*(.chr_rom_54  .chr_rom_54.*)) }  >chr_rom_54
  .chr_rom_55  : { KEEP(*(.chr_rom_55  .chr_rom_55.*)) }  >chr_rom_55
  .chr_rom_56  : { KEEP(*(.chr_rom_56  .chr_rom_56.*)) }  >chr_rom_56
  .chr_rom_57  : { KEEP(*(.chr_rom_57  .chr_rom_57.*)) }  >chr_rom_57
  .chr_rom_58  : { KEEP(*(.chr_rom_58  .chr_rom_58.*)) }  >chr_rom_58
  .chr_rom_59  : { KEEP(*(.chr_rom_59  .chr_rom_59.*)) }  >chr_rom_59
  .chr_rom_60  : { KEEP(*(.chr_rom_60  .chr_rom_60.*)) }  >chr_rom_60
  .chr_rom_61  : { KEEP(*(.chr_rom_61  .chr_rom_61.*)) }  >chr_rom_61
  .chr_rom_62  : { KEEP(*(.chr_rom_62  .chr_rom_62.*)) }  >chr_rom_62
  .chr_rom_63  : { KEEP(*(.chr_rom_63  .chr_rom_63.*)) }  >chr_rom_63
  .chr_rom_64  : { KEEP(*(.chr_rom_64  .chr_rom_64.*)) }  >chr_rom_64
  .chr_rom_65  : { KEEP(*(.chr_rom_65  .chr_rom_65.*)) }  >chr_rom_65
  .chr_rom_66  : { KEEP(*(.chr_rom_66  .chr_rom_66.*)) }  >chr_rom_66
  .chr_rom_67  : { KEEP(*(.chr_rom_67  .chr_rom_67.*)) }  >chr_rom_67
  .chr_rom_68  : { KEEP(*(.chr_rom_68  .chr_rom_68.*)) }  >chr_rom_68
  .chr_rom_69  : { KEEP(*(.chr_rom_69  .chr_rom_69.*)) }  >chr_rom_69
  .chr_rom_70  : { KEEP(*(.chr_rom_70  .chr_rom_70.*)) }  >chr_rom_70
  .chr_rom_71  : { KEEP(*(.chr_rom_71  .chr_rom_71.*)) }  >chr_rom_71
  .chr_rom_72  : { KEEP(*(.chr_rom_72  .chr_rom_72.*)) }  >chr_rom_72
  .chr_rom_73  : { KEEP(*(.chr_rom_73  .chr_rom_73.*)) }  >chr_rom_73
  .chr_rom_74  : { KEEP(*(.chr_rom_74  .chr_rom_74.*)) }  >chr_rom_74
  .chr_rom_75  : { KEEP(*(.chr_rom_75  .chr_rom_75.*)) }  >chr_rom_75
  .chr_rom_76  : { KEEP(*(.chr_rom_76  .chr_rom_76.*)) }  >chr_rom_76
  .chr_rom_77  : { KEEP(*(.chr_rom_77  .chr_rom_77.*)) }  >chr_rom_77
  .chr_rom_78  : { KEEP(*(.chr_rom_78  .chr_rom_78.*)) }  >chr_rom_78
  .chr_rom_79  : { KEEP(*(.chr_rom_79  .chr_rom_79.*)) }  >chr_rom_79
  .chr_rom_80  : { KEEP(*(.chr_rom_80  .chr_rom_80.*)) }  >chr_rom_80
  .chr_rom_81  : { KEEP(*(.chr_rom_81  .chr_rom_81.*)) }  >chr_rom_81
  .chr_rom_82  : { KEEP(*(.chr_rom_82  .chr_rom_82.*)) }  >chr_rom_82
  .chr_rom_83  : { KEEP(*(.chr_rom_83  .chr_rom_83.*)) }  >chr_rom_83
  .chr_rom_84  : { KEEP(*(.chr_rom_84  .chr_rom_84.*)) }  >chr_rom_84
  .chr_rom_85  : { KEEP(*(.chr_rom_85  .chr_rom_85.*)) }  >chr_rom_85
  .chr_rom_86  : { KEEP(*(.chr_rom_86  .chr_rom_86.*)) }  >chr_rom_86
  .chr_rom_87  : { KEEP(*(.chr_rom_87  .chr_rom_87.*)) }  >chr_rom_87
  .chr_rom_88  : { KEEP(*(.chr_rom_88  .chr_rom_88.*)) }  >chr_rom_88
  .chr_rom_89  : { KEEP(*(.chr_rom_89  .chr_rom_89.*)) }  >chr_rom_89
  .chr_rom_90  : { KEEP(*(.chr_rom_90  .chr_rom_90.*)) }  >chr_rom_90
  .chr_rom_91  : { KEEP(*(.chr_rom_91  .chr_rom_91.*)) }  >chr_rom_91
  .chr_rom_92  : { KEEP(*(.chr_rom_92  .chr_rom_92.*)) }  >chr_rom_92
  .chr_rom_93  : { KEEP(*(.chr_rom_93  .chr_rom_93.*)) }  >chr_rom_93
  .chr_rom_94  : { KEEP(*(.chr_rom_94  .chr_rom_94.*)) }  >chr_rom_94
  .chr_rom_95  : { KEEP(*(.chr_rom_95  .chr_rom_95.*)) }  >chr_rom_95
  .chr_rom_96  : { KEEP(*(.chr_rom_96  .chr_rom_96.*)) }  >chr_rom_96
  .chr_rom_97  : { KEEP(*(.chr_rom_97  .chr_rom_97.*)) }  >chr_rom_97
  .chr_rom_98  : { KEEP(*(.chr_rom_98  .chr_rom_98.*)) }  >chr_rom_98
  .chr_rom_99  : { KEEP(*(.chr_rom_99  .chr_rom_99.*)) }  >chr_rom_99
  .chr_rom_100 : { KEEP(*(.chr_rom_100 .chr_rom_100.*)) } >chr_rom_100
  .chr_rom_101 : { KEEP(*(.chr_rom_101 .chr_rom_101.*)) } >chr_rom_101
  .chr_rom_102 : { KEEP(*(.chr_rom_102 .chr_rom_102.*)) } >chr_rom_102
  .chr_rom_103 : { KEEP(*(.chr_rom_103 .chr_rom_103.*)) } >chr_rom_103
  .chr_rom_104 : { KEEP(*(.chr_rom_104 .chr_rom_104.*)) } >chr_rom_104
  .chr_rom_105 : { KEEP(*(.chr_rom_105 .chr_rom_105.*)) } >chr_rom_105
  .chr_rom_106 : { KEEP(*(.chr_rom_106 .chr_rom_106.*)) } >chr_rom_106
  .chr_rom_107 : { KEEP(*(.chr_rom_107 .chr_rom_107.*)) } >chr_rom_107
  .chr_rom_108 : { KEEP(*(.chr_rom_108 .chr_rom_108.*)) } >chr_rom_108
  .chr_rom_109 : { KEEP(*(.chr_rom_109 .chr_rom_109.*)) } >chr_rom_109
  .chr_rom_110 : { KEEP(*(.chr_rom_110 .chr_rom_110.*)) } >chr_rom_110
  .chr_rom_111 : { KEEP(*(.chr_rom_111 .chr_rom_111.*)) } >chr_rom_111
  .chr_rom_112 : { KEEP(*(.chr_rom_112 .chr_rom_112.*)) } >chr_rom_112
  .chr_rom_113 : { KEEP(*(.chr_rom_113 .chr_rom_113.*)) } >chr_rom_113
  .chr_rom_114 : { KEEP(*(.chr_rom_114 .chr_rom_114.*)) } >chr_rom_114
  .chr_rom_115 : { KEEP(*(.chr_rom_115 .chr_rom_115.*)) } >chr_rom_115
  .chr_rom_116 : { KEEP(*(.chr_rom_116 .chr_rom_116.*)) } >chr_rom_116
  .chr_rom_117 : { KEEP(*(.chr_rom_117 .chr_rom_117.*)) } >chr_rom_117
  .chr_rom_118 : { KEEP(*(.chr_rom_118 .chr_rom_118.*)) } >chr_rom_118
  .chr_rom_119 : { KEEP(*(.chr_rom_119 .chr_rom_119.*)) } >chr_rom_119
  .chr_rom_120 : { KEEP(*(.chr_rom_120 .chr_rom_120.*)) } >chr_rom_120
  .chr_rom_121 : { KEEP(*(.chr_rom_121 .chr_rom_121.*)) } >chr_rom_121
  .chr_rom_122 : { KEEP(*(.chr_rom_122 .chr_rom_122.*)) } >chr_rom_122
  .chr_rom_123 : { KEEP(*(.chr_rom_123 .chr_rom_123.*)) } >chr_rom_123
  .chr_rom_124 : { KEEP(*(.chr_rom_124 .chr_rom_124.*)) } >chr_rom_124
  .chr_rom_125 : { KEEP(*(.chr_rom_125 .chr_rom_125.*)) } >chr_rom_125
  .chr_rom_126 : { KEEP(*(.chr_rom_126 .chr_rom_126.*)) } >chr_rom_126
  .chr_rom_127 : { KEEP(*(.chr_rom_127 .chr_rom_127.*)) } >chr_rom_127
  .chr_rom_128 : { KEEP(*(.chr_rom_128 .chr_rom_128.*)) } >chr_rom_128
  .chr_rom_129 : { KEEP(*(.chr_rom_129 .chr_rom_129.*)) } >chr_rom_129
  .chr_rom_130 : { KEEP(*(.chr_rom_130 .chr_rom_130.*)) } >chr_rom_130
  .chr_rom_131 : { KEEP(*(.chr_rom_131 .chr_rom_131.*)) } >chr_rom_131
  .chr_rom_132 : { KEEP(*(.chr_rom_132 .chr_rom_132.*)) } >chr_rom_132
  .chr_rom_133 : { KEEP(*(.chr_rom_133 .chr_rom_133.*)) } >chr_rom_133
  .chr_rom_134 : { KEEP(*(.chr_rom_134 .chr_rom_134.*)) } >chr_rom_134
  .chr_rom_135 : { KEEP(*(.chr_rom_135 .chr_rom_135.*)) } >chr_rom_135
  .chr_rom_136 : { KEEP(*(.chr_rom_136 .chr_rom_136.*)) } >chr_rom_136
  .chr_rom_137 : { KEEP(*(.chr_rom_137 .chr_rom_137.*)) } >chr_rom_137
  .chr_rom_138 : { KEEP(*(.chr_rom_138 .chr_rom_138.*)) } >chr_rom_138
  .chr_rom_139 : { KEEP(*(.chr_rom_139 .chr_rom_139.*)) } >chr_rom_139
  .chr_rom_140 : { KEEP(*(.chr_rom_140 .chr_rom_140.*)) } >chr_rom_140
  .chr_rom_141 : { KEEP(*(.chr_rom_141 .chr_rom_141.*)) } >chr_rom_141
  .chr_rom_142 : { KEEP(*(.chr_rom_142 .chr_rom_142.*)) } >chr_rom_142
  .chr_rom_143 : { KEEP(*(.chr_rom_143 .chr_rom_143.*)) } >chr_rom_143
  .chr_rom_144 : { KEEP(*(.chr_rom_144 .chr_rom_144.*)) } >chr_rom_144
  .chr_rom_145 : { KEEP(*(.chr_rom_145 .chr_rom_145.*)) } >chr_rom_145
  .chr_rom_146 : { KEEP(*(.chr_rom_146 .chr_rom_146.*)) } >chr_rom_146
  .chr_rom_147 : { KEEP(*(.chr_rom_147 .chr_rom_147.*)) } >chr_rom_147
  .chr_rom_148 : { KEEP(*(.chr_rom_148 .chr_rom_148.*)) } >chr_rom_148
  .chr_rom_149 : { KEEP(*(.chr_rom_149 .chr_rom_149.*)) } >chr_rom_149
  .chr_rom_150 : { KEEP(*(.chr_rom_150 .chr_rom_150.*)) } >chr_rom_150
  .chr_rom_151 : { KEEP(*(.chr_rom_151 .chr_rom_151.*)) } >chr_rom_151
  .chr_rom_152 : { KEEP(*(.chr_rom_152 .chr_rom_152.*)) } >chr_rom_152
  .chr_rom_153 : { KEEP(*(.chr_rom_153 .chr_rom_153.*)) } >chr_rom_153
  .chr_rom_154 : { KEEP(*(.chr_rom_154 .chr_rom_154.*)) } >chr_rom_154
  .chr_rom_155 : { KEEP(*(.chr_rom_155 .chr_rom_155.*)) } >chr_rom_155
  .chr_rom_156 : { KEEP(*(.chr_rom_156 .chr_rom_156.*)) } >chr_rom_156
  .chr_rom_157 : { KEEP(*(.chr_rom_157 .chr_rom_157.*)) } >chr_rom_157
  .chr_rom_158 : { KEEP(*(.chr_rom_158 .chr_rom_158.*)) } >chr_rom_158
  .chr_rom_159 : { KEEP(*(.chr_rom_159 .chr_rom_159.*)) } >chr_rom_159
  .chr_rom_160 : { KEEP(*(.chr_rom_160 .chr_rom_160.*)) } >chr_rom_160
  .chr_rom_161 : { KEEP(*(.chr_rom_161 .chr_rom_161.*)) } >chr_rom_161
  .chr_rom_162 : { KEEP(*(.chr_rom_162 .chr_rom_162.*)) } >chr_rom_162
  .chr_rom_163 : { KEEP(*(.chr_rom_163 .chr_rom_163.*)) } >chr_rom_163
  .chr_rom_164 : { KEEP(*(.chr_rom_164 .chr_rom_164.*)) } >chr_rom_164
  .chr_rom_165 : { KEEP(*(.chr_rom_165 .chr_rom_165.*)) } >chr_rom_165
  .chr_rom_166 : { KEEP(*(.chr_rom_166 .chr_rom_166.*)) } >chr_rom_166
  .chr_rom_167 : { KEEP(*(.chr_rom_167 .chr_rom_167.*)) } >chr_rom_167
  .chr_rom_168 : { KEEP(*(.chr_rom_168 .chr_rom_168.*)) } >chr_rom_168
  .chr_rom_169 : { KEEP(*(.chr_rom_169 .chr_rom_169.*)) } >chr_rom_169
  .chr_rom_170 : { KEEP(*(.chr_rom_170 .chr_rom_170.*)) } >chr_rom_170
  .chr_rom_171 : { KEEP(*(.chr_rom_171 .chr_rom_171.*)) } >chr_rom_171
  .chr_rom_172 : { KEEP(*(.chr_rom_172 .chr_rom_172.*)) } >chr_rom_172
  .chr_rom_173 : { KEEP(*(.chr_rom_173 .chr_rom_173.*)) } >chr_rom_173
  .chr_rom_174 : { KEEP(*(.chr_rom_174 .chr_rom_174.*)) } >chr_rom_174
  .chr_rom_175 : { KEEP(*(.chr_rom_175 .chr_rom_175.*)) } >chr_rom_175
  .chr_rom_176 : { KEEP(*(.chr_rom_176 .chr_rom_176.*)) } >chr_rom_176
  .chr_rom_177 : { KEEP(*(.chr_rom_177 .chr_rom_177.*)) } >chr_rom_177
  .chr_rom_178 : { KEEP(*(.chr_rom_178 .chr_rom_178.*)) } >chr_rom_178
  .chr_rom_179 : { KEEP(*(.chr_rom_179 .chr_rom_179.*)) } >chr_rom_179
  .chr_rom_180 : { KEEP(*(.chr_rom_180 .chr_rom_180.*)) } >chr_rom_180
  .chr_rom_181 : { KEEP(*(.chr_rom_181 .chr_rom_181.*)) } >chr_rom_181
  .chr_rom_182 : { KEEP(*(.chr_rom_182 .chr_rom_182.*)) } >chr_rom_182
  .chr_rom_183 : { KEEP(*(.chr_rom_183 .chr_rom_183.*)) } >chr_rom_183
  .chr_rom_184 : { KEEP(*(.chr_rom_184 .chr_rom_184.*)) } >chr_rom_184
  .chr_rom_185 : { KEEP(*(.chr_rom_185 .chr_rom_185.*)) } >chr_rom_185
  .chr_rom_186 : { KEEP(*(.chr_rom_186 .chr_rom_186.*)) } >chr_rom_186
  .chr_rom_187 : { KEEP(*(.chr_rom_187 .chr_rom_187.*)) } >chr_rom_187
  .chr_rom_188 : { KEEP(*(.chr_rom_188 .chr_rom_188.*)) } >chr_rom_188
  .chr_rom_189 : { KEEP(*(.chr_rom_189 .chr_rom_189.*)) } >chr_rom_189
  .chr_rom_190 : { KEEP(*(.chr_rom_190 .chr_rom_190.*)) } >chr_rom_190
  .chr_rom_191 : { KEEP(*(.chr_rom_191 .chr_rom_191.*)) } >chr_rom_191
  .chr_rom_192 : { KEEP(*(.chr_rom_192 .chr_rom_192.*)) } >chr_rom_192
  .chr_rom_193 : { KEEP(*(.chr_rom_193 .chr_rom_193.*)) } >chr_rom_193
  .chr_rom_194 : { KEEP(*(.chr_rom_194 .chr_rom_194.*)) } >chr_rom_194
  .chr_rom_195 : { KEEP(*(.chr_rom_195 .chr_rom_195.*)) } >chr_rom_195
  .chr_rom_196 : { KEEP(*(.chr_rom_196 .chr_rom_196.*)) } >chr_rom_196
  .chr_rom_197 : { KEEP(*(.chr_rom_197 .chr_rom_197.*)) } >chr_rom_197
  .chr_rom_198 : { KEEP(*(.chr_rom_198 .chr_rom_198.*)) } >chr_rom_198
  .chr_rom_199 : { KEEP(*(.chr_rom_199 .chr_rom_199.*)) } >chr_rom_199
  .chr_rom_200 : { KEEP(*(.chr_rom_200 .chr_rom_200.*)) } >chr_rom_200
  .chr_rom_201 : { KEEP(*(.chr_rom_201 .chr_rom_201.*)) } >chr_rom_201
  .chr_rom_202 : { KEEP(*(.chr_rom_202 .chr_rom_202.*)) } >chr_rom_202
  .chr_rom_203 : { KEEP(*(.chr_rom_203 .chr_rom_203.*)) } >chr_rom_203
  .chr_rom_204 : { KEEP(*(.chr_rom_204 .chr_rom_204.*)) } >chr_rom_204
  .chr_rom_205 : { KEEP(*(.chr_rom_205 .chr_rom_205.*)) } >chr_rom_205
  .chr_rom_206 : { KEEP(*(.chr_rom_206 .chr_rom_206.*)) } >chr_rom_206
  .chr_rom_207 : { KEEP(*(.chr_rom_207 .chr_rom_207.*)) } >chr_rom_207
  .chr_rom_208 : { KEEP(*(.chr_rom_208 .chr_rom_208.*)) } >chr_rom_208
  .chr_rom_209 : { KEEP(*(.chr_rom_209 .chr_rom_209.*)) } >chr_rom_209
  .chr_rom_210 : { KEEP(*(.chr_rom_210 .chr_rom_210.*)) } >chr_rom_210
  .chr_rom_211 : { KEEP(*(.chr_rom_211 .chr_rom_211.*)) } >chr_rom_211
  .chr_rom_212 : { KEEP(*(.chr_rom_212 .chr_rom_212.*)) } >chr_rom_212
  .chr_rom_213 : { KEEP(*(.chr_rom_213 .chr_rom_213.*)) } >chr_rom_213
  .chr_rom_214 : { KEEP(*(.chr_rom_214 .chr_rom_214.*)) } >chr_rom_214
  .chr_rom_215 : { KEEP(*(.chr_rom_215 .chr_rom_215.*)) } >chr_rom_215
  .chr_rom_216 : { KEEP(*(.chr_rom_216 .chr_rom_216.*)) } >chr_rom_216
  .chr_rom_217 : { KEEP(*(.chr_rom_217 .chr_rom_217.*)) } >chr_rom_217
  .chr_rom_218 : { KEEP(*(.chr_rom_218 .chr_rom_218.*)) } >chr_rom_218
  .chr_rom_219 : { KEEP(*(.chr_rom_219 .chr_rom_219.*)) } >chr_rom_219
  .chr_rom_220 : { KEEP(*(.chr_rom_220 .chr_rom_220.*)) } >chr_rom_220
  .chr_rom_221 : { KEEP(*(.chr_rom_221 .chr_rom_221.*)) } >chr_rom_221
  .chr_rom_222 : { KEEP(*(.chr_rom_222 .chr_rom_222.*)) } >chr_rom_222
  .chr_rom_223 : { KEEP(*(.chr_rom_223 .chr_rom_223.*)) } >chr_rom_223
  .chr_rom_224 : { KEEP(*(.chr_rom_224 .chr_rom_224.*)) } >chr_rom_224
  .chr_rom_225 : { KEEP(*(.chr_rom_225 .chr_rom_225.*)) } >chr_rom_225
  .chr_rom_226 : { KEEP(*(.chr_rom_226 .chr_rom_226.*)) } >chr_rom_226
  .chr_rom_227 : { KEEP(*(.chr_rom_227 .chr_rom_227.*)) } >chr_rom_227
  .chr_rom_228 : { KEEP(*(.chr_rom_228 .chr_rom_228.*)) } >chr_rom_228
  .chr_rom_229 : { KEEP(*(.chr_rom_229 .chr_rom_229.*)) } >chr_rom_229
  .chr_rom_230 : { KEEP(*(.chr_rom_230 .chr_rom_230.*)) } >chr_rom_230
  .chr_rom_231 : { KEEP(*(.chr_rom_231 .chr_rom_231.*)) } >chr_rom_231
  .chr_rom_232 : { KEEP(*(.chr_rom_232 .chr_rom_232.*)) } >chr_rom_232
  .chr_rom_233 : { KEEP(*(.chr_rom_233 .chr_rom_233.*)) } >chr_rom_233
  .chr_rom_234 : { KEEP(*(.chr_rom_234 .chr_rom_234.*)) } >chr_rom_234
  .chr_rom_235 : { KEEP(*(.chr_rom_235 .chr_rom_235.*)) } >chr_rom_235
  .chr_rom_236 : { KEEP(*(.chr_rom_236 .chr_rom_236.*)) } >chr_rom_236
  .chr_rom_237 : { KEEP(*(.chr_rom_237 .chr_rom_237.*)) } >chr_rom_237
  .chr_rom_238 : { KEEP(*(.chr_rom_238 .chr_rom_238.*)) } >chr_rom_238
  .chr_rom_239 : { KEEP(*(.chr_rom_239 .chr_rom_239.*)) } >chr_rom_239
  .chr_rom_240 : { KEEP(*(.chr_rom_240 .chr_rom_240.*)) } >chr_rom_240
  .chr_rom_241 : { KEEP(*(.chr_rom_241 .chr_rom_241.*)) } >chr_rom_241
  .chr_rom_242 : { KEEP(*(.chr_rom_242 .chr_rom_242.*)) } >chr_rom_242
  .chr_rom_243 : { KEEP(*(.chr_rom_243 .chr_rom_243.*)) } >chr_rom_243
  .chr_rom_244 : { KEEP(*(.chr_rom_244 .chr_rom_244.*)) } >chr_rom_244
  .chr_rom_245 : { KEEP(*(.chr_rom_245 .chr_rom_245.*)) } >chr_rom_245
  .chr_rom_246 : { KEEP(*(.chr_rom_246 .chr_rom_246.*)) } >chr_rom_246
  .chr_rom_247 : { KEEP(*(.chr_rom_247 .chr_rom_247.*)) } >chr_rom_247
  .chr_rom_248 : { KEEP(*(.chr_rom_248 .chr_rom_248.*)) } >chr_rom_248
  .chr_rom_249 : { KEEP(*(.chr_rom_249 .chr_rom_249.*)) } >chr_rom_249
  .chr_rom_250 : { KEEP(*(.chr_rom_250 .chr_rom_250.*)) } >chr_rom_250
  .chr_rom_251 : { KEEP(*(.chr_rom_251 .chr_rom_251.*)) } >chr_rom_251
  .chr_rom_252 : { KEEP(*(.chr_rom_252 .chr_rom_252.*)) } >chr_rom_252
  .chr_rom_253 : { KEEP(*(.chr_rom_253 .chr_rom_253.*)) } >chr_rom_253
  .chr_rom_254 : { KEEP(*(.chr_rom_254 .chr_rom_254.*)) } >chr_rom_254
  .chr_rom_255 : { KEEP(*(.chr_rom_255 .chr_rom_255.*)) } >chr_rom_255

  .chr_rom_0_1     : { KEEP(*(.chr_rom_0_1     .chr_rom_0_1.*)) }     >chr_rom_0_1
  .chr_rom_2_3     : { KEEP(*(.chr_rom_2_3     .chr_rom_2_3.*)) }     >chr_rom_2_3
  .chr_rom_4_5     : { KEEP(*(.chr_rom_4_5     .chr_rom_4_5.*)) }     >chr_rom_4_5
  .chr_rom_6_7     : { KEEP(*(.chr_rom_6_7     .chr_rom_6_7.*)) }     >chr_rom_6_7
  .chr_rom_8_9     : { KEEP(*(.chr_rom_8_9     .chr_rom_8_9.*)) }     >chr_rom_8_9
  .chr_rom_10_11   : { KEEP(*(.chr_rom_10_11   .chr_rom_10_11.*)) }   >chr_rom_10_11
  .chr_rom_12_13   : { KEEP(*(.chr_rom_12_13   .chr_rom_12_13.*)) }   >chr_rom_12_13
  .chr_rom_14_15   : { KEEP(*(.chr_rom_14_15   .chr_rom_14_15.*)) }   >chr_rom_14_15
  .chr_rom_16_17   : { KEEP(*(.chr_rom_16_17   .chr_rom_16_17.*)) }   >chr_rom_16_17
  .chr_rom_18_19   : { KEEP(*(.chr_rom_18_19   .chr_rom_18_19.*)) }   >chr_rom_18_19
  .chr_rom_20_21   : { KEEP(*(.chr_rom_20_21   .chr_rom_20_21.*)) }   >chr_rom_20_21
  .chr_rom_22_23   : { KEEP(*(.chr_rom_22_23   .chr_rom_22_23.*)) }   >chr_rom_22_23
  .chr_rom_24_25   : { KEEP(*(.chr_rom_24_25   .chr_rom_24_25.*)) }   >chr_rom_24_25
  .chr_rom_26_27   : { KEEP(*(.chr_rom_26_27   .chr_rom_26_27.*)) }   >chr_rom_26_27
  .chr_rom_28_29   : { KEEP(*(.chr_rom_28_29   .chr_rom_28_29.*)) }   >chr_rom_28_29
  .chr_rom_30_31   : { KEEP(*(.chr_rom_30_31   .chr_rom_30_31.*)) }   >chr_rom_30_31
  .chr_rom_32_33   : { KEEP(*(.chr_rom_32_33   .chr_rom_32_33.*)) }   >chr_rom_32_33
  .chr_rom_34_35   : { KEEP(*(.chr_rom_34_35   .chr_rom_34_35.*)) }   >chr_rom_34_35
  .chr_rom_36_37   : { KEEP(*(.chr_rom_36_37   .chr_rom_36_37.*)) }   >chr_rom_36_37
  .chr_rom_38_39   : { KEEP(*(.chr_rom_38_39   .chr_rom_38_39.*)) }   >chr_rom_38_39
  .chr_rom_40_41   : { KEEP(*(.chr_rom_40_41   .chr_rom_40_41.*)) }   >chr_rom_40_41
  .chr_rom_42_43   : { KEEP(*(.chr_rom_42_43   .chr_rom_42_43.*)) }   >chr_rom_42_43
  .chr_rom_44_45   : { KEEP(*(.chr_rom_44_45   .chr_rom_44_45.*)) }   >chr_rom_44_45
  .chr_rom_46_47   : { KEEP(*(.chr_rom_46_47   .chr_rom_46_47.*)) }   >chr_rom_46_47
  .chr_rom_48_49   : { KEEP(*(.chr_rom_48_49   .chr_rom_48_49.*)) }   >chr_rom_48_49
  .chr_rom_50_51   : { KEEP(*(.chr_rom_50_51   .chr_rom_50_51.*)) }   >chr_rom_50_51
  .chr_rom_52_53   : { KEEP(*(.chr_rom_52_53   .chr_rom_52_53.*)) }   >chr_rom_52_53
  .chr_rom_54_55   : { KEEP(*(.chr_rom_54_55   .chr_rom_54_55.*)) }   >chr_rom_54_55
  .chr_rom_56_57   : { KEEP(*(.chr_rom_56_57   .chr_rom_56_57.*)) }   >chr_rom_56_57
  .chr_rom_58_59   : { KEEP(*(.chr_rom_58_59   .chr_rom_58_59.*)) }   >chr_rom_58_59
  .chr_rom_60_61   : { KEEP(*(.chr_rom_60_61   .chr_rom_60_61.*)) }   >chr_rom_60_61
  .chr_rom_62_63   : { KEEP(*(.chr_rom_62_63   .chr_rom_62_63.*)) }   >chr_rom_62_63
  .chr_rom_64_65   : { KEEP(*(.chr_rom_64_65   .chr_rom_64_65.*)) }   >chr_rom_64_65
  .chr_rom_66_67   : { KEEP(*(.chr_rom_66_67   .chr_rom_66_67.*)) }   >chr_rom_66_67
  .chr_rom_68_69   : { KEEP(*(.chr_rom_68_69   .chr_rom_68_69.*)) }   >chr_rom_68_69
  .chr_rom_70_71   : { KEEP(*(.chr_rom_70_71   .chr_rom_70_71.*)) }   >chr_rom_70_71
  .chr_rom_72_73   : { KEEP(*(.chr_rom_72_73   .chr_rom_72_73.*)) }   >chr_rom_72_73
  .chr_rom_74_75   : { KEEP(*(.chr_rom_74_75   .chr_rom_74_75.*)) }   >chr_rom_74_75
  .chr_rom_76_77   : { KEEP(*(.chr_rom_76_77   .chr_rom_76_77.*)) }   >chr_rom_76_77
  .chr_rom_78_79   : { KEEP(*(.chr_rom_78_79   .chr_rom_78_79.*)) }   >chr_rom_78_79
  .chr_rom_80_81   : { KEEP(*(.chr_rom_80_81   .chr_rom_80_81.*)) }   >chr_rom_80_81
  .chr_rom_82_83   : { KEEP(*(.chr_rom_82_83   .chr_rom_82_83.*)) }   >chr_rom_82_83
  .chr_rom_84_85   : { KEEP(*(.chr_rom_84_85   .chr_rom_84_85.*)) }   >chr_rom_84_85
  .chr_rom_86_87   : { KEEP(*(.chr_rom_86_87   .chr_rom_86_87.*)) }   >chr_rom_86_87
  .chr_rom_88_89   : { KEEP(*(.chr_rom_88_89   .chr_rom_88_89.*)) }   >chr_rom_88_89
  .chr_rom_90_91   : { KEEP(*(.chr_rom_90_91   .chr_rom_90_91.*)) }   >chr_rom_90_91
  .chr_rom_92_93   : { KEEP(*(.chr_rom_92_93   .chr_rom_92_93.*)) }   >chr_rom_92_93
  .chr_rom_94_95   : { KEEP(*(.chr_rom_94_95   .chr_rom_94_95.*)) }   >chr_rom_94_95
  .chr_rom_96_97   : { KEEP(*(.chr_rom_96_97   .chr_rom_96_97.*)) }   >chr_rom_96_97
  .chr_rom_98_99   : { KEEP(*(.chr_rom_98_99   .chr_rom_98_99.*)) }   >chr_rom_98_99
  .chr_rom_100_101 : { KEEP(*(.chr_rom_100_101 .chr_rom_100_101.*)) } >chr_rom_100_101
  .chr_rom_102_103 : { KEEP(*(.chr_rom_102_103 .chr_rom_102_103.*)) } >chr_rom_102_103
  .chr_rom_104_105 : { KEEP(*(.chr_rom_104_105 .chr_rom_104_105.*)) } >chr_rom_104_105
  .chr_rom_106_107 : { KEEP(*(.chr_rom_106_107 .chr_rom_106_107.*)) } >chr_rom_106_107
  .chr_rom_108_109 : { KEEP(*(.chr_rom_108_109 .chr_rom_108_109.*)) } >chr_rom_108_109
  .chr_rom_110_111 : { KEEP(*(.chr_rom_110_111 .chr_rom_110_111.*)) } >chr_rom_110_111
  .chr_rom_112_113 : { KEEP(*(.chr_rom_112_113 .chr_rom_112_113.*)) } >chr_rom_112_113
  .chr_rom_114_115 : { KEEP(*(.chr_rom_114_115 .chr_rom_114_115.*)) } >chr_rom_114_115
  .chr_rom_116_117 : { KEEP(*(.chr_rom_116_117 .chr_rom_116_117.*)) } >chr_rom_116_117
  .chr_rom_118_119 : { KEEP(*(.chr_rom_118_119 .chr_rom_118_119.*)) } >chr_rom_118_119
  .chr_rom_120_121 : { KEEP(*(.chr_rom_120_121 .chr_rom_120_121.*)) } >chr_rom_120_121
  .chr_rom_122_123 : { KEEP(*(.chr_rom_122_123 .chr_rom_122_123.*)) } >chr_rom_122_123
  .chr_rom_124_125 : { KEEP(*(.chr_rom_124_125 .chr_rom_124_125.*)) } >chr_rom_124_125
  .chr_rom_126_127 : { KEEP(*(.chr_rom_126_127 .chr_rom_126_127.*)) } >chr_rom_126_127
  .chr_rom_128_129 : { KEEP(*(.chr_rom_128_129 .chr_rom_128_129.*)) } >chr_rom_128_129
  .chr_rom_130_131 : { KEEP(*(.chr_rom_130_131 .chr_rom_130_131.*)) } >chr_rom_130_131
  .chr_rom_132_133 : { KEEP(*(.chr_rom_132_133 .chr_rom_132_133.*)) } >chr_rom_132_133
  .chr_rom_134_135 : { KEEP(*(.chr_rom_134_135 .chr_rom_134_135.*)) } >chr_rom_134_135
  .chr_rom_136_137 : { KEEP(*(.chr_rom_136_137 .chr_rom_136_137.*)) } >chr_rom_136_137
  .chr_rom_138_139 : { KEEP(*(.chr_rom_138_139 .chr_rom_138_139.*)) } >chr_rom_138_139
  .chr_rom_140_141 : { KEEP(*(.chr_rom_140_141 .chr_rom_140_141.*)) } >chr_rom_140_141
  .chr_rom_142_143 : { KEEP(*(.chr_rom_142_143 .chr_rom_142_143.*)) } >chr_rom_142_143
  .chr_rom_144_145 : { KEEP(*(.chr_rom_144_145 .chr_rom_144_145.*)) } >chr_rom_144_145
  .chr_rom_146_147 : { KEEP(*(.chr_rom_146_147 .chr_rom_146_147.*)) } >chr_rom_146_147
  .chr_rom_148_149 : { KEEP(*(.chr_rom_148_149 .chr_rom_148_149.*)) } >chr_rom_148_149
  .chr_rom_150_151 : { KEEP(*(.chr_rom_150_151 .chr_rom_150_151.*)) } >chr_rom_150_151
  .chr_rom_152_153 : { KEEP(*(.chr_rom_152_153 .chr_rom_152_153.*)) } >chr_rom_152_153
  .chr_rom_154_155 : { KEEP(*(.chr_rom_154_155 .chr_rom_154_155.*)) } >chr_rom_154_155
  .chr_rom_156_157 : { KEEP(*(.chr_rom_156_157 .chr_rom_156_157.*)) } >chr_rom_156_157
  .chr_rom_158_159 : { KEEP(*(.chr_rom_158_159 .chr_rom_158_159.*)) } >chr_rom_158_159
  .chr_rom_160_161 : { KEEP(*(.chr_rom_160_161 .chr_rom_160_161.*)) } >chr_rom_160_161
  .chr_rom_162_163 : { KEEP(*(.chr_rom_162_163 .chr_rom_162_163.*)) } >chr_rom_162_163
  .chr_rom_164_165 : { KEEP(*(.chr_rom_164_165 .chr_rom_164_165.*)) } >chr_rom_164_165
  .chr_rom_166_167 : { KEEP(*(.chr_rom_166_167 .chr_rom_166_167.*)) } >chr_rom_166_167
  .chr_rom_168_169 : { KEEP(*(.chr_rom_168_169 .chr_rom_168_169.*)) } >chr_rom_168_169
  .chr_rom_170_171 : { KEEP(*(.chr_rom_170_171 .chr_rom_170_171.*)) } >chr_rom_170_171
  .chr_rom_172_173 : { KEEP(*(.chr_rom_172_173 .chr_rom_172_173.*)) } >chr_rom_172_173
  .chr_rom_174_175 : { KEEP(*(.chr_rom_174_175 .chr_rom_174_175.*)) } >chr_rom_174_175
  .chr_rom_176_177 : { KEEP(*(.chr_rom_176_177 .chr_rom_176_177.*)) } >chr_rom_176_177
  .chr_rom_178_179 : { KEEP(*(.chr_rom_178_179 .chr_rom_178_179.*)) } >chr_rom_178_179
  .chr_rom_180_181 : { KEEP(*(.chr_rom_180_181 .chr_rom_180_181.*)) } >chr_rom_180_181
  .chr_rom_182_183 : { KEEP(*(.chr_rom_182_183 .chr_rom_182_183.*)) } >chr_rom_182_183
  .chr_rom_184_185 : { KEEP(*(.chr_rom_184_185 .chr_rom_184_185.*)) } >chr_rom_184_185
  .chr_rom_186_187 : { KEEP(*(.chr_rom_186_187 .chr_rom_186_187.*)) } >chr_rom_186_187
  .chr_rom_188_189 : { KEEP(*(.chr_rom_188_189 .chr_rom_188_189.*)) } >chr_rom_188_189
  .chr_rom_190_191 : { KEEP(*(.chr_rom_190_191 .chr_rom_190_191.*)) } >chr_rom_190_191
  .chr_rom_192_193 : { KEEP(*(.chr_rom_192_193 .chr_rom_192_193.*)) } >chr_rom_192_193
  .chr_rom_194_195 : { KEEP(*(.chr_rom_194_195 .chr_rom_194_195.*)) } >chr_rom_194_195
  .chr_rom_196_197 : { KEEP(*(.chr_rom_196_197 .chr_rom_196_197.*)) } >chr_rom_196_197
  .chr_rom_198_199 : { KEEP(*(.chr_rom_198_199 .chr_rom_198_199.*)) } >chr_rom_198_199
  .chr_rom_200_201 : { KEEP(*(.chr_rom_200_201 .chr_rom_200_201.*)) } >chr_rom_200_201
  .chr_rom_202_203 : { KEEP(*(.chr_rom_202_203 .chr_rom_202_203.*)) } >chr_rom_202_203
  .chr_rom_204_205 : { KEEP(*(.chr_rom_204_205 .chr_rom_204_205.*)) } >chr_rom_204_205
  .chr_rom_206_207 : { KEEP(*(.chr_rom_206_207 .chr_rom_206_207.*)) } >chr_rom_206_207
  .chr_rom_208_209 : { KEEP(*(.chr_rom_208_209 .chr_rom_208_209.*)) } >chr_rom_208_209
  .chr_rom_210_211 : { KEEP(*(.chr_rom_210_211 .chr_rom_210_211.*)) } >chr_rom_210_211
  .chr_rom_212_213 : { KEEP(*(.chr_rom_212_213 .chr_rom_212_213.*)) } >chr_rom_212_213
  .chr_rom_214_215 : { KEEP(*(.chr_rom_214_215 .chr_rom_214_215.*)) } >chr_rom_214_215
  .chr_rom_216_217 : { KEEP(*(.chr_rom_216_217 .chr_rom_216_217.*)) } >chr_rom_216_217
  .chr_rom_218_219 : { KEEP(*(.chr_rom_218_219 .chr_rom_218_219.*)) } >chr_rom_218_219
  .chr_rom_220_221 : { KEEP(*(.chr_rom_220_221 .chr_rom_220_221.*)) } >chr_rom_220_221
  .chr_rom_222_223 : { KEEP(*(.chr_rom_222_223 .chr_rom_222_223.*)) } >chr_rom_222_223
  .chr_rom_224_225 : { KEEP(*(.chr_rom_224_225 .chr_rom_224_225.*)) } >chr_rom_224_225
  .chr_rom_226_227 : { KEEP(*(.chr_rom_226_227 .chr_rom_226_227.*)) } >chr_rom_226_227
  .chr_rom_228_229 : { KEEP(*(.chr_rom_228_229 .chr_rom_228_229.*)) } >chr_rom_228_229
  .chr_rom_230_231 : { KEEP(*(.chr_rom_230_231 .chr_rom_230_231.*)) } >chr_rom_230_231
  .chr_rom_232_233 : { KEEP(*(.chr_rom_232_233 .chr_rom_232_233.*)) } >chr_rom_232_233
  .chr_rom_234_235 : { KEEP(*(.chr_rom_234_235 .chr_rom_234_235.*)) } >chr_rom_234_235
  .chr_rom_236_237 : { KEEP(*(.chr_rom_236_237 .chr_rom_236_237.*)) } >chr_rom_236_237
  .chr_rom_238_239 : { KEEP(*(.chr_rom_238_239 .chr_rom_238_239.*)) } >chr_rom_238_239
  .chr_rom_240_241 : { KEEP(*(.chr_rom_240_241 .chr_rom_240_241.*)) } >chr_rom_240_241
  .chr_rom_242_243 : { KEEP(*(.chr_rom_242_243 .chr_rom_242_243.*)) } >chr_rom_242_243
  .chr_rom_244_245 : { KEEP(*(.chr_rom_244_245 .chr_rom_244_245.*)) } >chr_rom_244_245
  .chr_rom_246_247 : { KEEP(*(.chr_rom_246_247 .chr_rom_246_247.*)) } >chr_rom_246_247
  .chr_rom_248_249 : { KEEP(*(.chr_rom_248_249 .chr_rom_248_249.*)) } >chr_rom_248_249
  .chr_rom_250_251 : { KEEP(*(.chr_rom_250_251 .chr_rom_250_251.*)) } >chr_rom_250_251
  .chr_rom_252_253 : { KEEP(*(.chr_rom_252_253 .chr_rom_252_253.*)) } >chr_rom_252_253
  .chr_rom_254_255 : { KEEP(*(.chr_rom_254_255 .chr_rom_254_255.*)) } >chr_rom_254_255
}