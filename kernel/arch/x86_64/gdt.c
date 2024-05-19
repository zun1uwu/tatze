#include <kernel/gdt.h>
#include <kernel/tty.h>
#include <stdlib.h>

#define DESCRIPTOR_COUNT 3
uint64_t gdt[DESCRIPTOR_COUNT];

struct gdt_ptr gp;

void
gdt_install(void)
{       
        gdt[0] = 0x0000000000000000; /* null descriptor */
        gdt[1] = 0x00C09A0000000000; /* 64-bit code descriptor readable */
        gdt[2] = 0x00C0920000000000; /* 64-bit data descriptor writable */

        gp.limit = (uint16_t) sizeof(gdt) - 1;
        gp.base = (uint64_t) &gdt;

        tty_print("loading gdt... ", 0xffffff);
        _gdt_load();
        tty_print("ok\n", 0xffffff);

        tty_print("reloading segments... ", 0xffffff);
        _reload_segments();
        tty_print("ok\n", 0xffffff);
}