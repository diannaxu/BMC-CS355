/*
Test of thread_yield
Uses two threads with functions f1, f2
thread with f1 runs first, then calls thread_yield
so thread 2 with f2 runs for its entirety
then thread 1 with f1 resumes and finishes
Expected output:
from f1
from f2
from f2
from f2
from f2
from f2
from f1
from f1
from f1
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
// #include "scheduler.h"

void f1() {
  for (int i = 0; i < 5; i++) {
    printf("\nfrom f1\n\n");
    sleep(1);
    thread_yield();
  }
}
void f2() {
  for (int i = 0; i < 5; i++) {
    printf("\nfrom f2\n\n");
    sleep(1);
  }
}

int main() {
  int tid, tid2;

  thread_libinit(FIFO);

  // create threads with functions f1, f2
  tid = thread_create(f1, NULL, 0);
  tid2 = thread_create(f2, NULL, 0);

  thread_join(tid);
  thread_join(tid2);

  thread_libterminate();
  printf("terminated\n");
  return 0;
}
