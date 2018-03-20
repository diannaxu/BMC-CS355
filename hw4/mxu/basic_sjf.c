#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"


void test(void* trash) {
  printf("hello, world\n");
}
/*
  a very simple basic sjf test.
  See whether sjf's priority queue works as expected.
*/

int main(int args, char** argv) {
  if(thread_libinit(SJF) == 0)
    printf("Ya ho!\n");
  else
    printf("Sad.. I fail\n");
  
  printf("thread 1 should ends more early than thread 2."); 
  int tid1 =  thread_create(test,NULL,0);
  int tid2 =  thread_create(test,NULL,0);
  if(thread_join(tid1) < 0)
    exit(EXIT_FAILURE);
  if(thread_libterminate() == 0)
    printf("lib term Ya ho!\n");
  else
    printf("Sad.. I fail to term\n");
  return 0;
}