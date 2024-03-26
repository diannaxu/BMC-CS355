// odd_alloc.c
// Expected result: address end with 0 or 8

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "mem.h"

int main() {
    if (Mem_Init(1024) == -1) {
        printf("Mem_Init() failed\n");
        exit(EXIT_FAILURE);
    }

    void *ptr1 = Mem_Alloc(1);
    void *ptr2 = Mem_Alloc(93);
    void *ptr3 = Mem_Alloc(777);

    if (ptr1 == NULL || ptr2 == NULL || ptr3 == NULL) {
        printf("Alloc failed\n");
        exit(EXIT_FAILURE);
    }

    printf("Pointer 1 address: %p\n", ptr1);
    printf("Pointer 2 address: %p\n", ptr2);
    printf("Pointer 3 address: %p\n", ptr3);

    return 0;
}
