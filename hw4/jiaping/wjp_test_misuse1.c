#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

void foo(void* args) {}
void bar(void* args) {}

int main(void) {
  printf("Testing simple misuses\n");
  printf("Shouldn't cause any crash on success\n");
  thread_libterminate();
  // the following three should return -1
  if (thread_create(foo, NULL, 0) != -1)
    exit(EXIT_FAILURE);
  if (thread_create(bar, NULL, 0) != -1)
    exit(EXIT_FAILURE);
  if (thread_join(1) != -1)
    exit(EXIT_FAILURE);

  if (thread_libinit(FIFO) == -1)
    exit(EXIT_FAILURE);

  int tid1 = thread_create(foo, NULL, 0);
  int tid2 = thread_create(foo, NULL, 0);
  int tid3 = thread_create(foo, NULL, 0);
  int tid4 = thread_create(foo, NULL, 0);
  int tid5 = thread_create(foo, NULL, 0);
  int tid6 = thread_create(foo, NULL, 0);

  int n  = 6;
  int tids[] = { tid1, tid2, tid3, tid4, tid5, tid6 };

  for (int i = 0; i < n; i++)  {
    if (tids[i] == -1)
      exit(EXIT_FAILURE);
  }

  if (thread_join(tid6) == -1)
    exit(EXIT_FAILURE);

  if (thread_libterminate() == -1)
    exit(EXIT_FAILURE);


  // more misuses...
  thread_libterminate();
  thread_join(123132);

  
  exit(EXIT_SUCCESS);
}
