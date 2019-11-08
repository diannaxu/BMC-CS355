#include <stdio.h>
#include <assert.h>
#include "mem.h"

int main(){

  Mem_Init(100);
  
  void* ptrs[100];
  for(int i=0; i<100; i++){
    ptrs[i] = Mem_Alloc(1);
    assert(ptrs[i]); 
  }

  // Now memory is filled with 32-byte headers and 8-byte allocated blocks,
  // with a 96-byte hole at the end
  // We try freeing the last and coalescing (should coalesce)
  Mem_Free(ptrs[99], 1); 
  //Mem_Dump();

  // Free two adjacent blocks elsewhere without coalesceing,
  // then free a third discrete one with coalesce flag,
  // which should cause them to coalesce
  Mem_Free(ptrs[10], 0);
  Mem_Free(ptrs[11], 0);
  Mem_Free(ptrs[72], 1); 
  Mem_Dump();
}
