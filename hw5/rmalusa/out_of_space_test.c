//out_of_space_test.c
//We use the 100-byte request setup from the earlier tests, which allows us to almost fill the available memory. If we then free enough of the allocated
//blocks to give us a remaining quota larger than the size of the largest hole, without coalescing, we can provoke an E_NO_SPACE. 
//Expected behavior: The assertions succeed, because the final allocation fails with E_NO_SPACE. 

#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h> 
#include "mem.h"

int main(){
  assert(Mem_Init(100) == 0);
  void* ptrs[100];
  for(int i=0; i<100; i++){
    ptrs[i] = Mem_Alloc(1);
    assert(ptrs[i]); 
  }

  for(int i=0; i<75; i++){
    assert(Mem_Free(ptrs[i], 0) == 0);
  }

  Mem_Dump(); 

  void* last_ptr = Mem_Alloc(72);
  assert(!last_ptr);
  assert(m_error = E_NO_SPACE);

  exit(EXIT_SUCCESS);

}