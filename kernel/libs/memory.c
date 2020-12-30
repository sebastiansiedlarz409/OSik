#include "memory.h"

#include <stdint.h>

void* memmove(void* src, void* dst, size_t size)
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