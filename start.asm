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

    SECTION .bss
        resb 8192
    _sys_stack: