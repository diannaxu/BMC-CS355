// Test 8: simple alloc and free
// Author: Cecilia Zhang

#include <stdio.h>
#include <stdlib.h>
#include "mem.h"

#define FAIL -1

int main() {
    if (Mem_Init(4096) == FAIL){
        printf("Can't init\n");
        exit(EXIT_FAILURE);
    }

    void *ptr = Mem_Alloc(2);

    printf("Pointer address: %p\n", ptr);

    Mem_Dump();

    if(Mem_Free(ptr, 0) == FAIL){
        printf("Can't free\n");
        exit(EXIT_FAILURE);
    }

    Mem_Dump();

    return 0;
}
