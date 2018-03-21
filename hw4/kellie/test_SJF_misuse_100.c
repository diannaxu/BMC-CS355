/*
User level thread library
Test of SJF policy

misuse case - we hope to catch it and not have undefined behavior
now with 100 threads!
calling thread_join before creating it should cause an error

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
  printf("thread running...\n");
}

int main() {
  int tids[THREADS];

  if (thread_libinit(SJF) != 0) {
    exit(EXIT_FAILURE);
  }

  for (int i = 1; i < THREADS; i++) {
    if (thread_join(tids[i]) != 0) {
      printf("thread_join failure\n");
      exit(EXIT_FAILURE);
    }
  }

  for (int i = 1; i < THREADS; i++) {
    tids[i] = thread_create(&f, (void*) (uintptr_t)i, 0);
    if (tids[i] != 0) {
      printf("thread_create failure\n");
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
