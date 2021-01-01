#ifndef MEMORY_H
#define MEMORY_H

#include "heap.h"

#include <stdint.h>

void* MM_Mmove(void* src, void* dst, uint64_t size);

#endif //MEMORY_H