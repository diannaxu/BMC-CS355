/*
 * File: alignment.c
 * Purpose: Testing for 8-byte alignment test using Mem_Dump and mod on pointer address.
 * Expected Output: Mem_Dump output should show 8-byte alignment, and pointer modular
 * arithmetic should yield 0 for 8-byte alignment
 */
#include "mem.h"
#include <stdlib.h>
#include <stdio.h>
#define FAILURE -1
#define BLOCK 5

int main() {
  printf("Testing for 8-byte alignment\n");
  if(Mem_Init(BLOCK)==FAILURE) return EXIT_FAILURE;
  Mem_Dump();

  void *ptr;
  if((ptr = Mem_Alloc(BLOCK)) == NULL) return EXIT_FAILURE;
  printf("\nPrinting pointer information...\n");
  printf("Pointer address: %p\n", ptr);
  long result = ((long)ptr%8);
  printf("Pointer mod 8 should yield zero: %lu\n", result);
  if(result!=0) {
    printf("Test failed\n");
  }
  else {
    printf("Test passed\n");
  }
  Mem_Dump();

  if(Mem_Free(ptr, 0) == FAILURE) return EXIT_FAILURE;
  Mem_Dump();

  return EXIT_SUCCESS;
}
