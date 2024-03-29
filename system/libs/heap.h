#ifndef HEAP_H
#define HEAP_H

#include <stdint.h>

typedef struct _MemorySegment MemorySegment;

struct _MemorySegment{
    uint64_t size;
    uint8_t free;
    MemorySegment* prev;
    MemorySegment* next;
    MemorySegment* prevFree;
    MemorySegment* nextFree;
};

enum MEM_USAGE{
    FREE = 0x1,
    NOT_FREE = 0x0
};

void HEAP_Init(uint64_t address, uint64_t size);
void* HEAP_Malloc(uint64_t size);
void HEAP_Free(void* ptr);

#endif //HEAP_H