/*
 * File: misuse-multiple-init-calls.c
 * Purpose: Try to call init multiple times
 * Expected Result: print "init failed" for every time mem_init is called after
 * the first time ("init failed" prints 4 times)
 */

#include "mem.h"
#include <stdlib.h>
#include <stdio.h>
#define FAILURE -1
#define SUCCESS 0
int allocate(int BLOCK);

int main() {
  int blocks[5] = {8, 16, 15, 13, 1};
  int size = 5;
  for(int i = 0; i < size; i ++) {
    allocate(blocks[i]);
  }

  return EXIT_SUCCESS;
}
int allocate(int BLOCK) {
  if(Mem_Init(BLOCK)==FAILURE) {
    printf("init failure\n");
    return EXIT_FAILURE;
  }
  Mem_Dump();

  void *ptr;
  if((ptr = Mem_Alloc(BLOCK)) == NULL) return EXIT_FAILURE;
  Mem_Dump();

  /*printf("\nPrinting pointer information...\n");
  printf("Pointer address: %p\n", ptr);
  long result = ((long)ptr%8);
  printf("Pointer mod 8 should yield zero: %lu\n", result);*/

  if(Mem_Free(ptr, 0) == FAILURE) return EXIT_FAILURE;
  Mem_Dump();
  return SUCCESS;
}
