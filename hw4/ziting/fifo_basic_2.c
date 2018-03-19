#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

#define THREAD_NUM	10

void hello(void *arg) {
  printf("%s\n", arg);
}

int main(void) {
  if (thread_libinit(FIFO) == -1) exit(EXIT_FAILURE);

  int tids[THREAD_NUM];
  int i;
  char *hello_str = "Hello, world!";

  for(i = 0; i < THREAD_NUM; i++) {
  	tids[i] = thread_create(hello, hello_str, 0);
  }

  printf("Another simplest test case for FIFO.\n");
  printf("Print \"Hello, world!\" for %i on success.\n", THREAD_NUM);
  printf("The %i threads should be scheduled in-order, i.e. the log should record increasing tids.\n", THREAD_NUM);

  for(i = 0; i < THREAD_NUM; i++) {
  	if (thread_join(tids[i]) < 0) exit(EXIT_FAILURE);
  }
  
  if (thread_libterminate() == -1) exit(EXIT_FAILURE);

  exit(EXIT_SUCCESS);
}