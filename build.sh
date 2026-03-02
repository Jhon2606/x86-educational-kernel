#!/bin/sh
echo Agora montando, compilando, e juntando seu Kernel:
nasm -f elf32 -o start.o start.asm
echo Lembre-se neste ponto aqui: Nós vamos adicionar comandos 'gcc' para compilar as fontes em C

echo Este junta todos seus arquivos. Lembre-se de como você adiciona arquivos *.o, você precisa
echo adicionar após start.o. Se você não adicionar eles de qualquer modo, eles não estarão em seu kernel!
ld -m elf_i386 -T link.ld -o kernel.bin start.o
echo Feito!