#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_ALLOC 8192
#define FAIL -1

void aligned_allocation_and_free()
{
    printf("Testing: Aligned Allocation and Free\n");
    if (Mem_Init(NUM_ALLOC) == FAIL)
        exit(EXIT_FAILURE);
    printf("----Mem_Init(8192)----\n");
    Mem_Dump();
    printf("----Mem_Alloc(8)----\n");
    void *ptr0 = Mem_Alloc(8);
    if (ptr0 == NULL)
        exit(EXIT_FAILURE);
    Mem_Dump();
    printf("The pointer 0's address is %p.\n", ptr0);

    printf("----Mem_Alloc(32)----\n");
    void *ptr1 = Mem_Alloc(32);
    if (ptr1 == NULL)
        exit(EXIT_FAILURE);
    Mem_Dump();
    printf("The pointer 1's address is %p.\n", ptr1);

    printf("----Mem_Alloc(64)----\n");
    void *ptr2 = Mem_Alloc(64);
    if (ptr2 == NULL)
        exit(EXIT_FAILURE);
    Mem_Dump();
    printf("The pointer 2's address is %p.\n", ptr2);

    printf("----Mem_Alloc(512)----\n");
    void *ptr3 = Mem_Alloc(512);
    if (ptr3 == NULL)
        exit(EXIT_FAILURE);
    Mem_Dump();
    printf("The pointer 3's address is %p.\n", ptr3);

    printf("----Mem_Free(ptr0, 0)----\n");
    if (Mem_Free(ptr0, 0) == FAIL)
    {
        exit(EXIT_FAILURE);
    }
    Mem_Dump();
    printf("----Mem_Free(ptr1, 0)----\n");
    if (Mem_Free(ptr1, 0) == FAIL)
    {
        exit(EXIT_FAILURE);
    }
    Mem_Dump();
    printf("----Mem_Free(ptr2, 0)----\n");
    if (Mem_Free(ptr2, 0) == FAIL)
    {
        exit(EXIT_FAILURE);
    }
    Mem_Dump();
    printf("----Mem_Free(ptr3, 1)----\n");
    if (Mem_Free(ptr3, 1) == FAIL)
    {
        exit(EXIT_FAILURE);
    }
    Mem_Dump();
    exit(EXIT_SUCCESS);
}

void main(void)
{
    aligned_allocation_and_free();
    exit(EXIT_SUCCESS);
}
