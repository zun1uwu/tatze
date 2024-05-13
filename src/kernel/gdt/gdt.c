#include <gdt.h>
#include <psf.h>

/*
        our segment descriptors:

        0x0000000000000000
        0x00C09A000000FFFF
        0x00C092000000FFFF
        0x00CF9A000000FFFF
        0x00CF92000000FFFF
        0x00C09A0000000000
        0x00C0920000000000
*/

uint64_t descriptors[7];

/* undone */
void
install_gdt(void)
{
        __asm__("cli");

        descriptors[0] = 0x0000000000000000; /* null descriptor */
        descriptors[1] = 0x00C09A000000FFFF; /* 16-bit code descriptor rd */
        descriptors[2] = 0x00C092000000FFFF; /* 16-bit code descriptor wr */
        descriptors[3] = 0x00CF9A000000FFFF; /* 32-bit code descriptor rd */
        descriptors[4] = 0x00CF92000000FFFF; /* 32-bit code descriptor wr */
        descriptors[5] = 0x00C09A0000000000; /* 64-bit code descriptor rd */
        descriptors[6] = 0x00C0920000000000; /* 64-bit code descriptor wr */
}