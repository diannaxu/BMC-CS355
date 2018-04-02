#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_ALLOC 8192
#define FAIL -1

void simple_allocation_and_free()
{
    printf("Test: Simple Allocation and Free\n");
    printf("----Mem_Init(8192)----\n");
    if (Mem_Init(NUM_ALLOC) == FAIL)
        exit(EXIT_FAILURE);
    Mem_Dump();
    printf("----Mem_Alloc(32)----\n");
    void *ptr = Mem_Alloc(32);
    if (ptr == NULL)
        exit(EXIT_FAILURE);
    Mem_Dump();
    printf("The pointer's address is %p.\n", ptr);
    printf("----Mem_Free(ptr, 1)----\n");
    if (Mem_Free(ptr, 1) == FAIL)
    {
        exit(EXIT_FAILURE);
    }
    Mem_Dump();
    exit(EXIT_SUCCESS);
}

void main(void)
{
    simple_allocation_and_free();
    exit(EXIT_SUCCESS);
}