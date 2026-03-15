#include <system.h>

//entrada IDT
struct idt_entry {
    unsigned short base_lo;
    unsigned short sel; //onde fica o segmento do kernel
    unsigned char always0; //autodescritivo
    unsigned char flags; //juntando a tabela acima
    unsigned short base_hi;
}__attribute__((packed));
/*
63                              32
+-------------------------------+
|          base_hi              |
+-------------------------------+
| flags | always0 |    sel      |
+-------------------------------+
|          base_lo              |
+-------------------------------+
31                               0
*/
struct idt_ptr {
    unsigned short limit;
    unsigned int base;
    /* data */
}__attribute__((packed));

struct idt_entry idt[256];
struct idt_ptr idtp;

//de start.asm para carregar a idt
extern void idt_load();

//atribuindo uma entrada idt
void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags){
    idt[num].base_lo = base & 0xFFFF;
    idt[num].base_hi = (base >> 16) & 0xFFFF;
    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
/* exemplo rapido de como fica a entrada
31                16 15                0
+------------------+-------------------+
|     base_hi      |     base_lo       |
+------------------+-------------------+
*/
}
//instalando a IDT
void idt_install(){
    //atribui o ponteiro especial id
    idtp.limit = (sizeof (struct idt_entry) * 256) - 1;
    idtp.base = (unsigned int)&idt;
    //inicia o idt com 0's
    memset((unsigned char*)idt, 0, sizeof(struct idt_entry) * 256);

    //Adicione qualquer ISRs novas para a IDT aqui usando idt_set_gate aqui

    //Aponta o registro interno do processador para a nova idt
    idt_load();
}