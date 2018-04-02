#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_ALLOC 8192
#define FAIL -1

void several_odd_sized_allocations()
{
    printf("Test: Several Odd Sized Allocations\n");
    printf("----Mem_Init(8192)----\n");
    if (Mem_Init(NUM_ALLOC) == FAIL)
        exit(EXIT_FAILURE);
    Mem_Dump();
    printf("----Mem_Alloc(9)----\n");
    void *ptr0 = Mem_Alloc(9);
    if (ptr0 == NULL)
        exit(EXIT_FAILURE);
    Mem_Dump();
    printf("The pointer 0's address is %p.\n", ptr0);

    printf("----Mem_Alloc(1)----\n");
    void *ptr1 = Mem_Alloc(1);
    if (ptr1 == NULL)
        exit(EXIT_FAILURE);
    Mem_Dump();
    printf("The pointer 1's address is %p.\n", ptr1); // should be 8's multiple

    printf("----Mem_Alloc(1243)----\n");
    void *ptr2 = Mem_Alloc(1243);
    if (ptr2 == NULL)
        exit(EXIT_FAILURE);
    Mem_Dump();
    printf("The pointer 2's address is %p.\n", ptr2);

    printf("----Mem_Alloc(777)----\n");
    void *ptr3 = Mem_Alloc(777);
    if (ptr3 == NULL)
        exit(EXIT_FAILURE);
    Mem_Dump();
    printf("The pointer 3's address is %p.\n", ptr3);
    exit(EXIT_SUCCESS);
}

void main(void)
{
    several_odd_sized_allocations();
    exit(EXIT_SUCCESS);
}
