extern void handler_IT_timer();

static int time = 0;

// demasquage de l'IT
void demasquer()
{
    outb(inb(PIC_DATA_PORT) & ~(1 << IRQ_PORT_NUM), PIC_DATA_PORT);
}

// masquage de l'IT
void masquer()
{
    outb(inb(PIC_DATA_PORT) | (1 << IRQ_PORT_NUM), PIC_DATA_PORT);
}

void init_timer()
{
    // configuration du PIT
    outb(PIT_CONFIG, PIT_REG_PORT);
    // fréquence timer
    outb(FREQUENCE & 0xFF, PIT_CH0_PORT);
    outb(FREQUENCE >> 8, PIT_CH0_PORT);
    // enregistrement du handler
    init_irq_entry(TIMER_IT, (uint32_t)handler_IT_timer);
    // demasquage de l'IT
    demasquer();
}

void print_time(int i)
{
    // ouais c'est moche
    int h, m, s;
    h = i / 3600000;
    m = (i - h * 3600000) / 60000;
    s = (i - h * 3600000 - m * 60000) / 1000;
    // print
    char buf[8];
    sprintf(buf, "%02i:%02i:%02i", h, m, s);
    console_putbytes_at(buf, 8, NB_COL - 8);
}

void handler_it_timer()
{
    outb(0x20, PIC_CMD_PORT); // ack
    print_time(time++);
    sti(); // le timer ne marche plus après schedule sinon
    if (time % RR_PERIOD == 0)
        scheduler();
}