#pragma once

#include <stdint.h>

struct gdt_ptr {
        uint16_t limit;
        uint64_t base;
} __attribute__((packed));

extern void _gdt_load(void);
void gdt_install(void);