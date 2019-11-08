//FREE_POINTER_TWICE_TEST.C
//Checks that freeing a pointer twice produces an error. 
//Expected behavior: The assertions succeed, because freeing the pointer for the first time is allowed, and freeing it for the second time is not. 

#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h> 
#include "mem.h"

int main(){
  assert(Mem_Init(100) == 0);

  void* ptr = Mem_Alloc(50);
  assert(ptr);
  assert(Mem_Free(ptr, 0) == 0);
  assert(Mem_Free(ptr, 0) == -1);
  Mem_Dump(); 

  exit(EXIT_SUCCESS);
}
