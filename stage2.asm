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

;https://software.intel.com/content/www/us/en/develop/articles/intel-sdm.html
;intel manuals 3
;segment selector (16-bit identifier for a segment) -> page 95

GDT:                                    ;GLOBAL DESCRIPTOR TABLE 32-BIT

; Null segment
dd 0, 0

; Code segment -> page 97
dd 0xffff                               ;2Bytes base address, 2Bytes segment limit(size)
;BA - bits [7:0] - base address
;Type - bits [11:8] - read/execution -> 0b1010 -> Table 3.1 page 100
;S - bit 12 - the segment descriptor is for a system segment (S flag is clear) or a code or data segment (S flag is set)
;DPL - bits[13:14] - DPL (descriptor privilege level) field specifies the privilege level of the segment -> 0 to 3
;P - bit 15 - indicates whether the segment is present in memory (set) or not present (clear)
;SegLimit - bits [19:16] - segment limit is 0xffff so here goes 0xf
;AVL - bit 20 - Available for use by system software
;L - bit 21 - 1 64 bit segment, 0 no 64 bits segment
;D/B - bit 22 - 0 16 bi segment, 1 32 bits segment
;G - bit 23 - Granularity -  granularity flag is clear, the segment limit is interpreted in byte units; when flag is set, the segment limit is interpreted in 4-KByte units.
dd (0b1010 << 8) | (0b1 << 12) | (0b1 << 15) | (0b1111 << 16) | (0b1 << 22) | (0b1 << 23)

; Data segment
dd 0xffff                               ;2Bytes base address, 2Bytes segment limit(size)
dd (2 << 8) | (1 << 12) | (1 << 15) | (0xf << 16) | (1 << 22) | (1 << 23)

GDT_END: