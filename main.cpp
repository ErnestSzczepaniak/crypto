#ifdef build_platform_host

#define CATCH_CONFIG_MAIN
#include "build.h"
#include "test.h"

#else

#include "build.h"
#include "aes.h"

extern "C" void faes_key_schedule(unsigned char * input, unsigned char * output);

#include <arm_neon.h>

int main()
{
    unsigned char key[] = {
        0x60, 0x3d, 0xeb, 0x10, 0x15, 0xca, 0x71, 0xbe, 
        0x2b, 0x73, 0xae, 0xf0, 0x85, 0x7d, 0x77, 0x81, 
        0x1f, 0x35, 0x2c, 0x07, 0x3b, 0x61, 0x08, 0xd7, 
        0x2d, 0x98, 0x10, 0xa3, 0x09, 0x14, 0xdf, 0xf4
    };

    unsigned char expanded[240];
    unsigned char expanded2[240];

    faes_key_schedule(key, expanded);
    aes_key_setup((BYTE *) key, (WORD *) expanded2, 256);

    while(1);
}

#endif
