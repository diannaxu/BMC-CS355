#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

#define FAILURE -1

void foo(void *) {}

void foo_yield(void *) {
  thread_yield();
}

void foo_join(void *tid) {
  thread_join(*((int *)tid));
}

int main(void) {
  if (thread_libinit(FIFO) == FAILURE)
    exit(EXIT_FAILURE);

  int tid1 = thread_create(foo_yield, NULL, 0);
  int tid2 = thread_create(foo_join, &tid1, 0);
  int tid3 = thread_create(foo_join, &tid2, 0);
  int tid4 = thread_create(foo_join, &tid3, 0);
  int tid5 = thread_create(foo_join, &tid4, 0);
  int tid6 = thread_create(foo_join, &tid5, 0);

  int n  = 6;
  int tids[] = { tid1, tid2, tid3, tid4, tid5, tid6 };

  printf(" * Testing a chain of joins for FIFO\n");
  printf(" * Threads should in this order: %d -> %d -> %d -> %d -> %d -> %d\n",
         tid1, tid2 ,tid3, tid4, tid5, tid6);

  for (int i = 0; i < n; i++)  {
    if (tids[i] == -1)
      exit(EXIT_FAILURE);
  }

  if (thread_join(tid6) == -1)
    exit(EXIT_FAILURE);

  if (thread_libterminate() == FAILURE)
    exit(EXIT_FAILURE);

  exit(EXIT_SUCCESS);
}
