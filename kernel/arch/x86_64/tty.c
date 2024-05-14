#include <limine.h>
#include <stdint.h>
#include <kernel/tty.h>
#include <string.h>

struct limine_framebuffer *fb;
struct psf_cursor cursor = { 0, 0 };
extern char _binary_font_psf_start[];
struct psf_font *font = (struct psf_font *) &_binary_font_psf_start;

#define PIXEL uint32_t
#define GLYPH uint8_t

#define FB_COLUMNS fb->width / (font->width + 1)
#define FB_ROWS fb->height / (font->height)

void
tty_init(struct limine_framebuffer *framebuffer)
{
        fb = framebuffer;
}

void
tty_drawchar(uint8_t c, int cx, int cy, uint32_t fg, uint32_t bg)
{
        int bytes_per_line = (font->width + 7) / 8;
        int scanline = fb->pitch;

        GLYPH *glyph = (GLYPH *) font + font->header_size
                + (c > 0 && c < font->num_glyph ? c : 0)
                * font->bytes_per_glyph;

        int offset = (cy * font->height * scanline)
                + (cx * (font->width + 1) * sizeof(PIXEL));

        int x, y, line, mask;
        for (y = 0; (uint32_t) y < font->height; y++) {
                line = offset;
                mask = 1 << (font->width - 1);

                for (x = 0; (uint32_t) x < font->width; x++) {
                        *((PIXEL *) (fb->address + line)) =
                                *((unsigned int *) glyph) & mask ? fg : bg;

                        mask >>= 1;
                        line += sizeof(PIXEL);
                }

                glyph += bytes_per_line;
                offset += scanline;
        }
}

int
handle_control_char(char c)
{
        switch (c) {
        case '\n':
                cursor.y++;
                cursor.x = 0;
                return 1;
        case '\r':
                cursor.x = 0;
                return 1;
        }

        return 0;
}

void
tty_moveline(int dest_y, int src_y)
{
        int x, gx, gy;

        for (x = 0; (uint64_t) x < FB_COLUMNS; x++) {
                int dest_offset = (dest_y * font->height * fb->pitch)
                        + (x * (font->width + 1) * sizeof(uint32_t));
                
                int src_offset = (src_y * font->height * fb->pitch)
                        + (x * (font->width + 1) * sizeof(uint32_t));

                for (gy = 0; (uint32_t) gy < font->height; gy++) {
                        int dest_line = dest_offset;
                        int src_line = src_offset;

                        for (gx = 0; (uint32_t) gx < font->width; gx++) {
                                *((PIXEL *) (fb->address + dest_line)) =
                                        *((PIXEL *) (fb->address + src_line));

                                dest_line += sizeof(PIXEL);
                                src_line += sizeof(PIXEL);
                        }

                        dest_offset += fb->pitch;
                        src_offset += fb->pitch;
                }
        }
}

void
tty_clearline(int y)
{
        for (cursor.x = 0; (uint64_t) cursor.x < FB_COLUMNS; cursor.x++)
                tty_drawchar(' ', cursor.x, y, 0x000000, 0x000000);
}

void
tty_clear(void)
{
        for (cursor.y = 0; (uint64_t) cursor.y < FB_ROWS; cursor.y++)
                tty_clearline(cursor.y);

        cursor.x = 0;
        cursor.y = 0;
}

void
tty_scroll(void)
{
        for (int i = 1; (uint64_t) i < FB_ROWS; i++)
                tty_moveline(i - 1, i);

        tty_clearline(FB_ROWS - 1);
        
        cursor.y--;
        cursor.x = 0;
}

void
tty_putchar(uint8_t c, uint32_t fg, uint32_t bg)
{
        if (handle_control_char(c))
                return;

        if ((uint64_t) cursor.x == FB_COLUMNS) {
                cursor.x = 0;
                cursor.y++;
        }

        if ((uint64_t) cursor.y == FB_ROWS) {
                tty_scroll();
        }

        tty_drawchar(c, cursor.x++, cursor.y, fg, bg);
}

void
tty_print(char *s, uint32_t color)
{
        for (int i = 0; i < strlen(s); i++)
                tty_putchar(s[i], color, 0x000000);
}