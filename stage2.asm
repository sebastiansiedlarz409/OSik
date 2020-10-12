[bits 16]
[org 0x0000]                            ;I choose to load stage2 to 0x10000
                                        ;check "Real mode address space" -> https://wiki.osdev.org/Memory_Map_(x86)


stage2:
    mov ax, 0x1000
    mov ds, ax                          ;set data segment address
    mov es, ax                          ;set extra segment address

    mov ax, 0x0f00                      
    mov ss, ax                          ;set stack segment address
    mov sp, 0                           ;0 to stack pointer

    mov [fs:bx], ax                     ;set fs segment register
                                        ;check "Segment Registers" -> https://en.wikibooks.org/wiki/X86_Assembly/X86_Architecture

    jmp $                               ;infinity loop

    times 1024 db 0x00