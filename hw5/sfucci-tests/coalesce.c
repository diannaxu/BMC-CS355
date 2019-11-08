#include "../mem.h"
#include <stdlib.h>
#include <stdio.h>
#define MEM_SIZE 60


/*

This tests whether coalescing is done properly.
If coalescing is correct, then the 60-byte allocation
should succeed.

Therefore the 60-byte allocation will not work
if the freed 20/40 chunks are not properly coalesced
*/

int main(){
  if(Mem_Init(MEM_SIZE) == -1){
    exit(EXIT_FAILURE);
  }

  void * ptr1 = Mem_Alloc(40);
  void * ptr2 = Mem_Alloc(20);

  Mem_Free(ptr1, 0);
  Mem_Free(ptr2, 1);

  if(Mem_Alloc(60) == NULL){
    printf("Test failed\n");
    exit(EXIT_FAILURE);
  }

  printf("Success\n");
  exit(EXIT_SUCCESS);
}
