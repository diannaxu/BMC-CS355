#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <unistd.h>

#define NUM_ALLOC 20
#define ADD_FREQ 5
#define BYTE 29

clock_t begin, end;

static void print_execution_time(clock_t begin, clock_t end) {
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Execution time: %.2f seconds\n", time_spent);
}

void test() {
  int size = 100;
  int result = Mem_Init(NUM_ALLOC * 40);
  assert(result == 0);
  void **ptrs = malloc(sizeof(void*) * 6);

  // void* m1 = malloc(sizeof(void*) * 100);
  // void* m2 = malloc(sizeof(void*) * 300);
  // void* m3 = malloc(sizeof(void*) * 500);
  // void* m4 = malloc(sizeof(void*) * 700);
  // void* m5 = malloc(sizeof(void*) * 900);
  // void* m6 = malloc(sizeof(void*) * 1100);

  for (int i = 0; i < 6; i++) {
    // printf("%d\n",i);
    ptrs[i] = Mem_Alloc(size);
    size = size + 200;
    assert(ptrs[i] != NULL);
  }

  int i = Mem_Free(ptrs[4], 0);
  assert(i == EXIT_SUCCESS);
  i = Mem_Free(ptrs[3], 0);
  assert(i == EXIT_SUCCESS);
  void* m1 = Mem_Alloc(size);
  printf("%s\n", "m1 should point to NULL");
  assert(m1 == NULL);
  i = Mem_Free(ptrs[0], 1);
  assert(i == EXIT_SUCCESS);
  i = Mem_Free(ptrs[1],1);
  assert(i == EXIT_SUCCESS);
  void* m = Mem_Alloc(size);
  printf("%s\n", "m should point to a valid memory");
  assert(m != NULL);

  end = clock();
  print_execution_time(begin, end);
}

int main(){
  test();
  return EXIT_SUCCESS;
}
