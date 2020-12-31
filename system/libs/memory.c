#include "../common.h"
#include "memory.h"
#include "heap.h"

#include <stdint.h>

void* MM_Mmove(void* src, void* dst, size_t size)
{
    if(src == dst)
        return dst;

    uint8_t* srcptr = (uint8_t*)src;
    uint8_t* dstptr = (uint8_t*)dst;

    if( dst < src ){
        for(size_t i = 0; i < size; i++){
            dstptr[i] = srcptr[i];
        }
    }
    else{
        size_t p = size - 1;
        while(p!=0){
            dstptr[p] = srcptr[p];
            p--;
        }
    }
    return dst;
}

void* MM_Malloc(size_t n)
{
    MemorySegment* current = &FIRST_SEG;
    uint64_t offset = current->address;
    while(1){
        if(current->free == USED){
            
            MemorySegment new;
            HEAP_Init(&new);
                
            offset+=current->size;
            new.address = offset;
            
            HEAP_InsertAfter(current, &new);
            
            current = current->next;
            continue;
        
        }
        else{
            current->size = n;
            current->free = USED;
            break;
        }

    }

    return (void*)current->address;
}