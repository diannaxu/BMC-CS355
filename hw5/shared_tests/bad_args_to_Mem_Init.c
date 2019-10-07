/*
 * Author: Jiaping Wang
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

void test_8_byte() {
  int result = Mem_Init(-1);
  assert(result == -1);

  result = Mem_Init(1024);
  assert(result == 0);

  result = Mem_Init(1024);
  assert(result == -1);

  assert(m_error == E_BAD_ARGS);

  end = clock();
  print_execution_time(begin, end);
  printf("You passed bad args to Mem_Init() test! Yay!\n");
  
}


int main() {
  test_8_byte();
  return EXIT_SUCCESS;
}