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
  // Free several blocks that are NEAR but not ADJACENT to a central block without coalescing, then free that with local coalescing
  Mem_Free(ptrs[60], 0);
  Mem_Free(ptrs[61], 0);
  Mem_Free(ptrs[67], 0);
  Mem_Free(ptrs[68], 0);
  Mem_Free(ptrs[73], 0);
  Mem_Free(ptrs[74], 0); 
  Mem_Free(ptrs[65], 2);
  Mem_Dump();
}
