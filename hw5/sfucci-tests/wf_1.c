#include "../mem.h"
#include <stdlib.h>


#define MEM_SIZE 4096


/*

This tests whether worst fit is actually used is done properly
This creates two holes of free memory, ptr2's allocation should
show that it took the bigger hole.

*/

int main(){
  Mem_Init(MEM_SIZE);

  void * ptr1 = Mem_Alloc(3000);

  Mem_Free(ptr1, 0);

  Mem_Dump();

  void * ptr2 = Mem_Alloc(50);

  Mem_Dump();
  exit(EXIT_SUCCESS);
}
