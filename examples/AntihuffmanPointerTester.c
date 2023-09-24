
#define THUMBLIB_VOLATILE

#include "gbafe.h"
#include "thumblib3.h"

THUMBLIB_FUNC void AntihuffmanPointerTester(const char* source, char* dest) {

  register bool isUncompressed asm("r2");

  const int uppermostBitIndex = (sizeof(source) * 8) - 1;

  PUSH_LR();

  LSR_I(isUncompressed, (int)source, uppermostBitIndex);
  BEQ(_AHCompressed);

    BL(AntihuffmanUncompressed);
    B(_AHReturn);

  _AHCompressed:;
    BL(AntihuffmanCompressed);

  _AHReturn:;
  POP_PC();

}
