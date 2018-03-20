#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "userthread.h"

#define N 3
void high(void *arg) {
  for(int i = 0; i < 100; i++){
    printf("running thread has priority -1\n");
    thread_yield();
  }

}
void middle(void* arg) {
  for(int i = 0; i < 100; i++){
    printf("running thread has priority 0\n");
    thread_yield();
  }

}
void low (void* arg) {
  for(int i = 0; i < 100; i++){
    printf("running thread has priority 1\n");
    thread_yield();
}
/**
 PRIORITY scheudling test 
 */
int main(void) {
  if (thread_libinit(PRIORITY) == -1)
    exit(EXIT_FAILURE);

  char arg[] = "Yay!";

  int tid1 = thread_create(high, arg, -1);
  int tid2 = thread_create(middle, arg, 0);
  int tid3 = thread_create(low, arg, 1);
  int tids[N] = {tid1,tid2,tid3};
  printf("Intensive priority scheudling tests\n");
  printf("The portion of high priority queue will be large\n");
  printf("the higher priority thread should show up more than low priority, but it is possible that low priority thread ends more early.\n");
  if (thread_join(tid1) < 0) 
      exit(EXIT_FAILURE);
  printf("we finish the join\n");
  if (thread_libterminate() == -1)
    exit(EXIT_FAILURE);

  exit(EXIT_SUCCESS);
}