# x86-educational-kernel
Este projeto consiste na implementação de um kernel educacional para a arquitetura x86, desenvolvido do zero com o objetivo de aprofundar o aprendizado em sistemas operacionais e programação de baixo nível.

O desenvolvimento foi baseado no tutorial Bran's Kernel Development, originalmente traduzido por Mauro Joel Schütz e posteriormente revisado e atualizado pelo professor Jacson R. C. Silva.

Ao longo do projeto, são explorados conceitos fundamentais como gerenciamento básico de hardware, tratamento de interrupções, entrada e saída (I/O) e funcionamento interno de um kernel.
## Ferramentas Necessárias
Para desenvolver, compilar e executar o kernel, é necessário ter um ambiente com as seguintes ferramentas:
### Compiladores
- O Compilador Gnu C Compiler (GCC) [Unix]
- DJGPP (GCC para DOS/Windows) [Windows]
### Assemblers
- Netwide Assembler (NASM) [Unix/Windows]
### Emuladores / Máquinas Virtuais
- **QEMU** (recomendado) – Emulação rápida e leve  
- **VirtualBox**  
- **VMware Workstation**  
- **Bochs** (útil para debug detalhado)
## Ambiente Recomendado
O desenvolvimento é recomendado em sistemas **GNU/Linux baseados em Debian**
## Instalação das Dependências
Execute os comandos abaixo para instalar todas as ferramentas necessárias:
```bash
sudo apt update
sudo apt install qemu-system-x86 nasm bison gcc gcc-multilib binutils make
