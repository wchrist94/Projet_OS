#include <n7OS/cpu.h>
#include <inttypes.h>
#include <n7OS/processor_structs.h>
#include <n7OS/console.h>


void kernel_start(void)
{
    
    // on ne doit jamais sortir de kernel_start
    while(1){
        printf("\f");
        printf("Hello,World\n");

        // Test appels systèmes
        sti();

        if (example() == 1) {
            printf("Appel système example ok\n");
        }

        hlt();
    }
}
