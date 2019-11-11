/*
 * File: allocation.c
 * Purpose: Make sure allocations of various sizes are 8-byte aligned
 * Expected Result: Mem_Dump output should still be 8-byte aligned, and pointer modular
 * arithmetic should still yield 0 for 8-byte alignment
 */

#include "mem.h"
#include <stdlib.h>
#include <stdio.h>
#define FAILURE -1
#define SUCCESS 0
#define BLOCK 8

int main() {
  printf("Blocks should be multiples of 8\n");
  if(Mem_Init(BLOCK)==FAILURE) {
    printf("init failure\n");
    return EXIT_FAILURE;
  }
  Mem_Dump();

  void *ptr;
  if((ptr = Mem_Alloc(BLOCK)) == NULL) return EXIT_FAILURE;
  Mem_Dump();

  printf("\nPrinting pointer information...\n");
  printf("Pointer address: %p\n", ptr);
  long result = ((long)ptr%8);
  printf("Pointer mod 8 should yield zero: %lu\n", result);

  if(Mem_Free(ptr, 0) == FAILURE) return EXIT_FAILURE;
  Mem_Dump();
  return SUCCESS;
}
