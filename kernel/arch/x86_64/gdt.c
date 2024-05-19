#include <kernel/gdt.h>
#include <kernel/tty.h>
#include <stdlib.h>


#define DESCRIPTOR_COUNT 5
uint64_t gdt[DESCRIPTOR_COUNT];

void
gdt_install(void)
{       
        gdt[0] = 0x0000000000000000; /* null descriptor */
        gdt[1] = 0x00CF9A000000FFFF; /* kernel code descriptor readable */
        gdt[2] = 0x00CF92000000FFFF; /* kernel data descriptor writable */
        gdt[3] = 0x00CFFA000000FFFF; /* user code descriptor readable */
        gdt[4] = 0x00CFF2000000FFFF; /* user data descriptor writable */

        __asm__ ("cli");

        tty_print("loading gdt... ", 0xffffff);
        _gdt_load(sizeof(gdt) - 1, (uint64_t) &gdt);
        tty_print("ok\n", 0xffffff);

        tty_print("reloading segments... ", 0xffffff);
        _reload_segments();
        tty_print("ok\n", 0xffffff);
}