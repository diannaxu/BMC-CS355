// Test 6: check worst fit allocation
// Author: Cecilia Zhang

#include <stdio.h>
#include <stdlib.h>
#include "mem.h"

#define FAIL -1

int main() {
    if (Mem_Init(4096) == FAIL) {
        printf("Can't init\n");
        exit(EXIT_FAILURE);
    }
    
    // do some worst fit allocations
    void *ptr1 = Mem_Alloc(100);
    void *ptr2 = Mem_Alloc(300);
    
    printf("Pointer 1 address: %p\n", ptr1);
    printf("Pointer 2 address: %p\n", ptr2);

    // free ptr1 but no coalesce
    if(Mem_Free(ptr1, 0) == FAIL){
        printf("Can't free ptr1\n");
        exit(EXIT_FAILURE);
    }

    void *ptr3 = Mem_Alloc(500);
    printf("Pointer 3 address: %p\n", ptr3);
    
    if(Mem_Free(ptr2, 0) == FAIL){
        printf("Can't free ptr2\n");
        exit(EXIT_FAILURE);
    }

    if(Mem_Free(ptr3, 0) == FAIL){
        printf("Can't free ptr3\n");
        exit(EXIT_FAILURE);
    }

    Mem_Dump();
    
    return 0;
}
