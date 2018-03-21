#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

int tid_1;

void hello(void *arg) {
	thread_join(tid_1);
  printf("%s\n", arg);
}

int main(void) {
  if (thread_libinit(FIFO) == -1) exit(EXIT_FAILURE);

  char *hello_str = "Hello, world!";
  tid_1 = thread_create(hello, hello_str, 0);

  printf("Test case for FIFO. Let one thread join itself.\n");
  printf("The program gets stuck and prints nothing on success.\n");

  if (thread_join(tid_1) < 0) exit(EXIT_FAILURE);

  if (thread_libterminate() == -1) exit(EXIT_FAILURE);

  exit(EXIT_SUCCESS);
}