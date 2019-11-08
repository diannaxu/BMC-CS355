// RUNNING_COALESCE_TEST.C
//This test is identical to simple_coalesce_test, except that the whole list is coalesced after each block is freed (i.e. each block is freed with
//coalesce flag 1.) It should have the same effect. It is designed to test that repeatedly calling coalesce does not mess up the hole list or behave 
//unexpectedly. 

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
  Mem_Free(ptrs[0], 1); // These two blocks should coalesce together 
  Mem_Free(ptrs[1], 1);
  Mem_Free(ptrs[5], 1); // These four blocks should coalesce together 
  Mem_Free(ptrs[6], 1);
  Mem_Free(ptrs[7], 1);
  Mem_Free(ptrs[8], 1);
  Mem_Free(ptrs[15], 1); // These two blocks stand alone
  Mem_Free(ptrs[17], 1);
  Mem_Free(ptrs[99], 1); // These two blocks merge with the final 64-byte hole 
  Mem_Free(ptrs[98], 1);

  Mem_Dump(); 
  exit(EXIT_SUCCESS);
}