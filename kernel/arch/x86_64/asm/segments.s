[bits 64]

global _reload_segments

_reload_segments:
        push 0x08                       ; causes triple fault
        lea rax, [rel .reload_cs]
        push rax                        ; causes triple fault
        retfq                           ; causes triple fault

.reload_cs:
        mov ax, 0x10
        mov ds, ax
        mov es, ax
        mov fs, ax
        mov gs, ax
        mov ss, ax
        ret