/*
User level thread library
Test of SJF policy

Create 100 threads and poll them
Make sure there aren't any memory leaks or failures

Expected output:
1, 2, 3, 4, ... 99
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

#define THREADS 100

void f(void* args) {
  printf("%d\n", (uintptr_t) args);
  poll(NULL, 0, (uintptr_t) args);
}

int main() {
  int tids[THREADS];

  if (thread_libinit(SJF) != 0) {
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < THREADS; i++) {
    tids[i] = thread_create(&f, (void*) (uintptr_t)i, 0);
    if (tids[i] == -1) {
      exit(EXIT_FAILURE);
    }
  }

  for (int i = 0; i < THREADS; i++) {
    if (thread_join(tids[i]) == -1) {
      exit(EXIT_FAILURE);
    }
  }

  if (thread_libterminate() != 0) {
    exit(EXIT_FAILURE);
  } else {
    printf("terminated\n");
  }
  return EXIT_SUCCESS;
}
