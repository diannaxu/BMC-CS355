/*
Test for simple allocation and free
alloc for size 20 and free it
use assert to make sure action is successful
Expected behavior:
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

  assert(Mem_Free(ptr1, NO_COALESCE) == SUCCESS);
  printf("Request is freed successfully\n");
  
  exit(EXIT_SUCCESS);
}
