// simple_alloc_free.c

#include <stdio.h>
#include <stdlib.h>
#include "mem.h"

int main() {
    if (Mem_Init(4096) != 0) {
        printf("Mem_Init failed\n");
        exit(EXIT_FAILURE);
    }

    void *ptr1 = Mem_Alloc(200);
    void *ptr2 = Mem_Alloc(300);
    void *ptr3 = Mem_Alloc(150);

    if (ptr1 == NULL || ptr2 == NULL || ptr3 == NULL) {
        printf("Mem_Alloc failed\n");
        exit(EXIT_FAILURE);
    }

    printf("Mem_Alloc success\n");
    printf("Pointer 1 address: %p\n", ptr1);
    printf("Pointer 2 address: %p\n", ptr2);
    printf("Pointer 3 address: %p\n", ptr3);

    // Free memory blocks
    if (Mem_Free(ptr1, 0) != 0 || Mem_Free(ptr2, 0) != 0 || Mem_Free(ptr3, 0) != 0) {
        printf("Mem_Free failed\n");
        exit(EXIT_FAILURE);
    }

    printf("After deallocation:\n");
    Mem_Dump();

    return 0;
}
