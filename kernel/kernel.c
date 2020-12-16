//objdump -d -M intel filename

#define LINE_WIDTH 160
#define LINE_COUNT 25
#define CHAR_STYLE 0x02

void _cls(void){
    //write whole buffer with value 0x0002
    char *textVRAM = (char*)0xB8000;
    for(int i = 0;i<LINE_WIDTH*LINE_COUNT;i+=2){
        textVRAM[i] = 0x00;
        textVRAM[i+1] = CHAR_STYLE;
    }
}

void _welcome(void* kernelEntryPointAddress, void* stackAddress){
    char* kernelString = "Kernel 0x";
    char kernelStringSize = 9;

    char* stackString = "Stack 0x";
    char stackStringSize = 8;

    //make unsigned 64 bit number from pointers
    unsigned long long kEPAddress = (unsigned long long)kernelEntryPointAddress;
    unsigned long long sAddress = (unsigned long long)stackAddress;
    
    char *textVRAM = (char*)(0xB8000 + (LINE_WIDTH * 20));

    int offset = 0;
    for(int i = 0; i < kernelStringSize; i++){
        textVRAM[offset] = kernelString[i];
        textVRAM[offset+1] = CHAR_STYLE;
        offset += 2;
    }

    textVRAM += (kernelStringSize*2);

    for(int i = 0; i < 32; i+=2){
        textVRAM[i] = "0123456789ABCDEF"[(kEPAddress >> 60) & 0xf];
        textVRAM[i+1] = CHAR_STYLE;
        kEPAddress <<= 4;
    }

    textVRAM = (char*)(0xB8000 + (LINE_WIDTH * 21));

    offset = 0;
    for(int i = 0; i < stackStringSize; i++){
        textVRAM[offset] = stackString[i];
        textVRAM[offset+1] = CHAR_STYLE;
        offset += 2;
    }

    textVRAM += (stackStringSize*2);

    for(int i = 0; i < 32; i+=2){
        textVRAM[i] = "0123456789ABCDEF"[(sAddress >> 60) & 0xf];
        textVRAM[i+1] = CHAR_STYLE;
        sAddress <<= 4;
    }
    
}

void _start(void* kernelEntryPointAddress, void* stackAddress){
    _welcome(kernelEntryPointAddress, stackAddress);

    //wait here some time

    _cls();

    for(;;);
}