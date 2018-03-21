#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

#define THREADS_NUM   10

void hello_n1(void *arg) {
  poll(NULL, 0, 200);
  printf("%s -1\n", arg);
}

void hello_0(void *arg) {
  poll(NULL, 0, 200);
  printf("%s 0\n", arg);
}

void hello_1(void *arg) {
  poll(NULL, 0, 200);
  printf("%s 1\n", arg);
}

int main(void) {
  if (thread_libinit(PRIORITY) == -1) exit(EXIT_FAILURE);

  char *hello_str = "Hello, world!";
  int i;
  int tid_n1[THREADS_NUM];
  int tid_0[THREADS_NUM];
  int tid_1[THREADS_NUM];

  for(i = 0; i < THREADS_NUM; i++) {
    tid_n1[i] = thread_create(hello_n1, hello_str, -1);
    tid_0[i] = thread_create(hello_0, hello_str, 0);
    tid_1[i] = thread_create(hello_1, hello_str, 1);
  }

  printf("Test case for PRIORITY given %i threads per priority.\n", THREADS_NUM);
  printf("Print \"Hello, world! <priority>\" for %i times per priority on success.\n", THREADS_NUM);

  for(i = 0; i < THREADS_NUM; i++) {
    if (thread_join(tid_n1[i]) < 0) exit(EXIT_FAILURE);
    if (thread_join(tid_0[i]) < 0) exit(EXIT_FAILURE);
    if (thread_join(tid_1[i]) < 0) exit(EXIT_FAILURE);
  }

  if (thread_libterminate() == -1) exit(EXIT_FAILURE);

  exit(EXIT_SUCCESS);
}