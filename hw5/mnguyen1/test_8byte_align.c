// Author: My Nguyen

#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

int main() {
  printf("Test for 8-byte alignment\n");
  int result = Mem_Init(sizeof(int));
  assert(result == 0);
  void* ptr = Mem_Alloc(sizeof(int));
  assert(ptr != NULL);
  if ((long)ptr % 8 != 0) {
    printf("Test failed for 8-byte alignment");
  } else {
    printf("Yay! Test passed\n");
  }
  return EXIT_SUCCESS;
}
  
  
