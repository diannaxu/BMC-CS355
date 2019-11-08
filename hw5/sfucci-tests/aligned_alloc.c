#include "../mem.h"
#include <stdlib.h>


#define MEM_SIZE 4096


/*

This tests whether an odd byte is 8-byte aligned.

*/

int main(){
  Mem_Init(MEM_SIZE);

  void * ptr1 = Mem_Alloc(45);

  Mem_Dump(); //should have a multiple of 8 block

  Mem_Free(ptr1, 1);
  
  Mem_Dump(); //contiguous empty block
  exit(EXIT_SUCCESS);
}
