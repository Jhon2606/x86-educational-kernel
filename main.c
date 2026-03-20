#include <system.h>
extern int csr_x;
extern int csr_y;
int start_x = 0;
int start_y = 0;

void __stack_chk_fail(void){
    //endereço é onde começa o modo texto em 32bits
    unsigned short *memoria_de_video = (unsigned short *)0xB8000;

    //escreve um P vermelho e branco
    memoria_de_video[0] = (0x4F << 8) | 'P';

    //desativa as interrupções e coloca o hardware para dormir ate a proxima interrupção (que não vai ter)
    __asm__ __volatile__ ("cli; hlt");

    //loop infinito por precaução
    for(;;);
}

unsigned char *memcpy(unsigned char *dest, const unsigned char *src, int count) {
    int i;
    for (i = 0; i < count; i++) {
        dest[i] = src[i];
    }
    return dest;
}

unsigned char *memset(unsigned char *dest, unsigned char val, int count) {
    int i;
    for (i = 0; i < count; i++) {
        dest[i] = val;
    }
    return dest;
}

//uma função de preenchimento semelhante a de cima, porem para blocos 16 bits (placas de video)
unsigned short *memsetw(unsigned short *dest, unsigned short val, int count) {
    int i;
    for (i = 0; i < count; i++) {
        dest[i] = val;
    }
    return dest;
}

int strlen(const char *str) {
    int tamanho = 0;
    while (str[tamanho] != '\0') {
        tamanho++;
    }
    return tamanho;
}

unsigned char inportb(unsigned short _port) {
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a"(rv) : "dN"(_port));
    return rv;
}

void outportb(unsigned short _port, unsigned char _data) {
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a"(_data));
}

void kmain(){
    gdt_install();
    idt_install();
    isrs_install();
    irq_install();
    __asm__ __volatile__ ("sti");
    init_video();
    timer_install();
    keyboard_install();
    puts((unsigned char *)"Meu Kernel v1.0\n");
    start_x = csr_x;
    start_y = csr_y;
    for(;;);
}