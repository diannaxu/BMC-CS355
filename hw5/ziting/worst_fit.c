#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <unistd.h>

#define HEADER_SIZE 32
#define BYTE 8

clock_t begin, end;

static void print_execution_time(clock_t begin, clock_t end) {
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Execution time: %.2f seconds\n", time_spent);
}

int main() {
  int result = Mem_Init(getpagesize());
  assert(result == 0);

  void *ptr, *ptr2, *ptr3, *ptr4, *ptr5;

  printf("--start allocating (assumed the header size is %d bytes).\n", HEADER_SIZE);
  ptr = Mem_Alloc(getpagesize()/2-HEADER_SIZE);
  assert(ptr != NULL);
  assert(((long) ptr) % 8 == 0);
  Mem_Dump();

  ptr2 = Mem_Alloc(getpagesize()/4-HEADER_SIZE);
  assert(ptr2 != NULL);
  assert(((long) ptr2) % 8 == 0);
  Mem_Dump();

  ptr3 = Mem_Alloc(getpagesize()/4-HEADER_SIZE);
  assert(ptr3 != NULL);
  assert(((long) ptr3) % 8 == 0);
  Mem_Dump();

  printf("--start freeing.\n");
  result = Mem_Free(ptr, 0);
  assert(result == 0);
  Mem_Dump();

  result = Mem_Free(ptr2, 0);
  assert(result == 0);
  Mem_Dump();

  result = Mem_Free(ptr3, 0);
  assert(result == 0);
  Mem_Dump();

  printf("--start allocating (assumed the header size is %d bytes).\n", HEADER_SIZE);
  ptr = Mem_Alloc(600);
  assert(ptr != NULL);
  assert(((long) ptr) % 8 == 0);
  Mem_Dump();

  ptr2 = Mem_Alloc(600);
  assert(ptr2 != NULL);
  assert(((long) ptr2) % 8 == 0);
  Mem_Dump();

  ptr3 = Mem_Alloc(600);
  assert(ptr3 != NULL);
  assert(((long) ptr3) % 8 == 0);
  Mem_Dump();

  ptr4 = Mem_Alloc(600);
  assert(ptr4 != NULL);
  assert(((long) ptr4) % 8 == 0);
  Mem_Dump();

  ptr5 = Mem_Alloc(600);
  assert(ptr5 != NULL);
  assert(((long) ptr5) % 8 == 0);
  Mem_Dump();

  printf("--start freeing.\n");
  result = Mem_Free(ptr, 0);
  assert(result == 0);
  Mem_Dump();

  result = Mem_Free(ptr2, 0);
  assert(result == 0);
  Mem_Dump();

  result = Mem_Free(ptr3, 0);
  assert(result == 0);
  Mem_Dump();

  result = Mem_Free(ptr4, 0);
  assert(result == 0);
  Mem_Dump();

  result = Mem_Free(ptr5, 0);
  assert(result == 0);
  Mem_Dump();

  end = clock();
  print_execution_time(begin, end);

  return EXIT_SUCCESS;
}