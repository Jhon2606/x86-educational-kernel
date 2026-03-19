CC_OPTIONS := -Wall -O -fstrength-reduce -fomit-frame-pointer \
              -finline-functions -nostdinc -fno-builtin -fno-pie \
              -I./include -c -m32

OUTPUT = kernel.bin

build:
	@echo 'Montando, compilando, e juntando o kernel'
	
	@echo 'Compilando start.asm ...'
	@# Não deve compilar com "-f aout" pois dá problema no
	@# momento da ligação, deve-se compilar tudo no mesmo
	@# formato: elf32
	nasm -f elf32 -o start.o start.asm
	
	@echo 'Compilando main.c ...'
	gcc $(CC_OPTIONS) -o main.o main.c
	
	@echo 'Compilando scrn.c ...'
	gcc $(CC_OPTIONS) -o scrn.o scrn.c
	
	@echo 'Compilando gdt.c ...'
	gcc $(CC_OPTIONS) -o gdt.o gdt.c
	
	@echo 'Compilando idt.c ...'
	gcc $(CC_OPTIONS) -o idt.o idt.c
	
	@echo 'Compilando isrs.c ...'
	gcc $(CC_OPTIONS) -o isrs.o isrs.c
	
	@echo 'Compilando irq.c ...'
	gcc $(CC_OPTIONS) -o irq.o irq.c
	
	@echo 'Compilando timer.c ...'
	gcc $(CC_OPTIONS) -o timer.o timer.c
	
	#@echo 'Compilando kb.c ...'
	#gcc $(CC_OPTIONS) -o kb.o kb.c
	
	#@echo 'Compilando cmds.c ...'
	#gcc $(CC_OPTIONS) -o cmds.o cmds.c

	@echo 'Unindo os arquivos...'
	ld -m elf_i386 -T link.ld -o $(OUTPUT) start.o main.o scrn.o gdt.o idt.o isrs.o irq.o timer.o
#A medida que for seguindo o tutorial, vá colocando os demais arquivos na linha acima:
#start.o scrn.o gdt.o idt.o isrs.o irq.o timer.o kb.o cmds.o
	@echo 'Feito!'
    