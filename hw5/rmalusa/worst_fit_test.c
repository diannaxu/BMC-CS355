//worst_fit_test.c
//We check that new allocations are placed in the largest available hole. To do this, we request 100 bytes of memory, which will cause 4096 bytes
//to be mapped. By then making a hundred 1-byte requests, we fill the first 4000 bytes with headers and allocated blocks, leaving 96 bytes (32-byte 
//header and 64-byte hole) at the end. We then free three contiguous blocks in the middle and coalesce, merging them into an 88-byte hole. Finally,
//we make one more 1-byte request. This allocated block should be placed in the new, larger hole, not in the leftover hole at the end. 
//Expected behavior: When we dump the memory, there will still be an unchanged 64-byte hole at the end of available memory. 48 bytes of the earlier hole
//will remain. 

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

  // We free three pointers without coalescing, creating three
  // 40-byte holes (really 8-byte holes with 32-byte headers but u know) 
  Mem_Free(ptrs[5], 0);
  Mem_Free(ptrs[6], 0);
  Mem_Free(ptrs[7], 0); 

  //Then we coalesce by calling free on a null ptr with the coalesce flag, 
  //creating an 88-byte hole with a 32-byte header
  Mem_Free(NULL, 1); 

  // The next allocation we make should go in the first, larger hole
  void* final_ptr = Mem_Alloc(1);

  Mem_Dump(); 
  exit(EXIT_SUCCESS);
}
