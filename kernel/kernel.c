//objdump -d -M intel filename

#define LINE_WIDTH 160
#define LINE_COUNT 25
#define CHAR_STYLE 0x02

//screen context
struct VRAM_ContextStruct {
  unsigned short x;
  unsigned short y;
} VRAM_Context;

//PORTS
//https://wiki.osdev.org/I/O_Ports
//http://bochs.sourceforge.net/techspec/PORTS.LST
//0x03B0-0x03DF
//how to use ports
//https://wiki.osdev.org/Port_IO
//inline assembly
//https://students.mimuw.edu.pl/SO/Projekt03-04/temat2-g6/inline.html

void HAL_PortOutByte(int port, unsigned char v) {
  __asm("out dx, al\n" : /*output var*/ : /*input var*/ "a" (v), "d" (port) : /*clear regs*/);
}

void HAL_PortOutWord(int port, unsigned short v) {
  __asm("out dx, ax\n" : /*output var*/ : /*input var*/ "a" (v), "d" (port) : /*clear regs*/);
}

void HAL_PortOutDword(int port, unsigned int v) {
  __asm("out dx, eax\n" : /*output var*/ : /*input var*/ "a" (v), "d" (port) : /*clear regs*/);
}

void _scp(unsigned short x, unsigned short y){
    //http://wiki.osdev.org/Text_Mode_Cursor#Moving_the_Cursor_with_the_BIOS
    unsigned int position = y * (LINE_WIDTH/2) + x;

    HAL_PortOutByte(0x3D4, 0x0F);                                       //tell that we want change reg 0x0F in 0x3D5 port
    HAL_PortOutByte(0x3D5, (unsigned char)(position & 0xFF));           //lower 8 bits
    HAL_PortOutByte(0x3D4, 0x0E);
    HAL_PortOutByte(0x3D5, (unsigned char)(position >> 8));

    VRAM_Context.x = x;
    VRAM_Context.y = y;
}

void _putchar(char ch){
    char *textVRAM = (char*)0xB8000;

    unsigned short x = VRAM_Context.x;
    unsigned short y = VRAM_Context.y;

    unsigned int position = y * (LINE_WIDTH/2) + x;

    textVRAM[position*2] = ch;
    textVRAM[position*2+1] = CHAR_STYLE;

    x++;

    if(x==80){
        x=0;
        y++;
    }
    _scp(x,y);
}

void _printf(char* value){
    while(*value != '\0'){

        if(*value == '\n'){
            _scp(VRAM_Context.x, VRAM_Context.y+1);
            value++;
            continue;
        }
        if(*value == '\r'){
            _scp(0, VRAM_Context.y);
            value++;
            continue;
        }

        _putchar(*value);
        value++;
    }
}

void _cls(void){
    //write whole buffer with value 0x0002
    char *textVRAM = (char*)0xB8000;
    for(int i = 0;i<LINE_WIDTH*LINE_COUNT;i+=2){
        textVRAM[i] = 0x00;
        textVRAM[i+1] = CHAR_STYLE;
    }

    //move cursor to 0, 0
    _scp(0, 0);
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

    _printf("test\r");

    for(;;);
}