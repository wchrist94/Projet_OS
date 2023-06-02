#include <n7OS/irq.h>
#include <n7OS/cpu.h>
#include <stdio.h>
#include <n7OS/time.h>

extern void handler_IT();

void init_irq()
{
    init_irq_entry(50, (uint32_t)handler_IT);
}

void handler_en_C()
{
    printf("IT 50 bien reçue\n");
}
