#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_ALLOC 8192
#define FAIL -1

void check_for_8_bytes_alignment()
{
  printf("Testing: Check for 8-byte alignment\n");
  printf("----Mem_Init(8192)----\n");
  if (Mem_Init(NUM_ALLOC) == FAIL)
    exit(EXIT_FAILURE);
  Mem_Dump();
  printf("----Mem_Alloc(50)----\n");
  void *ptr = Mem_Alloc(50);
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
  check_for_8_bytes_alignment();
  exit(EXIT_SUCCESS);
}