#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

#define THREADS_NUM   10
#define TEST_PRIORITY 1

void hello(void *arg) {
  printf("%s\n", arg);
}

int main(void) {
  if (thread_libinit(PRIORITY) == -1) exit(EXIT_FAILURE);

  int tids[THREADS_NUM];
  int i;
  char *hello_str = "Hello, world!";

  for(i = 0; i < THREADS_NUM; i++) {
    tids[i] = thread_create(hello, hello_str, TEST_PRIORITY);
  }

  printf("Test case for PRIORITY. All %i threads are given the same priority.\n", THREADS_NUM);
  printf("Print \"Hello, world!\" for %i times on success.\n", THREADS_NUM);

  for(i = 0; i < THREADS_NUM; i++) {
    if (thread_join(tids[i]) < 0) exit(EXIT_FAILURE);
  }

  if (thread_libterminate() == -1) exit(EXIT_FAILURE);

  exit(EXIT_SUCCESS);
}