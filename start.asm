[BITS 32]
start:
    mov esp, _sys_stack
    jump stublet

    ALIGN 4
    mboot:

    MULTIBOOT_PAGE_ALIGN equ 1<<0
    MULTIBOOT_MEMORY_INFO equ 1<<1
    MULTIBOOT_AOUT_KLUDGE equ 1<<16
    stublet: