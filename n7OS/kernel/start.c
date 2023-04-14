#include <n7OS/cpu.h>
#include <inttypes.h>
#include <n7OS/processor_structs.h>
#include <n7OS/console.h>


void kernel_start(void)
{
    
    // on ne doit jamais sortir de kernel_start
    while (1) {
        // cette fonction arrete le processeur
        console_clear();
        console_putbytes("Hello,World", 12);
        hlt();
    }
}
