#include <stdio.h>
#include <stdlib.h>
#include <poll.h>
#include "userthread.h"

void foo1(void *) {
  for (int i = 0; i < 4; i++) {
    poll(NULL, 0, 1);
    thread_yield();
  }
}

void foo200(void *) {
  for (int i = 0; i < 4; i++) {
    poll(NULL, 0, 200);
    thread_yield();
  }
}

/**
 * A simple test for SJF
 */
int main(void) {
  if (thread_libinit(PRIORITY) == -1)
    exit(EXIT_FAILURE);

  int tid1 = thread_create(foo1, NULL, 1);
  int tid2 = thread_create(foo200, NULL, 1);
  int tid3 = thread_create(foo1, NULL, 1);
  int tid4 = thread_create(foo200, NULL, 1);
  int tid5 = thread_create(foo1, NULL, 1);
  int tid6 = thread_create(foo200, NULL, 1);

  printf(" * A simple test for SJF scheduling\n");
  printf(" Assumptions\n");
  printf("(1) the default runtime value is less than 200 msec (real time rather than cputime).\n");
  printf(" * The threads with tid %d, %d and %d should end earlier than the threads with tid %d, %d, %d\n",
          tid1, tid3, tid5, tid2, tid4, tid6);

  int n  = 6;
  int tids[] = { tid1, tid2, tid3, tid4, tid5, tid6 };

  for (int i = 0; i < n; i++)  {
    if (tids[i] == -1)
      exit(EXIT_FAILURE);
  }

  for (int i = 0; i < n; i++)  {
    if (thread_join(tids[i]) == -1)
      exit(EXIT_FAILURE);
  }

  if (thread_libterminate() == -1)
    exit(EXIT_FAILURE);

  exit(EXIT_SUCCESS);
}
