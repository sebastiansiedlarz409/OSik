//objdump -d -M intel filename

void _printSign(void){
    *(short*)(0xb8000+160*20) = 0x4141;
}

void _start(void){
    _printSign();

    for(;;);
    
}