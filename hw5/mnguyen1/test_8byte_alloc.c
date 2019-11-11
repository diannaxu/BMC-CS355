// Author: My Nguyen

#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

#define INIT_SIZE 100
#define ALLOCS 6

int main() {
  printf("Test for 8-byte allocation\n");
  int result = Mem_Init(INIT_SIZE);
  assert(result == 0);
  for (int i = 0; i < ALLOCS; i++) {
    long* ptr = (long*)Mem_Alloc(sizeof(long));
    if (ptr == NULL) {
      printf("Failed to allocate memory for long\n");
      return EXIT_FAILURE;
    }
  }
  printf("If success, %d blocks will be allocated with size 8\n", ALLOCS);
  Mem_Dump();
  return EXIT_SUCCESS;
}
