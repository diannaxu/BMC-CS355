#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "userthread.h"

#define N 7
void high(void *arg) {
  printf("the priority is -1\n");

}
void middle(void* arg) {
  printf("the priority is 0\n");

}
void low (void* arg) {
  printf("the priority is 1\n");

}
/**
 PRIORITY scheudling test 
 */
int main(void) {
  if (thread_libinit(PRIORITY) == -1)
    exit(EXIT_FAILURE);

  char arg[] = "Yay!";

  int tid1 = thread_create(low, arg, 1);
  int tid2 = thread_create(high, arg, -1);
  int tid3 = thread_create(high, arg, -1);
  int tid4 = thread_create(high, arg, -1);
  int tid5 = thread_create(middle, arg, 0);
  int tid6 = thread_create(middle, arg, 0);
  int tid7 = thread_create(high, arg, -1);
  int tids[N] = {tid1,tid2,tid3,tid4,tid5,tid6,tid7};
  printf("Basic PRIORITY test, testing only add and join.\n");
  printf("Should print the priority of itself if successful\n");
  printf("it is still non-preemptive, mainly for testing whether the scheduler pick correct order of thread.\n");
  printf("the higher priority thread should show up more than low priority, but it is possible that low priority thread ends more early.\n");
  for(int i = 0; i < 7; i++) {
    if (thread_join(tids[i]) < 0) 
      exit(EXIT_FAILURE);
  }
  printf("we finish the join\n");
  if (thread_libterminate() == -1)
    exit(EXIT_FAILURE);

  exit(EXIT_SUCCESS);
}