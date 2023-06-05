#include <n7OS/sys.h>
#include <n7OS/syscall_defs.h>
#include <n7OS/console.h>
#include <n7OS/irq.h>
#include <unistd.h>
#include <n7OS/cpu.h>
#include <stdio.h>
#include <n7OS/process.h>

extern void handler_syscall();

void init_syscall()
{
    // ajout de la fonction de traitement de l'appel systeme 
    add_syscall(NR_example, sys_example);
    add_syscall(NR_shutdown, sys_shutdown);
    add_syscall(NR_write, sys_write);
    add_syscall(NR_fork, sys_fork);
    add_syscall(NR_exit, sys_exit);
    add_syscall(NR_getpid, sys_getpid);
    add_syscall(NR_sleep, sys_sleep);

    // initialisation de l'IT soft qui gère les appels systeme
    init_irq_entry(0x80, (uint32_t)handler_syscall);
}

// code de la fonction de traitement de l'appel systeme example
int sys_example()
{
    // on ne fait que retourner 1
    return 1;
}

int sys_shutdown(int n)
{
    if (n == 1)
    {
        outw(0x2000, 0x604); // Poweroff qemu > 2.0
        return -1;
    }
    else
        return n;
}

// code de la fonction de traitement de l'appel systeme write
int sys_write(const char *s, int len) {
    console_putbytes(s, len);
    return len;
}

// code de la fonction de traitement de l'appel systeme fork
pid_t sys_fork(const char *name, fnptr function) {
    pid_t pid = creer(name, function);
    return pid;
}

// code de la fonction de traitement de l'appel systeme exit
int sys_exit(int n) {
    terminer();
    return 0;
}


// code de la fonction de traitement de l'appel systeme getpid
pid_t sys_getpid() {
    return getpid();
}

// code de la fonction de traitement de l'appel systeme sleep
int sys_sleep(int n) {
    bloquer(n);
    return 0;
}

