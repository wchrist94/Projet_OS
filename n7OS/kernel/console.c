#include <n7OS/console.h>
#include <inttypes.h>
#include <string.h>

uint16_t *scr_tab = (uint16_t *) 0xB8000;
int pos  = 80;

void console_putbytes(const char *s, int len) {
  while (len-- > 0) {
    console_putchar(*s++);
  }
  
}

void console_putcursor(int pos) {
  outb(0x3D4, 0x0F);
  outb(0x3D5, (uint8_t) (pos & 0xFF));
  outb(0x3D4, 0x0E);
  outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

void console_clear() {
  memset(scr_tab, 0, 80*25*2);
}

void console_putchar(const char c) {

  if (c > 31 && c < 127) {
    // Afficher le caractère à l'écran
    scr_tab [pos++]= (0xF<<8)| 'c';
  } else if ( c == '\n' ) { // ou ( c == 10)
    // Aller à la ligne suivante
    pos += MAX_COLS - (pos % MAX_COLS);
  } else if ( c == '\b') {
    // Aller à la colonne précédente
    pos -= 1;
  } else if ( c == '\r') {
    // Aller au début de la ligne
    pos -= pos % MAX_COLS;
  } else {
  }
  
}