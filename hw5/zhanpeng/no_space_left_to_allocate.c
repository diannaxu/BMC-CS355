#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FAIL -1
#define NUM_ALLOC 8192

void no_space_left_to_allocate()
{
    printf("Testing: No Space Left to Allocate\n");
    printf("----Mem_Init(8192)----\n");
    if (Mem_Init(NUM_ALLOC) == FAIL)
        exit(EXIT_FAILURE);
    Mem_Dump();
    printf("----Mem_Alloc(8193)----\n");
    void *ptr = Mem_Alloc(NUM_ALLOC + 2);
    if (ptr != NULL)
        exit(EXIT_FAILURE);
    if (m_error == E_NO_SPACE)
        printf("Error: Not enough space for allocation.\n");
    printf("Should exit successfully.\n");
    exit(EXIT_SUCCESS);
}

void main(void)
{
    no_space_left_to_allocate();
    exit(EXIT_SUCCESS);
}