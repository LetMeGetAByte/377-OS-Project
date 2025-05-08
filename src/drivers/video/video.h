#ifndef VIDEO_H
#define VIDEO_H

#include <stdint.h>
#include "multiboot.h"

void video_init(struct multiboot_info *mbi);
void video_fill(uint32_t color);
void video_draw_pixel(uint32_t x, uint32_t y, uint32_t color);
void video_draw_char(char c, uint32_t x, uint32_t y, uint32_t color, uint32_t scale);
void video_draw_text(char *text, uint32_t x, uint32_t y, uint32_t color, uint32_t scale);

#endif
