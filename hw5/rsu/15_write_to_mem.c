/*
Test for writing to allocated memory
Expected behavior: print "Copied successfully!", exit normally
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
#include <string.h>

#define TRUE 1
#define FALSE 0
#define SUCCESS 0
#define FAIL -1
#define EIGHT_BYTES 8
#define NUM_ALLOCS 100
#define ALLOC_SIZE 8

enum {NO_COALESCE, COALESCE_ALL, PARTIAL_COALESCE};

int main() {
  int requested = Mem_Init(100);
  assert(requested == SUCCESS);

  void *ptr = Mem_Alloc(sizeof("Copied successfully!"));
  strcpy(ptr, "Copied successfully!");

  printf("%s\n", ptr);
  assert(Mem_Free(ptr, NO_COALESCE)== SUCCESS);

  exit(EXIT_SUCCESS);
}
