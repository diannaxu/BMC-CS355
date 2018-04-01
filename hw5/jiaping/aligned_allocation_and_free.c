#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <unistd.h>

#define NUM_ALLOC 10
#define FREE_FREQ 100     // 1:100
#define BYTE 8

clock_t begin, end;

static void print_execution_time(clock_t begin, clock_t end) {
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Execution time: %.2f seconds\n", time_spent);
}

void test_8_byte() {
  int result = Mem_Init(8504);
  assert(result == 0);

  void **ptrs = malloc(sizeof(void*) * NUM_ALLOC);
  for (int i = 0; i < NUM_ALLOC; i++) {
    ptrs[i] = Mem_Alloc(BYTE << i);
    assert(ptrs[i] != NULL);
    Mem_Dump();
  }

  for (int i = 0; i < NUM_ALLOC; i++) {
    printf("---------------------%d byte free-------------------\n", BYTE<<i);
    Mem_Free(ptrs[i], 0);
    Mem_Dump();
  }

  printf("---------------------Coalesce all-------------------\n");
  Mem_Free(NULL, 1);
  Mem_Dump();

  end = clock();
  print_execution_time(begin, end);
  free(ptrs);
}


int main() {
  test_8_byte();
  return EXIT_SUCCESS;
}