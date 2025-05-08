#include "video.h"
#include "font8x8.h"
#include "multiboot.h"
#include <stddef.h>
#include <stdint.h>

#define FB ((uint32_t *) (uintptr_t) framebuffer_addr)

static uint32_t *framebuffer = NULL;
static uint32_t fb_width = 0;
static uint32_t fb_height = 0;
static uint32_t fb_pitch = 0;
static uint8_t fb_bpp = 0;

void video_init(struct multiboot_info *mbi) {
	framebuffer = (uint32_t *) (uintptr_t) mbi->framebuffer_addr;
	fb_width = mbi->framebuffer_width;
	fb_height = mbi->framebuffer_height;
	fb_pitch = mbi->framebuffer_pitch;
	fb_bpp = mbi->framebuffer_bpp;
}

void video_fill(uint32_t color) {
	if (!framebuffer)
		return;

	for (uint32_t y = 0; y < fb_height; y++) {
		uint32_t *row = (uint32_t *) ((uint8_t *) framebuffer + y * fb_pitch);
		for (uint32_t x = 0; x < fb_width; x++) {
			row[x] = color;
		}
	}
}

void video_draw_pixel(uint32_t x, uint32_t y, uint32_t color) {
	if (!framebuffer || x >= fb_width || y >= fb_height)
		return;

	uint32_t *pixel = (uint32_t *) ((uint8_t *) framebuffer + y * fb_pitch +
	                                x * sizeof(uint32_t));
	*pixel = color;
}

unsigned char *chartofont(char c) {
	if (c == 0x20) {
		return (unsigned char *) font8x8[36];
	} else if (0x30 <= c && c <= 0x39) {
		// numbers
		return (unsigned char *) font8x8[26 + (c - 0x30)];
	} else if (0x41 <= c && c <= 0x5A) {
		// cap letters
		return (unsigned char *) font8x8[c - 0x41];
	} else if (0x61 <= c && c <= 0x7A) {
		// lower letters
		return (unsigned char *) font8x8[c - 0x61];
	}

	return NULL;
}

void video_draw_char(char c, uint32_t x, uint32_t y, uint32_t color,
                     uint32_t scale) {
	unsigned char *glyph = chartofont(c);
	for (uint32_t row = 0; row < 8; row++) {
		for (uint32_t col = 0; col < 8; col++) {
			if ((glyph[row] >> (7 - col)) & 1) {
				for (uint32_t i = 0; i < scale; i++) {
					for (uint32_t j = 0; j < scale; j++)
						video_draw_pixel(x + scale * col + i,
						                 y + scale * row + j, color);
				}
			}
		}
	}
}

void video_draw_text(char *text, uint32_t x, uint32_t y, uint32_t color,
                     uint32_t scale) {
    for (uint32_t i = 0, offset = 0; text[i] != 0x0; i++, offset++) {
		if (text[i] == 0x0A) {
			y += (8 * scale);
			offset = 0;
			i++;
		}
		video_draw_char(text[i], x + (8 * scale * offset), y, color, scale);
	}
}
