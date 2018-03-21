/*
More robust test of thread_yield with 6 threads
using FIFO priority

Each thread is called with f() that prints its thread number
f() calls thread_yield

Expected output: (prints 1, 2, 3, 4, 5, 6, 1, 2, 3... 6 times)
1
2
3
4
5
6
.
.
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

void f(void *message) {
  for (int i = 0; i < 5; i++) {
    printf("%s\n", message);
    sleep(3);
    thread_yield();
  }
}


int main() {
  int tid, tid2, tid3, tid4, tid5, tid6;

  thread_libinit(FIFO);

  // create threads with functions f1, f2
  tid = thread_create(&f, "1", 0);
  tid2 = thread_create(&f, "2", 0);
  tid3 = thread_create(&f, "3", 0);
  tid4 = thread_create(&f, "4", 0);
  tid5 = thread_create(&f, "5", 0);
  tid6 = thread_create(&f, "6", 0);

  if (thread_join(tid) != 0) {
    printf("failuRE\n");
    exit(EXIT_FAILURE);
  }

  if (thread_libterminate() != 0) {
    exit(EXIT_FAILURE);
  } else {
    printf("terminated\n");
  }
  return 0;
}
