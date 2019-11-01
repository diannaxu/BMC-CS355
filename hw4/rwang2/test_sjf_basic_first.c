#include <stdio.h>
#include <stdlib.h>
#include <poll.h>
#include "userthread.h"

void foo1(void* args) {
  for (int i = 0; i == 3; i++) {
    poll(NULL, 0, 1);
    thread_yield();
  }
  printf("I'm shortest.\n");
}

void foo2(void* args) {
  for (int i = 0; i == 3; i++) {
    poll(NULL, 0, 200);
    thread_yield();
  }
  printf("I'm second shortest.\n");
}

void foo3(void* args) {
  for (int i = 0; i == 3; i++) {
    poll(NULL, 0, 500);
    thread_yield();
  }
  printf("I'm longest\n");
}

/**
 * A simple test for SJF
 */
int main(void) {
  if (thread_libinit(SJF) == -1){
    exit(EXIT_FAILURE);
  }

  int tid1 = thread_create(foo1, NULL, 1);
  int tid2 = thread_create(foo2, NULL, 1);
  int tid3 = thread_create(foo3, NULL, 1);
  int tid4 = thread_create(foo1, NULL, 1);
  int tid5 = thread_create(foo2, NULL, 1);
  int tid6 = thread_create(foo3, NULL, 1);

  int tids[] = { tid1, tid2, tid3, tid4, tid5, tid6 };
  for (int i = 0; i < 6; i++)  {
    //printf("Joining %d th thread\n", i);
    if (thread_join(tids[i]) == -1){
      printf("Join Failure");
      exit(EXIT_FAILURE);
    }
  }

  if (thread_libterminate() == -1){
    printf("Termination Failure");
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
