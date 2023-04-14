#include <n7OS/console.h>
#include <n7OS/cpu.h>
#include <inttypes.h>
#include <string.h>

uint8_t *scr_tab = (uint8_t *) 0xB8000;
uint8_t pos = 0;

void console_putbytes(const char *s, int len) {
    for (int i = 0; i < len; i++){
        console_putchar(s[i]);
    }
    console_putcursor();
}

void console_clear(){
    for(int i = 0; i < MAX_SIZE; i++) {
        scr_tab[i*2] = ' ';
        scr_tab[i*2 + 1]  = 0x0F;
    }
}

void console_putcursor(){
    outb(0xF, 0x3D4);
    uint8_t val = pos & 0xFF;
    outb(pos & 0xFF, 0x3D5);
    outb(0xE, 0x3D4);
    val = (pos >> 8) & 0xFF;
    outb((pos >> 8) & 0xFF, 0x3D5);
}


void console_putchar(const char c){
    if(c > 31 && c < 127) {
        scr_tab[pos++] = c;
        scr_tab[pos++] = 0xF;
    } else if ( c == '\n') {
        pos += MAX_COLS - (pos % MAX_COLS);
    } else if ( c == '\b') {
        pos -= 1;
    } else if ( c == '\r') {
        pos -= pos % MAX_COLS;
    } else {
    }
}

