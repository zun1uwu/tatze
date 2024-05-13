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

#define DESCRIPTOR_COUNT 7
uint64_t gdt[DESCRIPTOR_COUNT];

/* undone */
void
install_gdt(void)
{
        __asm__("cli");

        gdt[0] = 0x0000000000000000; /* null descriptor */
        gdt[1] = 0x00C09A000000FFFF; /* 16-bit code descriptor rd */
        gdt[2] = 0x00C092000000FFFF; /* 16-bit data descriptor wr */
        gdt[3] = 0x00CF9A000000FFFF; /* 32-bit code descriptor rd */
        gdt[4] = 0x00CF92000000FFFF; /* 32-bit data descriptor wr */
        gdt[5] = 0x00C09A0000000000; /* 64-bit code descriptor rd */
        gdt[6] = 0x00C0920000000000; /* 64-bit data descriptor wr */

        gdt_load(sizeof(gp) - 1, (uint64_t) &gdt);
}