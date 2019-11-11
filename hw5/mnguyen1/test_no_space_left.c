// Author: My Nguyen

#include "mem.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

#define INIT_SIZE 4096

int main() {
  printf("Test for allocating until out of space\n");
  int result = Mem_Init(INIT_SIZE);
  assert(result == 0);
  while(1) {
    void* ptr = Mem_Alloc(sizeof(long)*2);
    if (ptr == NULL) {
      assert(m_error == E_NO_SPACE);
      printf("Yay, out of space!\n");
      return EXIT_SUCCESS;
    }
  }
  return EXIT_FAILURE;
}
