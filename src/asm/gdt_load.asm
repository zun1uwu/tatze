gdtr    dw 0 ; for limit storage
        dq 0 ; for base storage

global gdt_load

gdt_load:
        mov     [gdtr], di
        mov     [gdtr + 2], rsi
        lgdt    [gdtr]
        ret