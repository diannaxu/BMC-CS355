/*
Test for freeing null pointers
Expected behavior:
Mem_Free(NULL, NO_COALESCE) should have no affect on free list.
Mem_Free(NULL, COALESCE_ALL) should merge holes whereever possible.
exit normally
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

  printf("Request for 30 bytes.\n");
  void *ptr2 = Mem_Alloc(30);
  assert(ptr2 != NULL);
  printf("ptr2 address: %p\n", ptr2);
  assert((long long)ptr2%EIGHT_BYTES == SUCCESS);

  printf("Request for 50 bytes.\n");
  void *ptr3 = Mem_Alloc(50);
  assert(ptr3 != NULL);
  printf("ptr3 address: %p\n", ptr3);
  assert((long long)ptr3%EIGHT_BYTES == SUCCESS);

  assert(Mem_Free(ptr1, NO_COALESCE) == SUCCESS);
  assert(Mem_Free(ptr2, NO_COALESCE) == SUCCESS);
  assert(Mem_Free(ptr3, NO_COALESCE) == SUCCESS);
  printf("After freeing allocated 20 bytes, 30 bytes, and 50 bytes without coalescing:\n");
  Mem_Dump();

  printf("Mem_Free(NULL, NO_COALESCE) should have no affect on free list.\nBefore:\n");
  Mem_Dump();
  assert(Mem_Free(NULL, NO_COALESCE) == SUCCESS);
  printf("After:\n");
  Mem_Dump();
  
  printf("Mem_Free(NULL, COALESCE_ALL) should merge all holes.\n");
  assert(Mem_Free(NULL, COALESCE_ALL) == SUCCESS);
  printf("After coalescing all list:\n");
  Mem_Dump();

  exit(EXIT_SUCCESS);
}
