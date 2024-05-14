#include <string.h>

int
strlen(char *s)
{
        size_t len = 0;
        
        while (s[len])
                len++;

        return len;
}