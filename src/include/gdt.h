#pragma once

#include <stdint.h>

struct gdt_ptr {
        uint16_t limit;
        uint64_t base;
} __attribute__((packed));

struct gdt_ptr gp;

extern void gdt_load(uint16_t limit, uint64_t base);

void install_gdt(void);