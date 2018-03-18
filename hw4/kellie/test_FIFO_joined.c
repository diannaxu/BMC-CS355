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
  printf("\nfrom f1\n\n");
}
void f2() {
  printf("\nfrom f2\n\n");
}

int main() {
  int tid, tid2;

  thread_libinit(FIFO);

  // create threads with functions f1, f2
  tid = thread_create(f1, NULL, 0);
  tid2 = thread_create(f2, NULL, 0);

  // join f2 thread first so it finishes before f1
  thread_join(tid2);
  thread_join(tid);

  thread_libterminate();
  printf("terminated\n");
  return 0;
}
