#include <system.h>
int extended = 0;
int ctrl = 0;
int alt = 0;
int shift = 0;
int caps = 0;
//minusculo
unsigned char kbdus[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	
  '9', '0', '-', '=',
 '\b',	/* Backspace */
  '\t', /* Tab */
  'q', 'w', 'e', 'r',
  't', 'y', 'u', 'i', 'o', 'p', '[', ']',
 '\n',	/* Tecla enter */
    0,	/* 29 - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
 '\'', '`',
    0, /* Shift esquerdo */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',
  'm', ',', '.', '/',
    0, /* Shift direito */
  '*',
    0,	/* Alt */
  ' ',	/* Barra de espaço */
    0,	/* Caps lock */
    0,	/* tecla 59 - F1 ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock */
    0,	/* Scroll Lock */
    0,	/* Tecla Home */
    0,	/* Seta para cima */
    0,	/* Page Up */
  '-',
    0,	/* Seta esquerda */
    0,
    0,	/* Seta direita */
  '+',
    0,	/* tecla 79 - End */
    0,	/* Seta para baixo */
    0,	/* Page Down */
    0,	/* Tecla Insert */
    0,	/* Tecla Delete */
    0,   0,   0,
    0,	/* Tecla F11 */
    0,	/* Tecla F12 */
    0,	/* Todas as outras teclas são indefinidas */
};
//maiusculo
unsigned char kbdus_shift[128] = {
    0, 27, '!','@','#','$','%','^','&','*',
    '(' ,')','_','+', '\b','\t',
    'Q','W','E','R','T','Y','U','I','O','P','{','}',
    '\n', 0,
    'A','S','D','F','G','H','J','K','L',':','"','~',
    0,'|','Z','X','C','V','B','N','M','<','>','?',
    0,'*',0,' ',
};

//tratando interrupções do teclado
void keyboard_handler(struct regs *r) {
	unsigned char scancode;
	//le o buffer de dados do teclado
	scancode = inportb(0x60);
	if (scancode == 0xE0) {
		extended = 1;
		return;
	}
	//tecla solta
	if (scancode & 0x80) {
		scancode &= 0x7F;

		if (scancode == 42 || scancode == 54)
			shift = 0;

		if (scancode == 29)
			ctrl = 0;

		if (scancode == 56)
			alt = 0;

		return;
	}
	else {

		if (scancode == 42 || scancode == 54) {
			shift = 1;
			return;
		}

		if (scancode == 29) {
			ctrl = 1;
			return;
		}

		if (scancode == 56) {
			alt = 1;
			return;
		}

		if (scancode == 58) {
			caps = !caps;
			update_keyboard_leds();
			return;
		}

		if (extended) {
			extended = 0;
      //futuramente farei as setas aplicarem o seu papel
			switch (scancode) {
			case 0x48:
				puts((unsigned char *)"UP\n");
				break;
			case 0x50:
				puts((unsigned char *)"DOWN\n");
				break;
			case 0x4B:
				puts((unsigned char *)"LEFT\n");
				break;
			case 0x4D:
				puts((unsigned char *)"RIGHT\n");
				break;
			}
			return;
		}


		char c;
		if (shift) {
			c = kbdus_shift[scancode];
		} else {
			c = kbdus[scancode];
		}
		if (caps && c >= 'a' && c <= 'z') {
			c = c - 32;
		}
		if (c == '\b') {
			backspace();
		} else if (c == '\n') {
			putch('\n');
		} else if (c) {
			putch(c);
		}
	}
}
//registrando handler no irq 1
void keyboard_install() {
	irq_install_handler(1, keyboard_handler);
}

void keyboard_set_leds(unsigned char leds) {
	//espera o teclado ficar livre
	while (inportb(0x64) & 2);

	//envia comando: "vou configurar LEDs"
	outportb(0x60, 0xED);

	//espera novamente
	while (inportb(0x64) & 2);

	//envia quais LEDs ligar
	outportb(0x60, leds);
}
void update_keyboard_leds() {
	unsigned char leds = 0;

	if (caps) leds |= 0x04;

	keyboard_set_leds(leds);
}