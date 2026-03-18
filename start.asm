[BITS 32]
GLOBAL start ;tentativa externa ao tutotial de corrigir o erro do linker
start:
    mov esp, _sys_stack
    jmp stublet

    ALIGN 4
    mboot:

    MULTIBOOT_PAGE_ALIGN equ 1<<0
    MULTIBOOT_MEMORY_INFO equ 1<<1
    MULTIBOOT_AOUT_KLUDGE equ 1<<16
    MULTIBOOT_HEADER_MAGIC equ 0x1BADB002
    MULTIBOOT_HEADER_FLAGS equ MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO | MULTIBOOT_AOUT_KLUDGE
    MULTIBOOT_CHECKSUM equ -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)
    EXTERN code, bss, end
    
    dd MULTIBOOT_HEADER_MAGIC
    dd MULTIBOOT_HEADER_FLAGS
    dd MULTIBOOT_CHECKSUM

    dd mboot
    dd code
    dd bss
    dd end
    dd start
    stublet:
    extern kmain
    call kmain
        jmp $

        ;GDT flush

        global gdt_flush
        extern gp
        gdt_flush:
            lgdt [gp]     ; Carrega GDT com nosso ponteiro especial '_gp'
            mov ax, 0x10  ; 0x10 é o offset na GDT para nosso segmento de dados
            mov ds, ax
            mov es, ax
            mov fs, ax
            mov gs, ax
                jmp 0x08:flush2 ;0x08 é offset para nosso codigo: salto longo
        flush2:
            ret ;retorna para o codigo em c

            global idt_load
            extern idtp
            
            idt_load:
                lidt [idtp]
                ret
    global isr0
    global isr1
    global isr2
    global isr3
    global isr4
    global isr5
    global isr6
    global isr7
    global isr8
    global isr9
    global isr10
    global isr11
    global isr12
    global isr13
    global isr14
    global isr15
    global isr16
    global isr17
    global isr18
    global isr19
    global isr20
    global isr21
    global isr22
    global isr23
    global isr24
    global isr25
    global isr26
    global isr27
    global isr28
    global isr29
    global isr30
    global isr31
    ; 0: se dividir por 0
    isr0:
        cli
        push byte 0
        push byte 0
        jmp isr_common_stub
    ; 1: Exceção Debug
    isr1:
        cli
        push byte 0
        push byte 1
        jmp isr_common_stub
    ; 2: Exceção Interrupção Não Mascarada
    isr2:
        cli
        push byte 0
        push byte 2
        jmp isr_common_stub
    ; 3: Exceção Ponto de Parada (Breakpoint)
    isr3:
        cli
        push byte 0
        push byte 3
        jmp isr_common_stub
    ; 4: Exceção Detectado Overflow Interno
    isr4:
        cli
        push byte 0
        push byte 4
        jmp isr_common_stub
    ; 5: Exceção Fora da União
    isr5:
        cli
        push byte 0
        push byte 5
        jmp isr_common_stub
    ; 6: Exceção Opcode Invalido
    isr6:
        cli
        push byte 0
        push byte 6
        jmp isr_common_stub
    ; 7: Exceção Nenhum Coprocessador
    isr7:
        cli
        push byte 0
        push byte 7
        jmp isr_common_stub
    ; 8: Exceção Falta Dupla (Com código de Erro!)
    isr8:
        cli
        push byte 8
        jmp isr_common_stub
    ; 9: Exceção Coprocessador Segmento Overrun
    isr9:
        cli
        push byte 0
        push byte 9
        jmp isr_common_stub
    ; 10: Exceção TSS Ruim
    isr10:
        cli
        push byte 10
        jmp isr_common_stub
    ; 11: Exceção Segmento Não Presente
    isr11:
        cli
        push byte 11
        jmp isr_common_stub
    ; 12: Exceção Falta Pilha
    isr12:
        cli
        push byte 12
        jmp isr_common_stub
    ; 13: Exceção Falta de Proteção Geral
    isr13:
        cli
        push byte 13
        jmp isr_common_stub
    ; 14: Exceção Falta de Página
    isr14:
        cli
        push byte 14
        jmp isr_common_stub
    ; 15: Exceção Interrupção Desconhecida
    isr15:
        cli
        push byte 0
        push byte 15
        jmp isr_common_stub
    ; 16: 	Exceção Falta Coprocessador
    isr16:
        cli
        push byte 0
        push byte 16
        jmp isr_common_stub
    ; 17: Exceção Checagem de Alinhamento (486+)
    isr17:
        cli
        push byte 17
        jmp isr_common_stub
    ; 18: Exceção Checagem de Máquina (Pentium/586+)
    isr18:
        cli
        push byte 0
        push byte 18
        jmp isr_common_stub
    ; 19: Exceções Reservado (19 a 31)
    isr19:
        cli
        push byte 0
        push byte 19
        jmp isr_common_stub
    isr20:
        cli
        push byte 0
        push byte 20
        jmp isr_common_stub

    isr21:
        cli
        push byte 0
        push byte 21
        jmp isr_common_stub

    isr22:
        cli
        push byte 0
        push byte 22
        jmp isr_common_stub

    isr23:
        cli
        push byte 0
        push byte 23
        jmp isr_common_stub

    isr24:
        cli
        push byte 0
        push byte 24
        jmp isr_common_stub

    isr25:
        cli
        push byte 0
        push byte 25
        jmp isr_common_stub

    isr26:
        cli
        push byte 0
        push byte 26
        jmp isr_common_stub

    isr27:
        cli
        push byte 0
        push byte 27
        jmp isr_common_stub

    isr28:
        cli
        push byte 0
        push byte 28
        jmp isr_common_stub

    isr29:
        cli
        push byte 0
        push byte 29
        jmp isr_common_stub

    isr30:
        cli
        push byte 30
        jmp isr_common_stub

    isr31:
        cli
        push byte 0
        push byte 31
        jmp isr_common_stub

    extern fault_handler ; essa função existe em outro arquivo
    ; Salva o estado do processador, atribui os segmentos para modo kernel, chama o tratamento nível-C e finalmente restaura a forma da pilha
    isr_common_stub:
    ;salva registradores de segmento
        pusha
        push ds
        push es
        push fs
        push gs
    ;fazendo os segmentos apontarem para dados do kernel
        mov ax, 0x10
        mov ds, ax
        mov es, ax
        mov fs, ax
        mov gs, ax
        mov eax, esp
        push eax
        mov eax, fault_handler
        call eax
    ;Restauramos todos os registradores.
        pop eax
        pop gs
        pop fs
        pop es
        pop ds
        popa
        add esp, 8 ; Remove da pilha: 2 valores × 4 bytes = 8 bytes
        iret ; retorna exatamente para o ponto onde o programa parou

        ;IRQs e PICs
global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15

;32: IRQ0
irq0:
    cli
    push byte 0
    push byte 32
    jmp irq_common_stub
; 33: IRQ1
irq1:
    cli
    push byte 0
    push byte 33
    jmp irq_common_stub
; 34: IRQ2
irq2:
    cli
    push byte 0
    push byte 34
    jmp irq_common_stub
;...
irq3:
    cli
    push byte 0
    push byte 35
    jmp irq_common_stub
irq4:
    cli
    push byte 0
    push byte 36
    jmp irq_common_stub
irq5:
    cli
    push byte 0
    push byte 37
    jmp irq_common_stub
irq6:
    cli
    push byte 0
    push byte 38
    jmp irq_common_stub
irq7:
    cli
    push byte 0
    push byte 39
    jmp irq_common_stub
irq8:
    cli
    push byte 0
    push byte 40
    jmp irq_common_stub
irq9:
    cli
    push byte 0
    push byte 41
    jmp irq_common_stub
irq10:
    cli
    push byte 0
    push byte 42
    jmp irq_common_stub
irq11:
    cli
    push byte 0
    push byte 43
    jmp irq_common_stub

irq12:
    cli
    push byte 0
    push byte 44
    jmp irq_common_stub
irq13:
    cli
    push byte 0
    push byte 45
    jmp irq_common_stub
irq14:
    cli
    push byte 0
    push byte 46
    jmp irq_common_stub
irq15:
    cli
    push byte 0
    push byte 47
    jmp irq_common_stub
extern irq_handler

;chama irq_handler em nosso código 
irq_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp
    push eax
    mov eax, irq_handler
    call eax
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret
    SECTION .bss
        resb 8192
    _sys_stack: