/*
User level thread library
Test SJF policy
Calls three threads, each is polled at 100, 200, 300 time intervals
The 100 thread should complete first
Expected output:
100
200
300
100
100
100
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
#include <poll.h>
#include <stdint.h>

#include "userthread.h"
#include "scheduler.h"

void f(void* args) {
  for (int i = 0; i < 10; i++) {
    printf("%d\n", (uintptr_t) args);
    poll(NULL, 0, (uintptr_t) args);
    thread_yield();
  }
}

int main() {
  int tid, tid2, tid3;

  if (thread_libinit(SJF) != 0) {
    exit(EXIT_FAILURE);
  }

  // create threads with function f, number passed into poll()
  tid = thread_create(&f, (void*)100, 0);
  tid2 = thread_create(&f, (void*)200, 0);
  tid3 = thread_create(&f, (void*)300, 0);

  if(thread_join(tid) < 0 || thread_join(tid2) < 0 || thread_join(tid3) < 0) {
    exit(EXIT_FAILURE);
  }

  if (thread_libterminate() != 0) {
    exit(EXIT_FAILURE);
  } else {
    printf("terminated\n");
  }
  return 0;
}
