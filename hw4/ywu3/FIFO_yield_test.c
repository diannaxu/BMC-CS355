#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

void test(void *arg) {
  printf("thread %d is running\n", *((int *)arg));
}

int main() {
  if (thread_libinit(FIFO) == -1) {
    fprintf(stderr, "Failed to initialize thread library\n");
    exit(EXIT_FAILURE);
  }

  // create three threads
  int t1 = thread_create(test, &(int){1}, 0);
  int t2 = thread_create(test, &(int){2}, 0);
  int t3 = thread_create(test, &(int){3}, 0);

  if (thread_yield() == -1) {
    fprintf(stderr, "error: ailed to yield CPU\n");
    exit(EXIT_FAILURE);
  }

  // join threads
  if (thread_join(t1) == -1 || thread_join(t2) == -1 || thread_join(t3) == -1) {
    fprintf(stderr, "error: failed to join threads\n");
    exit(EXIT_FAILURE);
  }

  if (thread_libterminate() == -1) {
    fprintf(stderr, "error: failed to terminate thread library\n");
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}
