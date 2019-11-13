/*
Test for worst fit
total size 4000, alloced 1000, 2000, 1000,
freed without coalesce
new alloc of 500 should go into 2000 hole
Expected behavior: exit normally
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
#define NUM_ALLOC 8192

enum {NO_COALESCE, COALESCE_ALL, PARTIAL_COALESCE};

int main() {
  int requested = Mem_Init(4000);
  assert(requested == SUCCESS);

  printf("Request for 1000 bytes.\n");
  void *ptr1 = Mem_Alloc(1000);
  assert(ptr1 != NULL);
  printf("ptr1 address: %p\n", ptr1);
  assert((long long)ptr1%EIGHT_BYTES == SUCCESS);
  Mem_Dump();

  printf("Request for 2000 bytes.\n");
  void *ptr2 = Mem_Alloc(2000);
  assert(ptr2 != NULL);
  printf("ptr2 address: %p\n", ptr2);
  assert((long long)ptr2%EIGHT_BYTES == SUCCESS);
  Mem_Dump();

  printf("Request for 1000 bytes.\n");
  void *ptr3 = Mem_Alloc(1000);
  assert(ptr3 != NULL);
  printf("ptr3 address: %p\n", ptr3);
  assert((long long)ptr3%EIGHT_BYTES == SUCCESS);
  Mem_Dump();

  // assert(Mem_Alloc(1)==NULL);

  assert(Mem_Free(ptr1, NO_COALESCE) == SUCCESS);
  assert(Mem_Free(ptr2, NO_COALESCE) == SUCCESS);
  assert(Mem_Free(ptr3, NO_COALESCE) == SUCCESS);
  printf("After freeing allocated 1000 bytes, 2000 bytes, and 1000 bytes without coalescing:\n");
  Mem_Dump();

  printf("Request for 500 bytes.\n");
  void *ptr4 = Mem_Alloc(500);
  assert(ptr4 != NULL);
  printf("ptr4 address: %p\n", ptr4);
  assert((long long)ptr4%EIGHT_BYTES == 0);
  printf("ptr4 should go into second hole, according to worst fit: \n");
  Mem_Dump();

  exit(EXIT_SUCCESS);
}
