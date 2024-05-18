[bits 64]

global _gdt_load
extern gp

_gdt_load:
        cli
        lgdt    [gp]
        ret