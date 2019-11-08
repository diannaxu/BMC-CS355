#include "../mem.h"
#include <stdlib.h>

#define MEM_SIZE 4096


/*

This tests whether worst fit is actually used, but this just has a hole somewhere (a pointer that doesn't get freed)

*/

int main(){
  Mem_Init(MEM_SIZE);

  void * ptr1 = Mem_Alloc(3000);
  void * ptr2 = Mem_Alloc(50);

  Mem_Free(ptr1, 0);

  void * ptr3 = Mem_Alloc(2000);

  Mem_Free(ptr3,0);

  Mem_Dump();
  
  void * ptr4 = Mem_Alloc(1000);
  Mem_Dump();
  
  exit(EXIT_SUCCESS);
}
