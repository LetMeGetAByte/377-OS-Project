#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>

static inline uint8_t inb(uint16_t port) {
	uint8_t val;
	__asm__ volatile("inb %1, %0" : "=a"(val) : "Nd"(port));
	return val;
}

static inline void outb(uint16_t port, uint8_t val) {
	__asm__ volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

static const char scancode_to_ascii[] = {
    0,  27, '1','2','3','4','5','6','7','8','9','0','-','=','\b', // 0x0–0xF
    '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',    // 0x10–0x1D
    0,  'a','s','d','f','g','h','j','k','l',';','\'','`',         // 0x1E–0x29
    0,  '\\','z','x','c','v','b','n','m',',','.','/', 0,          // 0x2A–0x35
    '*', 0,  ' ', 0,                                              // 0x36–0x39
    // fill the rest with 0s
};

static const char scancode_to_ascii_shift[] = {
    0,  27, '!','@','#','$','%','^','&','*','(',')','_','+','\b',
    '\t','Q','W','E','R','T','Y','U','I','O','P','{','}','\n',
    0,  'A','S','D','F','G','H','J','K','L',':','"','~',
    0,  '|','Z','X','C','V','B','N','M','<','>','?', 0,
    '*', 0,  ' ', 0,
};

unsigned char kb_next_char();

void draw_input(uint32_t x,uint32_t y,uint32_t scale, uint32_t color);

#endif
