#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "userthread.h"

void inner_foo(void *arg) {
  thread_yield();
}


void foo(void *arg) {
  int tid;
  for (int i = 0; i < 5; ++i)
  {
    int tid = thread_create(inner_foo, NULL, 1);

    if (tid < 0) 
      exit(EXIT_FAILURE);

    if (thread_join(tid) < 0) 
      exit(EXIT_FAILURE);
  }

}

/**
 * Nested FIFO test
 */
int main(void) {
  if (thread_libinit(FIFO) == -1)
    exit(EXIT_FAILURE);

  char *arg = "Yay!";

  int tid1 = thread_create(foo, arg, 1);

  printf("More complicated FIFO test, with threads creating other threads.\n");
  printf("Assuming that the first thread is tid 1, it should finish in order\n");
  printf("2 -> 3 -> 4 -> 5 -> 6 -> 1\n");

  if (thread_join(tid1) < 0) 
    exit(EXIT_FAILURE);

  if (thread_libterminate() == -1)
    exit(EXIT_FAILURE);


  exit(EXIT_SUCCESS);
}
