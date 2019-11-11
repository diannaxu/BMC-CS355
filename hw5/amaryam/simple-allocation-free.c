/*
 * test #8
 * File: simple-allocation-free.c
 * Purpose: testing simple allocation and free
 * Expected Result: one contiguous block at end of test and block allocated should be freed
 */

#include "mem.h"
#include <stdlib.h>
#include <stdio.h>

#define BLOCK 16
#define FAILURE -1

int main() {
    if(Mem_Init(BLOCK) == FAILURE) return EXIT_FAILURE;
    Mem_Dump();

    void *ptr;
    if((ptr= Mem_Alloc(BLOCK)) == NULL) return EXIT_FAILURE;
    printf("Allocated.\n");
    Mem_Dump();

    if(Mem_Free(ptr, 0) == FAILURE) return EXIT_FAILURE;
    printf("freed lock\n");
    Mem_Dump();

    return EXIT_SUCCESS;
}
