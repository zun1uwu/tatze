[bits 64]

global _gdt_load

section .data

gdtr    dw 0 ; limit
        dq 0 ; base

section .text

_gdt_load:
        mov     [gdtr], di
        mov     [gdtr + 2], rsi
        lgdt    [gdtr]
        ret
        