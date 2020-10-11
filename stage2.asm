[bits 16]
[org 0x0000]                            ;I choose to load stage2 to 0x10000
                                        ;check "Real mode address space" -> https://wiki.osdev.org/Memory_Map_(x86)


stage2:
    dw 0x4150
    dw 0x4145
    dw 0x4143
    dw 0x415a
    dw 0x4145
    dw 0x414b
    dw 0x4120      ;space

    dw 0x414e
    dw 0x4149
    dw 0x4145
    dw 0x4120      ;space

    dw 0x4155
    dw 0x414d
    dw 0x4149
    dw 0x4145
    dw 0x4120      ;space

    dw 0x4150
    dw 0x4152
    dw 0x414f
    dw 0x4147
    dw 0x4152
    dw 0x4141
    dw 0x414d
    dw 0x414f
    dw 0x4157
    dw 0x4141
    dw 0x4143

    ;times 234 db 0x4146  