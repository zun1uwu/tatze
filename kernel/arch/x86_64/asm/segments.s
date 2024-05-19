[bits 64]

global _reload_segments

section .text

_reload_segments:
        push 0x08
        lea rax, [rel .reload_cs]
        push rax
        retfq 

.reload_cs:
        mov ax, 0x10    ; page fault at this instruction
        mov ds, ax
        mov es, ax
        mov fs, ax
        mov gs, ax
        mov ss, ax
        ret