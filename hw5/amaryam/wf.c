/* Test #6
 * file: wf.c
 * Purpose: make sure allocation occurs according to worst fit
 * Expected: Mem_Dump will show that worst fit allocation is used (always goes
 * to the biggest block even when there's a better fit available)
 *
 */

#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
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

  printf("\nNotice how when the two pointers are freed, the small allocation goes to the biggest block.\n");
  printf("\n\t\t\tMade it through all allocs\n\n");
  exit(EXIT_SUCCESS);

}
