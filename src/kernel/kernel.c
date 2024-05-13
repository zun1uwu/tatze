#include <psf.h>
#include <limine.h>
#include <stdbool.h>
#include <gdt.h>

static volatile LIMINE_BASE_REVISION(1);

static volatile struct limine_framebuffer_request fb_request = {
        .id = LIMINE_FRAMEBUFFER_REQUEST,
        .revision = 0
};

static void
hcf(void)
{
        __asm__("cli");

        while (1)
                __asm__("hlt");
}

void
kmain(void)
{
        if (LIMINE_BASE_REVISION_SUPPORTED == false)
                hcf();

        if (!fb_request.response || fb_request.response->framebuffer_count < 1)
                hcf();

        struct limine_framebuffer *fb = fb_request.response->framebuffers[0];

        psf_init(fb);
        // psf_print("Hello, world!", 0xffffff);
test();

        hcf();
}