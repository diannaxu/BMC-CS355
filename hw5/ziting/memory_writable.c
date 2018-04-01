#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <unistd.h>

#define BYTE 8

clock_t begin, end;

static void print_execution_time(clock_t begin, clock_t end) {
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Execution time: %.2f seconds\n", time_spent);
}

int main() {
  int result = Mem_Init(NUM_ALLOC * 40);
  assert(result == 0);

  int *ptr;

  printf("--start allocating.\n");
  ptr = (int *) Mem_Alloc(sizeof(int)*3);
  assert(ptr != NULL);
  assert(((long) ptr) % 8 == 0);

  Mem_Dump();

  *ptr = 1;
  *(ptr+1) = 2;
  *(ptr+2) = 3;

  for (int i = 0; i < 3; i++) {
    printf("memory at location %p writable: %d\n", ptr+i, *(ptr+i));
  }

  printf("--start freeing.\n");
  result = Mem_Free(ptr, 0);
  assert(result == 0);

  Mem_Dump();

  end = clock();
  print_execution_time(begin, end);

  return EXIT_SUCCESS;
}