#include "../mem.h"
#include <stdlib.h>
#include <stdio.h>

#define MEM_SIZE 4096


/*

This tests the worst case with memory allocation,
in which the user requests MEMSIZE 1-byte blocks.
All of these requests should be granted.
*/

int main(){
  if(Mem_Init(MEM_SIZE) == -1){
    exit(EXIT_FAILURE);
  }

  void * ptr;

  for(int i = 0; i < MEM_SIZE; i++){
    if((ptr = Mem_Alloc(1)) == NULL){
      printf("Requesting byte #%d failed (0-indexed).\n", i);
      exit(EXIT_FAILURE);
    }
  }
  
  exit(EXIT_SUCCESS);
}
