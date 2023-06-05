#include <n7OS/cpu.h>
#include <inttypes.h>
#include <n7OS/processor_structs.h>
#include <stdio.h>
#include <n7OS/irq.h>
#include <n7OS/time.h>
#include <unistd.h>
#include <n7OS/sys.h>
#include <n7OS/process.h>
#include <n7OS/console.h>



void kernel_start(void)
{
    console_clear();
    init_irq();
    init_syscall();   
    init_timer();
    sti();
    init_process();


    while (1)
    {
        //console_clear();
        // Test Console OK
        //for (int i = 0; i < 10000; i++)
            //printf("hello world\t%i\n", i);
        // cette fonction arrete le processeur

        // TEST IRQ OK
        //init_irq();
        //sti();
        //__asm__("int $50" ::);
        //init_syscall();
        // TEST timer OK   
        //init_timer();
        //sti();


        
        // TEST SYSCALL OK
        

        // Test Syscall example
        //sti();
        //if (example() == 1)
            //printf("Appel systeme example OK\n");

        // Test Syscall shutdown OK
        //shutdown(1);

        // Test Syscall write OK
        //printf("Appel systeme write OK\n");

        // TEST PROCESS OK
        //init_process();

        // TEST fork OK
        //pid_t pid = fork("processus1", (fnptr)processus1);

        
        hlt();
    }
}
