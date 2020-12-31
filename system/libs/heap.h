#ifndef HEAP_H
#define HEAP_H

#include <stdint.h>

typedef struct _MemorySegment MemorySegment;

enum MEM_USAGE{
    USED = 0x1,
    NOT_USED = 0x0
};

struct _MemorySegment{
    uint64_t address;
    uint64_t size;
    uint8_t free;
    MemorySegment* prev;
    MemorySegment* next;
};

MemorySegment FIRST_SEG;

void HEAP_Init(MemorySegment* seg);
void HEAP_InsertAfter(MemorySegment* seg, MemorySegment* newSeg);
void HEAP_InsertBefore(MemorySegment* seg, MemorySegment* newSeg);
void HEAP_PushBack(MemorySegment* seg, MemorySegment* newSeg);
void HEAP_PopBack(MemorySegment* seg);
void HEAP_Remove(MemorySegment* seg);

#endif //HEAP_H