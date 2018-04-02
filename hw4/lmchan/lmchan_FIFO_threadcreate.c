#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "userthread.h"

#define THREAD_NUM	50

void thread(void *arg) {
  printf("%s\n", arg);
}

void main() {
  printf("---------\n");
  printf("A FIFO test \n");
  printf("Should print -thread created!- %i times on success.\n", THREAD_NUM);
  printf("The %i threads should be scheduled in-order, sicne it is a FIFO scheduler\n", THREAD_NUM);
  printf("---------\n");


  if (thread_libinit(FIFO) == -1) {
    exit(EXIT_FAILURE);
  }

  int tids[THREAD_NUM];
  char *str = "thread created!";

  for(int i = 0; i < THREAD_NUM; i++) {
  	tids[i] = thread_create(thread, str, 0);
  }


  for(int i = 0; i < THREAD_NUM; i++) {
  	if (thread_join(tids[i]) < 0) {
      exit(EXIT_FAILURE);
    }
  }

  if (thread_libterminate() == -1) {
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
