#include <stdio.h>
#include <stdlib.h>
#include <poll.h>
#include "userthread.h"

int idx = 0;
int created_tids[3] = { -1, -1, -1 };

void foo(void *) {}
void foo_create(void *) {
  created_tids[idx] = thread_create(foo, NULL, 1);
  thread_join(created_tids[idx++]);
}

int main(void) {
  if (thread_libinit(FIFO) == -1)
    exit(EXIT_FAILURE);

  int tid1 = thread_create(foo_create, NULL, 1);
  int tid2 = thread_create(foo_create, NULL, 1);
  int tid3 = thread_create(foo_create, NULL, 1);

  int n = 3;
  int tids[] = { tid1, tid2, tid3 };

  for (int i = 0; i < n; i++)  {
    if (tids[i] == -1)
      exit(EXIT_FAILURE);
  }

  for (int i = 0; i < n; i++)  {
    if (thread_join(tids[i]) == -1)
      exit(EXIT_FAILURE);
  }

  for (int i = 0; i < 3; i++)  {
    if (created_tids[i] == -1)
      exit(EXIT_FAILURE);
  }

  printf(" * Testing thread_create within thread routines\n");
  printf(" * Threads should end in this order ");
  printf(" %d -> %d -> %d", created_tids[0], created_tids[1], created_tids[2]);
  printf(" -> %d -> %d -> %d \n", tid1, tid2, tid3);

  if (thread_libterminate() == -1)
    exit(EXIT_FAILURE);

  exit(EXIT_SUCCESS);
}
