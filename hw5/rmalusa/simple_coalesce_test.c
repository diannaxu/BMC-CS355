// SIMPLE_COALESCE_TEST.C
//We check that coalescing works as expected by doing the same 100-byte-request setup as above, freeing various blocks without coalescing, then calling
//Mem_Free on a NULL pointer with coalesce = 1. Afterwards, it does a memory dump so the results can be examined. 
//Expected behavior: The specifics of what should happen are described in the main function for the test. Essentially, we want the holes that can merge
//to merge, and to make sure the hole list is still in order afterwards. 

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "mem.h"

int main(){

  // Requesting 100 bytes will cause the program to allocate exactly one page - (8+32) * 100 = 4000
  Mem_Init(100);
  
  void* ptrs[100];
  for(int i=0; i<100; i++){
    ptrs[i] = Mem_Alloc(1);
    assert(ptrs[i]); 
  }

  // We should have 100 32-byte headers, each followed by an 8-byte allocated region,
  // and a 32-byte header + 64-byte hole in the last 96 bytes 

  // We free some of these allocations, trying to create as many distinct cases for coalesce as we can: 
  // - Coalesce at the head of the list
  // - Coalesce at the tail of the hole list
  // - Coalesce at the tail of the both-types list 
  // - Blocks standing alone which will not be coalesced 
  // - 2 blocks being coalesced
  // - More than two blocks being coalesced 
  Mem_Free(ptrs[0], 0); // These two blocks should coalesce together 
  Mem_Free(ptrs[1], 0);
  Mem_Free(ptrs[5], 0); // These four blocks should coalesce together 
  Mem_Free(ptrs[6], 0);
  Mem_Free(ptrs[7], 0);
  Mem_Free(ptrs[8], 0);
  Mem_Free(ptrs[15], 0); // These two blocks stand alone
  Mem_Free(ptrs[17], 0);
  Mem_Free(ptrs[99], 0); // These two blocks merge with the final 64-byte hole 
  Mem_Free(ptrs[98], 0);

  //Then we coalesce by calling free on a null ptr with the coalesce flag, 
  //creating an 88-byte hole with a 32-byte header
  Mem_Free(NULL, 1); 

  Mem_Dump(); 
  exit(EXIT_SUCCESS);
}