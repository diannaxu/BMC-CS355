// Test 7: check coalesce of free space
// Author: Cecilia

#include <stdio.h>
#include <stdlib.h>
#include "mem.h"

#define FAIL -1

int main() {
    if (Mem_Init(4096) == FAIL){
        printf("Can't init\n");
        exit(EXIT_FAILURE);
    }

    void *ptr1 = Mem_Alloc(16);
    void *ptr2 = Mem_Alloc(32);

    Mem_Dump();

    if(Mem_Free(ptr1, 1) == FAIL){
        printf("Can't free ptr1\n");
        exit(EXIT_FAILURE);
    }

    Mem_Dump();

    if(Mem_Free(ptr2, 1) == FAIL){
        printf("Can't free ptr2\n");
        exit(EXIT_FAILURE);
    }

    Mem_Dump();

    return 0;
}

