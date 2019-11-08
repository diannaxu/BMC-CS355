// EDGE_CASE_FREE_TEST.C
// We try to create unusual cases for freeing and re-adding a block to the hole list: when it is the first hole (before the current head of the hole //list), and when it is the last hole (after the current tail of the hole list). To do this, we use the same 100-allocation setup that we have 
//previously 
// Expected behavior: The hole list reacts as expected and is sane (TODO: write up better description)

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

  // Free first 64 pointers 
  for(int i=0; i<64; i++){
  	assert(Mem_Free(ptrs[i], 0) == 0);
  }

  // We should have 100 32-byte headers, each followed by an 8-byte allocated region,
  // and a 32-byte header + 64-byte hole in the last 96 bytes 
  void* last_ptr = Mem_Alloc(64);

  Mem_Dump(); 

  // Free the pointer before last_ptr, which should now be the new tail of the hole list 
  assert(Mem_Free(ptrs[99], 0) == 0);

  Mem_Dump(); 

  assert(Mem_Free(last_ptr, 0) == 0);

  Mem_Dump(); 

  exit(EXIT_SUCCESS); 

}