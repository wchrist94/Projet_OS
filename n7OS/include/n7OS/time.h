#ifndef TIME_H
#define TIME_H

//Horloge à 1ms
#define HORLOGE 1000
//Fréquence de l'oscillateur
#define f_osc 1190000
//Fréquence du timer
#define FREQ f_osc/HORLOGE

// Ports diviseur d'horloge
// connecté à l'entrée 0 du PIC
#define CH0_PORT 0x40
// gestion de la mémoire
#define CH1_PORT 0x41
// gestion du son
#define CH2_PORT 0x42
// registre de contrôle/commande
#define REG_PORT 0x43

// ports PIC
// Port de données de configuration
#define PIC_DATA 0x21
// Port de commande
#define PIC_CMD 0x20

// D'après la table
#define NumPortIRQ 0
// Numéro de l'IT du timer
#define TIMER_IT 0x20

#define RR_PERIOD 2000 // 2s


void init_timer();



#endif