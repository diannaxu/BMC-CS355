// made some changes to the one provided by dianna

/*
 * Author: Kyu
 * 
 * This 2 million malloc test with coalescing should be finished within seconds.
 */

#include "../mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <unistd.h>

#define NUM_ALLOC 2000000
#define FREE_FREQ 100          // 1:100
#define COALESCE_FREQ 100000 // 1:100000
#define BYTE 8

clock_t begin, end;

static void print_execution_time(clock_t begin, clock_t end) {
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Execution time: %.2f seconds\n", time_spent);
}

void test_two_mil() {
  begin = clock();
  int result = Mem_Init(NUM_ALLOC * 40);
  assert(result == 0);

  void **ptrs = malloc(sizeof(void*) * NUM_ALLOC);

  for (int i = 0; i < NUM_ALLOC; i++) {
    ptrs[i] = Mem_Alloc(BYTE);
    assert(ptrs[i] != NULL);

    if (i != 0 && i % FREE_FREQ == 0){
      Mem_Free(ptrs[i-FREE_FREQ+1], i % COALESCE_FREQ == 0);
      // free(ptrs[i-FREE_FREQ+1]);
    }
  }
  end = clock();
  printf("mem: ");
  print_execution_time(begin, end);
  free(ptrs);
}


void test_two_mil_malloc() {
  begin = clock();
  void **ptrs = malloc(sizeof(void*) * NUM_ALLOC);

  for (int i = 0; i < NUM_ALLOC; i++) {
    ptrs[i] = malloc(BYTE);
    assert(ptrs[i] != NULL);

    if (i != 0 && i % FREE_FREQ == 0){
      free(ptrs[i-FREE_FREQ+1]);
    }
  }
  end = clock();
  printf("Malloc: ");
  print_execution_time(begin, end);
  free(ptrs);
}

int main() {
  test_two_mil();
  test_two_mil_malloc();
  Mem_Dump();

  return EXIT_SUCCESS;
}