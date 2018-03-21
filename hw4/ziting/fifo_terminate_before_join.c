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

  printf("Test case for FIFO. Libterminate before join.\n");
  printf("Should not crash or generate memory leaks.\n");

  if (thread_libterminate() == -1) exit(EXIT_FAILURE);

  exit(EXIT_SUCCESS);
}