#include <n7OS/console.h>
#include <n7OS/cpu.h>
#include <inttypes.h>
#include <string.h>

uint8_t *scr_tab = (uint8_t *) 0xB8000;
int pos = 0;

void console_putbytes(const char *s, int len) {
    for (int i = 0; i < len; i++){
        console_putchar(s[i]);
    }
}

void console_clear(){
    memset(scr_tab, 0, 80*25*2);
}

void console_putcursor(int pos){
    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint16_t) (pos & 0xFF));
    outb(0x3D5, 0x0E);
    outb(0x3D5, (uint16_t) ((pos >> 8) & 0xFF));
}

int get_poscurseur

void console_putchar(const char c){
    if(c > 31 && c < 127) {
        scr_tab[pos++] = c;
        scr_tab[pos++] = 0xF;
    } else if ( c == '\n') {
        pos += 2*MAX_COLS - (pos % MAX_COLS);
    } else if ( c == '\b') {
        pos -= 1;
    } else if ( c == '\r') {
        pos -= pos % MAX_COLS;
    } else {
    }
}

