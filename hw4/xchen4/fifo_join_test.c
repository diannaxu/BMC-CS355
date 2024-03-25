// Author: Paprika Chen
// Test if no thread starts before the first join()
// Right behavior: Only print "nothing should be printed except this", no memory leaks

#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

#define THREAD_NUMBER 10
#define FAIL -1

void order_test(void *arg) {
  int i = *(int *)arg;
  printf("Thread %d is executing\n", i);
  free(arg); // Don't forget to free the allocated memory
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

  printf("No threads should start executing before this.\n");

  printf("Ready to join the last thread, threads should be printed in increasing order\n");

  if (thread_join(tids[THREAD_NUMBER - 1]) == FAIL) {
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
