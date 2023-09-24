
#ifndef THUMBLIB_3_OPCODES
#define THUMBLIB_3_OPCODES

  /* THUMBLIB3 opcode listing
   *
   * This file defines all of the THUMB opcodes provided
   * by the library and documents their usage.
   */

  /* Opcode cheat sheet
   *
   * All registers are r0-r7 unless r8-r15/sp/pc are mentioned.
   * This includes pseudoinstructions and shorthands.
   *
   * THUMBLIB syntax              | THUMB syntax       | Explanation
   *                              |                    |
   * MOV_I(Rd, Imm8bit)           | mov Rd, #nn        | Rd = nn
   * MOV(Rd, Rs)                  | mov Rd, Rs         | Rd = Rs + 0
   * MOV_H(Rd, Rs)                | mov Rd, Rs         | Rd = Rs, Rd and/or Rs r8-r12
   * MOV_SP(Rd)                   | mov Rd, sp         | Rd = sp, Rd r0-r12
   * MOV_TO_SP(Rs)                | mov sp, Rs         | sp = Rs, Rs r0-r12
   * MOV_LR(Rd)                   | mov Rd, lr         | Rd = lr, Rd r0-r12
   * MOV_TO_LR(Rs)                | mov lr, Rs         | lr = Rs, Rs r0-r12
   * MOV_PC(Rd)                   | mov Rd, pc         | Rd = $ + 4, Rd r0-r12
   * MOV_TO_PC(Rs)                | mov pc, Rs         | pc = Rs, Rs r0-r12
   * MVN(Rd, Rs)                  | mvn Rd, Rs         | Rd = NOT Rs
   * AND(Rd, Rs)                  | and Rd, Rs         | Rd = Rd AND Rs
   * TST(Rd, Rs)                  | tst Rd, Rs         | Void = Rd AND Rs
   * BIC(Rd, Rs)                  | bic Rd, Rs         | Rd = Rd AND NOT Rs
   * ORR(Rd, Rs)                  | orr Rd, Rs         | Rd = Rd OR Rs
   * EOR(Rd, Rs)                  | eor Rd, Rs         | Rd = Rd XOR Rs
   * LSL_I(Rd, Rs, Imm5bit)       | lsl Rd, Rs, #nn    | Rd = Rs SHL nn
   * LSL_I(Rd, Imm5bit)           | lsl Rd, #nn        | Rd = Rd SHL nn
   * LSL(Rd, Rs)                  | lsl Rd, Rs         | Rd = Rd SHL (Rs AND 0xFF)
   * LSR_I(Rd, Rs, Imm5bit)       | lsr Rd, Rs, #nn    | Rd = Rs SHR nn
   * LSR_I(Rd, Imm5bit)           | lsr Rd, #nn        | Rd = Rd SHR nn
   * LSR(Rd, Rs)                  | lsr Rd, Rs         | Rd = Rd SHR (Rs AND 0xFF)
   * ASR_I(Rd, Rs, Imm5bit)       | asr Rd, Rs, #nn    | Rd = Rs SAR nn
   * ASR_I(Rd, Imm5bit)           | asr Rd, #nn        | Rd = Rd SAR nn
   * ASR(Rd, Rs)                  | asr Rd, Rs         | Rd = Rd SAR (Rs AND 0xFF)
   * ROR(Rd, Rs)                  | ror Rd, Rs         | Rd = Rd ROR (Rs AND 0xFF)
   * NOP()                        | nop                | r8 = r8
   * ADD_RI(Rd, Rs, Imm3bit)      | add Rd, Rs, #nn    | Rd = Rs + nn
   * ADD_RI(Rd, Imm3bit)          | ---                | Rd = Rd + nn, use ADD_I
   * ADD_I(Rd, Imm8bit)           | add Rd, #nn        | Rd = Rd + nn
   * ADD_R(Rd, Rs, Rn)            | add Rd, Rs, Rn     | Rd = Rs + Rn
   * ADD_R(Rd, Rn)                | add Rd, Rn         | Rd = Rd + Rn
   * ADD_H(Rd, Rs)                | add Rd, Rn         | Rd = Rd + Rn, Rd and/or Rs r8-r12
   * ADD_SP(Rd)                   | add Rd, sp         | Rd = Rd + sp, Rd r0-r12
   * ADD_TO_SP_H(Rs)              | add sp, Rs         | sp = sp + Rs, Rs r0-r12
   * ADD_LR(Rd)                   | add Rd, lr         | Rd = Rd + lr, Rd r0-r12
   * ADD_TO_LR(Rs)                | add lr, Rs         | lr = lr + Rs, Rs r0-r12
   * ADD_PC(Rd)                   | add Rd, pc         | Rd = Rd + ($ + 4), Rd r0-r12
   * ADD_TO_PC(Rs)                | add pc, Rs         | pc = pc + Rs, Rs r0-r12
   * PCR(Rd, Imm8bit*4)           | add Rd, pc, #nn    | Rd = (($ + 4) AND NOT 2) + nn
   * SPR(Rd, Imm8bit*4)           | add Rd, sp, #nn    | Rd = sp + nn
   * ADD_TO_SP(Imm7bit*4)         | add sp, #nn        | sp = sp + nn
   * ADD_TO_SP(-Imm7bit*4)        | add sp, #-nn       | sp = sp - nn
   * SUB_FROM_SP(Imm7bit*4)       | sub sp, #nn        | sp = sp - nn
   * ADC(Rd, Rs)                  | adc Rd, Rs         | Rd = Rd + Rs + Cy
   * SUB_RI(Rd, Rs, Imm3bit)      | sub Rd, Rs, #nn    | Rd = Rs - nn
   * SUB_RI(Rd, Imm3bit)          | ---                | Rd = Rd - nn, use SUB_I
   * SUB_I(Rd, Imm8bit)           | sub Rd, #nn        | Rd = Rd - nn
   * SUB_R(Rd, Rs, Rn)            | sub Rd, Rs, Rn     | Rd = Rs - Rn
   * SUB_R(Rd, Rn)                | sub Rd, Rn         | Rd = Rd - Rn
   * SBC(Rd, Rs)                  | sbc Rd, Rs         | Rd = Rd - Rs - (NOT Cy)
   * NEG(Rd, Rs)                  | neg Rd, Rs         | Rd = 0 - Rs
   * CMP_I(Rd, Imm8bit)           | cmp Rd, #nn        | Void = Rd - nn
   * CMP(Rd, Rs)                  | cmp Rd, Rs         | Void = Rd - Rs
   * CMP_H(Rd, Rs)                | cmp Rd, Rs         | Void = Rd - Rs, Rd and/or Rs r8-r12
   * CMP_SP(Rd)                   | cmp Rd, sp         | Void = Rd - sp, Rd r0-r12
   * CMP_TO_SP(Rs)                | cmp sp, Rs         | Void = sp - Rs, Rs r0-r12
   * CMP_LR(Rd)                   | cmp Rd, lr         | Void = Rd - lr, Rd r0-r12
   * CMP_TO_LR(Rs)                | cmp lr, Rs         | Void = lr - Rs, Rs r0-r12
   * CMP_PC(Rd)                   | cmp Rd, pc         | Void = Rd - ($ + 4), Rd r0-r12
   * CMP_TO_PC(Rs)                | cmp pc, Rs         | Void = ($ + 4) - Rs, Rs r0-r12
   * CMN(Rd, Rs)                  | cmn Rd, Rs         | Void = Rd + Rs
   * MUL(Rd, Rs)                  | mul Rd, Rs         | Rd = Rd * Rs
   * B(Label)                     | b Label            | pc = &&Label
   * B_ABS(Position)              | b Position         | pc = Position
   * BL(Label)                    | bl Label           | pc = &&Label, lr = $ + 5
   * BEQ(Label)                   | beq Label          | if cond: pc = &&Label
   * BNE(Label)                   | bne Label          | if cond: pc = &&Label
   * BCS(Label)                   | bcs Label          | if cond: pc = &&Label
   * BCC(Label)                   | bcc Label          | if cond: pc = &&Label
   * BMI(Label)                   | bmi Label          | if cond: pc = &&Label
   * BPL(Label)                   | bpl Label          | if cond: pc = &&Label
   * BVS(Label)                   | bvs Label          | if cond: pc = &&Label
   * BVC(Label)                   | bvc Label          | if cond: pc = &&Label
   * BHI(Label)                   | bhi Label          | if cond: pc = &&Label
   * BLS(Label)                   | bls Label          | if cond: pc = &&Label
   * BGE(Label)                   | bge Label          | if cond: pc = &&Label
   * BLT(Label)                   | blt Label          | if cond: pc = &&Label
   * BGT(Label)                   | bgt Label          | if cond: pc = &&Label
   * BLE(Label)                   | ble Label          | if cond: pc = &&Label
   * BEQ_ABS(Position)            | beq Position       | if cond: pc = Position
   * BNE_ABS(Position)            | bne Position       | if cond: pc = Position
   * BCS_ABS(Position)            | bcs Position       | if cond: pc = Position
   * BCC_ABS(Position)            | bcc Position       | if cond: pc = Position
   * BMI_ABS(Position)            | bmi Position       | if cond: pc = Position
   * BPL_ABS(Position)            | bpl Position       | if cond: pc = Position
   * BVS_ABS(Position)            | bvs Position       | if cond: pc = Position
   * BVC_ABS(Position)            | bvc Position       | if cond: pc = Position
   * BHI_ABS(Position)            | bhi Position       | if cond: pc = Position
   * BLS_ABS(Position)            | bls Position       | if cond: pc = Position
   * BGE_ABS(Position)            | bge Position       | if cond: pc = Position
   * BLT_ABS(Position)            | blt Position       | if cond: pc = Position
   * BGT_ABS(Position)            | bgt Position       | if cond: pc = Position
   * BLE_ABS(Position)            | ble Position       | if cond: pc = Position
   * BX(Rs)                       | bx Rs              | pc = Rs, ARM/THUMB (Rs bit0), Rs r0-r12
   * BX_SP()                      | bx sp              | pc = sp, ARM/THUMB (sp bit0)
   * BX_LR()                      | bx lr              | pc = lr, ARM/THUMB (lr bit0)
   * BX_PC()                      | bx pc              | pc = (($ + 4) AND NOT 2), ARM
   * SWI(Imm8bit)                 | swi nn             | pc = 8, lr = $ + 2, ARM SVC
   * LDR_I(Rd, Rb, Imm5bit*4)     | ldr Rd, [Rb, #nn]  | Rd = WORD[Rb + nn]
   * LDR_I(Rd, Rb)                | ldr Rd, [Rb, #0]   | Rd = WORD[Rb + 0]
   * LDR_PC(Rd, Imm8bit*4)        | ldr Rd, [pc, #nn]  | Rd = WORD[pc + nn]
   * LDR_PC(Rd)                   | ldr Rd, [pc, #0]   | Rd = WORD[pc + 0]
   * LDR_POOL(Rd, Value)          | ldr Rd, =Value     | Rd = Value, Value in literal pool
   * LDR_SP(Rd, Imm8bit*4)        | ldr Rd, [sp, #nn]  | Rd = WORD[sp + nn]
   * LDR_SP(Rd)                   | ldr Rd, [sp, #0]   | Rd = WORD[sp + 0]
   * LDR(Rd, Rb, Ro)              | ldr Rd, [Rb, Ro]   | Rd = WORD[Rb + Ro]
   * LDR(Rd, Rb)                  | ldr Rd, [Rb]       | Rd = WORD[Rb]
   * LDRB_I(Rd, Rb, Imm5bit*1)    | ldrb Rd, [Rb, #nn] | Rd = BYTE[Rb + nn]
   * LDRB_I(Rd, Rb)               | ldrb Rd, [Rb, #0]  | Rd = BYTE[Rb + 0]
   * LDRB(Rd, Rb, Ro)             | ldrb Rd, [Rb, Ro]  | Rd = BYTE[Rb + Ro]
   * LDRB(Rd, Rb)                 | ldrb Rd, [Rb]      | Rd = BYTE[Rb]
   * LDRH_I(Rd, Rb, Imm5bit*2)    | ldrh Rd, [Rb, #nn] | Rd = HALFWORD[Rb + nn]
   * LDRH_I(Rd, Rb)               | ldrh Rd, [Rb, #0]  | Rd = HALFWORD[Rb + 0]
   * LDRH(Rd, Rb, Ro)             | ldrh Rd, [Rb, Ro]  | Rd = HALFWORD[Rb + Ro]
   * LDRH(Rd, Rb)                 | ldrh Rd, [Rb]      | Rd = HALFWORD[Rb]
   * LDSB(Rd, Rb, Ro)             | ldsb Rd, [Rb, Ro]  | Rd = SIGNED_BYTE[Rb + Ro]
   * LDSH(Rd, Rb, Ro)             | ldsh Rd, [Rb, Ro]  | Rd = SIGNED_HALFWORD[Rb + Ro]
   * STR_I(Rd, Rb, Imm5bit*4)     | str Rd, [Rb, #nn]  | WORD[Rb + nn] = Rd
   * STR_I(Rd, Rb)                | str Rd, [Rb, #0]   | WORD[Rb + 0] = Rd
   * STR_SP(Rd, Imm8bit*4)        | str Rd, [sp, #nn]  | WORD[sp + nn] = Rd
   * STR_SP(Rd)                   | str Rd, [sp, #0]   | WORD[sp + 0] = Rd
   * STR(Rd, Rb, Ro)              | str Rd, [Rb, Ro]   | WORD[Rb + Ro] = Rd
   * STR(Rd, Rb)                  | str Rd, [Rb]       | WORD[Rb] = Rd
   * STRB_I(Rd, Rb, Imm5bit*1)    | strb Rd, [Rb, #nn] | BYTE[Rb + nn] = Rd
   * STRB_I(Rd, Rb)               | strb Rd, [Rb]      | BYTE[Rb + 0] = Rd
   * STRB(Rd, Rb, Ro)             | strb Rd, [Rb, Ro]  | BYTE[Rb + Ro] = Rd
   * STRB(Rd, Rb)                 | strb Rd, [Rb]      | BYTE[Rb] = Rd
   * STRH_I(Rd, Rb, Imm5bit*2)    | strh Rd, [Rb, #nn] | HALFWORD[Rb + nn] = Rd
   * STRH_I(Rd, Rb)               | strh Rd, [Rb, #0]  | HALFWORD[Rb + 0] = Rd
   * STRH(Rd, Rb, Ro)             | strh Rd, [Rb, Ro]  | HALFWORD[Rb + Ro] = Rd
   * STRH(Rd, Rb)                 | strh Rd, [Rb]      | HALFWORD[Rb] = Rd
   * PUSH(Registers...)           | push {...}         |
   * PUSH_WITH_LR(Registers...)   | push {..., lr}     |
   * PUSH_LR()                    | push {lr}          |
   * POP(Registers...)            | pop {...}          |
   * POP_WITH_PC(Registers...)    | pop {..., pc}      |
   * POP_PC()                     | pop {pc}           |
   * STMIA(Rb, Registers...)      | stmia Rb!, {...}   |
   * LDMIA(Rb, Registers...)      | ldmia Rb!, {...}   |
   *
   * Notes:
   * Imm3bit   -> 0-7
   * Imm5bit   -> 0-31
   * Imm5bit*1 -> 0-31
   * Imm5bit*2 -> 0-62, in multiples of 2
   * Imm5bit*4 -> 0-124, in multiples of 4
   * Imm8bit   -> 0-255
   * Imm7bit*4 -> 0-508, in multiples of 4
   * Imm8bit*4 -> 0-1020, in multiples of 4
   *
   * $ denotes the instruction's address
   *
   * Registers... indicates a comma-separated list of
   * low registers.
   */

  #define LSL_I(...) _THUMBLIB_APPLY_OVERLOAD(MSR_I_, "lsl", __VA_ARGS__)
  #define LSR_I(...) _THUMBLIB_APPLY_OVERLOAD(MSR_I_, "lsr", __VA_ARGS__)
  #define ASR_I(...) _THUMBLIB_APPLY_OVERLOAD(MSR_I_, "asr", __VA_ARGS__)

  #define ADD_R(...) _THUMBLIB_APPLY_OVERLOAD(ADDSUB_R_, "add", __VA_ARGS__)
  #define SUB_R(...) _THUMBLIB_APPLY_OVERLOAD(ADDSUB_R_, "sub", __VA_ARGS__)

  #define ADD_RI(...) _THUMBLIB_APPLY_OVERLOAD(ADDSUB_RI_, "add", __VA_ARGS__)
  #define SUB_RI(...) _THUMBLIB_APPLY_OVERLOAD(ADDSUB_RI_, "sub", __VA_ARGS__)

  // Pseudoinstruction, affects cpsr
  #define MOV(Rd, Rs) ADD_RI(Rd, Rs, 0)

  #define MOV_I(Rd, Immediate)       \
    asm THUMBLIB_OP_FLAGS (          \
      "mov %[_Rd], %[_Immediate]"    \
      : [_Rd] "=l" (Rd)              \
      : [_Immediate] "I" (Immediate) \
      : "cc"                         \
    );

  #define ADD_I(Rd, Immediate) ADDSUB_I_BASE("add", Rd, Immediate)
  #define SUB_I(Rd, Immediate) ADDSUB_I_BASE("sub", Rd, Immediate)

  #define CMP_I(Rd, Immediate)                       \
    asm THUMBLIB_OP_FLAGS (                          \
      "cmp %[_Rd], %[_Immediate]"                    \
      :                                              \
      : [_Rd] "l" (Rd), [_Immediate] "I" (Immediate) \
      : "cc"                                         \
    );

  #define AND(Rd, Rs) ALU_BASE("and", Rd, Rs)
  #define EOR(Rd, Rs) ALU_BASE("eor", Rd, Rs)
  #define LSL(Rd, Rs) ALU_BASE("lsl", Rd, Rs)
  #define LSR(Rd, Rs) ALU_BASE("lsr", Rd, Rs)
  #define ASR(Rd, Rs) ALU_BASE("asr", Rd, Rs)
  #define ADC(Rd, Rs) ALU_BASE("adc", Rd, Rs)
  #define SBC(Rd, Rs) ALU_BASE("sbc", Rd, Rs)
  #define ROR(Rd, Rs) ALU_BASE("ror", Rd, Rs)
  #define ORR(Rd, Rs) ALU_BASE("orr", Rd, Rs)
  #define MUL(Rd, Rs) ALU_BASE("mul", Rd, Rs)
  #define BIC(Rd, Rs) ALU_BASE("bic", Rd, Rs)

  #define NEG(Rd, Rs) ALU_1_BASE("neg", Rd, Rs)
  #define MVN(Rd, Rs) ALU_1_BASE("mvn", Rd, Rs)

  #define TST(Rd, Rs) ALU_VOID_BASE("tst", Rd, Rs)
  #define CMP(Rd, Rs) ALU_VOID_BASE("cmp", Rd, Rs)
  #define CMN(Rd, Rs) ALU_VOID_BASE("cmn", Rd, Rs)

  // Shorthand names for 2-register usage of 3-register ops
  #define ADD(Rd, Rs) ADDSUB_R_3("add", Rd, Rs)
  #define SUB(Rd, Rs) ADDSUB_R_3("sub", Rd, Rs)

  #define ADD_H(Rd, Rs)     \
    asm THUMBLIB_OP_FLAGS ( \
      "add %[_Rd], %[_Rs]"  \
      : [_Rd] "+lh" (Rd)    \
      : [_Rs] "lh" (Rs)     \
    );

  #define CMP_H(Rd, Rs)                  \
    asm THUMBLIB_OP_FLAGS (              \
      "cmp %[_Rd], %[_Rs]"               \
      :                                  \
      : [_Rd] "lh" (Rd), [_Rs] "lh" (Rs) \
      : "cc"                             \
    );

  #define MOV_H(Rd, Rs)     \
    asm THUMBLIB_OP_FLAGS ( \
      "mov %[_Rd], %[_Rs]"  \
      : [_Rd] "=lh" (Rd)    \
      : [_Rs] "lh" (Rs)     \
    );

  // Hardcoded high register variants because
  // GCC really doesn't want you specifying these.
  // Use at your own risk.

  #define ADD_SP(Rd)        \
    asm THUMBLIB_OP_FLAGS ( \
      "add %[_Rd], sp"      \
      : [_Rd] "+lh" (Rd)    \
      :                     \
      :                     \
    );

  // Different name to avoid shadowing dedicated
  // SP-adjusting opcode
  #define ADD_TO_SP_H(Rs)   \
    asm THUMBLIB_OP_FLAGS ( \
      "add sp, %[_Rs]"      \
      :                     \
      : [_Rs] "lh" (Rs)     \
      :                     \
    );

  #define ADD_LR(Rd)        \
    asm THUMBLIB_OP_FLAGS ( \
      "add %[_Rd], lr"      \
      : [_Rd] "+lh" (Rd)    \
      :                     \
      :                     \
    );

  #define ADD_TO_LR(Rs)     \
    asm THUMBLIB_OP_FLAGS ( \
      "add lr, %[_Rs]"      \
      :                     \
      : [_Rs] "lh" (Rs)     \
      : "lr"                \
    );

  #define ADD_PC(Rd)        \
    asm THUMBLIB_OP_FLAGS ( \
      "add %[_Rd], pc"      \
      : [_Rd] "+lh" (Rd)    \
      :                     \
      :                     \
    );

  #define ADD_TO_PC(Rs)     \
    asm THUMBLIB_OP_FLAGS ( \
      "add pc, %[_Rs]"      \
      :                     \
      : [_Rs] "lh" (Rs)     \
      : "pc", "memory"      \
    );

  #define MOV_SP(Rd)        \
    asm THUMBLIB_OP_FLAGS ( \
      "mov %[_Rd], sp"      \
      : [_Rd] "+lh" (Rd)    \
      :                     \
      :                     \
    );

  #define MOV_TO_SP(Rs)     \
    asm THUMBLIB_OP_FLAGS ( \
      "mov sp, %[_Rs]"      \
      :                     \
      : [_Rs] "lh" (Rs)     \
      :                     \
    );

  #define MOV_LR(Rd)        \
    asm THUMBLIB_OP_FLAGS ( \
      "mov %[_Rd], lr"      \
      : [_Rd] "+lh" (Rd)    \
      :                     \
      :                     \
    );

  #define MOV_TO_LR(Rs)     \
    asm THUMBLIB_OP_FLAGS ( \
      "mov lr, %[_Rs]"      \
      :                     \
      : [_Rs] "lh" (Rs)     \
      : "lr"                \
    );

  #define MOV_PC(Rd)        \
    asm THUMBLIB_OP_FLAGS ( \
      "mov %[_Rd], pc"      \
      : [_Rd] "=lh" (Rd)    \
      :                     \
      :                     \
    );

  #define MOV_TO_PC(Rs)     \
    asm THUMBLIB_OP_FLAGS ( \
      "mov pc, %[_Rs]"      \
      :                     \
      : [_Rs] "lh" (Rs)     \
      : "pc", "memory"      \
    );

  #define CMP_SP(Rd)        \
    asm THUMBLIB_OP_FLAGS ( \
      "cmp %[_Rd], sp"      \
      :                     \
      : [_Rd] "lh" (Rd)     \
      : "cc"                \
    );

  #define CMP_TO_SP(Rs)     \
    asm THUMBLIB_OP_FLAGS ( \
      "cmp sp, %[_Rs]"      \
      :                     \
      : [_Rs] "lh" (Rs)     \
      : "cc"                \
    );

  #define CMP_LR(Rd)        \
    asm THUMBLIB_OP_FLAGS ( \
      "cmp %[_Rd], lr"      \
      :                     \
      : [_Rd] "lh" (Rd)     \
      : "cc"                \
    );

  #define CMP_TO_LR(Rs)     \
    asm THUMBLIB_OP_FLAGS ( \
      "cmp lr, %[_Rs]"      \
      :                     \
      : [_Rs] "lh" (Rs)     \
      : "cc"                \
    );

  #define CMP_PC(Rd)        \
    asm THUMBLIB_OP_FLAGS ( \
      "cmp %[_Rd], pc"      \
      :                     \
      : [_Rd] "lh" (Rd)     \
      : "cc"                \
    );

  #define CMP_TO_PC(Rs)     \
    asm THUMBLIB_OP_FLAGS ( \
      "cmp pc, %[_Rs]"      \
      :                     \
      : [_Rs] "lh" (Rs)     \
      : "cc"                \
    );


  // Pseudoinstruction, defined like this to
  // avoid needing to initialize r8.
  #define NOP() asm THUMBLIB_OP_FLAGS ("mov r8, r8");

  #define BX(Rs)            \
    asm THUMBLIB_OP_FLAGS ( \
      "bx %[_Rs]"           \
      :                     \
      : [_Rs] "lh" (Rs)     \
      : "pc"                \
    );

  #define BX_SP() asm THUMBLIB_OP_FLAGS ("bx sp" ::: "pc");
  #define BX_LR() asm THUMBLIB_OP_FLAGS ("bx lr" ::: "pc");
  #define BX_PC() asm THUMBLIB_OP_FLAGS ("bx pc" ::: "pc");

  #define LDR_POOL(Rd, Value)   \
    asm THUMBLIB_OP_FLAGS (     \
      "ldr %[_Rd], =%[_Value]" \
      : [_Rd] "=l" (Rd)         \
      : [_Value] "i" (Value)    \
      : "memory"                \
    );

  #define LDR_PC(...) _THUMBLIB_APPLY_OVERLOAD(LDR_PC_, "ldr", __VA_ARGS__)

  #define STR(...) _THUMBLIB_APPLY_OVERLOAD(STR_, "str", u32, __VA_ARGS__)
  #define STRB(...) _THUMBLIB_APPLY_OVERLOAD(STR_, "strb", u8, __VA_ARGS__)
  #define STRH(...) _THUMBLIB_APPLY_OVERLOAD(STR_, "strh", u16, __VA_ARGS__)

  #define STR_I(...) _THUMBLIB_APPLY_OVERLOAD(STR_I_, "str", u32, __VA_ARGS__)
  #define STRB_I(...) _THUMBLIB_APPLY_OVERLOAD(STR_I_, "strb", u8, __VA_ARGS__)
  #define STRH_I(...) _THUMBLIB_APPLY_OVERLOAD(STR_I_, "strh", u16, __VA_ARGS__)

  #define LDR(...) _THUMBLIB_APPLY_OVERLOAD(LDR_, "ldr", u32, __VA_ARGS__)
  #define LDRB(...) _THUMBLIB_APPLY_OVERLOAD(LDR_, "ldrb", u8, __VA_ARGS__)
  #define LDRH(...) _THUMBLIB_APPLY_OVERLOAD(LDR_, "ldrh", u16, __VA_ARGS__)

  #define LDSB(Rd, Rb, Ro) LDR_BASE("ldsb", s8, Rd, Rb, Ro)
  #define LDSH(Rd, Rb, Ro) LDR_BASE("ldsh", s16, Rd, Rb, Ro)

  #define LDR_I(...) _THUMBLIB_APPLY_OVERLOAD(LDR_I_, "ldr", u32, __VA_ARGS__)
  #define LDRB_I(...) _THUMBLIB_APPLY_OVERLOAD(LDR_I_, "ldrb", u8, __VA_ARGS__)
  #define LDRH_I(...) _THUMBLIB_APPLY_OVERLOAD(LDR_I_, "ldrh", u16, __VA_ARGS__)

  #define STR_SP(...) _THUMBLIB_APPLY_OVERLOAD(STR_SP_, "str", __VA_ARGS__)
  #define LDR_SP(...) _THUMBLIB_APPLY_OVERLOAD(LDR_SP_, "ldr", __VA_ARGS__)

  // These are the `add, Rd, pc/sp, #NN` instructions.

  #define PCR(...) _THUMBLIB_APPLY_OVERLOAD(GRA_, "add", "pc", __VA_ARGS__)
  #define SPR(...) _THUMBLIB_APPLY_OVERLOAD(GRA_, "add", "sp", __VA_ARGS__)

  // GCC actually doesn't let you say that you're
  // clobbering SP, so the optimizer might just do
  // anything here.
  #define ADD_TO_SP(Immediate)       \
    asm THUMBLIB_OP_FLAGS (          \
      "add sp, %[_Immediate]"        \
      :                              \
      : [_Immediate] "O" (Immediate) \
    );

  #define SUB_FROM_SP(Immediate) ADD_TO_SP(-Immediate)

  // If you need to push lr, see `PUSH_WITH_LR` and `PUSH_LR`.
  #define PUSH(Registers...)                                                                    \
    asm THUMBLIB_OP_FLAGS (                                                                     \
      "push {" _THUMBLIB_FOR_EACH_REG(_THUMBLIB_REGLIST, _THUMBLIB_REGLIST_LAST, Registers) "}" \
      :                                                                                         \
      : _THUMBLIB_FOR_EACH_REG(_THUMBLIB_INPUT, _THUMBLIB_INPUT_LAST, Registers)                \
      : "memory"                                                                                \
    );

  #define PUSH_WITH_LR(Registers...)                                                                \
    asm THUMBLIB_OP_FLAGS (                                                                         \
      "push {" _THUMBLIB_FOR_EACH_REG(_THUMBLIB_REGLIST, _THUMBLIB_REGLIST_LAST, Registers) ", lr}" \
      :                                                                                             \
      : _THUMBLIB_FOR_EACH_REG(_THUMBLIB_INPUT, _THUMBLIB_INPUT_LAST, Registers)                    \
      : "memory"                                                                                    \
    );

  #define PUSH_LR()         \
    asm THUMBLIB_OP_FLAGS ( \
      "push {lr}"           \
      :                     \
      :                     \
      : "memory"            \
    );

  // If you need to pop pc, see `POP_WITH_PC` `POP_PC`.
  #define POP(Registers...)                                                                    \
    asm THUMBLIB_OP_FLAGS (                                                                    \
      "pop {" _THUMBLIB_FOR_EACH_REG(_THUMBLIB_REGLIST, _THUMBLIB_REGLIST_LAST, Registers) "}" \
      : _THUMBLIB_FOR_EACH_REG(_THUMBLIB_OUTPUT, _THUMBLIB_OUTPUT_LAST, Registers)             \
      :                                                                                        \
      : "memory"                                                                               \
    );

  #define POP_WITH_PC(Registers...)                                                                \
    asm THUMBLIB_OP_FLAGS (                                                                        \
      "pop {" _THUMBLIB_FOR_EACH_REG(_THUMBLIB_REGLIST, _THUMBLIB_REGLIST_LAST, Registers) ", pc}" \
      : _THUMBLIB_FOR_EACH_REG(_THUMBLIB_OUTPUT, _THUMBLIB_OUTPUT_LAST, Registers)                 \
      :                                                                                            \
      : "pc", "memory"                                                                             \
    );

  #define POP_PC()          \
    asm THUMBLIB_OP_FLAGS ( \
      "pop {pc}"            \
      :                     \
      :                     \
      : "pc", "memory"      \
    );

  #define STMIA(Rb, Registers...)                                                                         \
    asm THUMBLIB_OP_FLAGS (                                                                               \
      "stmia %[_Rb]!, {" _THUMBLIB_FOR_EACH_REG(_THUMBLIB_REGLIST, _THUMBLIB_REGLIST_LAST, Registers) "}" \
      : [_Rb] "+l" (Rb)                                                                                   \
      : _THUMBLIB_FOR_EACH_REG(_THUMBLIB_INPUT, _THUMBLIB_INPUT_LAST, Registers)                          \
      : "memory"                                                                                          \
    );

  #define LDMIA(Rb, Registers...)                                                                         \
    asm THUMBLIB_OP_FLAGS (                                                                               \
      "ldmia %[_Rb]!, {" _THUMBLIB_FOR_EACH_REG(_THUMBLIB_REGLIST, _THUMBLIB_REGLIST_LAST, Registers) "}" \
      : [_Rb] "=l" (Rb), _THUMBLIB_FOR_EACH_REG(_THUMBLIB_OUTPUT, _THUMBLIB_OUTPUT_LAST, Registers)       \
      :                                                                                                   \
      : "memory"                                                                                          \
    );

  #define BEQ(Label) BRANCH_BASE("beq", Label)
  #define BNE(Label) BRANCH_BASE("bne", Label)
  #define BCS(Label) BRANCH_BASE("bcs", Label)
  #define BCC(Label) BRANCH_BASE("bcc", Label)
  #define BMI(Label) BRANCH_BASE("bmi", Label)
  #define BPL(Label) BRANCH_BASE("bpl", Label)
  #define BVS(Label) BRANCH_BASE("bvs", Label)
  #define BVC(Label) BRANCH_BASE("bvc", Label)
  #define BHI(Label) BRANCH_BASE("bhi", Label)
  #define BLS(Label) BRANCH_BASE("bls", Label)
  #define BGE(Label) BRANCH_BASE("bge", Label)
  #define BLT(Label) BRANCH_BASE("blt", Label)
  #define BGT(Label) BRANCH_BASE("bgt", Label)
  #define BLE(Label) BRANCH_BASE("ble", Label)

  #define BEQ_ABS(Position) BRANCH_ABS_BASE("beq", Position)
  #define BNE_ABS(Position) BRANCH_ABS_BASE("bne", Position)
  #define BCS_ABS(Position) BRANCH_ABS_BASE("bcs", Position)
  #define BCC_ABS(Position) BRANCH_ABS_BASE("bcc", Position)
  #define BMI_ABS(Position) BRANCH_ABS_BASE("bmi", Position)
  #define BPL_ABS(Position) BRANCH_ABS_BASE("bpl", Position)
  #define BVS_ABS(Position) BRANCH_ABS_BASE("bvs", Position)
  #define BVC_ABS(Position) BRANCH_ABS_BASE("bvc", Position)
  #define BHI_ABS(Position) BRANCH_ABS_BASE("bhi", Position)
  #define BLS_ABS(Position) BRANCH_ABS_BASE("bls", Position)
  #define BGE_ABS(Position) BRANCH_ABS_BASE("bge", Position)
  #define BLT_ABS(Position) BRANCH_ABS_BASE("blt", Position)
  #define BGT_ABS(Position) BRANCH_ABS_BASE("bgt", Position)
  #define BLE_ABS(Position) BRANCH_ABS_BASE("ble", Position)

  #define B(Label)               \
    asm goto THUMBLIB_OP_FLAGS ( \
      "b %l0"                    \
      :                          \
      :                          \
      :                          \
      : Label                    \
    );

  #define B_ABS(Position)   \
    asm THUMBLIB_OP_FLAGS ( \
      "b %c0"               \
      :                     \
      : "i" (Position)      \
    );

  #define BL(Symbol)         \
    asm THUMBLIB_OP_FLAGS (  \
      "bl " #Symbol          \
      :                      \
      :                      \
      : "lr", "memory", "cc" \
    );

  #define SWI(Index)         \
    asm THUMBLIB_OP_FLAGS (  \
      "swi %[_Index]"        \
      :                      \
      : [_Index] "I" (Index) \
    );

#endif // THUMBLIB_3_OPCODES
