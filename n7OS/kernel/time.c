#include <n7OS/time.h>
#include <n7OS/irq.h>
#include <inttypes.h>
#include <n7OS/console.h>
#include <n7OS/cpu.h>
#include <stdio.h>
#include <n7OS/process.h>

extern void handler_IT_timer();

// Initialisation de la valeur du timer time est en ms
static int time = 0;

// Masquage de l'IT
void masquer()
{
    // Désactivation de l'IT du timer
    outb(inb(PIC_DATA) | (1 << NumPortIRQ), PIC_DATA);
}


// Demasquage de l'IT
void demasquer()
{
    // Activation de l'IT du timer
    outb(inb(PIC_DATA) & ~(1 << NumPortIRQ), PIC_DATA);
}

// Acquittement de l'IT
void ack()
{
    // ACK de l'IT du master
    outb(PIC_CMD, PIC_CMD);
}

void init_timer()
{


    // Configuration

    // Channel 0, accès LSB/MSB, gérateur d'imulsions, fréquence binaire
    outb(0x34, REG_PORT); 
    // Affectation de la fréquence, poids faible au Channel 0
    outb(FREQ & 0xFF, CH0_PORT);
    // Affectation de la fréquence, poids fort au Channel 0
    outb(FREQ >> 8, CH0_PORT);

        // Enregistrement de l'IT correspondante
    init_irq_entry(TIMER_IT, (uint32_t)handler_IT_timer);

    // demasquage de l'IT
    demasquer();
}

// Affichage du temps
void format_timer(long milliseconds)
{
    long heures, minutes, secondes;
    // Conversion en hh:mm:ss
    secondes = (milliseconds / 1000) % 60;
    minutes = (milliseconds / (1000 * 60)) % 60;
    heures = (milliseconds / (1000 * 60 * 60));
    char horloge[8];
    sprintf(horloge, "%02ld:%02ld:%02ld", heures, minutes, secondes);
    console_putbytes_at(horloge, 8, MAX_COLS - 8);
}

void handler_it_timer()
{
    // Acquittement de l'IT
    ack();

    // Affichage du temps et incrémentation
    format_timer(time++);

    sti();
    // ROUND_ROBIN est défini dans n7OS/process.h
    if (time % ROUND_ROBIN == 0)
        schedule();

}