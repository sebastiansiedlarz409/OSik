#include "heap.h"
#include "../terminal/terminal.h"
#include "../terminal/terminal_B8000_8025.h"

#include <stdint.h>

//init node
void HEAP_Init(uint64_t address, uint64_t size)
{
    CUR_FREE_SEG = (MemorySegment*)address;
    CUR_FREE_SEG->free = FREE;
    CUR_FREE_SEG->next = 0;
    CUR_FREE_SEG->prev = 0;
    CUR_FREE_SEG->nextFree = 0;
    CUR_FREE_SEG->prevFree = 0;
    CUR_FREE_SEG->size = size - sizeof(MemorySegment); //space we want - size of this structure
}

void* HEAP_Malloc(uint64_t n)
{
    //   n += n % 8;

    if(CUR_FREE_SEG->size >= n){
        /*
        * |     |           |                          |
        * | CFS |     N     | NEWSEG and rest of space |
        * |     |           |                          |
        */
        MemorySegment* newSegment = (MemorySegment*)((uint64_t)CUR_FREE_SEG + sizeof(MemorySegment) + n);
        newSegment->size = CUR_FREE_SEG->size - (n + sizeof(CUR_FREE_SEG));

        CUR_FREE_SEG->next = newSegment;
        CUR_FREE_SEG->nextFree = newSegment;
        CUR_FREE_SEG->size = n;
        CUR_FREE_SEG->free = NOT_FREE;

        newSegment->prev = CUR_FREE_SEG;
        newSegment->prevFree = CUR_FREE_SEG->prevFree;
        newSegment->next = CUR_FREE_SEG->next;
        newSegment->nextFree = CUR_FREE_SEG->nextFree;
        newSegment->free = FREE;

        CUR_FREE_SEG = newSegment;

        return (void*)newSegment->prev;
    }
    else{
        //there is no more free space
        return 0;
    }
}