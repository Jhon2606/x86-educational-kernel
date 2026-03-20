#ifndef __SYSTEM_H
#define __SYSTEM_H

/*MAIN.C*/
extern unsigned char *memcpy(unsigned char *dest, const unsigned char *src, int count);
extern unsigned char *memset(unsigned char *dest, unsigned char val, int count);
extern unsigned short *memsetw(unsigned short *dest, unsigned short val, int count);
extern int strlen(const char *str);
extern unsigned char inportb (unsigned short _port);
extern void outportb (unsigned short _port, unsigned char _data);
extern void cls();
extern void putch(unsigned char c);
extern void puts(unsigned char *str);
extern void settextcolor(unsigned char forecolor, unsigned char backcolor);
extern void init_video();
void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);
void gdt_install();
extern void gdt_flush();
void idt_install();
void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);
// define qual pilha estamos olhando depois de um ISR estar rodando
struct regs
{
    unsigned int ds, es, fs, gs;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss;
};
void isrs_install();
void irq_install();
void irq_install_handler(int irq, void(*handler)(struct regs *r));
void  irq_uninstall_handler(int irq);
void timer_install();
void timer_install();
void timer_wait(int ticks);
void keyboard_handler(struct regs *r);
void keyboard_install();
void backspace();
#endif