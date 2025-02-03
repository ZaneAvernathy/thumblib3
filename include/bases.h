
#ifndef THUMBLIB_3_BASES
#define THUMBLIB_3_BASES

  /* THUMBLIB3 opcode base macros
   *
   * These macros are used to construct opcodes and
   * their overloads. See `include/opcodes.h` for a final
   * list of opcodes and their usage.
   */

  // `move shifted register`

    #define MSR_BASE(Opcode, Rd, Rs, Offset)     \
      asm THUMBLIB_OP_FLAGS (                    \
        Opcode " %[_Rd], %[_Rs], %[_Offset]"     \
        : [_Rd] "=l" (Rd)                        \
        : [_Rs] "l" (Rs), [_Offset] "N" (Offset) \
        : "cc"                                   \
      );

    #define MSR_I_3(Opcode, Rd, Immediate, ...) MSR_BASE(Opcode, Rd, Rd, Immediate)
    #define MSR_I_4(Opcode, Rd, Rs, Immediate, ...) MSR_BASE(Opcode, Rd, Rs, Immediate)

  // `addition/subtraction` with 3 registers

    #define ADDSUB_R_BASE(Opcode, Rd, Rs, Rn) \
      asm THUMBLIB_OP_FLAGS (                 \
        Opcode " %[_Rd], %[_Rs], %[_Rn]"      \
        : [_Rd] "=l" (Rd)                     \
        : [_Rs] "l" (Rs), [_Rn] "l" (Rn)      \
        : "cc"                                \
      );

    #define ADDSUB_R_3(Opcode, Rd, Rn, ...) ADDSUB_R_BASE(Opcode, Rd, Rd, Rn)
    #define ADDSUB_R_4(Opcode, Rd, Rs, Rn, ...) ADDSUB_R_BASE(Opcode, Rd, Rs, Rn)

  // `addition/subtraction` with two registers
  // and small immediate

    #define ADDSUB_RI_BASE(Opcode, Rd, Rs, Immediate)  \
      asm THUMBLIB_OP_FLAGS (                          \
        Opcode " %[_Rd], %[_Rs], %[_Immediate]"        \
        : [_Rd] "=l" (Rd)                              \
        : [_Rs] "l" (Rs), [_Immediate] "L" (Immediate) \
        : "cc"                                         \
      );

    #define ADDSUB_RI_3(Opcode, Rd, Immediate, ...) ADDSUB_RI_BASE(Opcode, Rd, Rd, Immediate)
    #define ADDSUB_RI_4(Opcode, Rd, Rs, Immediate, ...) ADDSUB_RI_BASE(Opcode, Rd, Rs, Immediate)

  // `addition/subtraction` with one register
  // and a large immediate

    #define ADDSUB_I_BASE(Opcode, Rd, Immediate) \
      asm THUMBLIB_OP_FLAGS (                    \
        Opcode " %[_Rd], %[_Immediate]"          \
        : [_Rd] "+l" (Rd)                        \
        : [_Immediate] "I" (Immediate)           \
        : "cc"                                   \
      );

  // `arithmetic logic unit` with return value

    #define ALU_BASE(Opcode, Rd, Rs) \
      asm THUMBLIB_OP_FLAGS (        \
        Opcode " %[_Rd], %[_Rs]"     \
        : [_Rd] "+l" (Rd)            \
        : [_Rs] "l" (Rs)             \
        : "cc"                       \
      );

  // `arithmetic logic unit` with one parameter

    #define ALU_1_BASE(Opcode, Rd, Rs) \
      asm THUMBLIB_OP_FLAGS (          \
        Opcode " %[_Rd], %[_Rs]"       \
        : [_Rd] "=l" (Rd)              \
        : [_Rs] "l" (Rs)               \
        : "cc"                         \
      );

  // `arithmetic logic unit` with no output

    #define ALU_VOID_BASE(Opcode, Rd, Rs) \
      asm THUMBLIB_OP_FLAGS (             \
        Opcode " %[_Rd], %[_Rs]"          \
        :                                 \
        : [_Rd] "l" (Rd), [_Rs] "l" (Rs)  \
        : "cc"                            \
      );

  // `store` with 3 registers

    #define STR_BASE(Opcode, Size, Rd, Rb, Ro)           \
      asm THUMBLIB_OP_FLAGS (                            \
        Opcode " %[_Rd], [%[_Rb], %[_Ro]]"               \
        : "=m" (*(Size*)((int)Rb + (int)Ro))             \
        : [_Rd] "l" (Rd), [_Rb] "l" (Rb), [_Ro] "l" (Ro) \
      );

  // `store` with 2 registers and an immediate

    // Technically, the `I` here is incorrect, but it's
    // so convenient to group these and the assembler can
    // spit the error itself.
    #define STR_I_BASE(Opcode, Size, Rd, Rb, Immediate)                \
      asm THUMBLIB_OP_FLAGS (                                          \
        Opcode " %[_Rd], [%[_Rb], %[_Immediate]]"                      \
        : "=m" (*(Size*)((int)Rb + Immediate))                         \
        : [_Rd] "l" (Rd), [_Rb] "l" (Rb), [_Immediate] "I" (Immediate) \
      );

    #define STR_I_4(Opcode, Size, Rd, Rb, ...) STR_I_BASE(Opcode, Size, Rd, Rb, 0)
    #define STR_I_5(Opcode, Size, Rd, Rb, Immediate, ...) STR_I_BASE(Opcode, Size, Rd, Rb, Immediate)

  // Shorthands to avoid specifying `_I` when you want
  // `str Rd, [Rb]`
  #define STR_4(Opcode, Size, Rd, Rb, ...) STR_I_BASE(Opcode, Size, Rd, Rb, 0)
  #define STR_5(Opcode, Size, Rd, Rb, Ro, ...) STR_BASE(Opcode, Size, Rd, Rb, Ro)

  // `load` with 3 registers

    #define LDR_BASE(Opcode, Size, Rd, Rb, Ro)                              \
      asm THUMBLIB_OP_FLAGS (                                               \
        Opcode " %[_Rd], [%[_Rb], %[_Ro]]"                                  \
        : [_Rd] "=l" (Rd)                                                   \
        : [_Rb] "l" (Rb), [_Ro] "l" (Ro), "m" (*(Size*)((int)Rb + (int)Ro)) \
      );

  // `load` with 2 registers and an immediate

    // See `STR_I_BASE` comments.
    #define LDR_I_BASE(Opcode, Size, Rd, Rb, Immediate)                                     \
      asm THUMBLIB_OP_FLAGS (                                                               \
        Opcode " %[_Rd], [%[_Rb], %[_Immediate]]"                                           \
        : [_Rd] "=l" (Rd)                                                                   \
        : [_Rb] "l" (Rb), [_Immediate] "I" (Immediate), "m" (*(Size*)((int)Rb + Immediate)) \
      );

    #define LDR_I_4(Opcode, Size, Rd, Rb, ...) LDR_I_BASE(Opcode, Size, Rd, Rb, 0)
    #define LDR_I_5(Opcode, Size, Rd, Rb, Immediate, ...) LDR_I_BASE(Opcode, Size, Rd, Rb, Immediate)

  // Shorthands to avoid specifying `_I` when you want
  // `ldr Rd, [Rb]`
  #define LDR_4(Opcode, Size, Rd, Rb, ...) LDR_I_BASE(Opcode, Size, Rd, Rb, 0)
  #define LDR_5(Opcode, Size, Rd, Rb, Ro, ...) LDR_BASE(Opcode, Size, Rd, Rb, Ro)

  // stack pointer relative memory access

    #define STR_SP_BASE(Rd, Immediate)                 \
      asm THUMBLIB_OP_FLAGS (                          \
        "str %[_Rd], [sp, %[_Immediate]]"              \
        :                                              \
        : [_Rd] "l" (Rd), [_Immediate] "M" (Immediate) \
        : "memory"                                     \
      );

    #define STR_SP_2(Opcode, Rd, ...) STR_SP_BASE(Rd, 0)
    #define STR_SP_3(Opcode, Rd, Immediate, ...) STR_SP_BASE(Rd, Immediate)

    #define LDR_SP_BASE(Rd, Immediate)    \
      asm THUMBLIB_OP_FLAGS (             \
        "ldr %[_Rd], [sp, %[_Immediate]]" \
        : [_Rd] "=l" (Rd)                 \
        : [_Immediate] "M" (Immediate)    \
        : "memory"                        \
      );

    #define LDR_SP_2(Opcode, Rd, ...) LDR_SP_BASE(Rd, 0)
    #define LDR_SP_3(Opcode, Rd, Immediate, ...) LDR_SP_BASE(Rd, Immediate)

  // `get relative address`

    #define GRA_BASE(Opcode, Register, Rd, Immediate) \
      asm THUMBLIB_OP_FLAGS (                         \
        Opcode " %[_Rd], " Register ", %[_Immediate]" \
        : [_Rd] "=l" (Rd)                             \
        : [_Immediate] "M" (Immediate)                \
      );

    #define GRA_3(Opcode, Register, Rd, ...) GRA_BASE(Opcode, Register, Rd, 0)
    #define GRA_4(Opcode, Register, Rd, Immediate, ...) GRA_BASE(Opcode, Register, Rd, Immediate)

  // load PC relative

    #define LDR_PC_BASE(Rd, Immediate)    \
      asm THUMBLIB_OP_FLAGS (             \
        "ldr %[_Rd], [pc, %[_Immediate]]" \
        : [_Rd] "=l" (Rd)                 \
        : [_Immediate] "M" (Immediate)    \
        : "memory"                        \
      );

    #define LDR_PC_2(Opcode, Rd, ...) LDR_PC_BASE(Rd, 0)
    #define LDR_PC_3(Opcode, Rd, Immediate) LDR_PC_BASE(Rd, Immediate)

  // conditional branches

    #define BRANCH_BASE(Opcode, Label) \
      asm goto THUMBLIB_OP_FLAGS (     \
        Opcode " %l0"                  \
        :                              \
        :                              \
        : "memory"                     \
        : Label                        \
      );

    // Absolute rather than label, for external symbols
    #define BRANCH_ABS_BASE(Opcode, Position) \
      asm THUMBLIB_OP_FLAGS (                 \
        Opcode " %c0"                         \
        :                                     \
        : "i" (Position)                      \
      );

#endif // THUMBLIB_3_BASES
