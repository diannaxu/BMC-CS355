#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <unistd.h>
#define NUM_ALLOC -1
#define ERROR -1

int test_mem_init() {
    int result = Mem_Init(NUM_ALLOC);
    if (result == ERROR) {
      return EXIT_SUCCESS;
    } else {
      return EXIT_FAILURE;
    }
}

int main() {
  //printf("%d\n", test_mem_init(NUM_ALLOC));
  exit(test_mem_init());
}
