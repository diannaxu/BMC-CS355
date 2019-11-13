/*
Test for initializing 1 page
actual allocated will be greater than 1 page, but should be multiples of a page
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
  long pagesize = getpagesize();
  int requested = Mem_Init(pagesize);
  assert(requested == SUCCESS);
  printf("Requested for 1 page,actual allocated will be greater than 1 page, but should be multiples of a page\n");
  Mem_Dump();

  exit(EXIT_SUCCESS);
}
