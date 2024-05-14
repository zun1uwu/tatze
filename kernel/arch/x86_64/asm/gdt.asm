[bits 64]

global _gdt_load
extern gp

_gdt_load:
        cli
        lgdt    [gp]
        call reload_segments
        ret

; uncommenting any lines below causes a triple fault
reload_segments:
        ;push 0x30
        lea rax, [rel .reload_cs]
        ;push rax
        ;retfq
        ret

.reload_cs:
        mov ax, 0x38
        mov ds, ax
        mov es, ax
        mov fs, ax
        mov gs, ax
        mov ss, ax
        ret