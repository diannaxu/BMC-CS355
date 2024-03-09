// Author: Paprika Chen
// Test if there is a avg running time, new created threads's estimated times are based on it
// Right behavior: threads executed in order

#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

#define FAIL -1

#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

#define THREAD_NUMBER 10
#define FAIL -1

void order_test(void *arg) {
  int i = *(int *)arg;
  printf("Thread %d is executing\n", i);
}

int main() {
  if (thread_libinit(FIFO) == FAIL)
    exit(EXIT_FAILURE);

  int tids[THREAD_NUMBER];
  
  // run three jobs first to accumulate a avg time
  for (int i = 0; i < 3; i++)
  {
    tids[i] = thread_create(order_test, i, 0);
  }

  for (int i = 0; i < 3; i ++)
  {
    if (thread_join(tids[i]) == FAIL)
      exit(EXIT_FAILURE);
  }

  // new created threads should based on avg time, still in FIFO
  for (int i = 3; i < THREAD_NUMBER; i++)
  {
    tids[i] = thread_create(order_test, i, 0);
  }

  for (int i = 3; i < THREAD_NUMBER; i ++)
  {
    if (thread_join(tids[i]) == FAIL)
      exit(EXIT_FAILURE);
  }

  if (thread_libterminate() == FAIL)
    exit(EXIT_FAILURE);

  exit(EXIT_SUCCESS);
}