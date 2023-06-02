#ifndef PROCESS_H
#define PROCESS_H
#include <inttypes.h>
#define NB_PROC 255


#define STACK_SIZE 1024

typedef void* (*fnptr)();

// Définition d'un pid
typedef uint32_t pid_t;

// Etat d'un processus
typedef enum
{
    FINI,
    ELU,
    PRET,
    BLOQUE,
} PROCESS_STATE;

// Définition d'un processus
typedef struct
{
    // pid
    pid_t pid;
    // état
    PROCESS_STATE state;
    // nom du programme
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

// Fonctions
pid_t creer(const char *name, fnptr function);
void schedule();
void arreter();
void terminer();
void bloquer();
void debloquer();

pid_t getpid();
int exit();
pid_t fork(const char *name, fnptr function);
int sleep(int n);

// Liste des processus en attente
typedef struct
{
    pid_t pid;
    waiting_process_list_t *next;
} waiting_process_list_t;

// Liste des processus endormis
typedef struct
{
    pid_t pid;
    int time;
    sleeping_process_list_t *next;
} sleeping_process_list_t;

// à fin de tests
void init_process();

#endif
