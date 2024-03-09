// Author: Paprika Chen
// Test if before any join happens, all jobs should be created with the same estimated time, and behave like FIFO
// Right behavior: threads executed in order(either increasing or decreasing depends on implementation)

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
  
  // create threads in increasing order
  for (int i = 0; i < THREAD_NUMBER; i++)
  {
    tids[i] = thread_create(order_test, i, 0);
  }

  // threads should be executed in order(either increasing or decreasing depends on implementation)
  for (int i = 0; i < THREAD_NUMBER; i ++)
  {
    if (thread_join(tids[i]) == FAIL)
      exit(EXIT_FAILURE);
  }

  if (thread_libterminate() == FAIL)
    exit(EXIT_FAILURE);

  exit(EXIT_SUCCESS);
}