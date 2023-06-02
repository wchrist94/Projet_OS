#include <n7OS/time.h>
#include <n7OS/irq.h>
#include <inttypes.h>
#include <n7OS/console.h>
#include <n7OS/cpu.h>

extern void handler_IT_timer();

static int time = 0;

// demasquage de l'IT
void demasquer()
{
    outb(inb(PIC_DATA) & ~(1 << IRQ_PORT_NUM), PIC_DATA);
}

// masquage de l'IT
void masquer()
{
    outb(inb(PIC_DATA) | (1 << IRQ_PORT_NUM), PIC_DATA);
}

void init_timer()
{
    // configuration du PIT
    outb(PIT_CONFIG, REG);
    // fréquence timer
    outb(FREQ & 0xFF, CH0);
    outb(FREQ >> 8, CH0);
    // enregistrement du handler
    init_irq_entry(TIMER_IT, (uint32_t)handler_IT_timer);
    // demasquage de l'IT
    demasquer();
}

void print_time(int i)
{
    // ouais c'est moche
    int h, m, s;
    h = i / 3600000;
    m = (i - h * 3600000) / 60000;
    s = (i - h * 3600000 - m * 60000) / 1000;
    // print
    char buf[8];
    sprintf(buf, "%02i:%02i:%02i", h, m, s);
    console_putbytes_at(buf, 8, MAX_COLS - 8);
}

void handler_it_timer()
{
    outb(0x20, PIC_CMD); // ack
    print_time(time++);
    sti(); // le timer ne marche plus après schedule sinon
    if (time % RR_PERIOD == 0)
        scheduler();
}