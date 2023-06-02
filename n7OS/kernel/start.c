#include <n7OS/cpu.h>
#include <inttypes.h>
#include <n7OS/processor_structs.h>
#include <stdio.h>
#include <n7OS/irq.h>
#include <n7OS/time.h>
#include <unistd.h>
#include <n7OS/sys.h>
#include <n7OS/process.h>

/**
 * Ce qui fonctionne :
 * - L'affichage
 * - Les IRQ
 * - Syscalls `write`, `shutdown` et `schedule`
 * - Timer
 * - Processus et RR
 */
void kernel_start(void)
{
    // inits
    init_irq();
    init_timer();
    init_syscall();

    // affichage
    printf("\f");
    // for (int i = 0; i < 10000; i++)
    //     printf("hello world\t%i\n", i);

    // irq
    __asm__("int $50" ::);

    // syscalls
    if (example() == 1)
        printf("Appel systeme systeme ok\n");
    // shutdown(1);

    // processus
    init_process();

    // on ne doit jamais sortir de kernel_start
    while (1)
    {
        // cette fonction arrete le processeur
        hlt();
    }
}
