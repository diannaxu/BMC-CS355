#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

void foo1(void *arg) {
  printf("I am the first thread!\n", arg);
}

void foo2(void *arg) {
  printf("I am the second thread!\n", arg);
}

void foo3(void *arg) {
  printf("I am the third thread!\n", arg);
}

int main(void) {
  if (thread_libinit(FIFO) == -1) exit(EXIT_FAILURE);
  printf(" * A simple test for FIFO scheduling\n");
  printf(" * Threads should in this order: 1 -> 2 -> 3\n");

  int tid_1 = thread_create(foo1, NULL, 0);
  int tid_2 = thread_create(foo2, NULL, 0);
  int tid_3 = thread_create(foo3, NULL, 0);
  int tids[] = { tid1, tid2, tid3 };

  for (int i = 0; i < 3; i++)  {
    if (tids[i] == -1)
      exit(EXIT_FAILURE);
  }

  for (int i = 0; i < 3; i++)  {
    if (thread_join(tids[i]) == -1)
      exit(EXIT_FAILURE);
  }

  if (thread_libterminate() == -1)
    exit(EXIT_FAILURE);

  if (thread_libterminate() == -1) exit(EXIT_FAILURE);

  exit(EXIT_SUCCESS);
}