#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

#if !defined(__i386__)
#error "Cross-Compiler exports not enabled. Try: source .source"
#endif

void kernel_main(uint32_t multiboot_info) {
    // Initialize kernel components
}
