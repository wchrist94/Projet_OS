#include <n7OS/console.h>
#include <n7OS/cpu.h>

console_entry *scr_tab = (console_entry *)0xB8000;
int cursor_pos = START_POS; // cursor position

// Slide the screen up one line
void console_slide()
{
    for (int i = START_POS; i < MAX_POS - NB_COL; i++)
        scr_tab[i] = scr_tab[i + NB_COL];
    for (int i = MAX_POS - NB_COL; i < MAX_POS; i++)
        scr_tab[i] = FORMAT << 8;
    cursor_pos = MAX_POS - NB_COL;
}

// Position the cursor at pos
void console_putcursor()
{
    outb(0xF, 0x3D4);
    outb(cursor_pos & 0xFF, 0x3D5);
    outb(0xE, 0x3D4);
    outb((cursor_pos >> 8) & 0xFF, 0x3D5);
}

// Put a character at the cursor position
void console_putchar(char c)
{
    switch (c)
    {
    case '\b': // backward
        cursor_pos -= 1;
        break;

    case '\t': // tab
        cursor_pos += 8;
        break;

    case '\n': // new line
        cursor_pos += NB_COL - cursor_pos % NB_COL;
        break;

    case '\f': // flush
        for (int i = 0; i < MAX_POS; i++)
            scr_tab[i] = FORMAT << 8;
        cursor_pos = START_POS;
        break;

    case '\r': // return to beginning of line
        cursor_pos -= cursor_pos % NB_COL;
        break;

    default: // print the character
        if (c > 31 && c < 127)
            scr_tab[cursor_pos++] = FORMAT << 8 | c;
        break;
    }

    // slide the screen if needed
    if (cursor_pos == MAX_POS)
        console_slide();

    // update the cursor position
    console_putcursor();
}

void console_putbytes(const char *s, int len)
{
    for (int i = 0; i < len; i++)
        console_putchar(s[i]);
}

// pour print à une certaine position puis "revenir"
void console_putbytes_at(const char *s, int len, int tpos)
{
    int prev_pos = cursor_pos;
    cursor_pos = tpos;
    console_putcursor();
    console_putbytes(s, len);
    cursor_pos = prev_pos;
    console_putcursor();
}
