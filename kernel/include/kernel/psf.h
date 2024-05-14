#pragma once

#include "limine.h"
#include <stdint.h>

#define PSF1_FONT_MAGIC 0x0436

struct psf1_header {
        uint16_t magic;
        uint8_t font_mode;
        uint8_t char_size;
};

#define PSF_FONT_MAGIC 0x864ab572

struct psf_font {
        uint32_t magic;
        uint32_t version;               /* zero */
        uint32_t header_size;           /* offset of bitmaps in file, 32 */
        uint32_t flags;                 /* 0 if there is no unicode table */
        uint32_t num_glyph;             /* number of glyphs */
        uint32_t bytes_per_glyph;       /* size of each glyph */
        uint32_t height;                /* height in pixels */
        uint32_t width;                 /* width in pixels */
} __attribute__((packed));

struct psf_cursor {
        int x;
        int y;
};

#define LOGLEVEL_INFO 0
#define LOGLEVEL_WARN 1
#define LOGLEVEL_ERROR 2

void psf_init(struct limine_framebuffer *fb_ptr);
void psf_drawchar(uint8_t c, int cx, int cy, uint32_t fg, uint32_t bg);
void psf_putchar(uint8_t c, uint32_t fg, uint32_t bg);
int handle_control_char(char c);
void psf_moveline(int dest_y, int src_y);
void psf_clearline(int y);
void psf_clear(void);
void psf_scroll(void);
void psf_putchar(uint8_t c, uint32_t fg, uint32_t bg);
void psf_print(char *s, uint32_t color);
void psf_log(int level, char *s);
void psf_info(void);