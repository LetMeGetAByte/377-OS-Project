#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "./drivers/video/video.h"
#include "multiboot.h"

#if !defined(__i386__)
#error "Cross-Compiler exports not enabled. Try: source .source"
#endif

void kernel_main(struct multiboot_info *mbi) {
    video_init(mbi);
    // byte order RGB --> 0xRRGGBB
    video_fill(0xFF0000);
}
