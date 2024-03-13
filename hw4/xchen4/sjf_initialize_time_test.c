// Author: Paprika Chen
// Test if before any join happens, all jobs should be created with the same estimated time, and behave like FIFO
// Right behavior: threads executed in order(either increasing or decreasing depends on implementation)

#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

#define THREAD_NUMBER 10
#define FAIL -1

void order_test(void *arg) {
  // Correctly cast the argument back to an integer
  int i = *((int*)arg);
  printf("Thread %d is executing\n", i);
}

int main() {
  if (thread_libinit(FIFO) == FAIL)
    exit(EXIT_FAILURE);

  int tids[THREAD_NUMBER];
  int args[THREAD_NUMBER]; // Create an array to store arguments to ensure they remain valid

  // Create threads in increasing order
  for (int i = 0; i < THREAD_NUMBER; i++) {
    args[i] = i; // Store the value of i in the args array
    // Pass the address of args[i] to ensure the correct value is used in the thread
    tids[i] = thread_create(order_test, &args[i], 0);
    if (tids[i] == FAIL) {
      // If thread creation fails, terminate the thread library and exit
      thread_libterminate();
      exit(EXIT_FAILURE);
    }
  }

  // Threads should be executed in order (either increasing or decreasing depends on implementation)
  for (int i = 0; i < THREAD_NUMBER; i++) {
    if (thread_join(tids[i]) == FAIL)
      exit(EXIT_FAILURE);
  }

  if (thread_libterminate() == FAIL)
    exit(EXIT_FAILURE);

  exit(EXIT_SUCCESS);
}
