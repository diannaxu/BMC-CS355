// Author: Paprika Chen
// Test if an invalid priority number is entered when create().
// Right behavior: "Invalid priority number!"

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
  if (thread_libinit(PRIORITY) == FAIL)
    exit(EXIT_FAILURE);

  int tid;

  tid = thread_create(order_test, 1, -5);
  if (tid < 0) {
    printf("Invalid priority number!\n");
    thread_libterminate();
    exit(EXIT_FAILURE);
  }
  
  if (thread_join(tid) == FAIL) {
    thread_libterminate();
    exit(EXIT_FAILURE);
  }

  if (thread_libterminate() == FAIL)
    exit(EXIT_FAILURE);

  exit(EXIT_SUCCESS);
}