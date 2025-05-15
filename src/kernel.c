#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "./drivers/video/video.h"
#include "./drivers/keyboard/keyboard.h"
#include "multiboot.h"

#if !defined(__i386__)
#error "Cross-Compiler exports not enabled. Try: source .source"
#endif

void kernel_main(struct multiboot_info *mbi) {
    video_init(mbi);
    // byte order RGB --> 0xRRGGBB
    video_fill(0x000000);

    video_draw_text("Hello and welcome to our silly OS feel free to type anything \n", 0, 0, 0xFFFFFF, 1);
    draw_input(0,8,1,0xFFFFFF);
}
