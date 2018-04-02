#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_ALLOC 8192
#define FAIL -1

void a_few_aligned_allocations()
{
    printf("Testing: A Few Aligned Allocations\n");
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

    printf("----Mem_Alloc(64)----\n");
    void *ptr1 = Mem_Alloc(64);
    if (ptr1 == NULL)
        exit(EXIT_FAILURE);
    Mem_Dump();
    printf("The pointer 1's address is %p.\n", ptr1);

    printf("----Mem_Alloc(512)----\n");
    void *ptr2 = Mem_Alloc(512);
    if (ptr2 == NULL)
        exit(EXIT_FAILURE);
    Mem_Dump();
    printf("The pointer 2's address is %p.\n", ptr2);

    printf("----Mem_Alloc(4096)----\n");
    void *ptr3 = Mem_Alloc(4096);
    if (ptr3 == NULL)
        exit(EXIT_FAILURE);
    Mem_Dump();
    printf("The pointer 3's address is %p.\n", ptr3);

    /*printf("----Mem_Free(ptr, 1)----\n");
    if (Mem_Free(ptr0, 1) == FAIL)
    {
        exit(EXIT_FAILURE);
    }
    if (Mem_Free(ptr1, 1) == FAIL)
    {
        exit(EXIT_FAILURE);
    }
    if (Mem_Free(ptr2, 1) == FAIL)
    {
        exit(EXIT_FAILURE);
    }
    if (Mem_Free(ptr3, 1) == FAIL)
    {
        exit(EXIT_FAILURE);
    }
    Mem_Dump();*/
    exit(EXIT_SUCCESS);
}

void main(void)
{
    a_few_aligned_allocations();
    exit(EXIT_SUCCESS);
}