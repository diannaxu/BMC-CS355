#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <unistd.h>

#define HEADER_SIZE 24
#define BYTE 8

clock_t begin, end;

static void print_execution_time(clock_t begin, clock_t end) {
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Execution time: %.2f seconds\n", time_spent);
}

int main() {
  int result = Mem_Init(getpagesize());
  assert(result == 0);

  void *ptr, *ptr2;

  printf("--start allocating (assumed the header size is %d bytes).\n", HEADER_SIZE);
  ptr = Mem_Alloc(getpagesize()/2-HEADER_SIZE);
  assert(ptr != NULL);
  assert(((long) ptr) % 8 == 0);
  Mem_Dump();

  ptr2 = Mem_Alloc(getpagesize()/2-HEADER_SIZE);
  assert(ptr2 != NULL);
  assert(((long) ptr2) % 8 == 0);
  Mem_Dump();

  printf("--start freeing.\n");
  result = Mem_Free(ptr, 0);
  assert(result == 0);
  Mem_Dump();

  result = Mem_Free(ptr2, 0);
  assert(result == 0);
  Mem_Dump();

  end = clock();
  print_execution_time(begin, end);

  return EXIT_SUCCESS;
}