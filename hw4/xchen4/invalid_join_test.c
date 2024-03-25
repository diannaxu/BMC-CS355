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
  free(arg); // Assuming dynamic allocation for args
}

int main() {
  if (thread_libinit(FIFO) == FAIL)
    exit(EXIT_FAILURE);

  int tids[THREAD_NUMBER];
  int *args[THREAD_NUMBER]; // For dynamic allocation
  
  // create threads in increasing order
  for (int i = 0; i < THREAD_NUMBER; i++) {
    args[i] = malloc(sizeof(int)); // Dynamically allocate argument
    if (args[i] == NULL) {
      perror("Failed to allocate memory for thread argument");
      // Cleanup previously allocated memory
      for (int j = 0; j < i; j++) {
        free(args[j]);
      }
      exit(EXIT_FAILURE);
    }
    *args[i] = i;
    tids[i] = thread_create(order_test, args[i], 0);
    if (tids[i] == FAIL) {
      // Handle the creation failure
      free(args[i]); // Cleanup the argument if thread creation fails
    }
  }

  // Attempt to join an invalid thread ID
  int status = thread_join(100);
  if (status == FAIL) {
    printf("The status of join is %d. No thread should execute.\n", status);
  } else {
    // If join did not fail as expected, perform cleanup
    for (int i = 0; i < THREAD_NUMBER; i++) {
      thread_join(tids[i]); // Assuming you want to wait for all threads in case of error
    }
  }

  // Cleanup dynamic memory for args not needed due to early termination logic
  for (int i = 0; i < THREAD_NUMBER; i++) {
    free(args[i]);
  }

  if (thread_libterminate() == FAIL)
    exit(EXIT_FAILURE);

  exit(EXIT_SUCCESS);
}
