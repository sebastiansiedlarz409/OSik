//objdump -d -M intel filename

void _welcome(void* kernelEntryPointAddress, void* stackAddress){
    char* kernelString = "Kernel loaded at";
    char kernelStringSize = 17;

    char* stackString = "Stack placed at";
    char stackStringSize = 16;

    //make unsigned 64 bit number from pointers
    unsigned long long kEPAddress = (unsigned long long)kernelEntryPointAddress;
    unsigned long long sAddress = (unsigned long long)stackAddress;
    
    char *textVRAM = (char*)(0xB8000 + (160 * 20));

    int offset = 0;
    for(int i = 0; i < kernelStringSize; i++){
        textVRAM[offset] = kernelString[i];
        textVRAM[offset+1] = 0x01;
        offset += 2;
    }

    textVRAM += (kernelStringSize*2);

    textVRAM[0] = '0';
    textVRAM[1] = 0x01;
    textVRAM[2] = 'x';
    textVRAM[3] = 0x01;
    textVRAM+=4;

    for(int i = 0; i < 32; i+=2){
        textVRAM[i] = "0123456789ABCDEF"[(kEPAddress >> 60) & 0xf];
        textVRAM[i+1] = 0x01;
        kEPAddress <<= 4;
    }

    textVRAM = (char*)(0xB8000 + (160 * 21));

    offset = 0;
    for(int i = 0; i < stackStringSize; i++){
        textVRAM[offset] = stackString[i];
        textVRAM[offset+1] = 0x01;
        offset += 2;
    }

    textVRAM += (stackStringSize*2);

    textVRAM[0] = '0';
    textVRAM[1] = 0x01;
    textVRAM[2] = 'x';
    textVRAM[3] = 0x01;
    textVRAM+=4;

    for(int i = 0; i < 32; i+=2){
        textVRAM[i] = "0123456789ABCDEF"[(sAddress >> 60) & 0xf];
        textVRAM[i+1] = 0x01;
        sAddress <<= 4;
    }
    
}

void _start(void* kernelEntryPointAddress, void* stackAddress){
    _welcome(kernelEntryPointAddress, stackAddress);

    for(;;);
}