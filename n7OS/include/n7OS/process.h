#ifndef PROCESS_H
#define PROCESS_H

#include <inttypes.h>

#define NB_PROC 255
#define STACK_SIZE 1024

typedef uint32_t pid_t;

typedef void *(*fnptr)();

// Etat d'un processus
// NONE: vide
typedef enum
{
    NONE,
    ELU,
    PRET,
    BLOQUE,
} PROCESS_STATE;

// Processus
typedef struct
{
    pid_t pid;
    PROCESS_STATE state;
    char name[20];
    uint32_t stack[STACK_SIZE];
    uint32_t ctx[5];
} process_t;

// Registres
typedef enum
{
    EBX,
    ESP,
    EBP,
    ESI,
    EDI,
} REGISTER;

// fonctions du noyau
pid_t creer(const char *name, fnptr function);
void scheduler();
void arreter();
void terminer();

pid_t getpid();

// à fin de tests
void init_process();

#endif
