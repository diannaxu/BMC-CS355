/* test #7
 * file: coalesce.c
 * Purpose: make sure memory coalesces
 * Expected: Mem_Dump will show that there is a single block of memory after
 * all the frees
 *
 */

#include "mem.h"
#include <stdlib.h>
#include <stdio.h>
#define BLOCK 4096
#define FAILURE -1

int main() {
  Mem_Init(BLOCK);
  void * ptr, *ptr1, *ptr2;
  if((ptr = Mem_Alloc(500)) == NULL) return EXIT_FAILURE;
  Mem_Dump();

  if(Mem_Free(ptr, 0) == FAILURE) return EXIT_FAILURE;
  Mem_Dump();

  if((ptr1 = Mem_Alloc(200)) == NULL) return EXIT_FAILURE;
  Mem_Dump();

  if(Mem_Free(ptr1, 0) == FAILURE) return EXIT_FAILURE;
  Mem_Dump();

  if((ptr2 = Mem_Alloc(10)) == NULL) return EXIT_FAILURE;
  Mem_Dump();

  if(Mem_Free(ptr2, 0) == FAILURE) return EXIT_FAILURE;
  Mem_Dump();

  printf("\n\nIf there is a single block of contiguous memory at the end of the printing, coalescing was successful\n\n");


  exit(EXIT_SUCCESS);

}
