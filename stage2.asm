[bits 16]
[org 0x0000]                            ;I choose to load stage2 to 0x10000
                                        ;check "Real mode address space" -> https://wiki.osdev.org/Memory_Map_(x86)

start:
    mov ax, 0x1000
    mov ds, ax                          ;set data segment address
    mov es, ax                          ;set extra segment address

    mov ax, 0x0f00                      
    mov ss, ax                          ;set stack segment address
    mov sp, 0                           ;0 to stack pointer

    lgdt [GDT_ADR]                      ;loads GDT to GDTR GDT register
                                        ;intel manual 2A -> page 663

    mov eax, cr0                        ;set processor flag
    or al, 1                            ;set PE (Protection Enable) bit in CR0 (Control Register 0)
    mov cr0, eax                        ;protected mode = 32 bits, real = 16 bits
                                        ;CR0 — Contains system control flags that control operating mode and states of the processor
                                        ;intel 3A -> page 76
                                        ;https://wiki.osdev.org/Protected_Mode

    ;0x8 is code segment id
    ;intel 3A - page 95
    ;jmp actualy switch modes
    ;we moved to 32 bits addresses
    jmp dword 0x8:(0x10000+stage32)

stage32:
    [bits 32]
    mov ax, 0x10                        ;0x10 is data segment id from GDT below
    mov ds, ax
    mov es, ax
    mov ss, ax

    lea eax, [0xb8000]                  ;lea toggele big/little endian
  
    mov dword [eax], 0x41414141

    jmp $                               ;infinity loop

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
dd (10 << 8) | (1 << 12) | (1 << 15) | (15 << 16) | (1 << 22) | (1 << 23)

; Data segment
dd 0xffff                               ;2Bytes base address, 2Bytes segment limit(size)
dd (2 << 8) | (1 << 12) | (1 << 15) | (15 << 16) | (1 << 22) | (1 << 23)

; Its helpfull when number of segment is multiply of 2
dd 0, 0

GDT_END:

;this is GDT address structure for lgdt instruction
;intel manuals 2A -> page 663
;2Bytes limit/size, 4Bytes Address
GDT_ADR:
dw (GDT_END - GDT) - 1                  ;size of GDT above as 2Bytes
dd 0x10000 + GDT                        ;16 bit mode address GDT
times (32 - ($ - $$) % 32) dd 0xcc

times 512 - ($ - $$) db 0