#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <unistd.h>

#define NUM_ALLOC 5
#define BYTE 8

clock_t begin, end;

static void print_execution_time(clock_t begin, clock_t end) {
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Execution time: %.2f seconds\n", time_spent);
}

int main() {
  int result = Mem_Init(NUM_ALLOC * 40);
  assert(result == 0);

  void **ptrs = malloc(sizeof(void*) * NUM_ALLOC);

  printf("--start allocating.\n");
  for (int i = 0; i < NUM_ALLOC; i++) {
    ptrs[i] = Mem_Alloc(BYTE);
    assert(ptrs[i] != NULL);
    assert(((long) ptrs[i]) % 8 == 0);

    Mem_Dump();
  }

  printf("--start freeing.\n");
  for (int i = 0; i < NUM_ALLOC; i++) {
    result = Mem_Free(ptrs[i], 0);
    assert(result == 0);

    Mem_Dump();
  }

  Mem_Free(0, 1);
  Mem_Dump();
  end = clock();
  print_execution_time(begin, end);
  free(ptrs);

  return EXIT_SUCCESS;
}