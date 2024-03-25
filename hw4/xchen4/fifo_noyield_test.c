// Author: Paprika Chen
// Test if threads execute in FIFO order on CREATE, instead of JOIN
// Right behavior: Threads should be printed in the order

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
  for (int i = 0; i < THREAD_NUMBER; i++) {
    int* arg = malloc(sizeof(int)); // Dynamically allocate memory for the argument
    if (arg == NULL) {
      perror("Failed to allocate memory for thread argument");
      exit(EXIT_FAILURE);
    }
    *arg = i;
    tids[i] = thread_create(order_test, arg, 0);
    if (tids[i] == FAIL) {
      free(arg); // Handle potential failure to create thread
    }
  }

  // join threads in decreasing order, but should still print in increasing order
  for (int i = THREAD_NUMBER - 1; i > -1; i--)
  {
    if (thread_join(tids[i]) == FAIL)
      exit(EXIT_FAILURE);
  }

  if (thread_libterminate() == FAIL)
    exit(EXIT_FAILURE);

  exit(EXIT_SUCCESS);
}