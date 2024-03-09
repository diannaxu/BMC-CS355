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
  count = index*count;
  printf("ThreadA is going to yield.\n");
  thread_yield();
  printf("ThreadA executes second time.\n");
  count = index*count;
}

void yieldB_test(void *arg) {
  int index = *(int *)arg;
  count = index*count;
  printf("Count is %d\n", count);
}

int main() {
  if (thread_libinit(FIFO) == FAIL)
    exit(EXIT_FAILURE);

  int tidA, tidB;
  
  tidA = thread_create(yieldA_test, Anum, 0);
  tidB = thread_create(yieldB_test, Bnum, 0);
  // create threads in increasing order


  printf("No threads should start executing before this.");

  printf("Ready to join the last thread, threads should be printed in increasing order");

  if (thread_join(tidA) == FAIL) {
    exit(EXIT_FAILURE);
  }

  if (thread_join(tidB) == FAIL) {
    exit(EXIT_FAILURE);
  }

  printf("Count is %d\n", count);

  exit(EXIT_SUCCESS);
}