//Author: Rachel(Ruochun) Wang
#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

void foo1(void *arg) {
  printf("First!\n");
}

void foo2(void *arg) {
  printf("Second!\n");
}

void foo3(void *arg) {
  printf("Third!\n");
}

int main(void) {
  if (thread_libinit(FIFO) == -1) exit(EXIT_FAILURE);
  printf(" Threads should be printed in order\n");

  int tid1 = thread_create(foo1, NULL, 0);
  int tid2 = thread_create(foo2, NULL, 0);
  int tid3 = thread_create(foo3, NULL, 0);
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

  exit(EXIT_SUCCESS);
}
