// Author: My Nguyen

#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

#define INIT_SIZE 4096
#define ALLOCS 12

int main() {
  printf("Test for different options of coalescion\n");
  int result = Mem_Init(INIT_SIZE);
  assert(result == 0);
  void* ptrs[ALLOCS];
  for (int i = 0; i < ALLOCS; i++) {
    void* ptr = Mem_Alloc(sizeof(long));
    assert(ptr != NULL);
    ptrs[i] = ptr;
  }
  for (int i = 0; i < ALLOCS; i = i + 3) {
    assert(Mem_Free(ptrs[i], 0) == 0);
  }
  printf("You should see each free block followed by 2 allocated blocks except the last block\n");
  Mem_Dump();
  for (int i = 1; i < ALLOCS; i = i + 3) {
    assert(Mem_Free(ptrs[i], 1) == 0);
  }
  printf("You should see each free block followed by an allocated block of half its size\n");
  Mem_Dump();
  for (int i = 2; i < ALLOCS; i = i + 3) {
    if (i == 2) {
      assert(Mem_Free(ptrs[i], 2) == 0);
    } else {
      assert(Mem_Free(ptrs[i], 0) == 0);
    }
  }
  printf("You should see a big free block at the beginning of size 32, then smaller uncombined free blocks\n");
  Mem_Dump();
  return 0;
}
  
