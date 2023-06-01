#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#define NB_COL 80                 // 80 columns
#define NB_ROW 25                 // 25 rows
#define MAX_POS (NB_COL * NB_ROW) // Maximal position
#define FORMAT 0x0F               // Text formatting

#define START_POS NB_COL

typedef __UINT16_TYPE__ console_entry;

/*
 * This is the function called by printf to send its output to the screen. You
 * have to implement it in the kernel and in the user program.
 */
void console_putbytes(const char *s, int len);

void console_putbytes_at(const char *s, int len, int tpos);

#endif
