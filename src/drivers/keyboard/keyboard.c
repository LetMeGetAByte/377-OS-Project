#include "keyboard.h"

#include "drivers/video/video.h"
#include <stdint.h>

unsigned char extended = 0;
unsigned char kb_next_char(){
    while((inb(0x64)&1) == 0){};
    uint8_t code = inb(0x60);

    if(extended == 1)
        if(code == 0x53)
            return 0x53;

    if(code == 0xE0)
        extended = 1;
    if(extended == 1 && kb_next_char() == 0x53)
    {
        extended = 0;
        return '^';
    }
    if(code & 0x80) return 0;
    return scancode_to_ascii[code];
}

void draw_input(uint32_t x,uint32_t y,uint32_t scale, uint32_t color){
    char next = kb_next_char();
    while(1 == 1){
        if(next == '^')
        {
            if(x != 0)
            {
                x-= scale*8;
                video_draw_char(' ',x,y,color, scale);
            }
            
        }
        else {
            video_draw_char(next,x,y,color,scale);
            x+= scale*8;
        }
        
        next = kb_next_char();


    }
}
