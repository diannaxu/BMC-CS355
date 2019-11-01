// Author: Rachel(Ruochun) Wang

#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"

char *string = "Thread with priority ";

void foo1(void *arg) {
  poll(NULL, 0, 200);
  printf("%s -1 is greeting you.\n", (char*)arg);
}

void foo2(void *arg) {
  poll(NULL, 0, 200);
  printf("%s 0 is greeting you.\n", (char*)arg);
}

void foo3(void *arg) {
  poll(NULL, 0, 200);
  printf("%s 1 is greeting you.\n", (char*)arg);
}

int main(void) {
  if (thread_libinit(PRIORITY) == -1){
    exit(EXIT_FAILURE);
  }

  printf("Should be greeted by all three thread with different priorities.\n");
  int tid_1 = thread_create(foo1, string, -1);
  int tid_2 = thread_create(foo2, string, 0);
  int tid_3 = thread_create(foo3, string, 1);



  if (thread_join(tid_1) < 0) exit(EXIT_FAILURE);
  if (thread_join(tid_2) < 0) exit(EXIT_FAILURE);
  if (thread_join(tid_3) < 0) exit(EXIT_FAILURE);

  if (thread_libterminate() == -1) exit(EXIT_FAILURE);

  exit(EXIT_SUCCESS);
}
