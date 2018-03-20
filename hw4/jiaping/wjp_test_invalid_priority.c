#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

void foo(void *arg) {
  printf("Hello world!\n");
}

/**
 * Simple FIFO test
 */
int main(void) {
  if (thread_libinit(FIFO) == -1)
    exit(EXIT_FAILURE);


  int tid1 = thread_create(foo, NULL, 1);
  int tid2 = thread_create(foo, NULL, 100);
  int tid3 = thread_create(foo, NULL, -100);

  printf("Tesing invalid policy number\n");
  printf("Should print exactly one 'Hello world' on success\n");

  if (thread_join(tid1) < 0) 
    exit(EXIT_FAILURE);

  if (thread_join(tid2) < 0) 
    exit(EXIT_FAILURE);
  
  if (thread_join(tid3) < 0) 
    exit(EXIT_FAILURE);

  if (thread_libterminate() == -1)
    exit(EXIT_FAILURE);

  exit(EXIT_SUCCESS);
}
