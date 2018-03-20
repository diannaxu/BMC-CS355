#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include "userthread.h"


void test_100(void* trash) {
  poll(NULL,0,100);
  printf("hello, world from 100 interval thread\n");
}

void test_200(void* nothing) {
    poll(NULL,0,200);
    printf("hello, world from 200 interval thread\n");
}

void test_300(void* nothing) {
    poll(NULL,0,300);
    printf("hello, world from 300 interval thread\n");
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
  
  printf("hello world from 100 -> hello world from 200 -> hello world from 300\n"); 
  int tid1 =  thread_create(test_100,NULL,0);
  int tid2 =  thread_create(test_200,NULL,0);
  int tid3 =  thread_create(test_300,NULL,0);
  if(thread_join(tid1) < 0)
    exit(EXIT_FAILURE);
  if(thread_libterminate() == 0)
    printf("lib term Ya ho!\n");
  else
    printf("Sad.. I fail to term\n");
  return 0;
}