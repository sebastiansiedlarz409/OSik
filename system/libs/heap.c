#include "heap.h"

MemorySegment FIRST_SEG = {
    .address = 0x500000,
    .size = 0,
    .free = NOT_USED,
    .next = &FIRST_SEG,
    .prev = &FIRST_SEG
};

//init node
void HEAP_Init(MemorySegment* seg)
{
    seg->next = seg;
    seg->prev = seg;
    seg->free = NOT_USED;
    seg->size = 0;
    seg->address = (uint64_t)seg;
}

void HEAP_InsertAfter(MemorySegment* seg, MemorySegment* newSeg)
{
    MemorySegment* seg_next = seg->next;
    MemorySegment* newSeg_prev = newSeg->prev; 

    seg->next = newSeg;
    newSeg->prev = seg;

    newSeg->next = seg_next;
    seg_next->prev = newSeg_prev;
}

void HEAP_InsertBefore(MemorySegment* seg, MemorySegment* newSeg)
{
    MemorySegment* seg_prev = seg->prev;
    MemorySegment* newSeg_next = newSeg->next;

    seg->prev = newSeg;
    newSeg->next = seg;

    seg_prev->next = newSeg_next;
    newSeg->prev = seg_prev;
}

void HEAP_PushBack(MemorySegment* seg, MemorySegment* newSeg)
{
    HEAP_InsertAfter(seg, newSeg);
}

void HEAP_PopBack(MemorySegment* seg)
{
    seg->prev->next = seg->prev;
}

void HEAP_Remove(MemorySegment* seg)
{
    MemorySegment* seg_prev = seg->prev;
    MemorySegment* seg_next = seg->next;

    seg_next->prev = seg_prev;
    seg_prev->next = seg_next;
}