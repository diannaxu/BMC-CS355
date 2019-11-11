 /*
  * test #11
  * File: one-page.c
  * Purpose: testing one page allocation, freeing
  * Expected Result: one contiguous block at end of test and block allocated should be freed, normal alignment, should
  * be able to allocate pagesize
  */
#include <unistd.h>
#include "mem.h"
#include <stdio.h>
#include <stdlib.h>

#define BLOCK getpagesize()
#define FAILURE -1

int main() {
  if(Mem_Init(BLOCK) == FAILURE) return EXIT_FAILURE;
   Mem_Dump();
   void *ptr;
  if((ptr= Mem_Alloc(BLOCK)) == NULL) {
    printf("Could not allocate page size\n");
    return EXIT_FAILURE;
  }
   printf("Allocated.\n");
  printf("\nPrinting pointer information...\n");
  printf("Pointer address: %p\n", ptr);
  long result = ((long)ptr%8);
  printf("Pointer mod 8 should yield zero: %lu\n", result);
  if(result!=0) {
    printf("Test failed because of alignment\n");
  }
  Mem_Dump();

  if(Mem_Free(ptr, 0) == FAILURE) {
    printf("Could not successfully free pagesize allocation\n");
    return EXIT_FAILURE;
  }

  printf("freed block\n");
  Mem_Dump();

  return EXIT_SUCCESS;
 }
