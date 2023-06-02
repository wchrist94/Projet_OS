#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#define MAX_COLS 80                 // 80 colonnes
#define MAX_ROW 25                 // 25 lignes
#define MAX_INDX (MAX_COLS * MAX_ROW) // indice max


void console_putbytes(const char *s, int len);

void console_clear();

void console_putchar(char c);

void console_putcursor();

void console_slide();

#endif
