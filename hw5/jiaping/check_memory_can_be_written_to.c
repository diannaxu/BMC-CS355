#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>

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

  printf("--------------8 byte allocation-----------------\n");
  char* ptr0 = Mem_Alloc(8);
  if (ptr0 == NULL) {
    exit(EXIT_FAILURE);
  }
  Mem_Dump();
  printf("The pointer ptr0 is at address %p.\n", ptr0);

  strcpy(ptr0, "Hello!");

  printf("%s\n", ptr0);


  printf("--------------8 byte free-----------------\n");
  Mem_Free(ptr0, 0);
  Mem_Dump();


}


int main() {
  test_8_byte();
  return EXIT_SUCCESS;
}