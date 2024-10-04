#ifndef _CORE_H
#define _CORE_H

#include <stdint.h>
#include "neslib.h"

// CHR Banks
#define CHR_DEFAULT    0

// Data Banks
#define DATA_00        0
#define DATA_01        1
#define DATA_02        2
#define DATA_03        3
#define DATA_04        4
#define DATA_05        5
#define DATA_06        6
#define DATA_07        7
#define DATA_08        8
#define DATA_09        9
#define DATA_10       10
#define DATA_11       11
#define DATA_12       12
#define DATA_13       13
#define DATA_14       14
#define DATA_15       15
#define DATA_16       16

// Music banks
#define MUSIC_01      17
#define MUSIC_02      18
#define MUSIC_03      19
#define MUSIC_04      20

// Sound effect banks
#define SOUND_01      21
#define SOUND_02      22
#define SOUND_03      23
#define SOUND_04      24

// Code Banks
#define CODE_XTD      52
#define CODE_EX9      53
#define CODE_EX8      54
#define CODE_EX7      55
#define CODE_EX6      56
#define CODE_EX5      57
#define CODE_EX4      58
#define CODE_EX3      59
#define CODE_EX2      60
#define CODE_EX1      61

// Stack operations
#define PUSH(s, v) (      \
  s[++s##_index] = (v)    \
)
#define POP(s) (          \
  s[s##_index--]          \
)
#define TOP(s) (          \
  s[s##_index]            \
)
#define IS_EMPTY(s) (     \
  s##_index < 0           \
)
#define IS_NOT_EMPTY(s) ( \
  s##_index >= 0          \
)

// Stack operations (2D Array)
#define M_PUSH(s, v, i) (      \
  s[i][++s##_index[i]] = (v)   \
)
#define M_POP(s, i) (          \
  s[i][s##_index[i]--]         \
)
#define M_TOP(s, i) (          \
  s[i][s##_index[i]]           \
)
#define IS_EMPTY_M(s, i) (     \
  s##_index[i] < 0             \
)
#define IS_NOT_EMPTY_M(s, i) ( \
  s##_index[i] >= 0            \
)

// Utility macros
#define MUL8(x)                   ((x) << 3)
#define DIV8(x)                   ((x) < 0 ? -(-(x) >> 3) : (x) >> 3)
#define UDIV8(x)                  ((x) >> 3)

#define MUL16(x)                  ((x) << 4)
#define DIV16(x)                  ((x) < 0 ? -(-(x) >> 4) : (x) >> 4)
#define UDIV16(x)                 ((x) >> 4)

#define SYM_RAND(x)               ((rand8() % ((2 * (x)) + 1)) - (x))

#define ROUND_UP(n, s)            ((((n) + (s) - 1) / (s)) * (s))

#define OBJECT(p, i)              (*(p + (i)))
#define MATRIX(p, x, y, len)      (*(p + ((len) * (y)) + (x)))

#define PERCENT(x, p)             (((((p) * 16) / 100) * (x)) / 16)

#define ONE                       (byte)1
#define BIT_ON(v, n)              (v |= ONE << n)
#define BIT_OFF(v, n)             (v &= ~(ONE << n))
#define BIT_VALUE(v, n)           ((v >> n) & ONE)
#define BIT_TOGGLE(v, n)          (v ^= ONE << n)
#define BIT_ARRAY_SET(a, i)       BIT_ON(a[UDIV8(i)], (i & 0x07))
#define BIT_ARRAY_UNSET(a, i)     BIT_OFF(a[UDIV8(i)], (i & 0x07))
#define BIT_ARRAY_VALUE(a, i)     BIT_VALUE(a[UDIV8(i)], (i & 0x07))

#define MASK_BIT_0                (0x01)
#define MASK_BIT_1                (0x02)
#define MASK_BIT_2                (0x04)
#define MASK_BIT_3                (0x08)
#define MASK_BIT_4                (0x10)
#define MASK_BIT_5                (0x20)
#define MASK_BIT_6                (0x40)
#define MASK_BIT_7                (0x80)

#define NOT(expr)                 (!(expr))
#define NEG(bool)                 (1 - (bool))
#define ABS(x)                    (x < 0 ? -x : x)
#define ABS_DIFF(a, b)            (((a) > (b)) ? ((a) - (b)) : ((b) - (a)))
#define DIRECTION(x)              (x + x - 1)
#define IN_RANGE(n, lower, upper) ((unsigned)(n - lower) < (upper - lower))
#define RETURN_IF(condition)      if ((condition)) return

#define BINARY_PATTERN       \
  "%c%c%c%c%c%c%c%c"

#define IN_BINARY(byte)      \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')

#define SIZE_OF_ARRAY(array) \
  (sizeof(array) / sizeof(array[0]))

#define LAST_INDEX_OF(array) \
  (sizeof(array) / sizeof(array[0]) - 1)

// LOOP() Macros
#define _ITER_1(i)  LOOP_CODE(i)
#define _ITER_2(i)  LOOP_CODE(i) _ITER_1(i - 1)
#define _ITER_3(i)  LOOP_CODE(i) _ITER_2(i - 1)
#define _ITER_4(i)  LOOP_CODE(i) _ITER_3(i - 1)
#define _ITER_5(i)  LOOP_CODE(i) _ITER_4(i - 1)
#define _ITER_6(i)  LOOP_CODE(i) _ITER_5(i - 1)
#define _ITER_7(i)  LOOP_CODE(i) _ITER_6(i - 1)
#define _ITER_8(i)  LOOP_CODE(i) _ITER_7(i - 1)
#define _ITER_9(i)  LOOP_CODE(i) _ITER_8(i - 1)
#define _ITER_10(i) LOOP_CODE(i) _ITER_9(i - 1)
#define _ITER_11(i) LOOP_CODE(i) _ITER_10(i - 1)
#define _ITER_12(i) LOOP_CODE(i) _ITER_11(i - 1)
#define _ITER_13(i) LOOP_CODE(i) _ITER_12(i - 1)
#define _ITER_14(i) LOOP_CODE(i) _ITER_13(i - 1)
#define _ITER_15(i) LOOP_CODE(i) _ITER_14(i - 1)
#define _ITER_16(i) LOOP_CODE(i) _ITER_15(i - 1)
#define _ITER_17(i) LOOP_CODE(i) _ITER_16(i - 1)
#define _ITER_18(i) LOOP_CODE(i) _ITER_17(i - 1)
#define _ITER_19(i) LOOP_CODE(i) _ITER_18(i - 1)
#define _ITER_20(i) LOOP_CODE(i) _ITER_19(i - 1)
#define _ITER_21(i) LOOP_CODE(i) _ITER_20(i - 1)
#define _ITER_22(i) LOOP_CODE(i) _ITER_21(i - 1)
#define _ITER_23(i) LOOP_CODE(i) _ITER_22(i - 1)
#define _ITER_24(i) LOOP_CODE(i) _ITER_23(i - 1)
#define _ITER_25(i) LOOP_CODE(i) _ITER_24(i - 1)
#define _ITER_26(i) LOOP_CODE(i) _ITER_25(i - 1)
#define _ITER_27(i) LOOP_CODE(i) _ITER_26(i - 1)
#define _ITER_28(i) LOOP_CODE(i) _ITER_27(i - 1)
#define _ITER_29(i) LOOP_CODE(i) _ITER_28(i - 1)
#define _ITER_30(i) LOOP_CODE(i) _ITER_29(i - 1)
#define _ITER_31(i) LOOP_CODE(i) _ITER_30(i - 1)
#define _ITER_32(i) LOOP_CODE(i) _ITER_31(i - 1)
#define _LOOP_EX(n) do { _ITER_##n(n - 1) } while(0)
#define LOOP(n) _LOOP_EX(n)

// Array initialization - fixed value
#define _ARR_1(value, size)  value
#define _ARR_2(value, size)  value, _ARR_1(value, size - 1)
#define _ARR_3(value, size)  value, _ARR_2(value, size - 1)
#define _ARR_4(value, size)  value, _ARR_3(value, size - 1)
#define _ARR_5(value, size)  value, _ARR_4(value, size - 1)
#define _ARR_6(value, size)  value, _ARR_5(value, size - 1)
#define _ARR_7(value, size)  value, _ARR_6(value, size - 1)
#define _ARR_8(value, size)  value, _ARR_7(value, size - 1)
#define _ARR_9(value, size)  value, _ARR_8(value, size - 1)
#define _ARR_10(value, size) value, _ARR_9(value, size - 1)
#define _ARR_11(value, size) value, _ARR_10(value, size - 1)
#define _ARR_12(value, size) value, _ARR_11(value, size - 1)
#define _ARR_13(value, size) value, _ARR_12(value, size - 1)
#define _ARR_14(value, size) value, _ARR_13(value, size - 1)
#define _ARR_15(value, size) value, _ARR_14(value, size - 1)
#define _ARR_16(value, size) value, _ARR_15(value, size - 1)
#define _ARR_17(value, size) value, _ARR_16(value, size - 1)
#define _ARR_18(value, size) value, _ARR_17(value, size - 1)
#define _ARR_19(value, size) value, _ARR_18(value, size - 1)
#define _ARR_20(value, size) value, _ARR_19(value, size - 1)
#define _ARR_21(value, size) value, _ARR_20(value, size - 1)
#define _ARR_22(value, size) value, _ARR_21(value, size - 1)
#define _ARR_23(value, size) value, _ARR_22(value, size - 1)
#define _ARR_24(value, size) value, _ARR_23(value, size - 1)
#define _ARR_25(value, size) value, _ARR_24(value, size - 1)
#define _ARR_26(value, size) value, _ARR_25(value, size - 1)
#define _ARR_27(value, size) value, _ARR_26(value, size - 1)
#define _ARR_28(value, size) value, _ARR_27(value, size - 1)
#define _ARR_29(value, size) value, _ARR_28(value, size - 1)
#define _ARR_30(value, size) value, _ARR_29(value, size - 1)
#define _ARR_31(value, size) value, _ARR_30(value, size - 1)
#define _ARR_32(value, size) value, _ARR_31(value, size - 1)
#define _ARR_EX(value, size) _ARR_##size(value, size)
#define ARRAY_INIT(value, size) _ARR_EX(value, size)

// Array initialization - sequence
#define _ARR_SEQ_1(value, size)  value
#define _ARR_SEQ_2(value, size)  value, _ARR_SEQ_1( value + 1, size - 1)
#define _ARR_SEQ_3(value, size)  value, _ARR_SEQ_2( value + 1, size - 1)
#define _ARR_SEQ_4(value, size)  value, _ARR_SEQ_3( value + 1, size - 1)
#define _ARR_SEQ_5(value, size)  value, _ARR_SEQ_4( value + 1, size - 1)
#define _ARR_SEQ_6(value, size)  value, _ARR_SEQ_5( value + 1, size - 1)
#define _ARR_SEQ_7(value, size)  value, _ARR_SEQ_6( value + 1, size - 1)
#define _ARR_SEQ_8(value, size)  value, _ARR_SEQ_7( value + 1, size - 1)
#define _ARR_SEQ_9(value, size)  value, _ARR_SEQ_8( value + 1, size - 1)
#define _ARR_SEQ_10(value, size) value, _ARR_SEQ_9( value + 1, size - 1)
#define _ARR_SEQ_11(value, size) value, _ARR_SEQ_10(value + 1, size - 1)
#define _ARR_SEQ_12(value, size) value, _ARR_SEQ_11(value + 1, size - 1)
#define _ARR_SEQ_13(value, size) value, _ARR_SEQ_12(value + 1, size - 1)
#define _ARR_SEQ_14(value, size) value, _ARR_SEQ_13(value + 1, size - 1)
#define _ARR_SEQ_15(value, size) value, _ARR_SEQ_14(value + 1, size - 1)
#define _ARR_SEQ_16(value, size) value, _ARR_SEQ_15(value + 1, size - 1)
#define _ARR_SEQ_17(value, size) value, _ARR_SEQ_16(value + 1, size - 1)
#define _ARR_SEQ_18(value, size) value, _ARR_SEQ_17(value + 1, size - 1)
#define _ARR_SEQ_19(value, size) value, _ARR_SEQ_18(value + 1, size - 1)
#define _ARR_SEQ_20(value, size) value, _ARR_SEQ_19(value + 1, size - 1)
#define _ARR_SEQ_21(value, size) value, _ARR_SEQ_20(value + 1, size - 1)
#define _ARR_SEQ_22(value, size) value, _ARR_SEQ_21(value + 1, size - 1)
#define _ARR_SEQ_23(value, size) value, _ARR_SEQ_22(value + 1, size - 1)
#define _ARR_SEQ_24(value, size) value, _ARR_SEQ_23(value + 1, size - 1)
#define _ARR_SEQ_25(value, size) value, _ARR_SEQ_24(value + 1, size - 1)
#define _ARR_SEQ_26(value, size) value, _ARR_SEQ_25(value + 1, size - 1)
#define _ARR_SEQ_27(value, size) value, _ARR_SEQ_26(value + 1, size - 1)
#define _ARR_SEQ_28(value, size) value, _ARR_SEQ_27(value + 1, size - 1)
#define _ARR_SEQ_29(value, size) value, _ARR_SEQ_28(value + 1, size - 1)
#define _ARR_SEQ_30(value, size) value, _ARR_SEQ_29(value + 1, size - 1)
#define _ARR_SEQ_31(value, size) value, _ARR_SEQ_30(value + 1, size - 1)
#define _ARR_SEQ_32(value, size) value, _ARR_SEQ_31(value + 1, size - 1)
#define _ARR_SEQ_EX(value, size) _ARR_SEQ_##size(value, size)
#define ARRAY_INIT_SEQ(value, size) _ARR_SEQ_EX(value, size)

// Code blocks
#define START_BLOCK  do
#define EXIT_BLOCK   break
#define END_BLOCK    while(NULL)
#define START_LOOP   do
#define END_LOOP     while(NULL)

// Masks
#define MASK_SPR              0x10
#define MASK_BG               0x08
#define MASK_EDGE_SPR         0x04
#define MASK_EDGE_BG          0x02
#define MASK_TINT_RED         0x20
#define MASK_TINT_BLUE        0x40
#define MASK_TINT_GREEN       0x80
#define MASK_MONO             0x01

// Multiply by 3
#define x3(v) ( \
  (v) + (v) + (v) \
)

// Obtain the corresponding VRAM attribute
// address from a VRAM nametable address
#define NT2ATTR_ADDRESS(a) ( \
  ((a & 0x2c00) | 0x3c0 | ((a >> 4) & 0x38) | ((a >> 2) & 0x07)) \
)

// Swap bytes
#define SWAP_BYTES(value_16bit) ( \
  ((value_16bit << 8) & 0xff00) | ((value_16bit >> 8) & 0x00ff) \
)

// Strings
#define EMPTY_STRING ""
#define _STR(s) #s
#define STR(s) _STR(s)

// Bool
typedef enum { false, true } bool;

#endif // core.h
