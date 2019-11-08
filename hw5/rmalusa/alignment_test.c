// ALIGNMENT_TEST.C
//Tests whether the addresses given to the user are 8-byte aligned, by requesting some blocks of memory that are divisible by 8 and some that are not,
//and printing out the returned addresses.
//Expected behavior: Every address printed ends in either 0 or 8. 

#include <stdlib.h> 
#include <assert.h>
#include <stdio.h> 
#include "mem.h"

extern int m_error; 

int main(){
  assert(Mem_Init(4096)==0);
  void* ptr1 = Mem_Alloc(8);
  assert(ptr1);
  printf("pointer should be 8-byte aligned: %p\n", ptr1);

  void* ptr2 = Mem_Alloc(56);
  assert(ptr2);
  printf("pointer should be 8-byte aligned: %p\n", ptr2);

  void* ptr3 = Mem_Alloc(3);
  assert(ptr3);
  printf("pointer should be 8-byte aligned: %p\n", ptr3);

  void* ptr4 = Mem_Alloc(8);
  assert(ptr4);
  printf("pointer should be 8-byte aligned: %p\n", ptr4);

  exit(EXIT_SUCCESS); 
}
