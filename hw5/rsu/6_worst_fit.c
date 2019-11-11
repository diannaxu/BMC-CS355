/*
Test for worst fit
total size 100, alloced 20, 30, 50,
freed without coalesce
new alloc of 10 should go into 50
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

enum {NO_COALESCE, COALESCE_ALL, PARTIAL_COALESCE};

int main() {
  int requested = Mem_Init(100);
  assert(requested == SUCCESS);

  printf("Request for 20 bytes.\n");
  void *ptr1 = Mem_Alloc(20);
  assert(ptr1 != NULL);
  printf("ptr1 address: %p\n", ptr1);
  assert((long long)ptr1%EIGHT_BYTES == SUCCESS);
  Mem_Dump();

  printf("Request for 30 bytes.\n");
  void *ptr2 = Mem_Alloc(30);
  assert(ptr2 != NULL);
  printf("ptr2 address: %p\n", ptr2);
  assert((long long)ptr2%EIGHT_BYTES == SUCCESS);
  Mem_Dump();

  printf("Request for 50 bytes.\n");
  void *ptr3 = Mem_Alloc(50);
  assert(ptr3 != NULL);
  printf("ptr3 address: %p\n", ptr3);
  assert((long long)ptr3%EIGHT_BYTES == SUCCESS);
  Mem_Dump();

  // assert(Mem_Alloc(1)==NULL);

  assert(Mem_Free(ptr1, NO_COALESCE) == SUCCESS);
  assert(Mem_Free(ptr2, NO_COALESCE) == SUCCESS);
  assert(Mem_Free(ptr3, NO_COALESCE) == SUCCESS);
  printf("After freeing allocated 20 bytes, 30 bytes, and 50 bytes without coalescing:\n");
  Mem_Dump();

  printf("Request for 10 bytes.\n");
  void *ptr4 = Mem_Alloc(10);
  assert(ptr4 != NULL);
  printf("ptr4 address: %p\n", ptr4);
  assert((long long)ptr4%EIGHT_BYTES == 0);
  printf("ptr4(10) fits 20, 30, 50. It should go into 50: \n");
  Mem_Dump();

  exit(EXIT_SUCCESS);
}
