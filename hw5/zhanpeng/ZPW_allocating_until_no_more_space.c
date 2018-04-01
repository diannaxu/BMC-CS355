#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_ALLOC 8192
#define FAIL -1
#define TRUE 1

void allocating_until_no_more_space_left()
{
    printf("Test: Allocating until no more memory space left\n");
    printf("It should run out of space.\n");
    printf("If it gets stuck in a infinite loop, memory allocation library has some problem.\n");
    printf("----Mem_Init(8192)----\n");
    if (Mem_Init(NUM_ALLOC) == FAIL)
        exit(EXIT_FAILURE);
    Mem_Dump();
    void *ptr;
    while (TRUE)
    {
        printf("----Mem_Alloc(8)----\n");
        ptr = Mem_Alloc(8);
        if (ptr == NULL)
        {
            printf("Oops! Run out of space!\n");
            if (m_error = E_NO_SPACE)
                printf("Error: Not enough space for allocation.\n");
            
            exit(EXIT_SUCCESS);
        }
    }
    exit(EXIT_FAILURE);
}

void main(void)
{
    allocating_until_no_more_space_left();
    exit(EXIT_SUCCESS);
}