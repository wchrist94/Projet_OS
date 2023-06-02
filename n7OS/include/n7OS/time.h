#ifndef TIME_H
#define TIME_H

#define FREQ 1190

// ports de sortie du timer
#define CH0 0x40
#define CH1 0x41
#define CH2 0x42
#define REG 0x43

// ports PIC
#define PIC_DATA 0x21
#define PIC_CMD 0x20

#define IRQ_PORT_NUM 0
#define TIMER_IT 0x20

#define RR_PERIOD 2000 // 2s

#define PIT_CONFIG 0x34

void init_timer();



#endif