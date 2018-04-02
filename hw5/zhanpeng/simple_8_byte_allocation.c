#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_ALLOC 8192
#define FAIL -1

void simple_8_byte_allocation()
{
  printf("Test: Simple 8-byte Allocation\n");
  printf("----Mem_Init(8192)----\n");
  if (Mem_Init(NUM_ALLOC) == FAIL)
    exit(EXIT_FAILURE);
  Mem_Dump();
  printf("----Mem_Alloc(8)----\n");
  void *ptr = Mem_Alloc(8);
  if (ptr == NULL)
    exit(EXIT_FAILURE);
  Mem_Dump();
  printf("The pointer's address is %p.\n", ptr);
  exit(EXIT_SUCCESS);
}

void main(void)
{
  simple_8_byte_allocation();
  exit(EXIT_SUCCESS);
}