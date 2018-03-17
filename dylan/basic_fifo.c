#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

void foo(void *arg) {
  printf("%s\n", arg);
}

/**
 * Simple FIFO test
 */
int main(void) {
  if (thread_libinit(FIFO) == -1)
    exit(EXIT_FAILURE);

  char *arg = "Yay!";

  int tid1 = thread_create(foo, arg, 1);

  printf("Basic FIFO test, testing only add and join.\n");
  printf("Should print 'Yay!' if successful\n");

  if (thread_join(tid1) < 0) 
    exit(EXIT_FAILURE);

  if (thread_libterminate() == -1)
    exit(EXIT_FAILURE);

  exit(EXIT_SUCCESS);
}
