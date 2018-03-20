#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

void foo_yield(void* args) {
  for (int i = 0; i < 100; i ++)
    thread_yield();
}

/**
 * A simple test for PRIORITY
 * Expected Log: thread 1 to thread 3 end in order.
 */
int main(void) {
  if (thread_libinit(PRIORITY) == -1)
    exit(EXIT_FAILURE);

  int tid1 = thread_create(foo_yield, NULL, -1);
  int tid2 = thread_create(foo_yield, NULL, 0);
  int tid3 = thread_create(foo_yield, NULL, 0);
  int tid4 = thread_create(foo_yield, NULL, -1);
  int tid5 = thread_create(foo_yield, NULL, 0);
  int tid6 = thread_create(foo_yield, NULL, 0);

  printf("Testing PRIORITY with multiple yield\n");
  printf("On success, thread 1 and thread 4 should end ahead of all other threads\n");

  int n  = 6;
  int tids[] = { tid1, tid2, tid3 , tid4, tid5, tid6};

  for (int i = 0; i < n; i++)  {
    if (tids[i] == -1)
      exit(EXIT_FAILURE);
  }

  for (int i = 0; i < n; i++)  {
    if (thread_join(tids[i]) == -1) {
      exit(EXIT_FAILURE);
    }
  }
  
  if (thread_libterminate() == -1)
    exit(EXIT_FAILURE);

  printf(" Exit success\n");
  exit(EXIT_SUCCESS);
}
