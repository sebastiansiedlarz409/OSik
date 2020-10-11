[bits 16]                       ;we start in 16 bits mode
[org 0x7c00]                    ;adres in memory where bios upload our image
                                ;THERE IS ONLY 512 BYTES SPACE -> https://wiki.osdev.org/Memory_Map_(x86)
                                ;its 16bit address mode
                                ;address = segment * 0x10 + offset
                                ;segment go to segment register CS, DS, ES, FS, GS, and SS
                                ;offset go to IP register
                                ;so CS = 0x0000, IP == 0x7c00
                                ;check "Memory Addressing" -> https://wiki.osdev.org/Real_Mode

jmp word 0x0000:stage1          ;just go to stage1 label

stage1:
    mov ax, 0xb800              ;so we can mov const to es directly
    mov es, ax                  
    mov bx, 0                   ;bx is offset in address [es:bx] (0x1000*0x10+0x0)
                                ;its just stage2 address in memory

    mov ah, 0x02                ;interrupt command
    mov al, 1                   ;sector count 1 sector = 512 bytes, how many sectors
    mov ch, 0                   ;cylinder number -> floppy = 0
    mov dh, 0                   ;head = 0
    mov cl, 2                   ;so 1 is boot, we start from 2, bits 7-6 = 00
    mov dl, 0                   ;index of floppy file
                                ;check page 6 -> http://www.gabrielececchetti.it/Teaching/CalcolatoriElettronici/Docs/i8086_and_DOS_interrupts.pdf

    int 13h                    ;interrutp from link above

epilogue:
%if ($ - $$) > 510
  %fatal "STAGE1 code cant exceed 512 bytes!!!"
%endif

times 510 - ($ - $$) db 0       ;if stage1 size is less than 510 add some trash
db 0x55                         ;last to bytes
db 0xAA                         ;check "MBR Format" -> https://wiki.osdev.org/MBR_(x86)