/*
Test for user thread library
Uses FIFO scheduling policy
Makes 1st thread wait for 2nd thread to finish
Expected output:
from f2
from f1
terminated
*/

#include <ucontext.h>
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "userthread.h"

void f1() {
  printf("from f1\n");
}
void f2() {
  printf("from f2\n");
}

int main() {
  int tid, tid2;

  if (thread_libinit(FIFO) != 0) {
    exit(EXIT_FAILURE);
  }

  // create threads with functions f1, f2
  tid = thread_create(f1, NULL, 0);
  tid2 = thread_create(f2, NULL, 0);

  // join f2 thread first so it finishes before f1
  if (thread_join(tid2) != 0) {
    printf("thread_join failure");
    exit(EXIT_FAILURE);
  }
  if (thread_join(tid) != 0) {
    printf("%s\n", "thread join failure");
    exit(EXIT_FAILURE);
  }

  thread_libterminate();
  printf("terminated\n");
  return 0;
}
