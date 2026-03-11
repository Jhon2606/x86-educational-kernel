#!/bin/sh
echo Agora montando, compilando, e juntando seu Kernel:
nasm -f elf32 -o start.o start.asm

gcc -Wall -O -fstrength-reduce -fomit-frame-pointer \
    -finline-functions -nostdinc -fno-builtin -fno-pie \
    -I./include -c -m32 -o main.o main.c
echo main pronta...

gcc -Wall -O -fstrength-reduce -fomit-frame-pointer \
    -finline-functions -nostdinc -fno-builtin -fno-pie \
    -I./include -c -m32 -o scrn.o scrn.c
echo Juntando kernel...


ld -m elf_i386 -T link.ld -o kernel.bin start.o main.o scrn.o
echo Feito!