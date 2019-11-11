/*
Test for 100 8-byte aligned allocations and frees
use assert to make sure adjacent pointer address difference is constant (8byte+header_size)
Expected behavior: should print 100 free blocks, exit normally
*/

#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdint.h>
#include <assert.h>

#define TRUE 1
#define FALSE 0
#define SUCCESS 0
#define FAIL -1
#define EIGHT_BYTES 8
#define NUM_ALLOCS 100
#define ALLOC_SIZE 8
enum {NO_COALESCE, COALESCE_ALL, PARTIAL_COALESCE};

int main() {
  int requested = Mem_Init(1600);
  assert(requested == SUCCESS);

  void **ptrs = malloc(sizeof(void *)*NUM_ALLOCS);

  for (int i = 0; i < NUM_ALLOCS; i++) {
    assert((ptrs[i] = Mem_Alloc(ALLOC_SIZE)) != NULL);
    printf("%dth ptr address: %p\n", i, ptrs[i]);
  }

  long constant_diff = ptrs[1] - ptrs[0];

  for (int i = 0; i < NUM_ALLOCS-1; i++) {
    assert((ptrs[i+1] - ptrs[i]) == constant_diff);
    printf("Distance between %dth and %dth pointer is constant: %d!\n", i, i+1, constant_diff);
  }

  for (int i = 0; i < NUM_ALLOCS; i++) {
    assert(Mem_Free(ptrs[i], NO_COALESCE) == SUCCESS);
    printf("%dth ptr freed successfully\n", i, ptrs[i]);
  }
  Mem_Dump();

  free(ptrs);
  exit(EXIT_SUCCESS);
}
