// SIMPLE_ALLOCATION_TEST.C
//Tests that simple 8-byte allocations are positioned where we expect them, by requesting some 8-byte blocks and printing the returned addresses.  
//Expected behavior: The addresses should be separated by 40/0x28 bytes, 32 for the header and 8 for the allocation. 

#include <stdlib.h> 
#include <assert.h>
#include <stdio.h> 
#include "mem.h"

int main(){
  assert(Mem_Init(4096)==0);
  void* ptr1 = Mem_Alloc(8);
  assert(ptr1);
  printf("pointer should be 8-byte aligned: %p\n", ptr1);

  void* ptr2 = Mem_Alloc(8);
  assert(ptr2);
  printf("pointer should be 8-byte aligned and 0x28 after the first: %p\n", ptr2);

  void* ptr3 = Mem_Alloc(8);
  assert(ptr3);
  printf("pointer should be 8-byte aligned and 0x28 after the last: %p\n", ptr3);

  void* ptr4 = Mem_Alloc(8);
  assert(ptr4);
  printf("pointer should be 8-byte aligned and 0x28 after the last: %p\n", ptr4);

  Mem_Dump(); 

  exit(EXIT_SUCCESS); 
}
