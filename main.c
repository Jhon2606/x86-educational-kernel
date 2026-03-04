#include <system.h>

__stack_chk_fail(){

}

unsigned char *memcpy(unsigned char *dest, const unsigned char *src, int count) {

}

unsigned char *memset(unsigned char *dest, unsigned char val, int count) {

}

unsigned short *memsetw(unsigned short *dest, unsigned short val, int count) {
   
}

int strlen(const char *str) {

}

unsigned char inportb(unsigned short _port) {
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a"(rv) : "dN"(_port));
    return rv;
}

void outportb(unsigned short _port, unsigned char _data) {
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a"(_data));
}

void main(){
    for(;;);
}