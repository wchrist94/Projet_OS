#include <n7OS/process.h>
#include <string.h>
#include <n7OS/cpu.h>
#include <stdio.h>

// Table des processus
static process_t process_table[NB_PROC];
// Processus courant
static process_t *current_process;
// PID courant
static pid_t pid_counter = 0;

pid_t creer(const char *name, fnptr function)
{
    printf("> creer %s\n", name);
    process_t *process;
    for (int i = 0; i < NB_PROC; i++)
    {
        process = &process_table[pid_counter];
        // si la case est "vide"
        if (process->state == NONE)
        {
            // on l'utilise
            process->pid = pid_counter;
            process->state = PRET;
            // copie du nom
            strcpy(process->name, name);
            // reset de la stack
            memset(process->stack, 0, sizeof(process->stack));
            // on place la fonction à la fin
            process->stack[STACK_SIZE - 1] = (uint32_t)function;
            // reset du context
            memset(process->ctx, 0, sizeof(process->ctx));
            // on place le PC
            process->ctx[ESP] = (uint32_t)&process->stack[STACK_SIZE - 1];
            return pid_counter;
        }
        pid_counter++;
    }
    return -1;
}

extern void ctx_sw(void *ctx_old, void *ctx_new);

void scheduler()
{
    printf("> scheduler\n");
    pid_t curr_pid = getpid();
    pid_t new_pid = -1;
    // on cherche le prochain processus prêt à partir du pid courant
    for (pid_t i = 1; i < NB_PROC; i++)
    {
        // on repart au début si on arrive à la fin du tableau
        pid_t npid = (curr_pid + i) % NB_PROC;
        if (process_table[npid].state == PRET)
        {
            new_pid = npid;
            break;
        }
    }
    printf(">> new pid: %i\n", new_pid);
    if (new_pid != -1)
    {
        // si il était élu, on le remet en pret
        if (current_process->state == ELU)
            current_process->state = PRET;
        // on passe au processus suivant
        process_table[new_pid].state = ELU;
        current_process = &process_table[new_pid];
        // context switch
        ctx_sw(&process_table[curr_pid].ctx, &process_table[new_pid].ctx);
    }
    else
        printf("> scheduler: no process to switch to\n");
}

void arreter()
{
    printf("> arreter %s\n", current_process->name);
    current_process->state = ELU;
    scheduler();
}

void terminer()
{
    printf("> terminer %s\n", current_process->name);
    // on "libère" la case
    current_process->state = NONE;
    scheduler();
}

pid_t getpid()
{
    return current_process->pid;
}

extern void init();
extern void processus1();

void init_process()
{
    // création des deux processus
    pid_t pid_init = creer("init", (fnptr)init);
    creer("processus1", (fnptr)processus1);

    // on lance init
    current_process = &process_table[pid_init];
    current_process->state = ELU;
    init();
}
