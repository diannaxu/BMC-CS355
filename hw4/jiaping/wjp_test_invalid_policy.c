#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

void foo(void *arg) {
}

/**
 * Simple FIFO test
 */
int main(void) {
  printf("Testing with wrong policy\n");
  if (thread_libinit(100) == -1)
    exit(EXIT_FAILURE);


  if (thread_libterminate() == -1)
    exit(EXIT_FAILURE);

  exit(EXIT_SUCCESS);
}
