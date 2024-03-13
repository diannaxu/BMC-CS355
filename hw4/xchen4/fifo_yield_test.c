// Author: Paprika Chen
// Test if the context of threads can be recorded after they call yield()
// Right behavior: 
//  ThreadA is going to yield.
//  Count is 6.
//  ThreadA executes second time.
//  Count is 12.

#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

#define FAIL -1
#define Anum 2
#define Bnum 3

int count = 1;

void yieldA_test(void *arg) {
  int index = *(int *)arg;
  count = index * count;
  printf("ThreadA is going to yield.\n");
  thread_yield();
  printf("ThreadA executes second time.\n");
  count = index * count;
  free(arg); // Free the dynamically allocated memory
}

void yieldB_test(void *arg) {
  int index = *(int *)arg;
  count = index * count;
  printf("Count is %d.\n", count);
  free(arg); // Free the dynamically allocated memory
}

int main() {
  if (thread_libinit(FIFO) == FAIL) {
    exit(EXIT_FAILURE);
  }

  int *argA = malloc(sizeof(int));
  int *argB = malloc(sizeof(int));
  if (!argA || !argB) {
    perror("Failed to allocate memory");
    if (argA) free(argA);
    if (argB) free(argB);
    exit(EXIT_FAILURE);
  }
  *argA = Anum;
  *argB = Bnum;

  int tidA = thread_create(yieldA_test, argA, 0);
  int tidB = thread_create(yieldB_test, argB, 0);
  
  printf("No threads should start executing before this.\n");

  if (thread_join(tidA) == FAIL) {
    exit(EXIT_FAILURE);
  }

  if (thread_join(tidB) == FAIL) {
    exit(EXIT_FAILURE);
  }

  printf("Ready to join the last thread, threads should be printed in increasing order.\n");
  printf("Final Count is %d.\n", count);

  exit(EXIT_SUCCESS);
}
