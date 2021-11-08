/*
 * Author: Haosong Huang
 */

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

void test_free_2() {
  int result = Mem_Init(1024);
  assert(result == 0);
  void* blocks[5];
  for(int i = 0; i < 5; i++){
      blocks[i] = Mem_Alloc(8);
      assert(blocks[i]!= NULL);
  }
  for(int i = 0; i < 4; i++){
      assert(Mem_Free(blocks[i], 0) == 0);
  }
  assert(Mem_Free(blocks[4],2) == 0);
  printf("In the following mem dump, we should observe that not all free chunks coalesce into a whole chunk\n");
  Mem_Dump();
  end = clock();
  print_execution_time(begin, end);  
}


int main() {
  test_free_2();
  return EXIT_SUCCESS;
}
