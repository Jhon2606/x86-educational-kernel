#include <system.h>

//guarda os tiques do sistema
int timer_ticks = 0;

void timer_phase(int hz){
    int divisor = 1193180 / hz;
    outportb(0x43, 0x36);
    outportb(0x40, divisor & 0xFF);
    outportb(0x40, divisor >> 8);
}

void timer_handler(struct regs *r){
    timer_ticks++;

    if(timer_ticks % 100 == 0){
        puts((unsigned char *)"\nUm segundo se passou...(certamente uma JoJo reference)\n");
    }
}
//atribui o relógio do sistema instalando o temporizador no IRQ0
void timer_install(){
    //instala timer_handler no IRQ0
    irq_install_handler(0, timer_handler);
    timer_phase(100);
}

void timer_wait(int ticks){
    unsigned long eticks;
    eticks = timer_ticks + ticks;
    while(timer_ticks < eticks);
}