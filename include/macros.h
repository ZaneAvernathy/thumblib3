
#ifndef THUMBLIB_3_MACROS
#define THUMBLIB_3_MACROS

  /* THUMBLIB3 special macros
   *
   * This file defines macros that uses might find
   * useful, like alignment tools and pool manipulation.
   */

  // Aligns assembly offset to a multiple of `Size` bytes.
  #define ALIGN(Size) \
    asm volatile (    \
      ".balign %c0"   \
      :               \
      : "i" (Size)    \
      : "memory"      \
    );

  // Aligns assembly offset to a multiple of `Size` bytes,
  // filling with repeated `Value` bytes.
  #define ALIGN_WITH(Size, Value)  \
    asm volatile (                 \
      ".balign %c0, %c1"           \
      :                            \
      : "i" (Size), "i" (Value)    \
      : "memory"                   \
    );

  // Aligns to the nearest multiple of 4 bytes and flushes the
  // literal pool.
  #define LTORG() asm volatile (".ltorg" ::: "memory");

#endif // THUMBLIB_3_MACROS
