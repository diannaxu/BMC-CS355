#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

void hello(void *arg) {
  printf("%s\n", arg);
}

int main(void) {
  if (thread_libinit(FIFO) == -1) exit(EXIT_FAILURE);

  char *hello_str = "Hello, world!";
  int tid_1 = thread_create(NULL, hello_str, 0);

  printf("Test case for FIFO given NULL as the funciton pointer.\n");
  printf("Print \"Fail to create thread.\" on success.\n");

  if(tid_1 == -1) {
  	printf("Fail to create thread.\n");
  	exit(EXIT_FAILURE);
  }

  if (thread_join(tid_1) < 0) exit(EXIT_FAILURE);

  if (thread_libterminate() == -1) exit(EXIT_FAILURE);

  exit(EXIT_SUCCESS);
}