// ALLOCATION_TEST.C
//Tests that some rounded and non-rounded allocations are positioned where we expect them, by requesting blocks of various sizes and printing the
//returned addresses, then doing a memory dump. 
//Expected behavior: The main function itself has more detail on the exact memory allocations and what they should be rounded to, but essentially, 
//we should see allocations that are multiples of 8, separated by 32-byte headers, and still together at the beginning of available memory (as in
//the previous test, we have made few enough requests that they're all just placed in order).

#include <stdlib.h> 
#include <stdio.h> 
#include <assert.h> 
#include "mem.h"

extern int m_error; 

int main(){

  assert(Mem_Init(4096) == 0);

  // Request 8 bytes of allocation (not rounded)
  void* allocation1 = Mem_Alloc(8);
  assert(allocation1);
  printf("Address of allocation 1: %p\n", allocation1);  

  // Request 64 bytes of allocation (not rounded)
  void* allocation2 = Mem_Alloc(64);
  assert(allocation2);
  printf("Address of allocation 2: %p\n", allocation2); 

  // Request odd-sized 10 bytes of allocation (will be rounded to 16)
  void* allocation3 = Mem_Alloc(10);
  assert(allocation3);
  printf("Address of allocation 3: %p\n", allocation3); 

  // Request odd-sized 1 byte of allocation (will be rounded to 8)
  void* allocation4 = Mem_Alloc(1);
  assert(allocation4);
  printf("Address of allocation 4: %p\n", allocation4); 

  // Request 104 bytes of allocation (not rounded)
  void* allocation5 = Mem_Alloc(104);
  assert(allocation5);
  printf("Address of allocation 5: %p\n", allocation4); 
  Mem_Dump();

  exit(EXIT_SUCCESS);
}
