// Author: Paprika Chen
// Test if an invalid tid is entered when call join(), also test memory clean up
// Right behavior: -1 should be printed, no thread should execute

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

  int status = thread_join(100);
  if (status == FAIL) {
    printf("the status of join is %d\n", status);
    exit(EXIT_FAILURE);
  }

  if (thread_libterminate() == FAIL)
    exit(EXIT_FAILURE);

  exit(EXIT_SUCCESS);
}