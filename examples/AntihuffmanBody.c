
#define THUMBLIB_VOLATILE

#include "gbafe.h"
#include "thumblib3.h"

extern char* gCurrentTextString;
char* String_GetFromIndexExt(int index, char* buffer);
extern void (*gpARM_HuffmanTextDecomp)(const char *, char *);
extern void BXR2();

enum {
  TEXT_END = 0x00,
};

THUMBLIB_FUNC char* GetStringFromIndex_Replacement(int index) {

  register char* textBuffer asm("r1");

  LDR_POOL(textBuffer, &gCurrentTextString);
  B_ABS(String_GetFromIndexExt);

  LTORG();

}

THUMBLIB_FUNC void AntihuffmanCompressed(const char* source, char* dest) {

  register void* decompressor asm("r2");

  PUSH_LR();

  LDR_POOL(decompressor, &gpARM_HuffmanTextDecomp);
  LDR(decompressor, decompressor);
  BL(BXR2);
  POP_PC();

  LTORG();

}

THUMBLIB_FUNC void AntihuffmanUncompressed(const char* source, char* dest) {

  register int theBit asm("r3");
  register char current asm("r2");

  MOV_I(theBit, (1 << (8 - 1)));
  LSL_I(theBit, ((sizeof(source) - 1) * 8));
  SUB_R(source, theBit);

  _AHLoop:;

    LDRB(current, source);
    STRB(current, dest);

    ADD_I(source, sizeof(char));
    ADD_I(dest, sizeof(char));

    CMP_I(current, TEXT_END);
    BNE(_AHLoop);

  BX_LR();

}
