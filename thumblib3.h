
#ifndef THUMBLIB_3
#define THUMBLIB_3

  /* THUMBLIB v3
   *
   * This library provides tools for writing native THUMB assembly
   * functions within C source files without wrapping large blocks
   * of instructions within a single `asm` statement.
   *
   * This library requires Clib, and relies on it being in your include
   * path when compiling anything.
   *
   * GCC will try everything in its power to prevent you from doing
   * this, so be aware that it's likely that the compiler/optimizer
   * will mangle your beautiful assembly. Functions that are purely
   * THUMBLIB-flavor assembly should be marked using the `THUMBLIB_FUNC`
   * function attribute macro and should provide mock C-style returns
   * at their end. See the example .c files in the /examples folder.
   *
   */

  #include "gbafe.h"

  #include "include/helpers.h"
  #include "include/bases.h"
  #include "include/opcodes.h"
  #include "include/macros.h"

#endif // THUMBLIB_3
