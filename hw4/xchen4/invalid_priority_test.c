// Author: Paprika Chen
// Test if an invalid priority number is entered when create().
// Right behavior: "Invalid priority number!"

#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

#define FAIL -1

void order_test(void *arg) {
  int i = *(int *)arg;
  printf("Thread %d is executing\n", i);
  free(arg); // Free the allocated memory
}

int main() {
  if (thread_libinit(PRIORITY) == FAIL) {
    exit(EXIT_FAILURE);
  }

  int *arg = malloc(sizeof(int)); // Dynamically allocate memory for the argument
  if (arg == NULL) {
    perror("Failed to allocate memory");
    thread_libterminate();
    exit(EXIT_FAILURE);
  }
  *arg = 1;

  int tid = thread_create(order_test, arg, -5);
  if (tid < 0) {
    printf("Invalid priority number!\n");
    free(arg); 
    thread_libterminate();
    exit(EXIT_FAILURE);
  }
  
  if (thread_join(tid) == FAIL) {
    thread_libterminate();
    exit(EXIT_FAILURE);
  }

  if (thread_libterminate() == FAIL) {
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
