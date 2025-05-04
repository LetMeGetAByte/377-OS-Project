#include "video.h"
#include <stdint.h>
#include <stddef.h>
#include "multiboot.h"

#define FB ((uint32_t *)(uintptr_t)framebuffer_addr)

static uint32_t *framebuffer = NULL;
static uint32_t fb_width = 0;
static uint32_t fb_height = 0;
static uint32_t fb_pitch = 0;
static uint8_t fb_bpp = 0;

void video_init(struct multiboot_info *mbi) {
    framebuffer = (uint32_t *)(uintptr_t)mbi->framebuffer_addr;
    fb_width = mbi->framebuffer_width;
    fb_height = mbi->framebuffer_height;
    fb_pitch = mbi->framebuffer_pitch;
    fb_bpp = mbi->framebuffer_bpp;
}

void video_fill(uint32_t color) {
    if (!framebuffer) return;

    for (uint32_t y = 0; y < fb_height; y++) {
        uint32_t *row = (uint32_t *)((uint8_t *)framebuffer + y * fb_pitch);
        for (uint32_t x = 0; x < fb_width; x++) {
            row[x] = color;
        }
    }
}
