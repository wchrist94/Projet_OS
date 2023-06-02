#include <stdio.h>
#include <n7OS/cpu.h>
#include <unistd.h>

void init()
{
    printf("Hello, world from init\n");
    while (1)
    {
        hlt();
    }
}
