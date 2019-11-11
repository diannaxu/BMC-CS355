/*
 * Test #3 from hw5
 * File: few-aligned-allocations.c
 * Purpose: Allocate a few blocks and show they are still aligned
 * Expected Result: Mem_Dump output should be 8-byte aligned, pointer arithmetic
 * should show alignment, mod 8 on ptr should yield zero
 */

#include "mem.h"
#include <stdlib.h>
#include <stdio.h>

#define FAILURE -1
#define BLOCK 8

void ptrPrint(void * ptr) {
  printf("\nPrinting pointer information...\n");
  printf("Pointer address: %p\n", ptr);
  long result = ((long)ptr%8);
  printf("Pointer mod 8 should yield zero: %lu\n", result);
}

int main() {
  if(Mem_Init(15*BLOCK) == FAILURE) return EXIT_FAILURE;
  Mem_Dump();

  void *ptr, *ptr2, *ptr3;

  if((ptr = Mem_Alloc(3*BLOCK)) == NULL) return EXIT_FAILURE;
  ptrPrint(ptr);
  Mem_Dump();

  if((ptr2 = Mem_Alloc(BLOCK))== NULL) return EXIT_FAILURE;
  ptrPrint(ptr2);
  Mem_Dump();

  if((ptr3 = Mem_Alloc(8*BLOCK)) == NULL) return EXIT_FAILURE;
  ptrPrint(ptr3);
  Mem_Dump();

  if(Mem_Free(ptr, 0) == FAILURE) return EXIT_FAILURE;
  Mem_Dump();

  if(Mem_Free(ptr2, 0) == FAILURE) return EXIT_FAILURE;
  Mem_Dump();

  if(Mem_Free(ptr3, 0) == FAILURE) return EXIT_FAILURE;
  Mem_Dump();

  return EXIT_SUCCESS;
}
