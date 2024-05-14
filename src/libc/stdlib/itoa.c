#include <stdlib.h>

char *
itoa(uint64_t val, uint64_t base)
{
    static char buf[32] = {0};

    uint64_t i = 30;

    for(; val && i; --i, val /= base)
        buf[i] = "0123456789abcdef"[val % base];

    return &buf[i + 1];
}