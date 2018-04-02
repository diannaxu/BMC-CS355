#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FAIL -1
#define NUM_ALLOC 8192
#define NOCOALESCE 0

void try_freeing_a_NULL_pointer()
{
    printf("Testing: Try to free a NULL pointer\n");
    printf("----Mem_Init(8192)----\n");
    if (Mem_Init(NUM_ALLOC) == FAIL)
        exit(EXIT_FAILURE);
    printf("Trying to free a NULL Pointer. Nothing should happen.\n");
    Mem_Free(NULL,NOCOALESCE);
    printf("Test success!\n");
    exit(EXIT_SUCCESS);
}

void main(void)
{
    try_freeing_a_NULL_pointer();
    exit(EXIT_SUCCESS);
}