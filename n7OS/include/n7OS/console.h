#ifndef __CONSOLE_H__
#define __CONSOLE_H__
#define MAX_COLS 80
#define MAX_LIGNES 25
#define MAX_SIZE (MAX_COLS*MAX_LIGNES)

/*
 * This is the function called by printf to send its output to the screen. You
 * have to implement it in the kernel and in the user program.
 */
void console_putbytes(const char *s, int len);

void console_clear();

void console_putchar(const char c);

#endif
