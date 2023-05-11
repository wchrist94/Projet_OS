#include <n7OS/console.h>
#include <n7OS/cpu.h>
#include <inttypes.h>
#include <string.h>

uint16_t *scr_tab = (uint16_t *) 0xB8000;
int pos = 0;

void console_putbytes(const char *s, int len) {
    for (int i = 0; i < len; i++){
        console_putchar(s[i]);
    }
}

void console_clear(){
    for(int i = 0; i < MAX_SIZE; i++) {
        scr_tab[i]  = 0x0F;
    }
}

void console_putcursor(){
    outb(0xF, 0x3D4);
    outb(pos & 0xFF, 0x3D5);
    outb(0xE, 0x3D4);
    outb((pos >> 8) & 0xFF, 0x3D5);
}


void console_putchar(const char c){
    if(c > 31 && c < 127) {
        scr_tab[pos++] = 0xF << 8 | c;
    } else {
        switch (c) {
            case '\b' :
                pos -= 1;
                break;
            case '\n' :
                pos += MAX_COLS - (pos % MAX_COLS);
                break;
            case '\r' :
                pos -= pos % MAX_COLS;
                break;
            default:
                break;
        }
    }
    console_putcursor();
}

