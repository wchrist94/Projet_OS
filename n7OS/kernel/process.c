#include <n7OS/process.h>
#include <string.h>
#include <n7OS/cpu.h>
#include <stdio.h>
#include <stdlib.h>

// Table des processus
static process_t process_table[NB_PROC];
// Processus courant
static process_t *current_process;
// PID courant
pid_t pid_counter = 0;



extern void ctx_sw(void *ctx_old, void *ctx_new);
extern void processus1();
extern void idle();

pid_t creer(const char *name, fnptr function) {
    process_t *new_process;

    // Recherche d'une entrée libre dans la table des processus
    for (int i = 0; i < NB_PROC; i++) {
        if (process_table[i].state == FINI) {
            new_process = &process_table[i];
            new_process->pid = pid_counter;
            pid_counter++;
            new_process->state = PRET;
            strcpy(new_process->name, name);
            memset(new_process->stack, 0, sizeof(new_process->stack));
            new_process->stack[STACK_SIZE - 1] = (uint32_t)function;
            memset(new_process->ctx, 0, sizeof(new_process->ctx));
            new_process->ctx[ESP] = (uint32_t)&new_process->stack[STACK_SIZE - 1];
            return new_process->pid;
        }
    }
    return -1;
}


void arreter() {
    if (current_process->state == ELU)
        current_process->state = PRET;
    schedule();
}

void terminer() {
    if (current_process->state == ELU)
        current_process->state = FINI;
    schedule();
}

void bloquer() {
    if (current_process->state == ELU)
        current_process->state = BLOQUE;
    schedule();
}

void debloquer() {
    if (current_process->state == BLOQUE)
        current_process->state = PRET;
    schedule();
}


void schedule(){
    pid_t pid = current_process->pid;
    pid_t next_pid = -1;

    printf("Schedule\n");
    for (pid_t i = 1; i < NB_PROC; i++) {
        pid_t npid = (pid + i) % NB_PROC;
        if (process_table[npid].state == PRET) {
            next_pid = npid;
            break;
        }
    }


    if (next_pid == -1) {
        printf("Aucun processus prêt\n");
        return;
    } else {
        if (current_process->state == ELU)
            current_process->state = PRET;

    
        process_table[next_pid].state = ELU;
        printf("pid = %d\n", next_pid);
        printf("process_table[next_pid].state = %d\n", process_table[next_pid].state);
        printf("Changement de processus\n");
        current_process = &process_table[next_pid];

        ctx_sw(&process_table[pid].ctx, &process_table[next_pid].ctx);
    }
    
}



void init_process() {
    
    for (int i = 0; i < NB_PROC; i++) {
        process_table[i].state = FINI;
    }
    pid_t pid_idle = creer("idle", (fnptr)idle);
    pid_t pid_p1 = creer("processus1", (fnptr)processus1);
    pid_t pid_p2 = creer("processus2", (fnptr)processus1);
    pid_t pid_p3 = creer("processus3", (fnptr)processus1);

    current_process = &process_table[pid_idle];
    current_process->state = ELU;
    idle();
}