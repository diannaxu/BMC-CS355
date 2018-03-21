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

  printf("Test case for FIFO. Attempt to join an non-existing thread.\n");
  printf("Print \"Failed to join thread.\" on success.\n");

  if (thread_join(-1) < 0) {
  	printf("Failed to join thread.\n");
  	exit(EXIT_FAILURE);
  }

  if (thread_libterminate() == -1) exit(EXIT_FAILURE);

  exit(EXIT_SUCCESS);
}