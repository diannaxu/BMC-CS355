// Test 9: aligned allocation and free
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

    void *ptr1 = Mem_Alloc(16);
    void *ptr2 = Mem_Alloc(32);
    void *ptr3 = Mem_Alloc(64);

    printf("Pointer 1 address: %p\n", ptr1);
    printf("Pointer 2 address: %p\n", ptr2);
    printf("Pointer 3 address: %p\n", ptr3);

    Mem_Dump();

    if(Mem_Free(ptr1, 0) == FAIL){
        printf("Can't free ptr1\n");
        exit(EXIT_FAILURE);
    }

    Mem_Dump();

    if(Mem_Free(ptr2, 0) == FAIL){
        printf("Can't free ptr2\n");
        exit(EXIT_FAILURE);
    }

    Mem_Dump();

    if(Mem_Free(ptr3, 0) == FAIL){
        printf("Can't free ptr3\n");
        exit(EXIT_FAILURE);
    }

    Mem_Dump();

    return 0;
}
