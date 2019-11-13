/*
Test for odd sized allocation and free
Use assert to make sure round up for odd-size alloc is as expected,
also to make sure Mem_Free is successful
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
#define HEADER_SIZE 24
enum {NO_COALESCE, COALESCE_ALL, PARTIAL_COALESCE};

int main() {
  int requested = Mem_Init(800);
  assert(requested == SUCCESS);

  printf("Request for 1 bytes.\n");
  void *ptr1 = Mem_Alloc(1);
  assert(ptr1 != NULL);
  printf("ptr1 address: %p\n", ptr1);
  assert((long long)ptr1%EIGHT_BYTES == SUCCESS);

  printf("Request for 27 bytes.\n");
  void *ptr2 = Mem_Alloc(27);
  assert(ptr2 != NULL);
  printf("ptr2 address: %p\n", ptr2);
  assert((long long)ptr2%EIGHT_BYTES == SUCCESS);

  assert((long long)ptr2-(long long)ptr1-HEADER_SIZE == 8);
  printf("Success: Returned space for 1 byte request is 8.\n");

  assert(Mem_Free(ptr1, NO_COALESCE) == SUCCESS);
  assert(Mem_Free(ptr2, NO_COALESCE) == SUCCESS);
  printf("After freeing ptr1 and ptr2 without coalescing:\n");
  Mem_Dump();
  exit(EXIT_SUCCESS);
}
