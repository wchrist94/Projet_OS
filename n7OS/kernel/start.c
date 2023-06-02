#include <n7OS/cpu.h>
#include <inttypes.h>
#include <n7OS/processor_structs.h>
#include <n7OS/console.h>
#include <stdio.h>
#include <n7OS/irq.h>
#include <unistd.h>
#include <n7OS/sys.h>


void kernel_start(void)
{
    
    // on ne doit jamais sortir de kernel_start
    while(1){
        console_clear();
        printf("Hello,World\n");


        // irq
        __asm__("int $50" ::);
        // Test appels systèmes
        sti();

        if (example() == 1) {
            printf("Appel système example ok\n");
        }

        hlt();
    }
}
