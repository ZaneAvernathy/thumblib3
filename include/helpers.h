
#ifndef THUMBLIB_3_HELPERS
#define THUMBLIB_3_HELPERS

  /* THUMBLIB3 helper macros
   *
   * This file includes helper macros
   * for users as well as internal library macros.
   * Internal macros are prefixed with an underscore.
   */

  // Library configuration

    /* THUMBLIB_VOLATILE
     *
     * When defined, this will mark all ASM within THUMBLIB
     * macros as volatile, which may aid in preventing the
     * compiler/optimizer from messing with your code.
     *
     * You can pass in `-D THUMBLIB_VOLATILE` from the
     * commandline or `#define THUMBLIB_VOLATILE` before
     * including thumblib.h to enable this.
     */

    #ifdef THUMBLIB_VOLATILE
      #define THUMBLIB_VOLATILE_OP __volatile__
    #else // THUMBLIB_VOLATILE
      #define THUMBLIB_VOLATILE_OP
    #endif // THUMBLIB_VOLATILE

    #define THUMBLIB_OP_FLAGS THUMBLIB_VOLATILE_OP

    /* THUMBLIB_OPTIMIZE_OVERRIDE
     *
     * When defined, this should be either an optimization
     * level integer (such as 0) or an optimization option
     * string (such as "Os") that will be used for functions
     * tagged with `THUMBLIB_FUNC`. If not defined, the default
     * optimization level is 3.
     *
     * You can pass in `-D THUMBLIB_OPTIMIZE_OVERRIDE=N` from the
     * commandline or `#define THUMBLIB_VOLATILE N` before
     * including thumblib.h to override this.
     */

    #ifdef THUMBLIB_OPTIMIZE_OVERRIDE
      #define THUMBLIB_OPTIMIZE_SETTING THUMBLIB_OPTIMIZE_OVERRIDE
    #else // THUMBLIB_OPTIMIZE_OVERRIDE
      #define THUMBLIB_OPTIMIZE_SETTING 3
    #endif // THUMBLIB_OPTIMIZE_OVERRIDE

  // Function attribute helpers

    // Aliases
    #define THUMBLIB_NAKED __attribute__((naked))
    #define THUMBLIB_OPTIMIZE(level) __attribute__((optimize (level)))
    #define THUMBLIB_USED __attribute__((used))

    /* THUMBLIB_FUNC
     *
     * Marks a function as a THUMBLIB assembly function.
     * Use this to help prevent the compiler/optimizer from
     * changing your code.
     */
    #define THUMBLIB_FUNC THUMBLIB_NAKED THUMBLIB_OPTIMIZE(THUMBLIB_OPTIMIZE_SETTING) THUMBLIB_USED

  // Internal variadic macro helpers

    // Taken from https://embeddedartistry.com/blog/2020/07/27/exploiting-the-preprocessor-for-fun-and-profit/

    /* _THUMBLIB_APPLY_OVERLOAD(Base, Opcode, ...)
     *
     * This macro allows for different variants of an opcode
     * macro to be chosen based on the number of parameters
     * specified, allowing you to type things like
     *
     * `LSL_I(r1, r1, 2)` <-> `LSL_I(r1, 2)`
     *
     * The `Base` parameter is the prefix of a macro name that will
     * be combined with the argument count in order to select which
     * version of a macro to be used.
     *
     * The `Opcode` parameter is a string that is used within the
     * assemly code as the opcode's name.
     *
     * The remaining parameters are up to the individual overloads.
     *
     * For example, `LSL_I` is implemented using
     * #define LSL_I(...) _THUMBLIB_APPLY_OVERLOAD(MSR_I_, "lsl", __VA_ARGS__)
     * and has the following overloads:
     * #define MSR_I_3(Opcode, Rd, Immediate, ...) MSR_BASE(Opcode, Rd, Rd, Immediate)
     * #define MSR_I_4(Opcode, Rd, Rs, Immediate, ...) MSR_BASE(Opcode, Rd, Rs, Immediate)
     */

    #define _THUMBLIB_NARG(...) _THUMBLIB_NARG_(__VA_ARGS__, _THUMBLIB_RSEQ_N())
    #define _THUMBLIB_NARG_(...) _THUMBLIB_ARG_N(__VA_ARGS__)

    #define _THUMBLIB_RSEQ_N() 9, 8, 7, 6, 5, 4, 3, 2, 1, 0
    #define _THUMBLIB_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, N, ...) N

    #define _THUMBLIB_CONCAT_(x, y) x ## y
    #define _THUMBLIB_CONCAT(x, y) _THUMBLIB_CONCAT_(x, y)

    #define _THUMBLIB_OVERLOAD(Macro, ...) _THUMBLIB_CONCAT(Macro, _THUMBLIB_NARG(__VA_ARGS__))
    #define _THUMBLIB_APPLY_OVERLOAD(Base, Opcode, ...) _THUMBLIB_OVERLOAD(Base, Opcode, __VA_ARGS__)(Opcode, __VA_ARGS__)

  // Internal register list helpers

    /* _THUMBLIB_FOR_EACH_REG(Body, Final, List...)
     *
     * This macro applies two macros to a list of
     * arguments: `Final` is applied to the last argument
     * and `Body` is applied to the rest.
     *
     * It's intended to be used with register lists,
     * such as those used by the `push`, `pop`, `stmia` and `ldmia`
     * instructions.
     *
     * Generally, the `Body` macros' outputs have a trailing comma
     * and the `Final` macros' outputs do not.
     */

    #define _THUMBLIB_RL_0(Body, Final)
    #define _THUMBLIB_RL_1(Body, Final, i)          Final(i)
    #define _THUMBLIB_RL_2(Body, Final, i, List...) Body(i) _THUMBLIB_RL_1(Body, Final, List)
    #define _THUMBLIB_RL_3(Body, Final, i, List...) Body(i) _THUMBLIB_RL_2(Body, Final, List)
    #define _THUMBLIB_RL_4(Body, Final, i, List...) Body(i) _THUMBLIB_RL_3(Body, Final, List)
    #define _THUMBLIB_RL_5(Body, Final, i, List...) Body(i) _THUMBLIB_RL_4(Body, Final, List)
    #define _THUMBLIB_RL_6(Body, Final, i, List...) Body(i) _THUMBLIB_RL_5(Body, Final, List)
    #define _THUMBLIB_RL_7(Body, Final, i, List...) Body(i) _THUMBLIB_RL_6(Body, Final, List)
    #define _THUMBLIB_RL_8(Body, Final, i, List...) Body(i) _THUMBLIB_RL_7(Body, Final, List)

    #define _THUMBLIB_GET(_0, _1, _2, _3, _4, _5, _6, _7, _8, NAME, ...) NAME
    #define _THUMBLIB_FOR_EACH_REG(Body, Final, List...) \
      _THUMBLIB_GET(_0, List, \
        _THUMBLIB_RL_8, _THUMBLIB_RL_7, _THUMBLIB_RL_6, _THUMBLIB_RL_5, \
        _THUMBLIB_RL_4, _THUMBLIB_RL_3, _THUMBLIB_RL_2, _THUMBLIB_RL_1, _THUMBLIB_RL_0 \
        )(Body, Final, List)

    // Macros for use with _THUMBLIB_FOR_EACH_REG

      /* _THUMBLIB_INPUT and _THUMBLIB_INPUT_LAST
       *
       * These macros are used to make a list of
       * input operands for the `asm` section of
       * reglist opcodes.
       */
      #define _THUMBLIB_INPUT(Reg) [_##Reg] "r" (Reg),
      #define _THUMBLIB_INPUT_LAST(Reg) [_##Reg] "r" (Reg)

      /* _THUMBLIB_OUTPUT and _THUMBLIB_OUTPUT_LAST
       *
       * These macros are used to make a list of
       * output operands for the `asm` section of
       * reglist opcodes.
       */
      #define _THUMBLIB_OUTPUT(Reg) [_##Reg] "=r" (Reg),
      #define _THUMBLIB_OUTPUT_LAST(Reg) [_##Reg] "=r" (Reg)

      /* _THUMBLIB_REGLIST and _THUMBLIB_REGLIST_LAST
       *
       * These are used to construct the actual register
       * list within an opcode's assembler template.
       */
      #define _THUMBLIB_REGLIST(Reg) "%[_" #Reg "], "
      #define _THUMBLIB_REGLIST_LAST(Reg) "%[_" #Reg "]"

#endif // THUMBLIB_3_HELPERS
