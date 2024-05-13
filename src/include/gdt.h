#pragma once

#include <stdint.h>

struct gdt {
        uint64_t base;
        uint64_t limit;
        uint8_t access_byte;
        uint8_t flags;
};

extern void test(void);

void encode_gdt_entry(uint8_t *target, struct gdt source);
void gdt_install(void);