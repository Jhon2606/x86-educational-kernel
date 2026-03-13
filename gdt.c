#include <system.h>

//entrada da GDT e prevenção de otimização por empacotamento

struct gdt_entry {
    unsigned short limit_low;
    unsigned short base_low;
    unsigned char base_middle;
    unsigned char access;
    unsigned char granularity;
    unsigned char base_high;
} __attribute__((packed));
/* esse exemplo  ficou tão bom que vou deixar aqui:
63                     56 55 52 51 48 47        40 39      32
+----------------------+-----+-----+------------+----------+
|     Base 31..24      | G D | 0 A |  Limit19..16 | Access |
+----------------------+-----+-----+------------+----------+
|       Base 23..16          |       Base 15..0            |
+----------------------------+-----------------------------+
|              Limit 15..0                                 |
+----------------------------------------------------------+
0                                                         31
esse é basicamente o struct acima na memória*/

//ponteiro especial que inclui o limite de bytes da GDT, menos 1.
struct gdt_ptr {
    unsigned short limit;
    unsigned int base;
}__attribute__((packed));

//o GDT e o seu ponteiro de GDT
struct gdt_entry gdt[3];
struct gdt_ptr gp;

//recarregando os novos registradores do segmento
extern void gdt_flush();

//atribui um descritor na tabela de descritores global
void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran){
    //atribui o endereço do descrito base
    gdt[num].base_low = (base  & 0xFFFF);
    gdt[num].base_middle = (base >>16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    //limites do descrittor
    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F);

    //flags de granularidade
    gdt[num].granularity |= (gran & 0xF0);
    gdt[num].access = access;
}
void gdt_install(){
    //atribui o ponteiro GDT
    gp.limit = (sizeof(struct gdt_entry) * 3) - 1;
    gp.base = (unsigned int)&gdt;

    //descritor nulo
    gdt_set_gate(0, 0, 0, 0, 0);

    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    //joga fora a gdt antiga e implementa as mudanças
    gdt_flush();
}