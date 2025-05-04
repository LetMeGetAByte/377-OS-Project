#ifndef VIDEO_H
#define VIDEO_H

#include <stdint.h>
#include "multiboot.h"

void video_init(struct multiboot_info *mbi);
void video_fill(uint32_t color);

#endif
