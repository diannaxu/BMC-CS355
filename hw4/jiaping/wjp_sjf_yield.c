#include <stdio.h>
#include <stdlib.h>
#include <poll.h>
#include "userthread.h"

void foo1(void* args) {
  for (int i = 0; i < 4; i++) {
    poll(NULL, 0, 1);
    thread_yield();
  }
  printf("I should end first\n");
}

void foo200(void* args) {
  for (int i = 0; i < 4; i++) {
    poll(NULL, 0, 200);
    thread_yield();
  }
  printf("I should end second\n");
}

void foo500(void* args) {
  for (int i = 0; i < 4; i++) {
    poll(NULL, 0, 500);
    thread_yield();
  }
  printf("I should end third\n");
}

/**
 * A simple test for SJF
 */
int main(void) {
  if (thread_libinit(SJF) == -1)
    exit(EXIT_FAILURE);

  int tid1 = thread_create(foo1, NULL, 1);
  int tid2 = thread_create(foo200, NULL, 1);
  int tid3 = thread_create(foo500, NULL, 1);
  int tid4 = thread_create(foo1, NULL, 1);
  int tid5 = thread_create(foo200, NULL, 1);
  int tid6 = thread_create(foo500, NULL, 1);

  printf("%s\n", );

  int n  = 6;
  int tids[] = { tid1, tid2, tid3, tid4, tid5, tid6 };

  for (int i = 0; i < n; i++)  {
    if (tids[i] == -1)
      exit(EXIT_FAILURE);
  }

  for (int i = 0; i < n; i++)  {
    if (thread_join(tids[i]) == -1){
      printf("You died from line 56 ");
      exit(EXIT_FAILURE);
    }
  }

  if (thread_libterminate() == -1){
    printf("You died from line 62 ");
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
