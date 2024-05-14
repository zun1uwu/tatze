#include <kernel/gdt.h>
#include <kernel/psf.h>
#include <stdlib.h>

/* our segment descriptors:
 *
 * 0x0000000000000000   null descriptor
 * 0x00C09A000000FFFF   16-bit code descriptor, readable
 * 0x00C092000000FFFF   16-bit data descriptor, writable
 * 0x00CF92000000FFFF   32-bit code descriptor, readable
 * 0x00CF9A000000FFFF   32-bit data descriptor, writable
 * 0x00C09A0000000000   64-bit code descriptor, readable
 * 0x00C0920000000000   64-bit data descriptor, writable
 */

#define DESCRIPTOR_COUNT 7
uint64_t gdt[DESCRIPTOR_COUNT];

struct gdt_ptr gp;

void
gdt_install(void)
{       
        gdt[0] = 0x0000000000000000; /* null descriptor */
        gdt[1] = 0x00C09A000000FFFF; /* 16-bit code descriptor readable */
        gdt[2] = 0x00C092000000FFFF; /* 16-bit data descriptor writable */
        gdt[3] = 0x00CF9A000000FFFF; /* 32-bit code descriptor readable */
        gdt[4] = 0x00CF92000000FFFF; /* 32-bit data descriptor writable */
        gdt[5] = 0x00C09A0000000000; /* 64-bit code descriptor readable */
        gdt[6] = 0x00C0920000000000; /* 64-bit data descriptor writable */

        gp.limit = (uint16_t) sizeof(gdt) - 1;
        gp.base = (uint64_t) &gdt;

        psf_print("loading gdt... ", 0xffffff);
        _gdt_load();
        psf_print("ok", 0x00ff00);
}