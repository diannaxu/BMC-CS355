// SIMPLE_FREE_TEST.C
// Tests that freeing regular-sized and odd-sized blocks of memory works as expected, and leaves a sane hole list. 
// Expected behavior: the memory dump has correctly placed holes and allocated blocks for this series of steps (not very specific, I know, but
// the sequence of steps is not very complicated or structured)

#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h> 
#include "mem.h"

int main(){

  // Request one page of memory
  printf("%d\n", Mem_Init(4096));
  Mem_Dump(); 

  // Request 8 bytes of allocation
  void* allocation1 = Mem_Alloc(8);
  assert(allocation1);

  // Request 64 bytes of allocation
  void* allocation2 = Mem_Alloc(64);
  assert(allocation2);

  // Request odd-sized 10 bytes of allocation (will be rounded to 16)
  void* allocation3 = Mem_Alloc(10);
  assert(allocation3);

  // Request odd-sized 1 byte of allocation (will be rounded to 8)
  void* allocation4 = Mem_Alloc(1);
  assert(allocation4);

  Mem_Free(allocation2, 0);
  Mem_Free(allocation4, 0);
  Mem_Dump();

  exit(EXIT_SUCCESS);

}
