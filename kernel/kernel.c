//objdump -d -M intel filename

void _printSign(void){
    *(long long*)0xb8000 = 0x4141414141414141LL;
}

void _start(void){
    _printSign();
}