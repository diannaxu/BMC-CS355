/*
Test for initializing a small amount: 100 bytes
actual allocated should be rounded up to one page
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
#define NUM_ALLOCS 100
#define ALLOC_SIZE 8

int main() {
  int requested = Mem_Init(100);
  assert(requested == SUCCESS);
  printf("Requested for less than 1 page, actual allocated should be rounded up to 1 page\n");
  Mem_Dump();

  exit(EXIT_SUCCESS);
}
