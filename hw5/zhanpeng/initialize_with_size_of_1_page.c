#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FAIL -1
#define MINIMUM_BLOCK_SIZE 8
#define MAXIMUM_HEADER_SIZE 32

long rounding(long val, long base)
{
  return ((val - 1) / base) * base + base;
}

void initialize_with_size_of_1_page()
{
    printf("Test: Initialize with Size of 1 page\n");
    int pagesize = getpagesize();
    if (Mem_Init(pagesize) == FAIL)
        exit(EXIT_FAILURE);
    printf("----Mem_Init(4192)----\n");
    long desired_memory_size = rounding(pagesize, MINIMUM_BLOCK_SIZE)/ MINIMUM_BLOCK_SIZE * MAXIMUM_HEADER_SIZE + pagesize;
    printf("The page size is %ld.\n", pagesize);
    printf("The desired memory size is %d.\n", desired_memory_size);
    Mem_Dump();
    printf("You should see that the size of the free block is a little off compared with the desired memory size. \n");
    exit(EXIT_SUCCESS);
}

void main(void)
{
    initialize_with_size_of_1_page();
    exit(EXIT_SUCCESS);
}