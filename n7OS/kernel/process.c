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


// Fonction de changement de contexte
extern void ctx_sw(void *ctx_old, void *ctx_new);
// Fonction des processus
extern void processus1();
extern void idle();

pid_t creer(const char *name, fnptr function) {
    // Nouveau processus
    process_t *new_process;

    // Recherche d'une entrée libre dans la table des processus
    for (int i = 0; i < NB_PROC; i++) {
        if (process_table[i].state == FINI) {
            // Attribution d'un espace mémoire pour le nouveau processus
            new_process = &process_table[i];
            // Attribution d'un PID
            new_process->pid = pid_counter;
            // Incrémentation du compteur de PID
            pid_counter++;
            // Initialisation du processus dans l'état PRET
            new_process->state = PRET;
            // Initialisation du nom du processus
            strcpy(new_process->name, name);
            // Initialisation de la pile
            memset(new_process->stack, 0, sizeof(new_process->stack));
            new_process->stack[STACK_SIZE - 1] = (uint32_t)function;
            // Initialisation du contexte
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

pid_t get_pid() {
    return current_process->pid;
}

void schedule(){
    pid_t pid = get_pid();
    pid_t next_pid = -1;


    printf("Schedule\n");
    for (pid_t i = 1; i < NB_PROC; i++) {
        pid_t current_pid = (pid + i) % NB_PROC;
        if (process_table[current_pid].state == PRET) {
            next_pid = current_pid;
            break;
        }
    }
    

    if (next_pid == -1) {
        printf("Aucun processus prêt\n");
        return;
    } else {
        // Changement d'état du processus courant
        if (current_process->state == ELU) 
            current_process->state = PRET;
            
        
        // Changement de processus
        process_table[next_pid].state = ELU;
        printf("pid = %d\n", next_pid);
        printf("process_table[next_pid].state = %d\n", process_table[next_pid].state);
        printf("name = %s\n", process_table[next_pid].name);
        printf("Changement de processus\n");   
        // Election du nouveau processus
        current_process = &process_table[next_pid];

        // Test Sleep
        //if (strcmp(current_process->name, "idle") == 0)
            //exit();
        
        // Changement de contexte
        ctx_sw(&process_table[pid].ctx, &process_table[next_pid].ctx);
    }
    
}





void init_process() {
    
    // Initialisation de la table des processus
    for (int i = 0; i < NB_PROC; i++) {
        process_table[i].state = FINI;
    }
    // Création des processus
    pid_t pid_idle = fork("idle", (fnptr)idle);
    pid_t pid_p1 = fork("processus1", (fnptr)processus1);

    // Initialisation du processus courant
    current_process = &process_table[pid_idle];
    current_process->state = ELU;
    // Lance le processus courant
    idle();
}