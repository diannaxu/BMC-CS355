// Author: My Nguyen 
#include "userthread.h"
#include <stdio.h>
#include <stdlib.h>
#include <poll.h>
#include <stdint.h>

void f(void *arg) {
  for (int i = 0; i < 100; i++) {
    if (i == 99)
      printf("Thread %d finished\n", (uintptr_t)arg);
    thread_yield();
  }
}

int main(void) {
  if (thread_libinit(PRIORITY) == -1)
    exit(EXIT_FAILURE);
  
  printf("Test to demonstrate priority scheduling\n");
  printf("If success most likely should see thread 1 ending before thread 2 before thread 3, although there might be cases where this is not true because our priority ratio is based on random seed\n");

  int t1 = thread_create(f, (void*)(uintptr_t)1, -1);
  int t2 = thread_create(f, (void*)(uintptr_t)2, 0);
  int t3 = thread_create(f, (void*)(uintptr_t)3, 1);
  int tids[] = { t1, t2, t3 };
  
  for (int i = 0; i < 3; i++)  {
    if (tids[i] == -1)
      exit(EXIT_FAILURE);
  }

  for (int i = 0; i < 3; i++)  {
    if (thread_join(tids[i]) == -1)
	exit(EXIT_FAILURE);
  }
  
  if (thread_libterminate() == -1)
    exit(EXIT_FAILURE);
  
  exit(EXIT_SUCCESS);
} 
