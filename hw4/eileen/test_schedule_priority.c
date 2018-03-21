#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <poll.h>
#include "userthread.h"

#define N 3

#define H -1
#define M 0
#define L 1

void foo(void* p) {
  for(int i = 0; i < 19; i++) {
    poll(NULL, 0, 100);
    printf("Thread with priority %d is running %d times\n", *(int*)p, i+1);
  }
}

int main(void) {
  printf("* Test for priority\n");
  printf("* When all three threads are not finished, threads with priority -1 should run 1.5 times more than threads with priority 0, which run 1.5 times more often than threads with priority 1\n");
  printf("* Check console output: when thread with priority -1 runs 9 times, thread with priority 0 should run 6 times, and priority 0 runs 4 times\n");

  if (thread_libinit(PRIORITY) == -1)
    exit(EXIT_FAILURE);

  int tids[N];
  memset(tids, -1, sizeof(tids));
  int h = H;
  int m = M;
  int l = L;
  
  tids[0] = thread_create(foo, &m, m);
  tids[1] = thread_create(foo, &h, h);
  tids[2] = thread_create(foo, &l, l);

  for (int i = 0; i < N; i++)  {
    if (tids[i] == -1)
      exit(EXIT_FAILURE);
  }

  for (int i = 0; i < N; i++)  {
    if (thread_join(tids[i]) == -1)
      exit(EXIT_FAILURE);
  }

  if (thread_libterminate() == -1)
    exit(EXIT_FAILURE);

  exit(EXIT_SUCCESS);
}
