#include <n7OS/console.h>
#include <n7OS/cpu.h>
#include <inttypes.h>
#include <string.h>

uint16_t *scr_tab = (uint16_t *)0xB8000; 
int position = 0; // Position du curseur

// Défilement de l'écran
void console_slide()
{
    // On décale les lignes de l'écran
    for (int i = 0; i < MAX_INDX - MAX_COLS; i++)
        scr_tab[i] = scr_tab[i + MAX_COLS];
    // On efface la dernière ligne
    for (int i = MAX_INDX - MAX_COLS; i < MAX_INDX; i++)
        scr_tab[i] = 0x0F << 8;

    // On remonte le curseur d'une ligne
    position = MAX_INDX - MAX_COLS;
}

// Efface l'écran
void console_clear()
{
    for (int i = 0; i < MAX_INDX; i++)
        scr_tab[i] = 0x0F << 8;
    position = 0;
}

// Affiche le curseur à la position courante
void console_putcursor()
{
    outb(0xF, 0x3D4);
    outb(position & 0xFF, 0x3D5);
    outb(0xE, 0x3D4);
    outb((position >> 8) & 0xFF, 0x3D5);
}

// Affiche un caractère à la position courante
void console_putchar(char c)
{

    if(c > 31 && c < 127) {
        scr_tab[position++] = 0x0F << 8 | c;
    } else {
        switch (c) {
            case '\b' :
                position -= 1;
                break;
            case '\n' :
                position += MAX_COLS - (position % MAX_COLS);
                break;
            case '\r' :
                position -= position % MAX_COLS;
                break;
            case '\f': 
                console_clear();
                break;
            default:
                break;
        }
        
    }
    // Si on est à la fin de l'écran, on défile
    if (position == MAX_INDX)
        console_slide();

    // On affiche le curseur
    console_putcursor();
}

// Affiche une chaîne de caractères à la position courante
void console_putbytes(const char *s, int len)
{
    for (int i = 0; i < len; i++)
        console_putchar(s[i]);
}

void console_putbytes_at(const char *s, int len, int tpos)
{
    int prev_pos = position;
    position = tpos;
    console_putcursor();
    console_putbytes(s, len);
    position = prev_pos;
    console_putcursor();
}
