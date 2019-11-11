/*
 * test #10
 * File: odd-aligned-alloc-free.c
 * Purpose: testing odd aligned byte allocation and free
 * Expected Result: one contiguous block at end of test and block allocated should be freed, normal alignment
 */

#include "mem.h"
#include <stdio.h>
#include <stdlib.h>

#define BLOCK 11
#define FAILURE -1

int main() {
    if(Mem_Init(BLOCK) == FAILURE) return EXIT_FAILURE;
    Mem_Dump();

    void *ptr;
    if((ptr= Mem_Alloc(BLOCK)) == NULL) return EXIT_FAILURE;
    printf("Allocated.\n");
    printf("\nPrinting pointer information...\n");
    printf("Pointer address: %p\n", ptr);
    long result = ((long)ptr%8);
    printf("Pointer mod 8 should yield zero: %lu\n", result);
    if(result!=0) {
      printf("Test failed\n");
    }
    else {
      printf("Test passed\n");
    }
    Mem_Dump();

    if(Mem_Free(ptr, 0) == FAILURE) return EXIT_FAILURE;
    printf("freed block\n");
    Mem_Dump();

    return EXIT_SUCCESS;
}
