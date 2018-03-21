#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

void hello(void *arg) {
  printf("%s\n", arg);
}

int main(void) {
  if (thread_libinit(FIFO) == -1) exit(EXIT_FAILURE);

  char *hello_str = "Hello, world!";
  int tid_1 = thread_create(hello, hello_str, 0);

  printf("Simplest test case for FIFO.\n");
  printf("Print \"Hello, world!\" on success.\n");

  if (thread_join(tid_1) < 0) exit(EXIT_FAILURE);

  if (thread_libterminate() == -1) exit(EXIT_FAILURE);

  exit(EXIT_SUCCESS);
}