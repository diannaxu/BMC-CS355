// LOCAL_COALESCE_TEST.C
//This test checks that local coalescence works as expected and leaves a sane hole list. It has the same setup as the other two coalescence tests, 
//setting up a single page of memory that is almost totally filled with a hundred pairs of 32-byte headers and 8-byte headers. Then, it frees all of
//those 8-byte allocations with the no-coalescence flag, except for a few select ones: one near the head, two near each other in the middle, one far from others in the middle, and one near the tail. Each of those allocations is then freed with the local coalesce flag on. 
//Expected behavior: Each allocation will coalesce with the neighborhood of holes around it. The two close coalesces will merge together. The hole list will be sane, with a correct head and tail and structure, afterwards. By looking at the sizes of holes that form at each step, we can also see 
//that the local coalescing stops when it encounters an allocated block (i.e. only merges adjacent holes) (this can be seen with the two initially un-
//freed blocks that are close together.)

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "mem.h"

#define SUCCESS 0

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

  // We free all of those pointers, leaving a field of holes 
  for(int i=0; i<100; i++){
    if(i != 0 && i != 20 && i != 24 && i != 98){
      assert(Mem_Free(ptrs[i], 0) == SUCCESS);  
    }
  }

  Mem_Dump(); 
 
  Mem_Free(ptrs[0], 2);
  Mem_Free(ptrs[20], 2);
  Mem_Free(ptrs[24], 2);
  Mem_Free(ptrs[98], 2);

  Mem_Dump(); 

  exit(EXIT_SUCCESS);
}