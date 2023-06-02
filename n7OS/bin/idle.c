#include <stdio.h>
#include <n7OS/cpu.h>
#include <unistd.h>
#include <n7OS/process.h>

void idle () {
    printf("idle\n");
    while (1) {
        hlt();
    }
}