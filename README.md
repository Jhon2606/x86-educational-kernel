# x86-educational-kernel
Este projeto consiste na implementação de um kernel educacional para a arquitetura x86, desenvolvido do zero com o objetivo de aprofundar o aprendizado em sistemas operacionais e programação de baixo nível.

O desenvolvimento foi baseado no tutorial Bran's Kernel Development, originalmente traduzido por Mauro Joel Schütz e posteriormente revisado e atualizado pelo professor Jacson R. C. Silva.

Ao longo do projeto, são explorados conceitos fundamentais como gerenciamento básico de hardware, tratamento de interrupções, entrada e saída (I/O) e funcionamento interno de um kernel.

## Ferramentas Necessárias
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

## Instalação das Dependências
O desenvolvimento é recomendado em sistemas **GNU/Linux baseados em Debian**. Caso esteja usando o mesmo
execute os comandos abaixo para instalar todas as ferramentas necessárias:
```bash
sudo apt update
sudo apt install qemu-system-x86 nasm bison gcc gcc-multilib binutils make
```

## Módulos e estrutura
Este kernel segue uma arquitetura modular simples, dividida em componentes responsáveis pela inicialização do sistema, configuração da CPU e interação básica com o hardware.

### Boot e Inicialização
Responsável por preparar o ambiente inicial do kernel após o carregamento pelo bootloader (GRUB via Multiboot).
Tendo como principais responsabilidades:

- Definição da pilha (stack)
- Declaração do cabeçalho Multiboot
- Transferência de controle para o kernel em C

```bash
Fluxo: GRUB → start.asm → kernel_main
```

### Configuração da CPU

Responsável por configurar estruturas fundamentais da arquitetura x86 para funcionamento em modo protegido.

#### GDT (Global Descriptor Table)
- Define os segmentos de memória  
- Configura níveis de privilégio  
- Base para execução em modo protegido  

#### IDT (Interrupt Descriptor Table)
- Define como interrupções e exceções são tratadas  
- Associa handlers às interrupções  

### Tratamento de Interrupções

Responsável por implementar o mecanismo de tratamento de exceções e interrupções da CPU, realizando a captura de eventos, preservação de contexto e encaminhamento para rotinas de tratamento em C.

- ISRs (Interrupt Service Routines)
- `isr_common_stub` (ponte entre Assembly e C)
- `fault_handler` em C

```bash
Fluxo: Evento → ISR (Assembly) → isr_common_stub → fault_handler (C)
```

### Driver de Vídeo (VGA Text Mode)
Responsável pela saída de dados na tela utilizando o modo texto da VGA.

- Escrita direta na memória de vídeo (`0xB8000`)
- Funções como:
  - `putch`
  - `puts`
  - `cls`
- Controle de cursor e scroll

### Núcleo do Kernel
Responsável por coordenar a inicialização dos subsistemas. Sendo suas funções principais

- Inicializar GDT
- Inicializar IDT
- Ativar interrupções
- Executar testes básicos

## Observações

Este kernel possui caráter educacional e implementa apenas funcionalidades essenciais para compreensão do funcionamento interno de sistemas operacionais.