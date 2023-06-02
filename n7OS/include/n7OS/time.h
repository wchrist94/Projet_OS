#ifndef TIME_H
#define TIME_H

#define FREQ 1190

// ports de sortie du timer
#define CH0 0x40
#define CH1 0x41
#define CH2 0x42

// ports PIC
#define PIC_DATA 0x21
#define PIC_CMD 0x20

void init_timer();

#endif