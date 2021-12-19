#include "heap.h"
#include "../terminal/terminal.h"
#include "../terminal/terminal_B8000_8025.h"

#include <stdint.h>

MemorySegment* CUR_FREE_SEG;

//init node
void HEAP_Init(uint64_t address, uint64_t size)
{
    CUR_FREE_SEG = (MemorySegment*)address;
    CUR_FREE_SEG->free = FREE;
    CUR_FREE_SEG->next = 0;
    CUR_FREE_SEG->prev = 0;
    CUR_FREE_SEG->nextFree = 0;
    CUR_FREE_SEG->prevFree = 0;
    if(size <= sizeof(MemorySegment)){
        CUR_FREE_SEG->size = sizeof(MemorySegment) + 10; //always create heap with min 10 byte space
    }
    else{
        CUR_FREE_SEG->size = size - sizeof(MemorySegment); //space we want - size of this structure
    }
}

void* HEAP_Malloc(uint64_t n)
{
    uint64_t remainder = n % 8;
	n -= remainder;
	if (remainder != 0) n += 8;

    MemorySegment* CURRENT = CUR_FREE_SEG;

    if(CURRENT->size > n){
        //if there is space to new segment
        if(CURRENT->size >= sizeof(MemorySegment) + n){
            /*
            * |     |           |                          |
            * | CFS |     N     | NEWSEG and rest of space |
            * |     |           |                          |
            */
            MemorySegment* newSegment = (MemorySegment*)((uint64_t)CURRENT + sizeof(MemorySegment) + n);

            //new segment size is equal current size - sizeof allocated memory
            newSegment->size = CUR_FREE_SEG->size - n;

            CURRENT->next = newSegment;
            CURRENT->nextFree = newSegment;
            CURRENT->size = n;
            CURRENT->free = NOT_FREE;

            newSegment->prev = CURRENT;
            newSegment->prevFree = CURRENT->prevFree;
            newSegment->next = CURRENT->next;
            newSegment->nextFree = CURRENT->nextFree;
            newSegment->free = FREE;
        }
        
        CURRENT = CURRENT->nextFree;
        CUR_FREE_SEG = CURRENT;

        return (void*)CURRENT->prev;
    }
    else{
        //there is no more free space
        return 0;
    }
}

void HEAP_Concat(MemorySegment* a, MemorySegment* b)
{
    if (a == 0 || b == 0)
        return;

    if(a < b){
        a->size += b->size + sizeof(MemorySegment);
        a->next = b->next;
        a->nextFree = b->nextFree;
        b->next->prev = a;
        b->next->prevFree = a;
        b->nextFree->prevFree = a;
    }
    else{
        b->size += a->size + sizeof(MemorySegment);
        b->next = a->next;
        b->nextFree = a->nextFree;
        a->next->prev = b;
        a->next->prevFree = b;
        a->nextFree->prevFree = b;
    }
}

void HEAP_Free(void* ptr)
{
    MemorySegment* CURRENT = ((MemorySegment*)ptr);

    CURRENT->free = FREE;

    if(CURRENT < CUR_FREE_SEG){
        CUR_FREE_SEG = CURRENT;
    }

    if(CURRENT->nextFree != 0){
        if(CURRENT->nextFree->prevFree < CURRENT){
            CURRENT->nextFree->prevFree = CURRENT;
        }
    }

    if(CURRENT->prevFree != 0){
        if(CURRENT->prevFree->nextFree > CURRENT){
            CURRENT->prevFree->nextFree = CURRENT;
        }
    }

    if(CURRENT->next != 0){
        CURRENT->next->prev = CURRENT;
        if(CURRENT->next->free)
            HEAP_Concat(CURRENT, CURRENT->next);
    }

    if(CURRENT->prev != 0){
        CURRENT->prev->next = CURRENT;
        if(CURRENT->prev->free)
            HEAP_Concat(CURRENT, CURRENT->prev);
    }
}