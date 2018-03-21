#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

void hello(void *arg) {
  for(int i = 0; i < 15; i++) {
    poll(NULL, 0, 300);
  }
  printf("%s\n", arg);
}

int main(void) {
  if (thread_libinit(PRIORITY) == -1) exit(EXIT_FAILURE);

  char *hello_str = "Hello, world!";
  int tid_1 = thread_create(hello, hello_str, -1);

  printf("Test case for PRIORITY. The thread will be scheduled for 15 times.\n");
  printf("Print \"Hello, world!\" on success.\n");

  if (thread_join(tid_1) < 0) exit(EXIT_FAILURE);

  if (thread_libterminate() == -1) exit(EXIT_FAILURE);

  exit(EXIT_SUCCESS);
}