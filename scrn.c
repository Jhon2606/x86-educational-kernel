#include <system.h>

//definindo ponteiro de texto, cores de fundo, atributos e coordenadas x e y
unsigned short *textmemptr;
int attrib = 0x0F;
int csr_x = 0, csr_y = 0;

//rolando a tela
void scroll(void){
    unsigned blank, temp;

    //definindo um vazio com um espaço, fazendo o mesmo com uma cor de fundo
    blank = 0x20 | (attrib << 8);

    //so vai ate a linha 24, então pode rolar mpara cima
    if(csr_y >= 25){
        temp = csr_y - 25 + 1;
        memcpy((unsigned char *)textmemptr, (unsigned char*)(textmemptr + temp * 80), (25 - temp) * 80 * 2);
    //limpando a ultima linha
    memsetw(textmemptr + (25 - temp) * 80, blank, 80);
    csr_y = 25 - 1;
    }
}
//atualiza o cursor do hardware (o ponto que pisca)
void move_csr(void){
    unsigned temp;

    //equeção que descobre o índice de um pedaço linear da memória é índice = [(y * largura) + x]
    temp = csr_y * 80 + csr_x;

    //Manda um comando para os índices 14 e 15 no registrado de Controle CRT do controle VGA, são os bytes superior e inferior do índice que mostra onde o cursor do hardware está piscando
    outportb(0x3D4, 14);
    outportb(0x3D5, temp >> 8);
    outportb(0x3D4, 15);
    outportb(0x3D5, temp);
}
//limpa a tela
void cls(){
    unsigned blank;
    int i;
    
    blank = 0x20 | (attrib << 8);

    for(i = 0; i < 25; i++)
        memsetw(textmemptr + i * 80, blank, 80);

    csr_x = 0;
    csr_y = 0;
    move_csr();
}
//coloca um caractere unico sobre a tela
void putch(unsigned char c){
    unsigned short *where;
    unsigned att = attrib << 8;

    //trata um backspace
    if(c == 0x08){
        if(csr_x != 0) csr_x--;
    }
    //tab incrementando o cursor x, mas somente para um ponto divisível por 8
    else if(c == 0x09){
        csr_x = (csr_x + 8) & ~(8 - 1);
    }
    //cursor para a margem
    else if(c == '\r'){
        csr_x = 0;
    }
    //vai para a linha de baixo
    else if(c =='\n'){
        csr_x = 0;
        csr_y++;
    }
    //equação para achar o índice em um pedaço da memória linear pode ser representado por: Índice = [(y * largura) + x]
    else if(c >= ' '){
        where = textmemptr + (csr_y * 80 + csr_x);
        *where = c | att; //caracter e atributos de cor
        csr_x++;
    }
    //se chegou na margem
    if(csr_x >= 80){
        csr_x = 0;
        csr_y++;
    }
    //rola a tela e move o cursor
    scroll();
    move_csr();
}
//usa rotina para escreever palavrinhas
void puts(unsigned char *text){
    int i;
    for(i = 0; i < strlen((const char *)text); i++){
        putch(text[i]);
    }
}
//bora colocar uma corzinha nesse trem
void settextcolor(unsigned char forecolor, unsigned char backcolor){
    //os primeiros 4 bytes são de fundo e os 4 bytes da frente são da frente (não me diga)
    attrib = (backcolor << 4) | (forecolor & 0x0F);
}
//atribui o ponteiro de modo texto certinho e depois limpa a tela pá nois
void init_video(void){
    textmemptr = (unsigned short *)0xB8000;
    cls();
}